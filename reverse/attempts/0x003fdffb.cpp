// ?rva003FDFFB@Rva003FDEAD@@QAEXXZ
// partial score=0.96 date=2026-10-08
// cl: /O1 /G7 /Oy- /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// Native callers211C68 and WB10737B0/10738A0/1073990 establish the
// receiver's14 reference block and38 army owner. Rva003FDEAD is the existing
// partial receiver spelling; the original three helper names are unknown.
// This aligned88-byte lifetime owner delegates construction to the already
// rowed tag4 provider2DA5D3 and cleanup to the canonical prefix destructor,
// whose existing verified binding reaches2D9A43. Its qualified destructor
// call is direct, as in all three complete retail bodies. No new alias or
// pin is needed. Flat reference slots are four-byte pointer ABI projections.
#include "Common/BfmeAudioEventPrefix136.h"
struct Rva002DA5D3 { Rva002DA5D3(const OpaqueRefElement4&,int); };
union EventStorage003FDF1B { int align; unsigned char bytes[0x88]; };
class OwnerAudioEvent003FDF1B {
 EventStorage003FDF1B storage;
public:
 __forceinline OwnerAudioEvent003FDF1B(const OpaqueRefElement4 &ref,int id) {
  ((Rva002DA5D3*)&storage)->Rva002DA5D3::Rva002DA5D3(ref,id);
 }
 __forceinline ~OwnerAudioEvent003FDF1B() {
  ((BfmeAudioEventPrefix136*)&storage)->BfmeAudioEventPrefix136::~BfmeAudioEventPrefix136();
 }
 __forceinline BfmeAudioEventPrefix136 *get() {return (BfmeAudioEventPrefix136*)&storage;}
};
class AudioManager;
extern AudioManager *TheAudio;
class ArmyAudioView003FDF1B {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
 SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21)
 SLOT(22) SLOT(23) SLOT(24)
#undef SLOT
 virtual int addAudioEvent(const BfmeAudioEventPrefix136*);
};
struct ArmyAudioRefs003FDF1B {
 char unknown00[0x18];
 OpaqueRefCounted *ref18,*ref1c,*ref20;
};
struct ArmyAudioOwner003FDF1B {
 char unknown00[0x20];
 int id;
 char unknown24[0x30];
 int player;
};
class Rva003FDEAD {
 char unknown00[0x14];
 ArmyAudioRefs003FDF1B *refs;
 char unknown18[0x20];
 ArmyAudioOwner003FDF1B *owner;
public:
 void rva003FDF1B();
 void rva003FDF8B();
 void rva003FDFFB();
};
void Rva003FDEAD::rva003FDF1B()
{
 const ArmyAudioRefs003FDF1B *block=refs;
 if(block->ref1c && owner) {
  OwnerAudioEvent003FDF1B event(*(const OpaqueRefElement4*)&block->ref1c,owner->id);
  event.get()->m_int70=owner->player;
  ((ArmyAudioView003FDF1B*)TheAudio)->addAudioEvent(event.get());
 }
}
void Rva003FDEAD::rva003FDF8B()
{
 if(refs->ref20 && owner) {
  OwnerAudioEvent003FDF1B event(*(const OpaqueRefElement4*)&refs->ref20,owner->id);
  event.get()->m_int70=owner->player;
  ((ArmyAudioView003FDF1B*)TheAudio)->addAudioEvent(event.get());
 }
}
void Rva003FDEAD::rva003FDFFB()
{
 if(refs->ref18 && owner) {
  OwnerAudioEvent003FDF1B event(*(const OpaqueRefElement4*)&refs->ref18,owner->id);
  ((ArmyAudioView003FDF1B*)TheAudio)->addAudioEvent(event.get());
 }
}
