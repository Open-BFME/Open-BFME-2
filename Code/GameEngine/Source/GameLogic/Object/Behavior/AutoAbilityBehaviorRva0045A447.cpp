// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0045A447@AutoAbilityBehavior@@QAEPAVObject@@PAUBfmeWideResult@@PBVCommandButton@@@Z
// retail 0x0045A447, 180 bytes. Picks the next object from the wide-result
// iterator that passes the behavior's gates: not the owner itself (unless the
// module data allows it), not a body whose slot-14 health fraction exceeds 0.8
// when the command button wants wounded targets, and not nearer than the module
// data's minimum range. Reference guide: Open-BFME-1 AutoAbilityBehavior
// bfmeCanAutoFire (clean 125 B predicate); fields below come from native
// accesses, donor semantics do not establish original BFME2 method names.
// WorldBuilder 0x117D380 keeps the iterator advance as the loop step with the
// null candidate returned from the loop exit; a 'return candidate' inside the
// loop plus 'return 0' after it gives retail's out-of-line success return.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
namespace _STL { template<unsigned int N> class _Base_bitset {
public: bool _M_is_any() const; unsigned int words[N];
}; }
class Rva00263546 { public: bool rva00263546(const Rva00263546*) const; };
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
class BodyModule { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual float slot14();
};
class CommandButton;
enum ObjectStatusTypes { AutoAbilityStatus74=74 };
class Object {
public:
 bool rva002922D9(const CommandButton*);
 int rva0028F4EF();
 bool testStatus(ObjectStatusTypes) const;
 char data00[0x38]; Coord3D position;
 char data44[0x94-0x44]; unsigned int status[4];
 char dataA4[0x10C-0xA4]; unsigned int model[19];
 char data158[0x254-0x158]; BodyModule *body;
 AIUpdateInterface *ai;
};
class CommandButton {
public:
 bool isReady(const Object*) const;
 char data00[0x134]; float range;
 bool flag138;
 char data139[3]; Rva00263546 exclude;
};
struct AutoAbilityData {
 char data00[0xC]; float minimumRange;
 char data10[0x1C-0x10]; _STL::_Base_bitset<4> forbiddenStatus;
 char data2C[0x5F-0x2C]; bool allowSelf;
};
class AutoAbilityBehavior {
public:
 Object *rva0045A447(BfmeWideResult*,const CommandButton*);
 char data00[4]; const AutoAbilityData *data; Object *object;
 char data0C[0x20-0xC]; AsciiString command;
};
Object *AutoAbilityBehavior::rva0045A447(BfmeWideResult *items,const CommandButton *button)
{
 const AutoAbilityData *modData=data;
 Object *owner=object;
 Object *candidate;
 for(candidate=items->next();candidate;candidate=items->next()) {
  if(!modData->allowSelf && candidate==owner) continue;
  if(button && button->flag138) {
   BodyModule *body=candidate->body;
   if(body && body->slot14()>0.8f) continue;
  }
  if(modData->minimumRange>0) {
   float x=owner->position.x,y=owner->position.y,z=owner->position.z;
   _ReadWriteBarrier();
   x-=candidate->position.x;y-=candidate->position.y;z-=candidate->position.z;
   _ReadWriteBarrier();
   Coord3D delta;delta.x=x;delta.y=y;delta.z=z;
   if(delta.length()<modData->minimumRange) continue;
  }
  return candidate;
 }
 return 0;
}

