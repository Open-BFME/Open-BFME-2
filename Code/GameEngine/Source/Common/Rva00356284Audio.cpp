// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /EHsc
// ?rva00356284@Rva00356284@@QAEXXZ @0x00356284 227B. Audio double-prefix refresh via TheAudio.
// Evidence: TheAudio 0x009FE6E8 plus rowed BfmeAudioEventPrefix136 ctor 0x002D97D6
// plus AudioManager slots 0x64 addAudioEvent 0x8c triple-int 0x28 touch plus rowed
// BfmeStringTailRecord144 dtor 0x002D9A43; caller 0x00356A1A; prev/next dtors.
#include "Common/BfmeAudioEventPrefix136.h"

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
};

extern AudioManager *TheAudio;

class Rva00356284
{
public:
	void rva00356284();
private:
	char m_pad00[0x14];
	OpaqueRefElement4 m_14;
	OpaqueRefElement4 m_18;
	int m_1c;
	int m_20;
};

void Rva00356284::rva00356284()
{
	m_1c = 1;
	m_20 = 1;
	if (TheAudio == 0)
		return;
	bool touched = false;
	if (m_14.referent != 0) {
		BfmeAudioEventPrefix136 ev1(m_14, 2);
		m_1c = TheAudio->addAudioEvent(&ev1);
		touched = true;
	}
	if (m_18.referent != 0) {
		TheAudio->slot8C(2, 1, 1);
		BfmeAudioEventPrefix136 ev2(m_18, 2);
		m_20 = TheAudio->addAudioEvent(&ev2);
		touched = true;
	}
	if (touched)
		TheAudio->slot28();
}
