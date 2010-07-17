#include "z64porter.h"

/* Global variables */
int verbose = 1;
int scene_to, scene_from;
N64Rom (*N64_TO), (*N64_FROM);
Z64 (*Z64_TO), (*Z64_FROM);
int music;

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
        z64_close(Z64_TO);
}

/* Parse arguments */
void
parse_args(int argc, char ** argv)
{
    int argn=5;
    
    if(argc < 5)
    {
        /* maybe asking for -h, --help, --about */
        if(argc > 1)
        {
            argn = 1;
            goto optionscan;
        }
        /* nope, just an idiot */
        error("not enough arguments");
    }
    
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
                default:
                    goto unhandled;
                }
            }
            else if(argv[argn][1] == '-')
            {
                if(!strcmp(argv[argn], "--help"))
                {
              help:
                    fprintf(stdout, "help: todo\n");
                    exit(EXIT_SUCCESS);
                }
                else if(!strcmp(argv[argn], "--about"))
                {
                    fprintf(stdout, "about: todo\n");
                    exit(EXIT_SUCCESS);
                }
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
    /* Set up Z64 ROMs */
    if((Z64_TO = z64_open(N64_TO)) == NULL)
        error("cannot open %s as a Zelda ROM", N64_TO->filename);
    if((Z64_FROM = z64_open(N64_FROM)) == NULL)
        error("cannot open %s as a Zelda ROM", N64_FROM->filename);
    
    /* bounds check verbosity - not specifically required, just to be safe */
    if(verbose < 0)
        verbose = 0;
    if(verbose > 3)
        verbose = 3;
    
    /* Bounds check music value */
    if(music < 0)
        music = 0;
    else if(Z64_TO->st->game == GameOOT && music > MUSIC_MAX_OOT)
        music = MUSIC_MAX_OOT;
    else if(Z64_TO->st->game == GameOOT && music > MUSIC_MAX_MM)
        music = MUSIC_MAX_MM;
    
    
    
}

int
main(int argc, char ** argv)
{
    /* Initialize variables */
    N64_TO = NULL, N64_FROM = NULL;
    Z64_TO = NULL, Z64_FROM = NULL;
    scene_to = 0, scene_from = 0;
    music = 0;
    
    parse_args(argc, argv);
    check_setup();
    //do_port();
    
    cleanup();
    
    return EXIT_SUCCESS;
}
