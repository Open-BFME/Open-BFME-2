// cl: /MD
//
// ?rva00318BEB@Rva00318BEB@@QAEXXZ, retail 0x00318BEB, 26 bytes.
// If TheAudio (0x00DFE6E8) is present and the +0x60 handle is not 1
// (AHSV_NoSound) calls AudioManager slot 0x6c removeAudioEvent with it.
// Caller is FUN_00719D01 at 0x00319D3B with the same this. Precedent is
// Rva002714CALoop/FoundationAIUpdateSlot14; TheAudio absolute idiom copied
// from FlammableUpdateXfer.cpp. Identity beyond the handle is unproven so
// the name stays honest address-derived.

typedef unsigned int AudioHandle;

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
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern class AudioManager *TheAudio;

class Rva00318BEB
{
public:
	void rva00318BEB();
private:
	unsigned char m_pre[0x60];
	AudioHandle m_60;
};

void Rva00318BEB::rva00318BEB()
{
	AudioManager *audio = TheAudio;
	if (audio == 0)
		return;
	AudioHandle h = m_60;
	if (h == 1)
		return;
	audio->removeAudioEvent(h);
}
