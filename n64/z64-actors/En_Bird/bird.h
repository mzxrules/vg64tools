#ifndef __Z_EN_BIRD_H__
#define __Z_EN_BIRD_H__

extern void En_Bird_f1 ( void *, void * );
extern void En_Bird_f2 ( void *, void * );
extern void En_Bird_f3 ( void *, void * );
extern void En_Bird_f4 ( void *, void * );
extern void En_Bird_f5 ( void *, void * );
extern void En_Bird_f6 ( void *, u16 );
extern void En_Bird_f7 ( void *, void * );
extern void En_Bird_f8 ( void *, void * );
extern void En_Bird_f9 ( void *, void * );

extern u32 En_Bird_dat1[];

extern void func_800780DC( void *, u32 * );
extern void func_8002D62C( struct z64_actor_old_t *, u32 );
extern void func_800A457C( u32*, struct z64_actor_old_t *, u32 hierarchy, u32 animation, u32, u32, u32 );
extern void func_8002B1E0( struct z64_actor_old_t *, u32, u32, u32 );
extern /*void*/u32 func_800A2000( u32 animation );
extern u32 func_80077D90( int, int );
extern void func_800A51A0(
	struct z64_actor_old_t *,
	u32 animation,
	u32,
	u32,
	f32,
	u32,
	u32
); /* FIXME: Dunno which args are floats and which are not temporairy hack will treat them all as u32s*/
extern f32  func_80100290( f32 );
extern void func_80078310( struct z64_actor_t *, f32, u32, f32, f32 );
extern void func_800A49FC( struct z64_actor_t * );
extern u32  func_80078068( u32, u32);
extern void func_80077B58( u32, u32, u16 );
extern void func_800A15C8( void *, u32, u32, u32, u32, u32 );

#endif /* __Z_EN_BIRD_H__ */

