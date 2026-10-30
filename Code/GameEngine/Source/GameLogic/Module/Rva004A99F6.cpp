// cl: /DNDEBUG /MD /EHsc
// ?rva004A99F6@Rva004A99F6@@QAEXXZ @0x004A99F6 28B: thiscall method passing member +0xE8 to TheAudio slot 0x6C virtual then setting it to 1.
// Evidence: unlock lane; caller 0x004A9A12; TheAudio extern in use ?TheAudio@@3PAVAudioManager@@A; vtable slot 0x6C index 27; member +0xE8 proved by lea and push then dword store of 1.
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

class Rva004A99F6
{
public:
	void rva004A99F6();
private:
	char m_pad[0xE8];
	int m_e8;
};

void Rva004A99F6::rva004A99F6()
{
	TheAudio->removeAudioEvent(m_e8);
	m_e8 = 1;
}
