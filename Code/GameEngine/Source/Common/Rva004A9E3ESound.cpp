// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// ?rva004A9E3E@Rva004A9E3E@@QAEXPAUAudioEventRTS@@H@Z @0x004A9E3E 123B.
// Dozer slot 23. A null referent at arg+4 returns immediately. Otherwise
// slot 24 runs first, then an 0x88 BfmeAudioEventPrefix136 is built from
// that field and 0, CondSetter 0x002D9531 takes the int, TheAudio slot
// 0x64 submits it, and the handle lands at this+0xE8.

#include "Common/BfmeAudioEventPrefix136.h"

#include "../../Include/GameLogic/Module/Rva002D9531.h"

struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct AbilityMiscAudio;
#include "../../Include/Common/GameAudio.h"

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
	m_e8 = TheAudio->addAudioEvent(&tmp);
}
