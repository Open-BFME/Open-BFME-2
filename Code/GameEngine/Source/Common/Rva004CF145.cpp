// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /EHsc
// ?Rva004CF145@@YAXXZ @0x004CF145 104B. Audio event via TheAudio slot 78 (+0x138, getMiscAudio).
// Evidence: TheAudio 0x009FE6E8 plus rowed BfmeAudioEventPrefix136 ctor 0x002D97D6
// plus AudioManager slots 0x64 addAudioEvent 0x138 provider plus rowed
// BfmeStringTailRecord144 dtor 0x002D9A43; callers 0x004D11C5 0x004D1231 0x004D14B9.
#include "Common/BfmeAudioEventPrefix136.h"

#include "Common/GameAudio.h"
#include "Common/MiscAudioClass.h"

extern AudioManager *TheAudio;

void __cdecl Rva004CF145()
{
	if (TheAudio == 0)
		return;
	const MiscAudio *info = TheAudio->getMiscAudio();
	if (info == 0)
		return;
	BfmeAudioEventPrefix136 ev(info->m_74, 0);
	TheAudio->addAudioEvent(&ev);
}
