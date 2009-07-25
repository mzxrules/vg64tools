#!/usr/bin/python

from struct import pack, unpack
from sys import argv
from os import path, system
from z64lib import *

#When editing scene maximums, the two are located below:
MAX_MM_SCENE    = 102
MAX_OOT_SCENE   = 109
# Scene max values ^---HERE

MM_SCENE_FMT    = ">LLLL"
OOT_SCENE_FMT   = ">LLLLL"
MM_SCENE_TABLE  = 0xC5A280
OOT_SCENE_TABLE = 0xBA0BB0
BAD_MM_SCENES   = [ 4, 5, 48, 39 ]

oot_to_mm_acts = {
#   OoT    : MM
    0x0000 : 0x0000,    #Link
    0x0008 : 0x0004,    #Flame
    0x0009 : 0x0005,    #Door
    0x0007 : 0x000F,    #Dissipating flames
    0x000A : 0x0006,    #Chest
    0x0010 : 0x0009,    #Bomb
    0x0011 : 0x000A,    #Wallmaster
    0x0012 : 0x000B,    #Dodongo
    0x0013 : 0x000C,    #Keese
    0x0014 : 0x0054,    #Epona
    0x0015 : 0x000E,    #Collectables
    0x0018 : 0x0010,    #Fairies
    0x0019 : 0x0011,    #Cucco
    0x001B : 0x0012,    #Tektite
    0x001C : 0x0013,    #???
    0x001D : 0x0014,    #Peahat
    0x001E : 0x0015,    #Butterfly
    0x0020 : 0x0016,    #Bugs
    0x0021 : 0x0017,    #Fish
    0x0023 : 0x0018,    #Room changing plane
    0x0025 : 0x0019,    #Dinolfos/Lizafos
    0x0026 : 0x001A,    #Wooden post with red cloth
    0x0029 : 0x0152,    #Zelda
    0x002D : 0x001D,    #Bubble
    0x002E : 0x001E,    #Studded lifting door
    0x0032 : 0x0020,    #Boomerang
    0x0032 : 0x0022,    #???
    0x0037 : 0x0024,    #Skulltula
    0x0039 : 0x0027,    #gameplay_keep stuffs
    0x003B : 0x0028,    #sounds
    0x0049 : 0x0162,    #Flame circle
    0x004C : 0x002F,    #Bombflowers
    0x0055 : 0x0033,    #Deku baba
    0x005D : 0x0038,    #Warp portals
    0x005E : 0x0039,    #Torch stand
    0x005F : 0x003A,    #Heart container
    0x0060 : 0x003B,    #Deku scrub
    0x0065 : 0x003F,    #Water
    0x0068 : 0x0061,    #Twisted hallway
    #NOTE: oot one requires objects 0x71, 0x72 and 0x73 to be loaded
    
    0x0069 : 0x003E,    #Bubble (bouncing skull)
    0x0077 : 0x0041,    #Tree
    0x008A : 0x0047,    #Beamos
    0x008D : 0x0172,    #Flame Wall
    0x008E : 0x004A,    #Floormaster
    0x0090 : 0x004C,    #ReDead
    0x0094 : 0x004F,    #Butterflies (again)
    0x0095 : 0x0050,    #Skullwalltula
    0x009D : 0x01E3,    #Gravestone
    0x00A1 : 0x0069,    #Ruto
    0x00B0 : 0x00A7,    #I'M ON A BOAT
    0x00B5 : 0x018E,    #Flying rubble
#Zeth's:
    0x00DD : 0x006C,    #Like Like
    0x0167 : 0x00bd,    #Kakariko Roof Guy
    0x0153 : 0x0248,    #Music Box Grinder man
    0x0162 : 0x017d,    #Runningman/postman
    0x019B : 0x00e2,    #Doggie
    0x01B9 : 0x00ef,    #Gossip Stones
    0x0178 : 0x01C7,    #Hyrule/Town guard      oot var 0000
    0x0142 : 0x01C7,    #Hyrule/Town guard      oot var 0001
    0x00B3 : 0x01C7,    #Hyrule/Town guard
    0x01CE : 0x0228,    #Zora   MM:normal       oot var 0000
    0x0186 : 0x00FA,    #Walking Gerudo Guards  oot Var < 3
    0x01AE : 0x0242,    #Gorons                 oot var < 0xD
    0x01AF : 0x00EC,    #Wolfos
    0x01C0 : 0x00F1     #Guay

}

mm_to_oot_acts = {
#   MM     : OoT
    0x0000 : 0x0000,    #Link
    0x0004 : 0x0008,    #Flame
    0x0005 : 0x0009,    #Door
    0x000F : 0x0007,    #Dissipating flames
    0x0006 : 0x000A,    #Chest
    0x0009 : 0x0010,    #Bomb
    0x000A : 0x0011,    #Wallmaster
    0x000B : 0x0012,    #Dodongo
    0x000C : 0x0013,    #Keese
    0x0054 : 0x0014,    #Epona
    0x000E : 0x0015,    #Collectables
    0x0010 : 0x0018,    #Fairies
    0x0011 : 0x0019,    #Cucco
    0x0012 : 0x001B,    #Tektite
    0x0013 : 0x001C,    #???
    0x0014 : 0x001D,    #Peahat
    0x0015 : 0x001E,    #Butterfly
    0x0016 : 0x0020,    #Bugs
    0x0017 : 0x0021,    #Fish
    0x0018 : 0x0023,    #Room changing plane
    0x0019 : 0x0025,    #Dinolfos/Lizafos
    0x001A : 0x0026,    #Wooden post with red cloth
    0x0152 : 0x0029,    #Zelda
    0x001D : 0x002D,    #Bubble
    0x001E : 0x002E,    #Studded lifting door
    0x0020 : 0x0032,    #Boomerang
    0x0022 : 0x0032,    #???
    0x0024 : 0x0037,    #Skulltula
    0x0027 : 0x0039,    #gameplay_keep stuffs
    0x0028 : 0x003B,    #sounds
    0x0162 : 0x0049,    #Flame circle
    0x002F : 0x004C,    #Bombflowers
    0x0033 : 0x0055,    #Deku baba
    0x0038 : 0x005D,    #Warp portals
    0x0039 : 0x005E,    #Torch stand
    0x003A : 0x005F,    #Heart container
    0x003B : 0x0060,    #Deku scrub
    0x003F : 0x0065,    #Water
    0x0061 : 0x0068,    #Twisted hallway
    0x003E : 0x0069,    #Bubble (bouncing skull)
    0x0041 : 0x0077,    #Tree
    0x0047 : 0x008A,    #Beamos
    0x0172 : 0x008D,    #Flame Wall
    0x004A : 0x008E,    #Floormaster
    0x004C : 0x0090,    #ReDead
    0x004F : 0x0094,    #Butterflies (again)
    0x0050 : 0x0095,    #Skullwalltula
    0x01E3 : 0x009D,    #Gravestone
    0x0069 : 0x00A1,    #Ruto
    0x00A7 : 0x00B0,    #I'M ON A BOAT
    0x018E : 0x00B5,    #Flying rubble
    0x01DA : 0x0090,    #Gibodo (Use oot var -2 )
    0x0235 : 0x0090,    #Gibodos (Use oot var -2)
    0x00ED : 0x01B0,    #Stalchild
    0x02A5 : 0x01B0,    #Stalchild
    0x0191 : 0x0115,    #Skullkid
    0x00E4 : 0x019E,    #Beehive
    0x00E5 : 0x01A0,    #Crate
    0x00E9 : 0x01AC,    #Honey and darling
    0x0105 : 0x0054,    #Armos
    0x0110 : 0x008D,    #Firewall
    0x028D : 0x01A8,    #Cracked wall
    0x0298 : 0x01A9,    #cracked wall
    0x0255 : 0x00CF,    #cracked wall
    0x0258 : 0x015B,    #cracked wall
    0x00F3 : 0x01C6,    #Cow
    0x0220 : 0x00E7,    #Cremia/Child malon
    0x01A4 : 0x01C5,    #Malon/Romani           oot var FFFF
    0x021F : 0x01C5,    #Malon/Romani(guess)    oot var FFFF
    0x02AF : 0x0112,    #invisible collectibles
    0x0066 : 0x00C7,    #Withered Deku Baba
    0x011F : 0x01C7,    #Iceicles
    0x012D : 0x0055,    #Bio deku baba
    0x01BD : 0x011A,    #Deku salesman
    0x0274 : 0x011A,    #Deku salesman
    0x026E : 0x0142,    #Gaurd
    0x01EE : 0x019B,    #racing dog
    0x01F1 : 0x0021,    #Labratory fish
    0x01F3 : 0x000D,    #Poe
    0x0208 : 0x006D,    #Big poe
    0x01CA : 0x0085,    #Dampe
    0x008F : 0x0121,    #Freezard
    0x0216 : 0x001C,    #leever
#Zeth's:
    0x006C : 0x00DD,    #Like Like
    0x00bd : 0x0167,    #Kakariko Roof Guy
    0x0248 : 0x0153,    #Music Box Grinder man
    0x017d : 0x0162,    #Runningman/postman
    0x00e2 : 0x019B,    #Doggie
    0x00ef : 0x01B9,    #Gossip Stones
    0x01C7 : 0x0142,    #Hyrule/Town guard      oot var 0001
    0x00F8 : 0x01CE,    #Zora   MM:Swimming     oot var 0000
    0x0228 : 0x01CE,    #Zora   MM:normal       oot var 0000
    0x0231 : 0x01CE,    #Zora   MM:Guitarist    oot var 0000
    0x0238 : 0x01CE,    #Zora   MM:Drummer      oot var 0000
    0x0241 : 0x01CE,    #Zora   MM:Pianist      oot var 0000
    0x0252 : 0x01CE,    #Zora   MM:Singer       oot var 0000
    0x0260 : 0x01CE,    #Zora   MM:Swimming     oot var 0000
    0x00FA : 0x0186,    #Walking Gerudo Guards  oot Var < 3
    0x0242 : 0x01AE,    #Gorons                 oot var < 0xD
    0x00EC : 0x01AF,    #Wolfos
    0x00F1 : 0x01C0     #Guay
}

oot_to_mm_objs = {
#   OoT    : MM
    0x000E : 0x000C,    #Chests
    0x000B : 0x0009,    #Wallmaster
    0x000C : 0x000A,    #Dodongo
    0x000D : 0x000B,    #Keese
    0x001A : 0x007D,    #Epona
    0x0013 : 0x000F,    #Cucco
    0x0016 : 0x0012,    #Tektie
    0x0017 : 0x0013,    #???
    0x0018 : 0x0014,    #Peahat
    0x001B : 0x0017,    #Dinolfos/Lizafos
    0x0076 : 0x005F,    #Wooden post with red cloth
    0x001D : 0x014B,    #Zelda
    0x0012 : 0x000E,    #Bubble
    0x0022 : 0x00BC,    #???
    0x0024 : 0x0020,    #Skulltula
    0x0031 : 0x002A,    #bombflowers
    0x0039 : 0x0031,    #deku baba
    0x0048 : 0x003E,    #Warp portals
    0x00A4 : 0x0080,    #Torch stand
    0x00BD : 0x0096,    #Heart container
    0x004A : 0x0040,    #Deku scrub
    0x0059 : 0x017E,    #Water
    0x0070 : 0x0088,    #Twisted hallway
    0x005D : 0x0051,    #Bubble (bouncing skull)
    0x007C : 0x0061,    #Tree
    0x008B : 0x006A,    #Beamos
    0x002C : 0x0153,    #Flame Wall
    0x000B : 0x0009,    #Floormaster
    0x0098 : 0x0075,    #ReDead
    0x0024 : 0x0020,    #Skullwalltula
    0x00A2 : 0x01C2,    #Gravestone
    0x00A3 : 0x00A2,    #Ruto
    0x0069 : 0x017F,    #I'M ON A BOAT
    0x0092 : 0x018D,    #Flying rubble
    0x00D4 : 0x00AB,    #Like like
    0x00EC : 0x00C2,    #Kakariko roof guy
    0x0133 : 0x00FF,    #windmill man
    0x013C : 0x0107,    #Runningman/postman
    0x016B : 0x0132,    #Dog
    0x0188 : 0x0143,    #Gossip stones
    0x0097 : 0x01B5,    #Gaurds
    0x00FE : 0x00D0,    #Zora (Swimming and normal)
    0x0167 : 0x0130,    #Gerudo walkers
    0x00C9 : 0x00A1,    #Gorons
    0x0183 : 0x0141,    #Wolfos
    0x0008 : 0x0006     #Guay
}

mm_to_oot_objs = {
#   MM     : OoT
    0x000C : 0x000E,    #Chests
    0x0009 : 0x000B,    #Wallmaster
    0x000A : 0x000C,    #Dodongo
    0x000B : 0x000D,    #Keese
    0x007D : 0x001A,    #Epona
    0x000F : 0x0013,    #Cucco
    0x0012 : 0x0016,    #Tektie
    0x0013 : 0x0017,    #???
    0x0014 : 0x0018,    #Peahat
    0x0017 : 0x001B,    #Dinolfos/Lizafos
    0x005F : 0x0076,    #Wooden post with red cloth
    0x014B : 0x001D,    #Zelda
    0x000E : 0x0012,    #Bubble
    0x00BC : 0x0022,    #???
    0x0020 : 0x0024,    #Skulltula
    0x002A : 0x0031,    #bombflowers
    0x0031 : 0x0039,    #deku baba
    0x003E : 0x0048,    #Warp portals
    0x0080 : 0x00A4,    #Torch stand
    0x0096 : 0x00BD,    #Heart container
    0x0040 : 0x004A,    #Deku scrub
    0x017E : 0x0059,    #Water
    0x0088 : 0x0070,    #Twisted hallway
    0x0051 : 0x005D,    #Bubble (bouncing skull)
    0x0061 : 0x007C,    #Tree
    0x006A : 0x008B,    #Beamos
    0x0153 : 0x002C,    #Flame Wall
    0x0009 : 0x000B,    #Floormaster
    0x0075 : 0x0098,    #ReDead
    0x0020 : 0x0024,    #Skullwalltula
    0x01C2 : 0x00A2,    #Gravestone
    0x00A2 : 0x00A3,    #Ruto
    0x017F : 0x0069,    #I'M ON A BOAT
    0x018D : 0x0092,    #Flying rubble
    0x00AB : 0x00D4,    #Like like
    0x00C2 : 0x00EC,    #Kakariko roof guy
    0x00FF : 0x0133,    #windmill man
    0x0107 : 0x013C,    #Runningman/postman
    0x0132 : 0x016B,    #Dog
    0x0143 : 0x0188,    #Gossip stones
    0x01B5 : 0x0097,    #Gaurds
    0x00D0 : 0x00FE,    #Zora (Swimming and normal)
    0x0211 : 0x00FE,    #Zora (guitarist)
    0x0216 : 0x00FE,    #Zora (drummer)
    0x0220 : 0x00FE,    #Zora (Pianist)
    0x022B : 0x00FE,    #Zora (Singer)
    0x0130 : 0x0167,    #Gerudo walkers
    0x00A1 : 0x00C9,    #Gorons
    0x0141 : 0x0183,    #Wolfos
    0x0006 : 0x0008,    #Guay
    0x0142 : 0x0184,    #Stalchildren
    0x0192 : 0x010A,    #Skullkid
    0x01B9 : 0x0002,    #beehive
    0x0133 : 0x0170,    #Crate
    0x0140 : 0x0182,    #Honey and darling
    0x0030 : 0x0038,    #Armos
    0x0153 : 0x002C,    #Firewall
    0x0267 : 0x0074,    #Cracked wall
    0x0234 : 0x00B1,    #Cracked wall
    0x0203 : 0x002C,    #cracked wall
    0x01E0 : 0x00F1,    #cracked wall
    0x0146 : 0x018B,    #Cow
    0x00A7 : 0x00E0,    #Cremia
    0x00B7 : 0x00D0,    #Malon/Romani
    0x0031 : 0x0039,    #Withered Deku Baba
    0x0157 : 0x006B,    #Icicles
    0x015E : 0x0039,    #Bio deku baba
    0x01E5 : 0x0168,    #Deku salesman
    0x01B6 : 0x0097,    #Gaurd
    0x01C3 : 0x0009,    #Poe
    0x01F1 : 0x006D,    #Big poe
    0x01AF : 0x0089,    #Dampe
    0x00E4 : 0x0114,    #Freezard
    0x0201 : 0x0017     #leever
}

def fix_doors(inFile, outFile, OutFileOff, inFileOff, NoDoors, DestGame="OoT", loud = False):
    oldPos = inFile.tell()
    outFile.seek(OutFileOff)
    door = []
    fixed = 0
    
    for i in range(inFileOff, (NoDoors * 16) + inFileOff, 16):
        inFile.seek(i)
        door_ = unpack(">BBBBHhhhhH",inFile.read(16))
        door[:] = door_[:]
        if DestGame == "OoT":
            try:
                door[4] = mm_to_oot_acts[door[4]]
                if (door[4] == 0x23):
                    door[-1] = 0x13F
                fixed+=1
            except:
                if loud:
                    print "Unmapped door: %04X" % ( door[4] )
                door[4] = 0x0009
                door[-1] = 0
        elif DestGame == "MM":
            try:
                door[4] = oot_to_mm_acts[door[4]]
                fixed+=1
            except:
                door[4] = 0x0005
        else:
            return -1
        outFile.write(pack(">BBBBHhhhhH", door[0], door[1], door[2],
                               door[3], door[4], door[5], door[6], door[7],
                               door[8], door[9] ))
    if loud:
        if NoDoors:
            print "Matched %.2f%% of doors with OoT parallels." % ( 100 * ( fixed / float( NoDoors ) ) )
        else:
            print "No objects to match!"
    inFile.seek(oldPos)
    return 0

def fix_actors(inFile, outFile, OutFileOff, inFileOff, NoActors, DestGame="OoT", loud = False):
    oldPos = inFile.tell()
    outFile.seek(OutFileOff)
    actor = []
    fixed = 0
    
    for i in range(inFileOff, (NoActors * 16) + inFileOff, 16):
        inFile.seek(i)
        actor_ = unpack(">HhhhhhhH",inFile.read(16))
        actor[:] = actor_[:]
        actor[0] = actor[0] & 0xFFF
        if DestGame == "OoT":
            try:
                actor[0] = mm_to_oot_acts[actor[0]]
                #Set variables for certain actors:
                if actor[0]   == 0x0142:
                    actor[7] = 1
                elif actor[0] == 0x01CE:
                    actor[7] = 0
                elif actor[0] == 0x0162:    #Running man
                    actor[7] = 1
                elif actor_[0] == 0x235 or actor_[0] == 0x1DA:
                    actor[7] = 0xFFFE
                elif actor[0] == 0x1B0:
                    actor[7] = 0
                elif actor[0] == 0x1C6:
                    actor[7] = 0
                elif actor[0] == 0x1C5:
                    actor[7] = 0xFFFF
                elif actor[0] == 0x05D:
                    actor[7] = actor[7] & 7
                fixed+=1
            except:
                #print "%08X %04X"%(i, actor[0])
                actor[0] = 0x0008
                actor[7] = actor[7]&0xF
        elif DestGame == "MM":
            try:
                actor[0] = oot_to_mm_acts[actor[0]]
                fixed+=1
            except:
                actor[0] = 0x0004
        else:
            return -1
        outFile.write(pack(">HhhhhhhH",actor[0], actor[1], actor[2],
                               actor[3], actor[4], actor[5], actor[6], actor[7]))
    if loud:
        if NoActors:
            print "Matched %.2f%% of actors with OoT parallels." % ( 100 * ( fixed / float( NoActors ) ) )
        else:
            print "No actors to match!"
    inFile.seek(oldPos)
    return 0

def fix_objects(inFile, outFile, OutFileOff, inFileOff, NoObjects, DestGame="OoT", loud = False):
    oldPos = inFile.tell()
    outFile.seek(OutFileOff)
    inFile.seek(inFileOff)
    fixed = 0
    objs = []
    objs_ = unpack( ">" + "H" * NoObjects, inFile.read( NoObjects * 2 ) )
    objs[:] = objs_[:]
    wobjs = []
    
    for i in range(NoObjects):
        obj = objs[i]
        if DestGame == "OoT":
            try:
                wobjs.append( mm_to_oot_objs[obj] )
                fixed+=1
            except:
                pass
        elif DestGame == "MM":
            try:
                wobjs.append( mm_to_oot_objs[obj] )
                fixed+=1
            except:
                pass
    for i in range( fixed ):
        outFile.write(pack( ">H", wobjs[i] ))
    for i in range( NoObjects - fixed ):
        outFile.write(pack( ">H", 0 ))
    if loud:
        if NoObjects:
            print "Matched %.2f%% of objects with OoT parallels." % ( 100 * ( fixed / float( NoObjects ) ) )
        else:
            print "No objects to match!"
    inFile.seek(oldPos)
    return fixed

def fix_map(inFile, outFile, outFileOff, inFileOff, loud = False, DestGame="OoT", IsScene = False, safe = False):
    oldPos = inFile.tell()
    outFile.seek(outFileOff)
    fpos = inFileOff
    
    while (1):
        inFile.seek(fpos)
        ID = unpack(">B",inFile.read(1))[0]
        if (ID == 0xB):
            if safe:
                outFile.seek(outFileOff+(fpos-inFileOff)+1)
                outFile.write(pack(">B",0))
            else:
                NoObjects, LocalOff = unpack(">BxxL",inFile.read(7))
                LocalOff = LocalOff & 0xFFFFFF
                NoObjects = fix_objects(inFile, outFile, outFileOff+LocalOff, inFileOff+LocalOff, NoObjects, DestGame, loud)
                outFile.seek(outFileOff+(fpos-inFileOff)+1)
                if NoObjects > 0xF:
                    outFile.write(pack(">B",0xF))
                else:
                    outFile.write(pack(">B",NoObjects))
        elif (ID == 1 or ID == 0):
            if safe and ID == 1:
                outFile.seek(outFileOff+(fpos-inFileOff)+1)
                outFile.write(pack(">B",0))
            else:
                NoActors, LocalOff = unpack(">BxxL",inFile.read(7))
                LocalOff = LocalOff & 0xFFFFFF
                fix_actors(inFile, outFile, outFileOff+LocalOff, inFileOff+LocalOff, NoActors, DestGame, loud)
        elif (ID == 0xE):
            if safe:
                outFile.seek(outFileOff+(fpos-inFileOff)+1)
                outFile.write(pack(">B",0))
            else:
                NoDoors, LocalOff = unpack(">BxxL",inFile.read(7))
                LocalOff = LocalOff & 0xFFFFFF
                fix_doors(inFile, outFile, outFileOff+LocalOff, inFileOff+LocalOff, NoDoors, DestGame, loud)
        elif (IsScene == True and ID == 0x4):
            IsScene = unpack(">BxxL",inFile.read(7))
            IsScene = [IsScene[0],IsScene[1]]
            IsScene[1] = IsScene[1] & 0xFFFFFF
        elif (ID == 0x18 or ID == 0x12): #bai bai multiple object sets :)
            outFile.seek(outFileOff+(fpos-inFileOff))
            outFile.write(pack(">Q",0x0100000000000000))
        elif (ID == 0x11):
            enabled = unpack("xxxxxB",inFile.read(6))[0]&1
            outFile.seek(outFileOff+(fpos-inFileOff))
            if not enabled:
                outFile.write(pack(">Q",0x1100000001000000))
            else:
                outFile.write(pack(">Q",0x1100000000000100))
        elif ( ID == 3 ):
            offset = unpack(">xxxL",inFile.read(7))[0]
            outFile.seek( outFileOff + ( offset & 0xFFFFFF ) + 0x20)
            outFile.write( pack( ">L", 0 ) )
        elif (ID == 0x14):
            break
        fpos += 8
    inFile.seek(oldPos)
    if (IsScene != False):
        return IsScene
    else:
        return 0
    
def _int(string):
    if len(string)>2 and string[:2]=='0x':
        return int(string,16)
    else:
        return int(string)

def FindEndOfFiles(File):
    """Finds the end offset within a ROM that is safe to write to"""
    End = 0
    FPos = FindFileTable( File ,">" )[0]+4
    Entry = -1
    while (Entry != 0):
        File.seek(FPos)
        Entry = unpack( ">L", File.read(4) )[0]
        if (Entry > End):
            End = Entry
        FPos+=16
    codeOff = FindCode( File,">" )[0]
    for i in range( codeOff + 0xF9440, codeOff + 0xFB5E0, 0x20 ):
        File.seek(i+4)
        Entry = unpack( ">L", File.read(4) )[0]
        if (Entry > End):
            End = Entry
    for i in range( codeOff + 0x10A6D0, codeOff + 0x10B360, 0x8 ):
        File.seek(i+4)
        Entry = unpack( ">L", File.read(4) )[0]
        if (Entry > End):
            End = Entry
    for i in range( codeOff + 0x10CBB0, codeOff + 0x10CBB0 + MAX_OOT_SCENE * 0x14, 0x14 ):
        File.seek(i+4)
        Entry = unpack( ">L", File.read(4) )[0]
        if (Entry > End):
            End = Entry
    return End
    
def checkArgs():
    if ( len(argv) < 5 ):
        return -1
    
    if ( (not path.exists(argv[1])) | (not path.exists(argv[2])) ):
        return -2
    
    try:
        argv[3] = _int(argv[3])
        argv[4] = _int(argv[4])
        
    except ValueError:
        return -3
    
    if ( ( argv[3] > MAX_OOT_SCENE ) | ( argv[4] > MAX_MM_SCENE ) ):
        return -4
    
    ret = 1
    
    if ( len(argv) > 5 ):
        cnt = 5
        while ( cnt < len(argv) ):
            if ( argv[cnt] == "-q" ):
                ret = ret & 0xFFFFFFFE
            if ( argv[cnt] == "-s" ):   #safe mode
                ret = ret | 0x100000000
            elif ( argv[cnt] == "-o" ):
                ret = ret | ( _int(argv[cnt+1]) & 0xFFFFFFF0 )
                cnt += 1
            cnt += 1
    return ret

def main():
    while (1):  #So I can use break
        status = checkArgs()
        if ( status < 0 ):
            if ( status == -1 ):
                print "ArgumentError: Not enough arguments. Usage:"
            elif ( status == -2 ):
                print "IOError: Cannot open specified ROMs. Usage:"
            elif ( status == -3 ):
                print "ValueError: Cannot convert scene numbers to integers. Usage:"
            elif ( status == -4 ):
                print (
"OverflowError: Scene numbers specified are too great.\n\
If your ROM can handle bigger scene numbers, edit this script on lines 9 and 10. Usage:" )
            print "python %s <rom to port to> <rom port from> <scene to port over> <scene to port>" % ( argv[0] )
            break
        try:
            BAD_MM_SCENES.index( argv[4] )
            print "Error: Chosen scene is a invalid Majora's Mask scene"
            break
        except:
            pass
        inFile  = open( argv[2], "rb" )
        outFile = open( argv[1], "r+b" )
        inFile.seek(MM_SCENE_TABLE + argv[4] * 16)
        OldSceneOffs = unpack( ">LL", inFile.read(8) )
        safe = bool( status & 0x100000000 )
        if ( status > 15 ):
            SceneStart = status & 0xFFFFFFF0
        else:
            SceneStart = FindEndOfFiles(outFile)
        if ( status & 1 ):
            print ("Porting scene %i from ROM %s to scene %i of ROM %s at offset 0x%08X"
                   % ( argv[4], argv[2], argv[3], argv[1], SceneStart ))
        SceneEnd = SceneStart + ( OldSceneOffs[1] - OldSceneOffs[0] )
        outFile.seek(SceneStart)
        inFile.seek(OldSceneOffs[0])
        outFile.write( inFile.read( OldSceneOffs[1] - OldSceneOffs[0] ) )
        if ( status & 1):
            print "Fixing scene file"
        Map_Infos = fix_map(inFile, outFile, SceneStart, OldSceneOffs[0], status & 1 ,"OoT", True , safe)
        if ( status & 1):
            print ("Old offsets: %08X - %08X\nNew offsets: %08X - %08X"
                   % ( OldSceneOffs[0], OldSceneOffs[1], SceneStart, SceneEnd ) )
        MapStart = (SceneEnd & 0xFFFFFFF0) + 0x10
        count = 0
        for ptr_offset in range(Map_Infos[1], Map_Infos[1] + Map_Infos[0] * 8, 8):
            if ( status & 1 ):
                print "Fixing map %i" % ( count )
            inFile.seek(OldSceneOffs[0]+ptr_offset)
            oldMapOffs = unpack( ">LL", inFile.read(8) )
            outFile.seek(MapStart)
            inFile.seek(oldMapOffs[0])
            outFile.write( inFile.read( oldMapOffs[1] - oldMapOffs[0] ) )
            MapEnd = outFile.tell()
            fix_map( inFile, outFile, MapStart, oldMapOffs[0], status & 1, "OoT", False, safe )
            outFile.seek( SceneStart + ptr_offset )
            outFile.write( pack( ">LL" , MapStart, MapEnd ) )
            if ( status & 1 ):
                print ( "Old offsets: %08X - %08X\nNew offsets: %08X - %08X"
                       % ( oldMapOffs[0], oldMapOffs[1], MapStart, MapEnd ) )
            MapStart = MapEnd
            count += 1
            
        outFile.seek( OOT_SCENE_TABLE + argv[3] * 0x14 )
        outFile.write( pack( OOT_SCENE_FMT, SceneStart, SceneEnd, 0, 0, 0 ) )
        if ( status & 1 ):
            print "Done. Using space %08X - %08X for maps and scenes." % ( SceneStart, MapEnd )
        inFile.close()
        outFile.close()
        break
    
if __name__ == "__main__":
    main()
