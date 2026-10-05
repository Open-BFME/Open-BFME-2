// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva0051C0E7@@QAE@XZ @0x0051C0E7 82B: default ctor, two ints + AsciiString[8] via ehvec plus 8B tail memset; evidence callees 0x0048BA39 clear/dtor 0x00326BE6 UnicodeString/AsciiString ctor 0x00629512 ehvec 0x006291AE memset caller 0x005202C8
#include "ascii_string.h"
#include <vector>

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count) throw();
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct EmptyBase0051C0E7 {
	EmptyBase0051C0E7() {}
	~EmptyBase0051C0E7();
	AsciiString m_00;
};

struct Rva0051C0E7 : public EmptyBase0051C0E7 {
	int m_04;
	AsciiString m_08[8];
	char m_28[8];
	Rva0051C0E7();
};

Rva0051C0E7::Rva0051C0E7() : m_04(0)
{
	ji_006291ae(m_28, 0, 8);
}

class PlayerListMid0051C241 {
public:
	char _00[0x58];
	AsciiString m_58;
};

class PlayerList {
public:
	char _00[0x10];
	PlayerListMid0051C241 *m_10;
};

extern PlayerList *ThePlayerList;

struct Rva004266A1Rec {
	AsciiString text;
	unsigned char f0;
	unsigned char f1;
	unsigned char f2;
};

class Rva004266A1 {
public:
	char _00[4];
	_STL::vector<Rva004266A1Rec> m_04;
	unsigned char rva0042680D(int index);
	unsigned char rva004269F7(int index);
	unsigned char rva004268F6(int index);
	void *rva004267E9(int index);
};

struct Rva0051C0E7G {
	char _00[0x10];
	Rva004266A1 *m_10;
};

extern Rva0051C0E7G *g_00E031E8;

void Rva0051C241Fill(Rva0051C0E7 *obj)
{
	PlayerList *pl = ThePlayerList;
	if (!pl)
		return;
	PlayerListMid0051C241 *mid = pl->m_10;
	if (!mid)
		return;
	obj->m_00.set(mid->m_58);
	if (!g_00E031E8)
		return;
	obj->m_04 = 0;
	Rva004266A1 *vec = g_00E031E8->m_10;
	if (!vec)
		return;
	for (int i = 0; i < (int)vec->m_04.size(); i++)
	{
		if (!vec->rva0042680D(i))
			continue;
		if (!vec->rva004269F7(i))
			continue;
		unsigned char f = vec->rva004268F6(i);
		obj->m_28[obj->m_04] = (char)f;
		void *p = vec->rva004267E9(i);
		obj->m_08[obj->m_04].set(*(AsciiString *)p);
		obj->m_04++;
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00E031E8@@3PAURva0051C0E7G@@A=?g_00E031E8@@3PAURva0039B95FHolder@@A")
