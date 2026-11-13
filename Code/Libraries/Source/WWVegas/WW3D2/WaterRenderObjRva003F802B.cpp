// cl: /MD
//
// ?rva003F802B@Rva003F802B@@QAE_NXZ @0x003F802B 39B.
// Predicate on +8/+0xC gated by TheAudio vtable slot 0xD0.
// Evidence: cmp [ecx+8] 0 je false; cmp [ecx+0xC] 5 jb false;
// TheAudio ?TheAudio@@3PAVAudioManager@@A; call [edx+0xD0] push int test al;
// callers at 0x003F847B 0x003F8F97.
#include "../../../../GameEngine/Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

#include "../../../../GameEngine/Include/Common/Rva003F802B.h"

bool Rva003F802B::rva003F802B()
{
	if (m_08 && (unsigned int)m_0C >= 5 && TheAudio->isCurrentlyPlaying(m_0C))
		return true;
	return false;
}

// Address-derived name: Rva003F8052 (21B, retail 0x003F8052). Null-guarded
// negated call to the 0x003F7D29 grid predicate through the pointer at +0x14.
class Rva003F7D29
{
public:
	unsigned char rva003F7D29();
};

class Rva003F8052
{
public:
	bool rva003F8052();
private:
	char m_pad00[0x14];
	Rva003F7D29 *m_14;
};

bool Rva003F8052::rva003F8052()
{
	Rva003F7D29 *p = m_14;
	if (p)
		return !p->rva003F7D29();
	return false;
}
