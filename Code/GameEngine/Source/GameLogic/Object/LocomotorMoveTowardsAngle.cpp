// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// ?locoUpdate_moveTowardsAngle@Locomotor@@QAEXPAVObject@@M@Z
// Retail 0x001EA0F4..0x001EA2CF (475 bytes; RET 8).
// Reference: Zero Hour GeneralsMD Locomotor.cpp locoUpdate_moveTowardsAngle
// in BFME1 revision 575ba2b04. Its angle-turn/min-speed branches provide
// the semantic guide. Target evidence establishes the matrix bit-copy at
// Object+8 to Locomotor+0x68, template+4/turn limit+0x84, orientation+0x44,
// Object position+0x38, and the nullable interface at +0x250. The interface
// and transaction slot meanings are unproven and retain neutral names.
// BFME2's transaction calls and two-argument Z worker differ from ZH.
// Volatile orientation preserves retail's separate SSE load; the barrier
// after matrix word +0x10 places the goal-angle load at retail's position.
#include "Lib/Coord3D.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Matrix3D;
class Object;
class Thing;
struct Rva001E4194A;
bool __stdcall Rva001E4194Get(Rva001E4194A *);
float normalizeAngle(float);
float Cos(float);float Sin(float);
class Matrix3D {public:unsigned v00,v04,v08,v0C,v10,v14,v18,v1C,v20,v24,v28,v2C;__forceinline void set(const Matrix3D &m){v00=m.v00;v04=m.v04;v08=m.v08;v0C=m.v0C;v10=m.v10;_ReadWriteBarrier();v14=m.v14;v18=m.v18;v1C=m.v1C;v20=m.v20;v24=m.v24;v28=m.v28;v2C=m.v2C;}};
class Rva001EA0F4Transaction { public:
virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual void s34();virtual void s38();virtual void s3C();virtual void s40();
};
class Rva001EA0F4Interface250 { public:
virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual void s34();virtual void s38();virtual void s3C();virtual void s40();virtual void s44();virtual void s48();virtual void s4C();virtual void s50();virtual void s54();virtual void s58();virtual void s5C();virtual void s60();virtual void s64();virtual void s68();virtual void s6C();virtual void s70();virtual void s74();virtual void s78();virtual Rva001EA0F4Transaction *s7C();
};
class Object {public:char pad[8]; Matrix3D matrix;Coord3D pos;float orientation;char pad48[0x250-0x48];Rva001EA0F4Interface250 *interface250;};
class Rva0030A3E4 {public:void rva0030A3E4(const Matrix3D *);};
struct Rva001E3F08Arg;
class Rva001E3F08 {public:float rva001E3F08(Rva001E3F08Arg *);};
class Rva001E702E {public:void rva001E702E(Thing *,int,int);};
class Rva001E46E1 {public:void rva001E9083(Object *,const Coord3D *,float,float);bool rva001E7ECA(Object *,const Coord3D *);};
struct LocomotorData {char pad[0x84];float turnLimit;};
class Locomotor {public:
 void locoUpdate_moveTowardsAngle(Object *,float);
 void rva001E41FA(float);
 char pad[4];const LocomotorData *data;char pad08[0x44-8];unsigned flags;char pad48[0x68-0x48];Matrix3D matrix;
};
void Locomotor::locoUpdate_moveTowardsAngle(Object *obj,float goalAngle)
{
 flags &=~4U;
 if(!obj||!data)return;
 if(Rva001E4194Get((Rva001E4194A *)obj))return;
 matrix.set(obj->matrix);
 float relative=normalizeAngle(goalAngle-*(volatile float*)&obj->orientation);
 float limit=data->turnLimit;
 float cosine=Cos(relative);
 if(cosine<Cos(limit)) {
  Rva001EA0F4Interface250 *iface=obj->interface250;
  Rva001EA0F4Transaction *transaction=iface?iface->s7C():0;
  if(transaction){transaction->s3C();rva001E41FA(goalAngle);((Rva0030A3E4*)obj)->rva0030A3E4(&matrix);transaction->s40();}
 }
 float minSpeed=((Rva001E3F08*)this)->rva001E3F08((Rva001E3F08Arg*)obj);
 if(minSpeed>0) {
  Coord3D desired;desired.x=obj->pos.x;desired.y=obj->pos.y;desired.z=obj->pos.z;
  desired.x+=Cos(goalAngle)*minSpeed*2;
  desired.y+=Sin(goalAngle)*minSpeed*2;
  ((Rva001E46E1*)this)->rva001E9083(obj,&desired,99999.0f,minSpeed);
 } else {
  const Coord3D *position=&obj->pos;Coord3D desired;desired.x=position->x;desired.y=position->y;desired.z=position->z;
  desired.x+=Cos(goalAngle)*1000.0f;
  desired.y+=Sin(goalAngle)*1000.0f;
  ((Rva001E702E*)this)->rva001E702E((Thing*)obj,(int)&desired,0);
  ((Rva001E46E1*)this)->rva001E7ECA(obj,position);
 }
}
