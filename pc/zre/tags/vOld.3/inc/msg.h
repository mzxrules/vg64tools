/******************
* RETURN MESSAGES *
******************/

#ifndef __MSG_H
#define __MSG_H

/* Messages for application */
#define zre_print_header() { printf(__MSG_HEAD,__BUILD_NUM,__DATE__,__TIME__); }
#define __MSG_HEAD \
	" oooooooooooo ooooooooo.   oooooooooooo " "\n" \
	"d'\"\"\"\"\"\"d888' `888   `Y88. `888'     `8 " "\n" \
	"      .888P    888   .d88'  888         " "\n" \
	"     d888'     888ooo88P'   888oooo8    " "\n" \
	"   .888P       888`88b.     888    \"    " "\n" \
	"  d888'    .P  888  `88b.   888       o " "\n" \
	".8888888888P  o888o  o888o o888ooooood8 " "\n" \
	"======================================= " "\n" \
	"Build %lu, built: %s %s\n" \
	"=======================================\n" \

/* Credits */
#define zre_print_credits() { puts(__MSG_CREDITS); exit(0); }
#define __MSG_CREDITS "\n~> ~> ~> ~> ~> ~> ~> ~> ~> ~>\n" \
	"~> ZRE CREDITS             ~>\n" \
	"~> ~> ~> ~> ~> ~> ~> ~> ~> ~>\n\n" \
	"~Programmers~\n" \
	" ZZT32\n" \
	" cooliscool\n" \
	" sakura\n\n" \
	"~Testers~\n" \
	" Elemental\n" \
	" Hanabi\n" \
	" Jani\n" \
	" TheTeej\n" \
	" Xu_Yuan\n\n"


/* Messages returned for CLI parsing */
#define __MSG_YTA    "=> Answering YES to all questions.\n"
#define __MSG_STRIP  "=> Stripping prefixes/suffixes from filenames.\n"
#define __MSG_DBG    "=> Debug mode on.\n"
#define __MSG_ODIR   "=> Output directory set to \"%s\".\n"
#define __MSG_ODIRNE "=> Flag \"-o\" was encountered but no output directory was given!\n"
#define __MSG_FID1   "=> Prefixing file ID relative to file table.\n"
#define __MSG_FID2   "=> Prefixing file ID relative to files extracted.\n"
#define __MSG_NWRT   "=> Not writing anything to disk.\n"
#define __MSG_NNAMES "=> Skipping filename grabbing process.\n"
#define __MSG_UFLAG  "=> Unknown flag \"%c\".\n"
#define __MSG_UARG   "=> Unknown argument \"%s\".\n"
#define __MSG_IROM   "=> Using file \"%s\" as input.\n"
#define __MSG_OTYPE  "=> Using offset type %u in filenames.\n"
#define __MSG_NTABLE "=> Not looking for object tables (scenes, maps and actors).\n"
#define __MSG_NACTOR "=> Not looking for actor table.\n"
#define __MSG_NSCENE "=> Not looking for scene table.\n"

/* Help menu */
#define zre_print_help() { puts(__MSG_HELP); exit(0); }
#define __MSG_HELP \
	"\n~~~~~~> Help <~~~~~~\n" \
	"-y\tanswer yes to everything\n" \
	"-L\tfile id relative to file table\n" \
	"-l\tfile id relative to files extracted\n" \
	"-n\tdon't write data to disk\n" \
	"-s\tstrip file suffixes/prefixes\n" \
	"-S\tsilent mode\n" \
	"-U\tsuppress all messages (even errors)\n" \
	"-u\tdo not extract filenames\n" \
	"-o\tset output directory\n" \
	"-d\tdebug mode\n" \
	"-O#\tadd offsets to filenames\n" \
	"-t\tdisable scene/actor table detection\n" \
	"-T\tdisable scene table detection\n" \
	"-A\tdisable actor table detection\n\n" \
	"--credits   display credits\n" \
	"--help      display this help\n"

#endif
