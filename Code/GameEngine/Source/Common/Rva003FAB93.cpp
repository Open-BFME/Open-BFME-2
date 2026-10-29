// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva003FAB93@Rva003FAB93@@QAEXXZ @0x003FAB93 172B
// Chain over 0x002D982A. Evidence: m_2c gate <5, m_14 referent null and +0xB0 flag,
// TheAudio 0x009FE6E8 slot 0x8c with 1 1 0, BfmeAudioEventPrefix136 ctor 0x002D982A
// with m_14/m_08/1, m_18 bit6 gates Weapon::setLeechRangeActive 0x002D95FE,
// TheAudio slot 0x64 storing handle to m_2c plus m_30=1,
// dtor 0x002D9A43 via alias. Callers 0x003FAF13 0x003FAFB9 0x003FAC83.
// Neighbours ConstIntGetters4.cpp and Rva003FAC3F.cpp (/O1 /DNDEBUG /MD +EHsc here).
#include "../../Include/Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva003FAB93AudioView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *);
	virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void s34();
	virtual void slot35(int a, int b, int c);
};

#include "../../Include/GameLogic/Weapon.h"

struct RefInner14 {
	unsigned char pad[0xB0];
	int flag;
};

class Rva003FAB93
{
public:
	void rva003FAB93();
private:
	void *m_vptr00;
	unsigned char m_pad04[4];
	BfmeEventPositionView m_pos08;
	OpaqueRefElement4 m_ref14;
	unsigned int m_flags18;
	unsigned char m_pad1C[0x10];
	unsigned int m_2c;
	unsigned char m_30;
};

void Rva003FAB93::rva003FAB93()
{
	if (m_2c >= 5)
		return;
	OpaqueRefElement4 *pref = &m_ref14;
	if (pref->referent == 0)
		return;
	AudioManager *audio = TheAudio;
	if (audio == 0)
		return;
	RefInner14 *inner = (RefInner14 *)pref->referent;
	int flagB0 = inner->flag;
	if (flagB0 == 0)
		reinterpret_cast<Rva003FAB93AudioView *>(audio)->slot35(1, 1, 0);
	BfmeAudioEventPrefix136 evt(m_ref14, m_pos08, 1);
	if ((((unsigned char)(m_flags18 >> 6)) & 1) != 0)
		reinterpret_cast<Weapon *>(&evt)->setLeechRangeActive(true);
	m_2c = reinterpret_cast<Rva003FAB93AudioView *>(TheAudio)->addAudioEvent(&evt);
	m_30 = 1;
}
