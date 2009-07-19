#include "mips.h"

extern int ActorSpawn(u32 const_1, u32 const_2, int actor, f32 fx, f32 fy, f32 fz, u16 rx, u16 ry, u16 rz, int variable);

void SetTextRGBA(void * DList, u8 r, u8 g, u8 b, u8 a);
void SetTextXY(void * DList, u16 x, u16 y);
void SetTextString(void * DList, char * format, ...);

void func8009899C(void *, void *);
void func800985DC(void *, void *);

typedef struct
{
    u8 Number;
    u16 Object;
}
ObjectEntry;

typedef struct
{
    u8 Number;
    u8 buff;
   /* struct MapActorEntry *Actor;  Screw this, it's harder to deal with */
    u16 ActorNo;
    s16 x;
    s16 y;
    s16 z;
    s16 xr;
    s16 yr;
    s16 zr;
    u16 var;
} SavedActorEntry;

struct MapActorEntry
{
    u16 ActorNo;
    s16 x;
    s16 y;
    s16 z;
    s16 xr;
    s16 yr;
    s16 zr;
    u16 var;
};

typedef struct
{
    u32 o_addr;
    u32 a_addr;
    u8 no_objects;
    u8 no_actors;
    u16 oe_addr;
    u16 ae_addr;
    u16 buff;
}
ModifiedSetPtr;

/* OoT controller layout */
typedef struct
{
    /* Buttons */
    u16 pad;
    
    /* Joystick */
    signed x : 8;
    signed y : 8;
} 
Controller;

struct OTE
{
    u32 Start;
    u32 End;
};
/* Misc */
#define OBJ_TABLE	0x80127528
#define	MSA		0x8015E740
#define SAVE_BASE	0x8015EF40
#define P2_CONTROLLER   0x80166B08
#define FREEZE_ACTORS	0x80211174
#define CAMERA_PTR	0x80212290
#define MAP_POINTER	0x80223CE8
#define	NO_MAP_ACTORS	0x80223E0B
#define MAP_ACTOR_LIST	0x80223E18

/* values program reads */
#define CURRENT_ACT	0x80602000	/* Current selected actor */
#define CURRENT_OBJ	0x80602001	/* Current selected object */
#define STATUS		0x80602002	/* Toolmode status */
#define ACTOR_STATUS	0x80602003	/* Actor editor status */
#define NO_MAP_ACT_SAVE	0x80602004	/* Amount of Map actors */
#define NO_OBJECTS	0x80602005	/* Amount of objects */
#define INC		0x80602006	/* Increment amount */
/* stored pointers */
#define OBJECT_A1	0x80602008	/* second arg given to object handler routine */
#define ACTOR_A1	0x8060200C	/* second arg given to actor handler routine */
#define M_OBJ_L_PTR	0x80602010	/* original object list address (for comparison) */
/* Arrays */
#define MAP_ACT_RAML	0x80602020
#define MAP_ACT_LS	0x80602420
#define OBJ_L		0x80603410

/* Buttons */
#define BUTTON_NONE	0x0000
#define BUTTON_DPAD_R	0x0100
#define BUTTON_DPAD_L	0x0200
#define BUTTON_DPAD_D	0x0400
#define BUTTON_DPAD_U	0x0800
#define BUTTON_START	0x1000
#define BUTTON_Z	0x2000
#define BUTTON_B	0x4000
#define BUTTON_A	0x8000
#define BUTTON_CR	0x0001
#define BUTTON_CL	0x0002
#define BUTTON_CD	0x0004
#define BUTTON_CU	0x0008
#define BUTTON_R	0x0010
#define BUTTON_L	0x0020
/* Statuses */
#define STAT_NONE	0x00
#define STAT_ACT	0x01
#define STAT_OBJ	0x02
/* Actor statuses */
#define SA_POS		0x00
#define SA_ROT		0x01
#define SA_NUMVAR	0x02
#define SA_NONE		0x03

