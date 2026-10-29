// ?rva00426914@Rva004266A1@@QAEXHE@Z
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /arch:SSE /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Schedule note (W7-S2 r14): the scheduling fence of the earlier draft is replaced by two textual volatile
// reads (the PlayerList field and the a->m_34 field); a fence also pins compiler-made stores.
// ?rva00426914@Rva004266A1@@QAEXHE@Z @0x00426914 227B evidence: same Rva004266A1 vector at +4 as rowed 0x4266A1 plus flag2 store +6 via callers 0x3BA7ED 0x3BD389 0x3BD3AB; TheAudio ThePlayerList TheGameLogic plus BfmeAudioEventPrefix136 ctor 0x2D97D6 plus dword slot set 0x33F15D plus tail dtor 0x2D9A43 via prefix alias plus AudioManager slot 0x64
#include <vector>

#include "Common/BfmeAudioEventPrefix136.h"


struct Rva004266A1Rec { AsciiString text; unsigned char flag0; unsigned char flag1; unsigned char flag2; };

struct Rva004266A1 {
public:
	char pad[4];
public:
	_STL::vector<Rva004266A1Rec> vec;
public:
	bool rva004266A1(int index);
public:
	void *rva004267E9(int index);
public:
	unsigned char rva0042680D(int index);
public:
	void rva0042682B(int index, unsigned char value);
public:
	unsigned char rva004268F6(int index);
public:
	void rva00426914(int index, unsigned char value);
public:
	unsigned char rva004269F7(int index);
};

class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

struct Bfield
{
	char m_pad[0x1a8];
	OpaqueRefElement4 m_ref1a8;
	OpaqueRefElement4 m_ref1ac;
};

class Afield
{
public:
	char m_pad0[0x34];
	Bfield *m_34;
	char m_pad1[0x54 - 0x38];
	int m_54;
};

class PlayerList
{
public:
	Afield *getLocalPlayer() { return m_10; }
	char m_pad[0x10];
	Afield *m_10;
};

extern PlayerList *ThePlayerList;

class GameLogic;
struct GameLogicFrameView
{
	char m_pad[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class AudioManager
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
	virtual void s24();
	virtual void audioEvent(BfmeAudioEventPrefix136 *ev);
};

extern AudioManager *TheAudio;

void Rva004266A1::rva00426914(int index, unsigned char value)
{
	if (!rva004266A1(index))
		return;
	unsigned char old = vec[index].flag2;
	vec[index].flag2 = value;
	if (TheAudio == 0 || old != 0 || value == 0)
		return;
	Afield *afield = (*(Afield * volatile *)&(ThePlayerList->m_10));
	if (afield == 0)
		return;
	if ((*(Bfield * volatile *)&(afield->m_34)) == 0)
		return;
	if (afield->m_34->m_ref1ac.referent == 0)
		return;
	if (TheGameLogic == 0 || (unsigned int)((GameLogicFrameView *)TheGameLogic)->m_40 <= 3)
		return;
	
	BfmeAudioEventPrefix136 ev(ThePlayerList->m_10->m_34->m_ref1ac, 2);
	((Rva0033F15DDwordSlot *)&ev)->set(ThePlayerList->m_10->m_54);
	TheAudio->audioEvent(&ev);
}
