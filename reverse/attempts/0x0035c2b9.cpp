// ?rva0035C2B9@Shell@@QAEXXZ
// partial score=0.98 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
// ?rva0035C2B9@Shell@@QAEXXZ retail 0x0035C2B9 266 bytes.
// Shell music update: +0x6c gate then TheAudio slotD0 on +0x68 handle then +0x6d clear then slot138 base plus 0x8c or 0x90 via TheWritableGlobalData +0xaf0 into OpaqueRef copy then slot8C triple then BfmeAudioEventPrefix136 ctor plus rva002D94CE 2 then slot64 addAudioEvent storing handle. Evidence: callers 0x0035C566 0x00514FE9 0x0051511D; callees 0x00239099 0x002D97D6 0x002D94CE 0x002D9A43 0x00050ED3 rowed; neighbours ShellTop prev 0x0035C16A next 0x0035C3C3.
#include "Common/BfmeAudioEventPrefix136.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AudioManager
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
	virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09();
	virtual void slot28();
	virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20();
	virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *ev);
	virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30();
	virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34();
	virtual void slot8C(int a, int b, int c);
	virtual void q36(); virtual void q37(); virtual void q38(); virtual void q39(); virtual void q40();
	virtual void q41(); virtual void q42(); virtual void q43(); virtual void q44(); virtual void q45();
	virtual void q46(); virtual void q47(); virtual void q48(); virtual void q49(); virtual void q50();
	virtual void q51();
	virtual bool slotD0(unsigned int handle);
	virtual void r53(); virtual void r54(); virtual void r55(); virtual void r56(); virtual void r57();
	virtual void r58(); virtual void r59(); virtual void r60(); virtual void r61(); virtual void r62();
	virtual void r63(); virtual void r64(); virtual void r65(); virtual void r66(); virtual void r67();
	virtual void r68(); virtual void r69(); virtual void r70(); virtual void r71(); virtual void r72();
	virtual void r73(); virtual void r74(); virtual void r75(); virtual void r76(); virtual void r77();
	virtual void *slot138();
};

extern AudioManager *TheAudio;

class GlobalData
{
public:
	unsigned char m_pad[0xAF0];
	bool m_af0;
};

extern GlobalData *TheWritableGlobalData;

class Rva002D94CE
{
public:
	void rva002D94CE(int value);
	char m_pad[0x30];
	int m_value;
};

struct TmpRef : public OpaqueRefElement4
{
	TmpRef() { referent = 0; }
	~TmpRef() { if (referent) referent->Release_Ref(); }
};

class Shell
{
public:
	void rva0035C2B9();
private:
	unsigned char m_pad00[0x68];
	unsigned int m_musicHandle;
	bool m_6c;
	bool m_6d;
};

// ?rva0035C2B9@Shell@@QAEXXZ present-unmatched
void Shell::rva0035C2B9()
{
	if (!m_6c)
		return;
	if (TheAudio == 0)
		return;
	if (TheAudio->slotD0(m_musicHandle))
		return;
	if (m_6d) {
		m_6d = false;
		return;
	}
	void *base = TheAudio->slot138();
	if (base == 0)
		return;
	TmpRef tmp;
	OpaqueRefElement4 *src;
	if (TheWritableGlobalData != 0 && !TheWritableGlobalData->m_af0)
		src = (OpaqueRefElement4 *)((char *)base + 0x8C);
	else
		src = (OpaqueRefElement4 *)((char *)base + 0x90);
	((OpaqueRefElement4 &)tmp).operator=(*src);
	if (tmp.referent != 0) {
		TheAudio->slot8C(2, 1, 0);
		BfmeAudioEventPrefix136 evt(tmp, 0);
		((Rva002D94CE *)&evt)->rva002D94CE(2);
		m_musicHandle = TheAudio->addAudioEvent(&evt);
	}
}
