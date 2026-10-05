// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?reset@GameInfo@@UAEXXZ @0x003FFF8F (267B):
// GameInfo::reset, virtual slot 10 (+0x28) of vtable 0x008193C8 (rowed copy
// ctor ??0Rva00382FA7@@QAE@ABU0@@Z sets it; slot 13 getLocalSlotNum rowed,
// slot 19 rva003FF3B5 rowed in GameSlotApparent.cpp). BFME2 reset vs ZH donor
// (GameInfo.cpp reset: NOMAP via temp, seed from GetTickCount, slots loop,
// preorderMask clear): extra Unicode clear at +0x04, Version init at +0x90,
// global at +0x0C from g_00DBC800, rules reset at +0x60 via Rva00559FAC,
// rand seed at +0x88, owned ptr at +0xC8 via TreeHint dtor+delete, tail block
// at +0xCC via memset. Callees rowed/pinned: releaseBuffer wide 0x36E70,
// initializeBuildMetadata 0x23870E, StringBase ctor 0x37BA0, set 0x366F0,
// releaseBuffer narrow 0x36410, GetTickCount IAT, rand IAT, TreeHint dtor
// 0x229840, operator delete 0x2FD60, memset thunk 0x6291AE, Rva00559FAC pin.
// Callers 0x00400A07 (ctor) and 0x004FDC73.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;

extern int g_00DBC800;
extern "C" __declspec(dllimport) unsigned int __stdcall GetTickCount(void);
extern "C" __declspec(dllimport) int __cdecl rand(void);
void __cdecl Rva00559FAC(int mode, void *rules);
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Version
{
public:
	void initializeBuildMetadata();
private:
	char m_pad[0x30];
};

class GameSlot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void reset();
};

class TreeHintOpaque0043671B
{
public:
	~TreeHintOpaque0043671B();
};

class GameInfo
{
public:
	virtual void reset();
private:
	UnicodeString m_04;
	Int m_08;
	Int m_0C;
	bool m_10;
	bool m_11;
	bool m_12;
	char m_pad13;
	Int m_14;
	GameSlot *m_slot[8];
	Int m_38;
	short m_3C;
	char m_pad3E[2];
	AsciiString m_40;
	Int m_44;
	Int m_48;
	Int m_4C;
	Int m_50;
	Int m_54;
	Int m_58;
	Int m_5C;
	Int m_60[10];
	Int m_88;
	bool m_8C;
	char m_pad8D[3];
	Version m_90;
	Int m_C0;
	Int m_C4;
	TreeHintOpaque0043671B *m_C8;
	Int m_CC[4];
};

void GameInfo::reset()
{
	m_04.clear();
	m_90.initializeBuildMetadata();
	m_C0 = 0;
	m_C4 = 0;
	m_0C = g_00DBC800;
	m_10 = false;
	m_11 = false;
	m_14 = 0;
	{
		AsciiString tmp("NOMAP");
		AsciiString &dst = m_40;
		dst.set(tmp);
	}
	m_58 = -1;
	m_4C = 0;
	m_50 = (Int)GetTickCount();
	m_54 = -1;
	m_12 = false;
	m_44 = 0;
	m_48 = 0;
	for (Int i = 0; i < 8; ++i)
	{
		if (m_slot[i])
			m_slot[i]->reset();
	}
	m_5C = -1;
	m_08 = 0;
	Rva00559FAC(-1, m_60);
	m_88 = rand();
	m_8C = false;
	if (m_C8 != 0)
	{
		delete m_C8;
		m_C8 = 0;
	}
	ji_006291ae(m_CC, 0, 0x10);
}
