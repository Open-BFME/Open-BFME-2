// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva003FDEAD@Rva003FDEAD@@QAEXXZ @0x003FDEAD 110B: __thiscall void method guarding on +0x14 ref and +0x38 then BfmeAudioEventPrefix136(ref 1) plus +0x70 from +0x38->+0x54 then TheAudio addAudioEvent slot 0x64. Evidence: rowed ctor 0x002D97D6 plus rowed dtor 0x002D9A43 plus TheAudio 0x009FE6E8 plus caller 0x003191CA plus sibling Rva003184B8 same slot pattern.
#include "Common/BfmeAudioEventPrefix136.h"

// Native 3FDF1B/3FDF8B/3FDFFB call tag4 ctor2DA5D3 and prefix dtor2D9A43.
// The 0x88-byte aligned storage owns that exact lifetime without a second
// destructor. Only +14 reference slots18/1C/20 and +38 owner20/54 are asserted.
// Original helper names remain unknown; existing home-TU /O2 settings close
// the banked /O1 guard scheduling delta in all three independent bodies.
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

class Rva003FDEADAudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *);
};

struct Rva003FDEADRefBlock
{
	char m_pad[0x10];
	OpaqueRefElement4 ref10, ref14;
	OpaqueRefElement4 ref18, ref1c, ref20;
	OpaqueRefElement4 m_ref;
};

struct Rva003FDEADParam38
{
	char m_pad[0x20];
	int id;
	char m_pad24[0x30];
	int m_val54;
};

class Rva003FDEAD
{
	char m_pad00[0x14];
	Rva003FDEADRefBlock *m_p14;
	char m_pad18[0x20];
	Rva003FDEADParam38 *m_p38;
public:
	void rva003FDEAD();
	void rva003FDD41(int unused0,int unused1,int enabled);
	void rva003FDDAC();
	void rva003FDF1B();
	void rva003FDF8B();
	void rva003FDFFB();
};

void Rva003FDEAD::rva003FDEAD()
{
	if (m_p14->m_ref.referent == 0)
		return;
	if (m_p38 == 0)
		return;
	Rva003FDEADRefBlock *blk = m_p14;
	BfmeAudioEventPrefix136 evt(blk->m_ref, 1);
	evt.m_int70 = m_p38->m_val54;
	reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(&evt);
}

void Rva003FDEAD::rva003FDF1B()
{
	if (!m_p14->ref1c.referent) return;
	if (!m_p38) return;
	Rva003FDEADRefBlock *block=m_p14;
	OwnerAudioEvent003FDF1B event(block->ref1c,m_p38->id);
	event.get()->m_int70=m_p38->m_val54;
	reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(event.get());
}

void Rva003FDEAD::rva003FDF8B()
{
	if (!m_p14->ref20.referent) return;
	if (!m_p38) return;
	Rva003FDEADRefBlock *block=m_p14;
	OwnerAudioEvent003FDF1B event(block->ref20,m_p38->id);
	event.get()->m_int70=m_p38->m_val54;
	reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(event.get());
}

void Rva003FDEAD::rva003FDFFB()
{
	if (!m_p14->ref18.referent) return;
	if (!m_p38) return;
	Rva003FDEADRefBlock *block=m_p14;
	OwnerAudioEvent003FDF1B event(block->ref18,m_p38->id);
	reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(event.get());
}

// Native 3FDD41..3FDDAC: unused first two dword args and nonzero third
// gate the same receiver14 reference block at14; RET12 proves stack ABI.
void Rva003FDEAD::rva003FDD41(int,int,int enabled)
{
 if (enabled && m_p14->ref14.referent && m_p38) {
  Rva003FDEADRefBlock *block=m_p14;
  OwnerAudioEvent003FDF1B event(block->ref14,m_p38->id);
  reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(event.get());
 }
}
class Rva005391A9 {public:void rva005391A9();};
// Native 3FDDAC..3FDE1A: reference10 audio followed unconditionally by
// existing5391A9 on the same receiver, including the failed-guard path.
void Rva003FDEAD::rva003FDDAC()
{
 if (m_p14->ref10.referent && m_p38) {
  Rva003FDEADRefBlock *block=m_p14;
  OwnerAudioEvent003FDF1B event(block->ref10,m_p38->id);
  reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(event.get());
 }
 reinterpret_cast<Rva005391A9 *>(this)->rva005391A9();
}
