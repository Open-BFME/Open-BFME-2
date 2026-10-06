// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// ?rva004A9E3E@Rva004A9E3E@@QAEXPAUAudioEventRTS@@H@Z @0x004A9E3E 123B.
// Dozer slot 23. A null referent at arg+4 returns immediately. Otherwise
// slot 24 runs first, then an 0x88 BfmeAudioEventPrefix136 is built from
// that field and 0, CondSetter 0x002D9531 takes the int, TheAudio slot
// 0x64 submits it, and the handle lands at this+0xE8.

#include "Common/BfmeAudioEventPrefix136.h"

class Rva002D9531
{
public:
	void rva002D9531(int v);
};

class AudioManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual int v25(BfmeAudioEventPrefix136 *p);
};

extern AudioManager *TheAudio;

struct AudioEventRTS
{
	int m_lead;
	OpaqueRefElement4 m_ref;
};

class Rva004A9E3E
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void finish();
	void rva004A9E3E(const AudioEventRTS *ev, int id);

private:
	char m_pad[0xE4];
	int m_e8;
};

void Rva004A9E3E::rva004A9E3E(const AudioEventRTS *ev, int id)
{
	const OpaqueRefElement4 *ref =
		(const OpaqueRefElement4 *)((const char *)ev + 4);
	if (ref->referent == 0)
		return;
	finish();
	BfmeAudioEventPrefix136 tmp(*ref, 0);
	((Rva002D9531 *)&tmp)->rva002D9531(id);
	m_e8 = TheAudio->v25(&tmp);
}
