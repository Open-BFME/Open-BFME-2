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
#include "../../../Include/GameLogic/LocomotorClass.h"
#include "../../../Include/GameLogic/LocomotorTemplate.h"
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
bool Locomotor::locoUpdate_maintainCurrentPosition(Object *obj)
{
 if(!obj) return false;
 Matrix3D *dst=&m_68;
 dst->Row[0].X=obj->transform.Row[0].X; dst->Row[0].Y=obj->transform.Row[0].Y; dst->Row[0].Z=obj->transform.Row[0].Z; dst->Row[0].W=obj->transform.Row[0].W; dst->Row[1].X=obj->transform.Row[1].X; dst->Row[1].Y=obj->transform.Row[1].Y; dst->Row[1].Z=obj->transform.Row[1].Z; dst->Row[1].W=obj->transform.Row[1].W; dst->Row[2].X=obj->transform.Row[2].X; dst->Row[2].Y=obj->transform.Row[2].Y; dst->Row[2].Z=obj->transform.Row[2].Z; dst->Row[2].W=obj->transform.Row[2].W;
 if(!getFlag(MAINTAIN_POS_IS_VALID)) {m_maintainPos=obj->position;m_flags|=(1<<MAINTAIN_POS_IS_VALID);}
 if(!obj->hasCondition(61)) {
  obj->clearCondition(133); obj->clearCondition(134);
  obj->clearCondition(137); obj->clearCondition(138);
  obj->clearCondition(135); obj->clearCondition(136);
  obj->clearCondition(131);
 }
 m_flags&=~(1U<<IS_BRAKING);
 m_98=false;
 if(!obj->physics) return true;
 bool requiresConstantCalling=true; // assume the worst.
 switch(m_template->m_appearance) {
 case 0: case 4: case 7:
  m_40=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 1:
  m_40=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 6:
  m_40=0.0f;
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 8:
  ((Rva001E6516*)this)->rva001E6516(obj);
  requiresConstantCalling=false;break;
 case 2: case 5:
  m_40=0.0f; requiresConstantCalling=true;break;
 case 3:
  maintainCurrentPositionWings(obj);requiresConstantCalling=true;break;
 default:
  m_40=0.0f;((Rva001E6516*)this)->rva001E6516(obj);requiresConstantCalling=true;break;
 }
 // but we do need to do this even if not moving, for hovering/Thrusting things.
 if(rva001E7ECA(obj,&m_maintainPos)) requiresConstantCalling=true;
 ((Thing*)obj)->setTransformMatrix(&m_68);
 return requiresConstantCalling;
}
