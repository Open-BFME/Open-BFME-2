// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva003FDEAD@Rva003FDEAD@@QAEXXZ @0x003FDEAD 110B: __thiscall void method guarding on +0x14 ref and +0x38 then BfmeAudioEventPrefix136(ref 1) plus +0x70 from +0x38->+0x54 then TheAudio addAudioEvent slot 0x64. Evidence: rowed ctor 0x002D97D6 plus rowed dtor 0x002D9A43 plus TheAudio 0x009FE6E8 plus caller 0x003191CA plus sibling Rva003184B8 same slot pattern.
#include "Common/BfmeAudioEventPrefix136.h"

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
	char m_pad[0x24];
	OpaqueRefElement4 m_ref;
};

struct Rva003FDEADParam38
{
	char m_pad[0x54];
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
