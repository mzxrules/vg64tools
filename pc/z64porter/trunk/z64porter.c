#include "z64porter.h"
#include "convert.h"
#include "yaz0.h"

#define count(x)	sizeof(x)/sizeof(x[0])

typedef struct {
    size_t size, comp_size;
    unsigned char * data;
} MapPointer;

typedef struct {
	int start;
	size_t size;
} free_space_desc;

/* Global variables */
int verbose = 1;
int warnflag = 0, warnignore = 0;
int scene_to=0, scene_from=0;
int music=0, destgame=GameOOT;
int safe=0, compress=0;
int freed_file_count = 0;
int map_count=0;
float rotval;
size_t scene_size;
unsigned char * map_list=0;
unsigned char * scene_orig=NULL, * scene_fixed=NULL;
int * freed_files = NULL;
int * voffsets = NULL;
MapPointer * MapList = NULL;
N64Rom *N64_TO=NULL, *N64_FROM=NULL;
Z64 *Z64_TO=NULL, *Z64_FROM=NULL;
free_space_desc ins[2] = {{0,0},{0,0}};

/* cleanup function */
void
cleanup()
{
    if(N64_TO != NULL)
        n64rom_close(N64_TO);
    if(N64_FROM != NULL)
        n64rom_close(N64_FROM);
    if(Z64_TO != NULL)
        z64_close(Z64_TO);
    if(Z64_FROM != NULL)
        z64_close(Z64_FROM);
    if(MapList != NULL)
    {
        int i;
        for(i=0;i<count(MapList);i++)
        {
            if(MapList[i].data != NULL)
                free(MapList[i].data);
        }
        free(MapList);
    }
    if(scene_orig != NULL)
        free(scene_orig);
    if(scene_fixed !=NULL)
        free(scene_fixed);
    if(freed_files != NULL)
        free(freed_files);
    if(voffsets != NULL)
        free(voffsets);
}

/* Parse arguments */
void
parse_args(int argc, char ** argv)
{
    int argn=5;
    
    if(argc < 5)
    {
        /* maybe asking for -h, --help, --about */
        if(argc == 2)
        {
            argn = 1;
            goto optionscan;
        }
        /* nope, just an idiot */
        error("not enough arguments");
    }
    
    /* ROM to and ROM from the same ? */
    if(!strcmp(argv[1], argv[2]))
        error("destination and source ROMs are the same");
    
    /* ROM to */
    if((N64_TO = n64rom_load(argv[1])) == NULL)
        error("%s", n64rom_error());
    
    /* ROM from */
    if((N64_FROM = n64rom_load(argv[2])) == NULL)
        error("%s", n64rom_error());
    
    /* Scene to and from */
    scene_to = strtoint(argv[3]);
    scene_from = strtoint(argv[4]);
    
  optionscan:
    /* Parse extra arguments */
    for(;argn<argc;argn++)
    {
        if(argv[argn][0] == '-')
        {
            if(strlen(argv[argn]) == 2)
            {
                switch(argv[argn][1])
                {
                case 'v':
                    if(++argn < argc)
                    {
                        verbose = strtoint(argv[argn]);
                    }
                    else
                        error("option for -v is missing.");
                    break;
                case 'm':
                    if(++argn < argc)
                        music = strtoint(argv[argn]);
                    else
                        error("option for -m is missing.");
                    break;
                case 'h':
                    goto help;
                case 's':
                    safe = 1;
                    break;
                case 'c':
                    compress = 1;
                    break;
                default:
                    goto unhandled;
                }
            }
            else if(argv[argn][1] == '-')
            {
                if(!strcmp(argv[argn], "--help"))
                {
              help:
                    fprintf(stdout, "Usage: %s [ROM to] [ROM from] [scene to] [scene from] [options]\n", argv[0]);
                    fprintf(stdout, "Options:\n");
                    fprintf(stdout, " -v level\t\tSet verbosity (0-3)\n");
                    fprintf(stdout, " -m music\t\tSet music value for destination scene\n");
                    fprintf(stdout, " --force-warnings\tIf any warnings, ignore and do port anyways\n");
                    fprintf(stdout, " -s, --safe\t\tIncrease chances of success\n");
                    fprintf(stdout, " -c, --compress\t\tCompress scene and map(s)\n");
                    fprintf(stdout, " -h, --help\t\tThis message\n");
                    fprintf(stdout, " --about\t\tAbout\n");
                    exit(EXIT_SUCCESS);
                }
                else if(!strcmp(argv[argn], "--about"))
                {
                    fprintf(stdout, "about: todo\n");
                    exit(EXIT_SUCCESS);
                }
                else if(!strcmp(argv[argn], "--safe"))
                    safe = 1;
                else if(!strcmp(argv[argn], "--compress"))
                    compress = 1;
                else if(!strcmp(argv[argn], "--force-warnings"))
                    warnignore = 4;
                else
              unhandled:
                    error("unhandled option `%s'", argv[argn]);
            }
            else
                goto unhandled;
        }
        else
            goto unhandled;
    }
}

void
check_setup()
{
    int checkval;
    
    /* bounds check verbosity - not specifically required, just to be safe */
    if(verbose < 0)
        verbose = 0;
    if(verbose > 3)
        verbose = 3;
    
    /* Set up Z64 ROMs */
    if((Z64_TO = z64_open(N64_TO)) == NULL)
        error("cannot open %s as a Zelda ROM", N64_TO->filename);
    if((Z64_FROM = z64_open(N64_FROM)) == NULL)
        error("cannot open %s as a Zelda ROM", N64_FROM->filename);
    
    /* set destination game */
    destgame = Z64_TO->st->game;
    rotval = (destgame = GameOOT) ? 1.42222 : 0.703125;
    
    /* Bounds check music value */
    if(music < 0)
    {
        msg(warnignore, "Warning: Music value too low; defaulting to 0");
        warnflag = 1;
        music = 0;
    }
    checkval = (destgame == GameOOT) ? MAX_MUSIC_OOT : MAX_MUSIC_MM;
    if(music > checkval)
    {
        msg(warnignore, "Warning: Music value too high; defaulting to %i", checkval);
        warnflag = 1;
        music = checkval;
    }
    
    /* Bounds check scene values */
    if(scene_to < 0)
    {
        msg(warnignore, "Warning: Scene (to) value too low; defaulting to 0");
        warnflag = 1;
        scene_to = 0;
    }
    if(scene_from < 0)
    {
        msg(warnignore, "Warning: Scene (from) value too low; defaulting to 0");
        warnflag = 1;
        scene_from = 0;
    }
    if(scene_to > Z_ST_COUNT( Z64_TO ))
    {
        msg(warnignore, "Warning: Scene (to) value too high; defaulting to %i", Z_ST_COUNT( Z64_TO ));
        warnflag = 1;
        scene_to = Z_ST_COUNT( Z64_TO );
    }    
    if(scene_from > Z_ST_COUNT( Z64_FROM ))
    {
        msg(warnignore, "Warning: Scene (from) value too high; defaulting to %i", Z_ST_COUNT( Z64_FROM ));
        warnflag = 1;
        scene_from = Z_ST_COUNT( Z64_FROM );
    }
    /* okay, everything is sane */
}

void
fix_objects(unsigned char * list, int count)
{
    int i, limit;
    unsigned short *obj_lookup, obj_curr;
    
    /* Get max object number and object lookup table */
    limit = (destgame == GameOOT) ? OOT_OBJ_MAX : MM_OBJ_MAX;
    obj_lookup = (destgame == GameOOT) ? obj_lookup_oot : obj_lookup_mm;
    
    for(i=0;i<count;i++,list+=2)
    {
        obj_curr = U16(list);
        if(obj_curr <= limit && (obj_curr = obj_lookup[obj_curr]))
            setU16(list, obj_curr)/* no semicolon, it screws up the if-else when the macro expands */
        else
            setU16(list, 0);
    }
}

void
fix_actors(unsigned char * list, int count)
{
    int i, limit;
    unsigned short *act_lookup, act_curr, act_default;
    
    /* Get max actor number */
    if(!(Z64_TO->status&Z64_LOADED_AT)) /* Actor table may not be loaded for some odd reason */
        limit = (destgame == GameOOT) ? MM_ACT_MAX : OOT_ACT_MAX;
    else
        limit = Z_AT_COUNT( Z64_TO );
    
    /* Get default actor and lookup table */
    act_default = (destgame == GameOOT) ? OOT_ACT_FLAME : MM_ACT_FLAME;
    act_lookup = (destgame == GameOOT) ? act_lookup_oot : act_lookup_mm;
    
    for(i=0;i<count;i++,list+=16)
    {
        act_curr = U16(list) & 0xFFF;
        if(act_curr <= limit && (act_curr = act_lookup[act_curr]))
            setU16(list, act_curr)
        else
            setU16(list, act_default);
        /* fix rotation */
        setU16(list+8, (short)(U16(list+8) * rotval));
        setU16(list+10, (short)(U16(list+10) * rotval));
        setU16(list+12, (short)(U16(list+12) * rotval));
        /* variable */
        setU16(list+14, 0);
    }

}

void
fix_link_actors(unsigned char * list, int count)
{
    int i;
    
    for(i=0;i<count;i++,list+=16)
    {
        /* fix rotation */
        setU16(list+8, (short)(U16(list+8) * rotval));
        setU16(list+10, (short)(U16(list+10) * rotval));
        setU16(list+12, (short)(U16(list+12) * rotval));
        /* variable */
        setU16(list+14, 0x0FFF);
    }

}

void
fix_doors(unsigned char * list, int count)
{
    int i, limit;
    unsigned short *act_lookup, act_curr, act_default;
    
    /* Get max actor number */
    if(!(Z64_TO->status&Z64_LOADED_AT)) /* Actor table may not be loaded for some odd reason */
        limit = (destgame == GameOOT) ? MM_ACT_MAX : OOT_ACT_MAX;
    else
        limit = Z_AT_COUNT( Z64_TO );
    
    /* Get default actor and lookup table */
    act_default = (destgame == GameOOT) ? OOT_ACT_DOOR : MM_ACT_DOOR;
    act_lookup = (destgame == GameOOT) ? act_lookup_oot : act_lookup_mm;
    
    for(i=0;i<count;i++,list+=16)
    {
        act_curr = U16(list+4) & 0xFFF;
        if(act_curr <= limit && (act_curr = act_lookup[act_curr]))
            setU16(list+4, act_curr)
        else
            setU16(list, act_default);
        /* fix rotation */
        setU16(list+12, (short)(U16(list+12) * rotval));
        /* variable */
        setU16(list+14, 0);
    }

}

void
set_maps()
{
    unsigned char *list = map_list, *data;
    int i, fileno;
    if(MapList != NULL)
        return;
    MapList = calloc(map_count, sizeof(MapList[0]));
    memset(MapList, 0, sizeof(MapList));
    msg(2, "%i maps found, setting up...", map_count);
    for(i=0;i<map_count;i++,list+=8)
    {
        fileno = z64fs_search_offset(Z64_FROM, U32(list));
        if(fileno == -1)
            error("cannot find map with offsets %08X-%08X in file list", U32(list), U32(list+4));
        dump(i, "%i");
        dump(fileno, "%i");
        MapList[i].size = ZFileVirtSize(Z64_FROM->fs, fileno);
        dump(MapList[i].size, "%#x");
        data = malloc(MapList[i].size);
        check_mem(data);
        z64fs_read_file(Z64_FROM, fileno, data);
        MapList[i].data = data;
        MapList[i].comp_size = MapList[i].size;
    }
    msg(2, "%i maps successfully set up", i);
}

unsigned char *
fix_area(unsigned char * src, size_t siz, char bank)
{
    int pos, inheader = 1;
    unsigned char * dest = malloc(siz);
    check_mem(dest);
    memcpy(dest, src, siz);
    msg(2, "Interpreting header...");
    for(pos=0; pos<siz; pos+=8)
    {
        if(inheader)
        {
            switch(dest[pos])
            {
            case ZLH_ENTRANCES:
                msg(3, " - Fixing link instances");
                fix_link_actors(dest + U24(dest + pos + 5), dest[pos+1]);
                break;
            case ZLH_ACTORS:
                msg(3, " - Fixing actors")
                if(dest[pos+4] == bank && !safe)
                    fix_actors(dest + U24(dest + pos + 5), dest[pos+1]);
                else
                    dest[pos+1] = 0;
                break;
            case ZLH_OBJECTS:
                msg(3, " - Fixing objects");
                if(dest[pos+4] == bank && !safe)
                    fix_objects(dest + U24(dest + pos + 5), dest[pos+1]);
                else
                    dest[pos+1] = 0;
                break;
            case ZLH_END:
                msg(3, " - End of header");
                inheader = 0;
                break;
            case ZLH_COLLISION: /* Kill special camera angles */
                msg(3, " - Killing special camera angles");
                setU32(dest + U24(dest + pos + 5) + 0x20, 0x00000000);
                break;
            case ZLH_SKYCONTROL:
            case ZLH_ALT_HEADERS:
                setU32(dest, 0x01000000);
                setU32(dest+4, 0x00000000);
                break;
            case ZLH_MAPS:
                msg(3, " - Reading in map list");
                map_list = dest + U24(dest + pos + 5);
                map_count = dest[pos+1];
                set_maps();
                break;
            default:
                break;
            }
        }
        /* Kill display list jumps to undefined banks... */
        else if(dest[pos] == 0xDE && !U24(dest+pos+1) && dest[pos+4] != bank)
        {
            msg(3, "Killing display list jump to %08X", U32(dest+pos+4));
            dest[pos] = 0;
        }
    }
    return dest;
}


void
get_uneeded_files()
{
    int map_count=0, i, pos;
    unsigned char *tmp_scene;
    size_t old_scene_size;
    
    /* Get old scene filenumber */
    freed_files = malloc(sizeof(int));
    check_mem(freed_files);
    freed_files[0] = z64fs_search_offset(Z64_TO, scene_to);
    if(freed_files[0] == -1)
        error("could not find scene to be overwritten in filesystem");
    msg(3, "old scene is file %i", freed_files[0]);
    freed_file_count = 1;
    
    /* read in old scene */
    old_scene_size = ZFileVirtSize(Z64_TO->fs, freed_files[0]);
    tmp_scene = malloc(old_scene_size);
    check_mem(tmp_scene);
    z64fs_read_file(Z64_TO, freed_files[0], tmp_scene);
    
    /* Get old maps */
    for(pos=0;pos<old_scene_size;pos+=8)
    {
        if(tmp_scene[pos] == ZLH_MAPS)
        {
            map_count = tmp_scene[pos+1];
            freed_files = realloc(freed_files, sizeof(int) * map_count);
            check_mem(freed_files);
            pos = U24(scene_fixed + pos + 5);
            for(i=1; i<=map_count; i++, pos+=8 )
            {
                freed_files[i] = z64fs_search_offset(Z64_TO, U32((char*)pos));
                if(freed_files[i] == -1) /* This will probably happen with cen's room 120 fix,
                                            or any similar hacks for that matter */
                {
                    free(tmp_scene);
                    error("could not find map %i of old scene in filesystem", i);
                }
                msg(3, "old map %i is file %i", i - 1, freed_files[i]);
                freed_file_count ++;
            }
            break;
        }
        else if(tmp_scene[pos] == ZLH_END)
            break;
    }
    
    free(tmp_scene);
    
    if(!map_count)
        error("no old maps found");
    
    msg(2, "found %i files that are not needed", freed_file_count);
}

int
calcsize(int scene_size)
{
    size_t siz = scene_size;
    int i;
    
    for(i=0;i<count(MapList);i++)
        siz+=MapList[i].comp_size;
    
    return siz;
}

void
calc_voffsets()
{
    int i;
    voffsets  = malloc(map_count + 2);
    check_mem(voffsets);
    /* First two are for the scene... */
    voffsets[0] = ZFileVirtEnd(Z64_TO->fs, z64fs_entries(Z64_TO->fs)-1);
    /* End of scene = start of map 0 */
    voffsets[1] = voffsets[0] + scene_size;
    /* Calculate map offsets */
    for(i=0;i<map_count;i++)
        voffsets[i+2] = voffsets[i+1] + MapList[i].size;
    
    /* Write virtual offsets */
    for(i=0;i<map_count;i++,map_list+=8)
    {
        setU32(map_list, voffsets[i+1]);
        setU32(map_list+4, voffsets[i+2]);
    }
}

void
compress_files()
{
    unsigned char * tmp;
    int i;
    msg(1, "Compressing maps and scene");
    for(i=0;i<map_count;i++)
    {
        tmp = encodeAll(MapList[i].data, MapList[i].size);
        free(MapList[i].data); /* free the uncompressed map */
        MapList[i].data = malloc(dstSize);
        check_mem(MapList[i].data);
        memcpy(MapList[i].data, tmp, dstSize);
        free(tmp);
        msg(2, "Compressed map %i to %#x bytes from %#x bytes", i, dstSize, MapList[i].size);
        MapList[i].comp_size = dstSize;
    }
    tmp = encodeAll(scene_fixed, scene_size);
    free(scene_fixed); /*free the uncompressed scene */
    scene_fixed = malloc(dstSize);
    check_mem(scene_fixed);
    memcpy(scene_fixed, tmp, dstSize);
    msg(2, "Compressed scene to %#x bytes from %#x bytes", dstSize, scene_size);
    scene_size = dstSize;
    free(tmp);
}

#define SCENEATFREE	1
#define MAPATFREE	2

/* Save a file - write virt and phys pointers, data */
void
write_file(Z64 * z64, int f, int vs, int ve, int ps, int pe, unsigned char * data, size_t siz)
{
    char * buff = malloc(16);
    check_mem(buff);
    setU32(buff+0x0, vs);
    setU32(buff+0x4, ve);
    setU32(buff+0x8, ps);
    setU32(buff+0xC, pe);
    /* write pointers */
    fseek(z64->handle, z64->fs->start + (f * 0x10), SEEK_SET);
    fwrite(buff, 1, 0x10, z64->handle);
    /* write data */
    fseek(z64->handle, ps, SEEK_SET);
    fwrite(data, 1, siz, z64->handle);
    free(buff);
}

/* Write scene pointers
Note: This does not save to ROM! */
void
write_scene(Z64 * z64, int s, int f)
{
    char * buff = (destgame == GameOOT) ? malloc(0x14) : malloc(0x10);
    check_mem(buff);
    memset(buff, 0, sizeof(buff));
    setU32(buff+0x0, ZFileVirtStart(z64->fs, f));
    setU32(buff+0x4, ZFileVirtEnd(z64->fs, f));
    memcpy(z64->f_code_data + (s * sizeof(buff)), buff, sizeof(buff));
}

/* Save 'code' */
void
save_code(Z64 * z64)
{
    unsigned char * tmp;
    size_t siz;
    int fileno;
    /* Compress? */
    if(z64->f_code->end)
    {
        tmp = encodeAll(z64->f_code_data, z64->f_code->vend - z64->f_code->vstart);
        siz = dstSize;
        if(siz > z64->f_code->end - z64->f_code->start)
        {
        /* FFFFFFFFFFFUUUUU */
            free(tmp);
            error("code ended up compressing bigger than before, I don't know what to do")
        }
    }
    else
    {
        tmp = z64->f_code_data;
        siz = z64->f_code->vend - z64->f_code->vstart;
    }
    fileno = z64fs_search_offset(z64, z64->f_code->vstart);
    if(fileno == -1)
    {
        if(z64->f_code->end)
            free(tmp);
        error("cannot find code file number");
    }
    write_file(z64, fileno, z64->f_code->vstart, z64->f_code->vend, z64->f_code->start, z64->f_code->start + siz, tmp, siz);
    if(z64->f_code->end)
        free(tmp);
}

void
insert_port()
{
    int freed_start, freed_end, flags=0, maps_at_free=0, i;
    size_t freed_size, siz_calc;
    
    /* Get uneeded files */
    get_uneeded_files();
    if(freed_file_count < map_count+1)
        error("not enough files freed as needed");
    
    /* Get start, end, and size of area freed */
    freed_start = ZFileStart(Z64_TO->fs, freed_files[0]);
    freed_end = ZFileEnd(Z64_TO->fs, freed_files[freed_file_count-1]);
    freed_size = freed_end-freed_start;
    
    /* Calculate where everything is going */
    if(calcsize(scene_size) > freed_size)
    {
        if(scene_size > freed_size)
            siz_calc = 0;
        else
        {
            siz_calc = scene_size;
            flags |= SCENEATFREE;
        }
        for(i=0;i<map_count;i++)
        {
            siz_calc+=MapList[i].comp_size;
            if(siz_calc > freed_size)
            {
                maps_at_free = --i;
                break;
            }
        }
        if(i < 0 && !(flags & SCENEATFREE))
        {
            /* Shit, that freed space is useless */
            ins[0].start = ZFileEnd(Z64_TO->fs, z64fs_entries(Z64_TO->fs)-1);
            ins[0].size = Z64_TO->filesize - ins[0].start;
        }
        else
        {
            /* Fuck. The port is going to have to be done in two areas */
            ins[0].start = freed_start;
            ins[0].size = freed_size;
            ins[1].start = ZFileEnd(Z64_TO->fs, z64fs_entries(Z64_TO->fs)-1);
            ins[1].size = Z64_TO->filesize - ins[1].start;
            flags |= MAPATFREE;
        }
    }
    else
    {/* whoo, this is going to be easy */
        ins[0].start = freed_start;
        ins[0].size = freed_size;
    }
    
    /* Insert scene * / this is basically all that's left
    if(flags & SCENEATFREE)
    {
        write_file(Z64_TO, freed_files[0], voffsets[0], voffsets[1], ins[0].start, ins[0].start + scene_size, scene_fixed, scene_size);
        write_scene(Z64_TO, scene_to, freed_files[0]);
    }
    else if( flag & MAPATFREE)*/
        
}

void
do_port()
{
    int scene_fs_num, i;
    
    /* Check that the scene from exists (some MM scenes are NULL) */
    if(!z64st_getstart( Z64_FROM, scene_to ))
        error("Scene to is a null scene");
    
    msg(2, "Scene to: %08X - %08X", z64st_getstart( Z64_TO, scene_to ), z64st_getend( Z64_TO, scene_to ) );
    msg(2, "Scene from: %08X - %08X", z64st_getstart( Z64_FROM, scene_from ), z64st_getend( Z64_FROM, scene_from ) );
    
    /* Get scene file information */
    scene_fs_num = z64fs_search_offset(Z64_FROM, z64st_getstart(Z64_FROM, scene_from));
    if(scene_fs_num == -1)
        error("cannot find destination scene in filesystem");
    scene_size = ZFileVirtSize(Z64_FROM->fs, scene_fs_num);
    dump(scene_fs_num, "%i");
    dump(scene_size, "%i");
    
    /* Allocate memory for scene and read it */
    scene_orig = malloc(scene_size);
    check_mem(scene_orig);
    z64fs_read_file(Z64_FROM, scene_fs_num, scene_orig);
    
    /* MM <-> OOT */
    if(destgame != Z64_FROM->st->game)
    {
        /* fix scene */
        msg(2, "Fixing scene...");
        scene_fixed = fix_area(scene_orig, scene_size, 2);
        
        /* Check for the map list before continuing */
        if(MapList == NULL)
            error("no maps found");
        
        /* Fix maps */
        for(i=0;i<map_count;i++)
        {
            msg(2, "Fixing map %i...", i);
            MapList[i].data = fix_area(MapList[i].data, MapList[i].size, 3);
        }
    }
    
    /* MM -> MM or OOT -> OOT */
    else
    {
        int pos;
        scene_fixed = scene_orig;
        
        /* Get map list */
        for(pos=0;pos<scene_size;pos+=8)
        {
            if(scene_fixed[pos] == ZLH_MAPS)
            {
                map_list = scene_fixed + U24(scene_fixed + pos + 5);
                map_count = scene_fixed[pos+1];
                set_maps();
                break;
            }
            else if(scene_fixed[pos] == ZLH_END)
                break;
        }
        /* Check for the map list before continuing */
        if(MapList == NULL)
            error("no maps found");
    }
    
    /* Calculate virtual offsets */
    calc_voffsets();
    
    /* Compress? */
    if(compress)
        compress_files();
        
    insert_port();
}

int
main(int argc, char ** argv)
{
    /* Initialize variables */
    char warn_yesno[2];
    
    parse_args(argc, argv);
    check_setup();
    
    dump(verbose, "%i");
    dump(music, "%i");
    dump(warnflag, "%i");
    dump(scene_from, "%i");
    dump(scene_to, "%i");
    dump(N64_FROM->filename, "%s");
    dump(N64_TO->filename, "%s");
    
    if(warnflag && !warnignore)
    {
        printf("Continue despite warnings? (y/n): ");
        fgets(warn_yesno, sizeof(warn_yesno), stdin);
        if(tolower(warn_yesno[0]) == 'y')
            goto port;
        else
        {
            cleanup();
            return EXIT_FAILURE;
        }
    }
  port:
    msg(3, "Doing port...");
    do_port();
    
    cleanup();
    
    return EXIT_SUCCESS;
}
