// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva005D62E8@Rva005D62E8@@QAEPAV1@PAVPlayerInfo@@@Z, retail 0x005D62E8, 178 bytes.
// Evidence: __thiscall, ret 4 single PlayerInfo arg; calls g_00E05FB4 vf10,
// TheGameSpyInfo vf24/vf31 rows, _M_find map<int,int> row, PlayerInfo::isIgnored row.
// Vtable slots 0x28/0x60/0x7c read off retail; PlayerInfo +0x14 profileID +0x18 flags.
// Returns this (retail mov eax,esi).
#include <map>

class Rva00E05FB4
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8();
	virtual void vf9();
	virtual bool vf10(int v);
};
extern Rva00E05FB4 *g_00E05FB4;

class GameSpyInfoInterface
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8();
	virtual void vf9();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void vf22();
	virtual void vf23();
	virtual _STL::map<int, int> *vf24();
	virtual void vf25();
	virtual void vf26();
	virtual void vf27();
	virtual void vf28();
	virtual void vf29();
	virtual void vf30();
	virtual int vf31();
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class PlayerInfo
{
public:
	bool isIgnored();
private:
	unsigned char m_pad00[0x14];
public:
	int m_profileID; // +0x14
	int m_flags; // +0x18
};

class Rva005D62E8
{
public:
	Rva005D62E8 *rva005D62E8(PlayerInfo *p);
private:
	PlayerInfo *m_player; // +0x0
	int m_state; // +0x4
	int m_sub; // +0x8
};

Rva005D62E8 *Rva005D62E8::rva005D62E8(PlayerInfo *p)
{
	m_state = 0;
	m_player = p;
	m_sub = 11;
	if ((p->m_flags & 0x20) == 0 && !g_00E05FB4->vf10(p->m_profileID))
	{
		_STL::map<int, int> *m = TheGameSpyInfo->vf24();
		if (m->find(m_player->m_profileID) != m->end())
		{
			m_state = 1;
			m_sub = 8;
		}
		else if (m_player->m_profileID == TheGameSpyInfo->vf31())
		{
			m_state = 3;
			m_sub = 10;
		}
		else
		{
			m_state = 0;
			m_sub = 6;
		}
	}
	else
	{
		m_state = 2;
		m_sub = 7;
	}
	if (m_player->isIgnored())
	{
		m_state += -4;
		m_sub = 11;
	}
	return this;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00E05FB4@@3PAVRva00E05FB4@@A=?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A")
