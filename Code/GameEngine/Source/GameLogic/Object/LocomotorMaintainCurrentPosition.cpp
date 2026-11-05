// cl: /MD /DNDEBUG /ICode/Libraries/Include
// Locomotor::locoUpdate_maintainCurrentPosition, native 1E84E5..1E86D0:
// 455 bytes of instructions and a nine-entry switch table. WorldBuilder
// AEF4D0 names the method and confirms the transform save/restore, flag clears
// and maintain-position lifecycle. Pinned BFME1 a7c38d3b Locomotor.cpp provides
// the appearance dispatch and wings/height-worker semantics; BFME2 removes
// the Physics argument and changes the appearance enum and model conditions.
#include "Lib/Coord3D.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

#include "../../Common/Thing/thing.h"
class Object {
public:
 void rva0028AE6D();
 __forceinline bool hasCondition(unsigned bit) const {return (condition[bit>>5]&(1U<<(bit&31)))!=0;}
 __forceinline void clearCondition(unsigned bit) {
  unsigned mask=1U<<(bit&31);
  if(condition[bit>>5]&mask) {condition[bit>>5]&=~mask;rva0028AE6D();}
 }
 char unknown00[8]; Matrix3D transform; Coord3D position;
 char unknown44[0x10C-0x44]; unsigned condition[19];
 char unknown158[0x25C-0x158]; void *physics;
};
class Rva001E6516
{
public:
	void rva001E6516(Object *obj);
};
struct MaintainTemplate {char unknown[0x74];int appearance;};
class Locomotor {
public:
 bool rva001E7ECA(Object*,const Coord3D*);
 bool locoUpdate_maintainCurrentPosition(Object*);
 __forceinline bool getFlag(unsigned bit) const {return (flags&(1U<<bit))!=0;}
protected:
 void maintainCurrentPositionWings(Object*);
private:
 void *unknown0; MaintainTemplate *parameters; Coord3D maintainPos;
 char unknown14[0x40-0x14]; float speed; unsigned flags;
 char unknown48[0x68-0x48]; Matrix3D savedTransform; bool unknown98;
};
bool Locomotor::locoUpdate_maintainCurrentPosition(Object *obj)
{
 if(!obj) return false;
 Matrix3D *dst=&savedTransform;
 dst->Row[0].X=obj->transform.Row[0].X; dst->Row[0].Y=obj->transform.Row[0].Y; dst->Row[0].Z=obj->transform.Row[0].Z; dst->Row[0].W=obj->transform.Row[0].W; dst->Row[1].X=obj->transform.Row[1].X; dst->Row[1].Y=obj->transform.Row[1].Y; dst->Row[1].Z=obj->transform.Row[1].Z; dst->Row[1].W=obj->transform.Row[1].W; dst->Row[2].X=obj->transform.Row[2].X; dst->Row[2].Y=obj->transform.Row[2].Y; dst->Row[2].Z=obj->transform.Row[2].Z; dst->Row[2].W=obj->transform.Row[2].W;
 if(!getFlag(2)) {maintainPos=obj->position;flags|=4;}
 if(!obj->hasCondition(61)) {
  obj->clearCondition(133); obj->clearCondition(134);
  obj->clearCondition(137); obj->clearCondition(138);
  obj->clearCondition(135); obj->clearCondition(136);
  obj->clearCondition(131);
 }
 flags&=~1U;
 unknown98=false;
 if(!obj->physics) return true;
 bool requiresConstantCalling=true; // assume the worst.
 switch(parameters->appearance) {
 case 0: case 4: case 7:
  speed=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 1:
  speed=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 6:
  speed=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 8:
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 2: case 5:
  speed=0.0f; requiresConstantCalling=true;break;
 case 3:
  maintainCurrentPositionWings(obj);requiresConstantCalling=true;break;
 default:
  speed=0.0f;((Rva001E6516*)this)->rva001E6516(obj);requiresConstantCalling=true;break;
 }
 // but we do need to do this even if not moving, for hovering/Thrusting things.
 if(rva001E7ECA(obj,&maintainPos)) requiresConstantCalling=true;
 ((Thing*)obj)->setTransformMatrix(&savedTransform);
 return requiresConstantCalling;
}
