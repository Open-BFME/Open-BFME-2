// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /EHsc
// ?Rva004CF145@@YAXXZ @0x004CF145 104B. Audio event via TheAudio slot138.
// Evidence: TheAudio 0x009FE6E8 plus rowed BfmeAudioEventPrefix136 ctor 0x002D97D6
// plus AudioManager slots 0x64 addAudioEvent 0x138 provider plus rowed
// BfmeStringTailRecord144 dtor 0x002D9A43; callers 0x004D11C5 0x004D1231 0x004D14B9.
#include "Common/BfmeAudioEventPrefix136.h"

struct Rva004CF145Info
{
	char m_pad[0x74];
	OpaqueRefElement4 m_74;
};

class AudioManager
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
	virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09();
	virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
	virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *ev);
	virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30();
	virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40();
	virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45();
	virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50();
	virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55();
	virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60();
	virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65();
	virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70();
	virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75();
	virtual void p76(); virtual void p77();
	virtual Rva004CF145Info *slot138();
};

extern AudioManager *TheAudio;

void __cdecl Rva004CF145()
{
	if (TheAudio == 0)
		return;
	Rva004CF145Info *info = TheAudio->slot138();
	if (info == 0)
		return;
	BfmeAudioEventPrefix136 ev(*(OpaqueRefElement4 *)((char *)info + 0x74), 0);
	TheAudio->addAudioEvent(&ev);
}
