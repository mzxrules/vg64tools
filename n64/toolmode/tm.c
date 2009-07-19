#include "mips.h"
#include "tm.h"
#include "../z_snippets/actor.h"

/*
ToolMode - By spinout (spinout182 AT yahoo DOT com)

CONTROLS (Player 2)
Start: Toggle ToolMode on/off. When you turn it off, it gets the changes ready for you to save when you save normally.
Right: Reset any changes you have made to what you are currently editing.
Left: Toggle what you are editing. Possible values are:
	- Objects
	- Actors, which have three sub modes:
	    - XYZ Pos
	    - XYZ Rot
	    - Actor number/Variable
C-Up and C-Down increase and decrease which instance of a (actor/object) you are editing
C-Left and C-Right increase and decrease the current incementation amount
DPad up/down edit:
	- Z rotation or pos, when in actor rot or pos modes
	- Actor variable
DPad left/right edit:
	- Z rotation or pos, when in actor rot or pos modes
	- Actor number
A and B edit:
	- Y rotation or pos, when in actor rot or pos modes

Designed for Zelda 64 Debug ROM, but could probably be adapted for other ROM versions.

Credits go to:
cen	- Pointers to all sorts of things within RAM
jsa	- ZLE2's source code was a great reference!
zzt32	- Tought me how to do this, and some of the functions modified
	  would not have been found without his hack of Mupen64Plus to
	  get console debugging information.

801274A4 - Actor routine addr  (800985DC)
801274CC - Object routine addr (8009899C)
*/

ModifiedSetPtr (*ModifiedSets)[255] = (void*)MSA;
u8  *NoActors = (void*)NO_MAP_ACT_SAVE;
u8  *NoObjects	= (void*)NO_OBJECTS;
u8 *currAct	= (void*)CURRENT_ACT;
u8 *currObj	= (void*)CURRENT_OBJ;
u16 (*MapObjList)[1] = (void*)OBJ_L;
u32 *MObjLPtr	= (void*)M_OBJ_L_PTR;
u32 (*MActRAMI)[1]	= (void*)MAP_ACT_RAML;
u32	*ObjectA1	= (void*)OBJECT_A1;
u32	*ActorA1	= (void*)ACTOR_A1;
struct MapActorEntry 	(**MapActorList)[255]	= (void*)MAP_ACTOR_LIST;
struct MapActorEntry (*SMAL)[255]	= (void*)MAP_ACT_LS;

void EditMode(void * a0)
{
    Controller  *input  = (void*)P2_CONTROLLER;
    u8	*status		= (void*)STATUS;
    u8	*actorStatus	= (void*)ACTOR_STATUS;
    u16	*actorFreeze	= (void*)FREEZE_ACTORS;
    u32 *camera		= (void*)CAMERA_PTR;
    u16 *inc		= (void*)INC;
    u16	(*OrigObjL)[64]	= (void*)*MObjLPtr;
    struct z64_actor_t * Actor;
    Actor = (struct z64_actor_t*)(*MActRAMI)[*currAct];
    int i = 0;
    int m = 0;
    int SetNo;
    u16 end;

    if (*status)
    {
        if (*inc == 0)
        {
            *inc = 1;
        }
        switch (input->pad)
        {
        case BUTTON_START:
            while (i < 128)
            {
                if ((*ModifiedSets)[i].ae_addr > end)
                {
                    end = (*ModifiedSets)[i].ae_addr + ((*ModifiedSets)[i].no_actors * 0x12);
                }
                if ((*ModifiedSets)[i].oe_addr > end)
                {
                    end = (*ModifiedSets)[i].oe_addr + ((*ModifiedSets)[i].no_objects * 4);
                }
                if ((*ModifiedSets)[i].o_addr == *ObjectA1)
                {
                    break;
                }
                else if ((*ModifiedSets)[i].a_addr == *ActorA1)
                {
                    break;
                }
                else if ((*ModifiedSets)[i].a_addr == 0 && (*ModifiedSets)[i].o_addr == 0)
                {
                    break;
                }
                i++;
            }
            SetNo = i;
            (*ModifiedSets)[SetNo].a_addr = *ActorA1;
            (*ModifiedSets)[SetNo].o_addr = *ObjectA1;
            (*ModifiedSets)[SetNo].ae_addr = end;
            i = 0;
            m = 0;
            SavedActorEntry	(*ALSAV)[1] = (void*)(0x9015EF40+end);/* Why use 9 instead of 8? GCC adds 0xF0000000 to the address >:(*/
            while (i < *NoActors)
            {
                if (((*SMAL)[i].ActorNo	!= (**MapActorList)[i].ActorNo) ||
                    ((*SMAL)[i].x	!= (**MapActorList)[i].x)	||
                    ((*SMAL)[i].y	!= (**MapActorList)[i].y)	||
                    ((*SMAL)[i].z	!= (**MapActorList)[i].z)	||  /* Ugh, this is so inefficient. memcmp anybody? */
                    ((*SMAL)[i].xr	!= (**MapActorList)[i].xr)	||
                    ((*SMAL)[i].yr	!= (**MapActorList)[i].yr)	||
                    ((*SMAL)[i].zr	!= (**MapActorList)[i].zr)	||
                    ((*SMAL)[i].var	!= (**MapActorList)[i].var) )
                {
                    (*ALSAV)[m].Number	= i;
                    (*ALSAV)[m].ActorNo	= (*SMAL)[i].ActorNo;
                    (*ALSAV)[m].x	= (*SMAL)[i].x;
                    (*ALSAV)[m].y	= (*SMAL)[i].y;
                    (*ALSAV)[m].z	= (*SMAL)[i].z;
                    (*ALSAV)[m].xr	= (*SMAL)[i].xr;
                    (*ALSAV)[m].yr	= (*SMAL)[i].yr;
                    (*ALSAV)[m].zr	= (*SMAL)[i].zr;
                    (*ALSAV)[m].var	= (*SMAL)[i].var;
                    m++;
                    end+=0x12;
                }
                i++;
            }
            (*ModifiedSets)[SetNo].oe_addr = end;
            (*ModifiedSets)[SetNo].no_actors = m;
            i = 0;
            m = 0;
            ObjectEntry	(*OLSAV)[1] = (void*)(0x9015EF40+end);/*(SAVE_BASE + end);*/
            while (i < *NoObjects)
            {
                if ((*MapObjList)[i] != (*OrigObjL)[i])
                {
                    (*OLSAV)[m].Object = (*MapObjList)[i];
                    (*OLSAV)[m].Number = i;
                    m++;
                }
                i++;
            }

            (*ModifiedSets)[SetNo].no_objects = m-1;

            /* The changes should be saved by now... */
            *status = STAT_NONE;
            *actorFreeze = 0;
            *camera = 0x802245B0;
            break;
        case BUTTON_Z:
            /* Spawn actor */
            break;
        case BUTTON_R:
            switch (*status)
            {
            case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.x = (f32)(**MapActorList)[*currAct].x;
                    Actor->coords_2.y = (f32)(**MapActorList)[*currAct].y;
                    Actor->coords_2.z = (f32)(**MapActorList)[*currAct].z;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xB8) = (**MapActorList)[*currAct].xr;
                    AVAL(Actor,s16,0xBA) = (**MapActorList)[*currAct].yr;
                    AVAL(Actor,s16,0xBC) = (**MapActorList)[*currAct].zr;
                    break;
                case SA_NUMVAR:
                    (*SMAL)[*currAct].ActorNo = (**MapActorList)[*currAct].ActorNo;
                    (*SMAL)[*currAct].var = (**MapActorList)[*currAct].var;
                    break;
                }
                break;
            case STAT_OBJ:
                (*MapObjList)[*currObj] = (*OrigObjL)[*currObj];
            }
            break;
        case BUTTON_L:
            switch (*status)
            {
            case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                case SA_ROT:
                    *actorStatus += 1;
                    break;
                case SA_NUMVAR:
                    *status = STAT_OBJ;
                    *camera = 0x802245B0;
                    *actorStatus = 0;
                    break;
                default:
                    break;
                }
                break;
            case STAT_OBJ:
                *status = STAT_ACT;
                break;
            default:
                break;
            }
            break;
        case BUTTON_CU:
            if (*status == STAT_ACT && *currAct < *NoActors)
            {
                *currAct+=1;
            }
            else if (*currObj < *NoObjects)
            {
                *currObj+=1;
            }
            break;
        case BUTTON_CD:
            if (*status == STAT_ACT && *currAct > 0)
            {
                *currAct-=1;
            }
            else if (*currObj > 0)
            {
                *currObj-=1;
            }
            break;
        case BUTTON_CR: /* increase increment amount */
            *inc<<=1;
            break;
        case BUTTON_CL: /* decrease increment amount*/
            if (*inc < 0x1000)
                *inc>>=1;
            break;
        case BUTTON_DPAD_R: /* DPad right */
           switch (*status)
           {
           case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.x += (f32)*inc;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xB8) += *inc;
                    break;
                case SA_NUMVAR:
                    if (((*SMAL)[*currAct].ActorNo + *inc) < 0x1D7)
                    {
                        (*SMAL)[*currAct].ActorNo += *inc;
                    }
                    break;
                break;
                }
            case STAT_OBJ:
                if ((*MapObjList)[*currObj] + *inc < 0x192)
                {
                    (*MapObjList)[*currObj]+=*inc;
                }
            }
            break;
        case BUTTON_DPAD_L: /* DPad left */
           switch (*status)
           {
           case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.x -= (f32)*inc;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xB8) -= *inc;
                    break;
                case SA_NUMVAR:
                    if (((*SMAL)[*currAct].ActorNo - *inc) >= 0)
                    {
                        (*SMAL)[*currAct].ActorNo -= *inc;
                    }
                    break;
                break;
                }
            case STAT_OBJ:
                if ((*MapObjList)[*currObj] - *inc > 0)
                {
                    (*MapObjList)[*currObj] -= *inc;
                }
            }
            break;
        case BUTTON_DPAD_U: /* DPad up */
           switch (*status)
           {
           case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.z += (f32)*inc;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xBC) += *inc;
                    break;
                case SA_NUMVAR:
                    if (((*SMAL)[*currAct].var + *inc) < 0x10000)
                    {
                        (*SMAL)[*currAct].var += *inc;
                    }
                    break;
                break;
                }
            case STAT_OBJ:
                break;
            }
            break;
        case BUTTON_DPAD_D: /* DPad down */
           switch (*status)
           {
           case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.z -= (f32)*inc;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xBC) -= *inc;
                    break;
                case SA_NUMVAR:
                    if (((*SMAL)[*currAct].var - *inc) >= 0)
                    {
                        (*SMAL)[*currAct].var -= *inc;
                    }
                    break;
                break;
                }
            case STAT_OBJ:
                break;
            }
            break;
        case BUTTON_A: /* A */
           switch (*status)
           {
           case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.y += (f32)*inc;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xBA) += *inc;
                    break;
                case SA_NUMVAR:
                    break;
                break;
                }
            case STAT_OBJ:
                break;
            }
            break;
        case BUTTON_B: /* B */
           switch (*status)
           {
           case STAT_ACT:
                switch (*actorStatus)
                {
                case SA_POS:
                    Actor->coords_2.y -= (f32)*inc;
                    break;
                case SA_ROT:
                    AVAL(Actor,s16,0xBA) -= *inc;
                    break;
                case SA_NUMVAR:
                    break;
                break;
                }
            case STAT_OBJ:
                break;
            }
            break;
        default:
            break;
        }

        SetTextRGBA( a0, 0, 0xCC, 0xFF, 0xFF);
        SetTextXY( a0, 0, 7);
        SetTextString( a0, "Tool Mode\n");
    
        if (*status == STAT_ACT)
        {
            Actor = (struct z64_actor_t*)(*MActRAMI)[*currAct];
            
            /* Check for differences in pos/rot */
            if ( (s16)Actor->coords_2.x != (**MapActorList)[*currAct].x)
            {
                (*SMAL)[*currAct].x = (s16)Actor->coords_2.x;
            }
            if ( (s16)Actor->coords_2.y != (**MapActorList)[*currAct].y)
            {
                (*SMAL)[*currAct].y = (s16)Actor->coords_2.y;
            }
            if ( (s16)Actor->coords_2.z != (**MapActorList)[*currAct].z)
            {
                (*SMAL)[*currAct].z = (s16)Actor->coords_2.z;
            }
            if ( AVAL(Actor,s16,0xB8) != (**MapActorList)[*currAct].xr)
            {
                (*SMAL)[*currAct].xr = AVAL(Actor,s16,0xB8);
            }
            if ( AVAL(Actor,s16,0xBA) != (**MapActorList)[*currAct].yr)
            {
                (*SMAL)[*currAct].yr = AVAL(Actor,s16,0xBA);
            }
            if ( AVAL(Actor,s16,0xBC) != (**MapActorList)[*currAct].zr)
            {
                (*SMAL)[*currAct].zr = AVAL(Actor,s16,0xBC);
            }
            
            if ( *actorStatus != SA_NONE )
            {
                u32 *ActNameOff = (void*)(0x801162B8 + ((*SMAL)[*currAct].ActorNo << 5));
                SetTextString(
    				a0,
    				"Act %02i: %04hX / %s\nX: %i\nY: %i\nZ: %i\nXR: %i\xb0\nYR: %i\xb0\nZR: %i\xb0\nV: %04hX\n",
                                *currAct,
    				(*SMAL)[*currAct].ActorNo,
	    			*ActNameOff,
	    			(*SMAL)[*currAct].x,
	    			(*SMAL)[*currAct].y,
	    			(*SMAL)[*currAct].z,
	    			(*SMAL)[*currAct].xr/182,
	    			(*SMAL)[*currAct].yr/182,
	    			(*SMAL)[*currAct].zr/182,
	    			(*SMAL)[*currAct].var
    		);
            }

            switch (*actorStatus)
            {
            case SA_POS:
                SetTextString( a0, "Set XYZ pos" );
                break;
            case SA_ROT:
                SetTextString( a0, "Set XYZ rot" );
                break;
            case SA_NUMVAR:
                SetTextString( a0, "Set Number/variable" );
                break;
            case SA_NONE:
                SetTextString( a0, "Actor not found" );
            }
            /* SetTextString( a0, "\nRAM: %08X\n", (*MActRAMI)[*currAct] ); */
            int AP;
            AP = (*MActRAMI)[*currAct];
            if (AP != 0)
            {
                *camera = AP;
                if (*actorStatus = SA_NONE)
                {
                    *actorStatus = SA_POS;
                }
            }
            else
            {
                *camera = 0x802245B0;
                *actorStatus = SA_NONE;
            }
        }
        else if (*status == STAT_OBJ)
        {   
            SetTextString(
			a0,
			"Object mode\nObject %02i: %04hX",
			*currObj,
			*MapObjList[*currObj]
            );
        }
        SetTextString( a0, "\n\nInc amount: %i (%i\xb0)", *inc, *inc/182);
    }

    else if (input->pad == BUTTON_START)
    {
        *status = STAT_ACT;
        *actorFreeze = 1;
        i = 0;
        while (i < *NoActors) /* Reset all actors to original positions/rotations */
        {
            if ((*MActRAMI)[i])
            {
                struct z64_actor_t* Actor;
                Actor = (struct z64_actor_t*)(*MActRAMI)[i];
                Actor->coords_2.x = (f32)(*SMAL)[i].x;
                Actor->coords_2.y = (f32)(*SMAL)[i].y;
                Actor->coords_2.z = (f32)(*SMAL)[i].z;
                AVAL(Actor,s16,0xB8) = (*SMAL)[i].xr;
                AVAL(Actor,s16,0xBA) = (*SMAL)[i].yr;
                AVAL(Actor,s16,0xBC) = (*SMAL)[i].zr;
            }
            i++;
        }
    }
}

void LoadActors(void * a0, void * a1) /* Replaces 0x800985DC */
{
    func800985DC(a0, a1); /* We do this first - it gets data we need. */

    int i	= 0;
    int j	= 0;
    int Actor;
    u8  *NoActorsRam	= (void*)NO_MAP_ACTORS;

    *NoActors	= *NoActorsRam - 1;
    *ActorA1	= (u32)a1;
    *currAct	= 0;

    while (i < 128) /* Check for modified objects */
    {
        if ((int)a1 == (*ModifiedSets)[i].a_addr) /* If true, copy the saved object list over... */
        {
            SavedActorEntry 	(*SavedActorList)[255] = (void*)SAVE_BASE + (*ModifiedSets[i]).ae_addr;
            while (j < (*ModifiedSets[i]).no_actors)
            {
                Actor = (*SavedActorList)[j].Number;
                (**MapActorList)[Actor].ActorNo =	(*SavedActorList)[j].ActorNo;
                (**MapActorList)[Actor].x	=	(*SavedActorList)[j].x;
                (**MapActorList)[Actor].y	=	(*SavedActorList)[j].y;
                (**MapActorList)[Actor].z	=	(*SavedActorList)[j].z;
                (**MapActorList)[Actor].xr	=	(*SavedActorList)[j].xr;
                (**MapActorList)[Actor].yr	=	(*SavedActorList)[j].yr;
                (**MapActorList)[Actor].zr	=	(*SavedActorList)[j].zr;
                (**MapActorList)[Actor].var	=	(*SavedActorList)[j].var;
                j++;
            }
            break;
        }
        if ((*ModifiedSets)[i].a_addr == 0)
        {
            break;
        }
        i++;
    }

    i = 0;
    while (i < *NoActorsRam)
    {
        (*SMAL)[i] = (**MapActorList)[i];
        i++;
    }
}

void LoadObjects(void * a0, void * a1) /* Replaces 0x8009899C */
{
    u8	*MapNoObjects	= (void*)a1+1;			/* Number of objects */
    u32	*MapStart	= (void*)MAP_POINTER;
    u32	*LocalObjPtr	= (void*)((u32)a1+4);
    *MObjLPtr = ((*LocalObjPtr&0xFFFFFF)+*MapStart);
    u16	(*MapObjectList)[*MapNoObjects]	= (void*)*MObjLPtr; /* Offset of objects in RAM*/
    int i = 0;
    int j = 0;
    int Number;
    
    
    *ObjectA1	= (u32)a1;		/* Back up a1 - for saving later */
    *NoObjects	= *MapNoObjects; 	/* Back up the amount of objects */
    *currObj = 0;
    
    while (i < 128) /* Check for modified objects */
    {
        if ((int)a1 == (*ModifiedSets)[i].o_addr) /* If true, copy the saved object list over... */
        {
            ObjectEntry 	(*SavedObjectList)[255] = (void*)SAVE_BASE + (*ModifiedSets[i]).oe_addr;
            while (j < (*ModifiedSets[i]).no_objects)
            {
                (*MapObjectList)[ (*SavedObjectList)[j].Number ] = (*SavedObjectList)[j].Object;
                j++;
            }
            break;
        }
        if ((*ModifiedSets)[i].o_addr == 0)
        {
            break;
        }
        i++;
    }

    i = 0;
    while (i < *MapNoObjects)
    {
        (*MapObjList)[i] = (*MapObjectList)[i];
        i++;
    }
    func8009899C(a0, a1); /* We do this last - as it spawns objects as it reads them, unlike the original actor loading function */
}


void SpawnMapActor(void * a0, void * a1, void * a2) /* Hijack JAL at 800306A8 */
{
    u32 AP;
    struct MapActorEntry *act = (void*)(u32)a1;
    AP = ActorSpawn(	/* 80031F50 */
	(u32)a0,
	(u32)a2,
	act->ActorNo,
	(f32)act->x,
	(f32)act->y,
	(f32)act->z,
	act->xr,
	act->yr,
	act->zr,
	act->var
    );
    (*MActRAMI)[*currAct] = AP;
    *currAct+=1;
    if (*currAct == *NoActors)
    {
        *currAct = 0;
    }
}
