// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva003FAB93@Rva003FAB93@@QAEXXZ @0x003FAB93 172B
// Chain over 0x002D982A. Evidence: m_2c gate <5, m_14 referent null and +0xB0 flag,
// TheAudio 0x009FE6E8 slot 0x8c with 1 1 0, BfmeAudioEventPrefix136 ctor 0x002D982A
// with m_14/m_08/1, m_18 bit6 gates Weapon::setLeechRangeActive 0x002D95FE,
// TheAudio slot 0x64 storing handle to m_2c plus m_30=1,
// dtor 0x002D9A43 via alias. Callers 0x003FAF13 0x003FAFB9 0x003FAC83.
// Neighbours ConstIntGetters4.cpp and Rva003FAC3F.cpp (/O1 /DNDEBUG /MD +EHsc here).
#include "ascii_string.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

typedef long Long;
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(Long volatile *addend);

struct BfmePoolHolder88
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef08
{
	OpaqueRefCounted *m_target;
public:
	__forceinline BfmePoolRef08() : m_target(0) {}
	__forceinline ~BfmePoolRef08() { if (m_target != 0) m_target->Release_Ref(); }
};

class BfmePoolRef10
{
	BfmePoolHolder88 *m_target;
public:
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
	__forceinline BfmePoolRef10() : m_target(0) {}
};

struct OpaqueRefElement4 { OpaqueRefCounted *referent; OpaqueRefElement4 &operator=(const OpaqueRefElement4 &); };

struct BfmeEventPositionView {
	float x, y, z;
};

struct BfmeAudioEventPrefix136
{
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &, const BfmeEventPositionView &, int);
	virtual ~BfmeAudioEventPrefix136();
	AsciiString m_string04;
	BfmePoolRef08 m_pool08;
	int m_int0C;
	BfmePoolRef10 m_pool10;
	int m_int14;
	int m_int18;
	AsciiString m_string1C;
	AsciiString m_string20;
	float m_f24;
	float m_f28;
	float m_f2C;
	int m_int30;
	int m_int34;
	int m_int38;
	BfmeEventPositionView m_position;
	unsigned char m_b48;
	unsigned char m_b49;
	unsigned char m_b4A;
	unsigned char m_b4B;
	unsigned char m_b4C;
	unsigned char m_b4D;
	unsigned char m_b4E;
	unsigned char m_b4F;
	unsigned char m_b50;
	unsigned char m_b51;
	unsigned char m_b52;
	unsigned char m_b53;
	float m_f54;
	float m_f58;
	float m_f5C;
	float m_f60;
	float m_f64;
	int m_int68;
	int m_int6C;
	int m_int70;
	int m_int74;
	int m_int78;
	int m_int7C;
	int m_int80;
	AsciiString m_string84;
};

#pragma comment(linker, "/alternatename:??1BfmeAudioEventPrefix136@@UAE@XZ=??1BfmeStringTailRecord144@@UAE@XZ")

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

class Weapon
{
public:
	void setLeechRangeActive(bool);
};

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
