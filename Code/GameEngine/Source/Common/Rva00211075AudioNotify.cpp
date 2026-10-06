// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva00211075@Rva00211075@@QAEXXZ @ 0x00211075 (106B): set flag then post audio event via TheAudio.
// Evidence: ret no args thiscall reads ecx; byte [ecx+0x2c0]=1; TheAudio null gate 0x009FE6E8;
// OpaqueRefElement4 at +0x164 null gate then BfmeAudioEventPrefix136 ctor 0x002D97D6 with 1;
// AudioManager slot 0x64 addAudioEvent; dtor 0x002D9A43; EH prolog; caller 0x002BE8F9 unclaimed.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva00211075AudioView
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
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *);
};

class Rva00211075
{
	char _pad0[0x164];
	OpaqueRefElement4 m_elem164;
	char _pad1[0x158];
	bool m_flag2c0;
public:
	void rva00211075();
};

void Rva00211075::rva00211075()
{
	m_flag2c0 = true;
	if (TheAudio == 0)
		return;
	OpaqueRefElement4 *p = &m_elem164;
	if (p->referent == 0)
		return;
	BfmeAudioEventPrefix136 event(*p, 1);
	reinterpret_cast<Rva00211075AudioView *>(TheAudio)->addAudioEvent(&event);
}
