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

struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct AbilityMiscAudio;
class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	// vslot 25 (+0x64)
	virtual int addAudioEvent(BfmeAudioEventPrefix136 *event) = 0;
	virtual void _pad26() = 0;
	// vslot 27 (+0x6C)
	virtual void removeAudioEvent(unsigned int handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	// vslot 52 (+0xD0)
	virtual bool isCurrentlyPlaying(int handle) = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	// vslot 78 (+0x138)
	virtual AbilityMiscAudio * getMiscAudio() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	// vslot 88 (+0x160)
	virtual void xferAudioHandle(Xfer *xfer, unsigned int *handle) = 0;
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
	m_e8 = TheAudio->addAudioEvent(&tmp);
}
