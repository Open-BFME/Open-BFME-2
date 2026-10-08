// ?rva003FDF1B@Rva003FDEAD@@QAEXXZ
// partial score=0.9 date=2026-10-08
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
	char m_pad[0x1C];
	OpaqueRefElement4 m_ref1C;
	OpaqueRefElement4 m_ref20;
	OpaqueRefElement4 m_ref;
};

struct Rva003FDEADParam38
{
	char m_pad[0x20];
	int m_id20;
	char m_pad24[0x54 - 0x24];
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
	void rva003FDF1B();
	void rva003FDF8B();
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

// Rowed tag-4 constructor 0x002DA5D3 uses the same native 0x88-byte
// event prefix as the method above. Preserve its provider declaration.
enum Rva002DA555Id { Rva002DA555Id_Zero = 0 };

struct Rva002DA5D3
{
	Rva002DA5D3(const OpaqueRefElement4 &, int);
	Rva002DA5D3(const OpaqueRefElement4 &, Rva002DA555Id);
	virtual ~Rva002DA5D3();
	AsciiString m_string04;
	BfmePoolRef08 m_pool08;
	int m_int0C;
	BfmePoolRef10 m_pool10;
	int m_int14;
	int m_int18;
	AsciiString m_string1C;
	AsciiString m_string20;
	float m_f24;
	float m_f28;
	float m_f2C;
	int m_int30;
	int m_int34;
	int m_int38;
	BfmeEventPositionView m_position;
	unsigned char m_b48;
	unsigned char m_b49;
	unsigned char m_b4A;
	unsigned char m_b4B;
	unsigned char m_b4C;
	unsigned char m_b4D;
	unsigned char m_b4E;
	unsigned char m_b4F;
	unsigned char m_b50;
	unsigned char m_b51;
	unsigned char m_b52;
	unsigned char m_b53;
	float m_f54;
	float m_f58;
	float m_f5C;
	float m_f60;
	float m_f64;
	int m_int68;
	int m_int6C;
	int m_int70;
	int m_int74;
	int m_int78;
	int m_int7C;
	int m_int80;
	AsciiString m_string84;
};
typedef char VerifyRva002DA5D3Size[(sizeof(Rva002DA5D3) == 0x88) ? 1 : -1];


// Missing shared destructor provider reconciliation: native calls 0x002D9A43.
// Native 0x003FDF1B..0x003FDF8B: receiver +14 block +1C reference;
// +38 object +20 owner ID; +54 value copied into event +70; Audio slot64.
void Rva003FDEAD::rva003FDF1B()
{
    if (m_p14->m_ref1C.referent == 0)
        return;
    if (m_p38 == 0)
        return;
    Rva002DA5D3 event(m_p14->m_ref1C, m_p38->m_id20);
    event.m_int70 = m_p38->m_val54;
    reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(reinterpret_cast<BfmeAudioEventPrefix136 *>(&event));
}

// Native 0x003FDF8B..0x003FDFFB differs only in the block reference at +20.
void Rva003FDEAD::rva003FDF8B()
{
    if (m_p14->m_ref20.referent == 0)
        return;
    if (m_p38 == 0)
        return;
    Rva002DA5D3 event(m_p14->m_ref20, m_p38->m_id20);
    event.m_int70 = m_p38->m_val54;
    reinterpret_cast<Rva003FDEADAudioView *>(TheAudio)->addAudioEvent(reinterpret_cast<BfmeAudioEventPrefix136 *>(&event));
}
