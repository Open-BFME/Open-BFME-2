// ?rva001E84E5@Rva001E46E1@@QAE_NPAVObject@@@Z
// partial score=0.6643949902226793 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference Locomotor::locoUpdate_maintainCurrentPosition guides purpose;
// all offsets and BFME2 movement-type dispatch below read independently from
// native001E84E5..001E86D0 (including nine-entry dispatch table).
#include "Lib/Coord3D.h"
#include "matrix3d.h"
class Thing {public:void setTransformMatrix(const Matrix3D*);};
struct ModelFlags {unsigned words[19];bool test(int x)const{return (words[x>>5]&(1u<<(x&31)))!=0;}void clear(int x){words[x>>5]&=~(1u<<(x&31));}};
class Object {public:char pad0[8];Matrix3D matrix;Coord3D position;char pad44[0x10c-0x44];ModelFlags modelFlags;char pad158[0x25c-0x158];void*physics;void rva0028AE6D();__forceinline void clearFlag(int n){if(modelFlags.test(n)){modelFlags.clear(n);rva0028AE6D();}}};
class Rva001E6516 {public:void rva001E6516(Object*);};
class Rva001E7CDF {public:void rva001E7CDF(Object*);};
struct Rva001E46E1Data {char pad0[0x74];int appearance;};
class Rva001E46E1 {public:bool rva001E84E5(Object*);bool rva001E7ECA(Object*,const Coord3D*);void*vptr;const Rva001E46E1Data*data;Coord3D maintain;char pad14[0x40-0x14];float speed;unsigned flags;char pad48[0x68-0x48];Matrix3D matrix;unsigned char state98;};
bool Rva001E46E1::rva001E84E5(Object*obj)
{
 if(!obj)return false;
 const Matrix3D*transform=&matrix;
 matrix=obj->matrix;
 if(!(flags&4)){maintain=obj->position;flags|=4;}
 if(!obj->modelFlags.test(61)){
  obj->clearFlag(133);obj->clearFlag(134);obj->clearFlag(137);obj->clearFlag(138);obj->clearFlag(135);obj->clearFlag(136);obj->clearFlag(131);
 }
 flags&=~1u;state98=0;
 if(!obj->physics)return true;
 bool calling=true;
 switch(data->appearance){
 case 0:case 1:case 4:case 6:case 7:
  speed=0;
 case 8:
  ((Rva001E6516*)this)->rva001E6516(obj);calling=false;break;
 case 2:case 5:speed=0;calling=true;break;
 case 3:((Rva001E7CDF*)this)->rva001E7CDF(obj);calling=true;break;
 default:speed=0;((Rva001E6516*)this)->rva001E6516(obj);calling=true;break;
 }
 if(rva001E7ECA(obj,&maintain))calling=true;
 ((Thing*)obj)->setTransformMatrix(transform);
 return calling;
}
