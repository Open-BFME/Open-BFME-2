// ?rva0045A447@AutoAbilityBehavior@@QAEPAVObject@@PAVBfmeWideResult@@PBVCommandButton@@@Z
// partial score=0.97 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc
// Reference guide: Open-BFME-1 f98983a7d AutoAbilityBehavior_bfmeCanAutoFire.cpp
// (clean125B predicate). Target0045A57C/WB117C610 adds module-status mask,
// target model/status gates, tri-state eligibility and button exclusion mask.
// Fields below come from native accesses; donor semantics do not establish
// original BFME2 method names.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
namespace _STL { template<unsigned int N> class _Base_bitset {
public: bool _M_is_any() const; unsigned int words[N];
}; }
class Rva00331682Holder { public: bool test(const void*) const; };
class Rva00263546 { public: bool rva00263546(const Rva00263546*) const; };
class AIUpdateInterface { public: char data00[0x34]; void *active; };
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
class ControlBar { public: const CommandButton *findCommandButton(const AsciiString&); };
extern ControlBar *TheControlBar;
struct AutoAbilityData {
 char data00[0xC]; float minimumRange;
 char data10[0x1C-0x10]; _STL::_Base_bitset<4> forbiddenStatus;
 char data2C[0x5F-0x2C]; bool allowSelf;
};
class BfmeWideResult { public: Object *next(); };
class AutoAbilityBehavior {
public:
 bool rva0045A57C();
 Object *rva0045A447(BfmeWideResult*,const CommandButton*);
 char data00[4]; const AutoAbilityData *data; Object *object;
 char data0C[0x20-0xC]; AsciiString command;
};
Object *AutoAbilityBehavior::rva0045A447(BfmeWideResult *items,const CommandButton *button)
{
 const AutoAbilityData *modData=data;
 Object *owner=object;
 Object *candidate;
 goto nextCandidate;
 for(;;) {
  if(!modData->allowSelf && candidate==owner) goto nextCandidate;
  if(button && button->flag138) {
   BodyModule *body=candidate->body;
   if(body && body->slot14()>0.8f) goto nextCandidate;
  }
  if(modData->minimumRange>0) {
   float x=owner->position.x,y=owner->position.y,z=owner->position.z;
   _ReadWriteBarrier();
   x-=candidate->position.x;y-=candidate->position.y;z-=candidate->position.z;
   _ReadWriteBarrier();
   Coord3D delta;delta.x=x;delta.y=y;delta.z=z;
   if(delta.length()<modData->minimumRange) goto nextCandidate;
  }
  break;
nextCandidate:
  candidate=items->next();
  if(!candidate) return 0;
 }
 return candidate;
}
