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

#include "../../Include/Common/GameAudio.h"

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
