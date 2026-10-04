// ?Rva002BEF4BGet@@YGXPAVRva002BEF4BObj@@@Z
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
// ?Rva002BEF4BGet@@YGXPAVRva002BEF4BObj@@@Z @0x002BEF4B 154B: loop LM_%02d format via 0x00038150 plus empty fallback g_Rva0107301CEmptyString plus virtual slot 0x80 get plus slot 0x194 use plus refcount release. Evidence: callers 0x002BF2B7 0x002BF5B0 push ebx plus mov ecx esi plus g_009FE1C8 count at +0x18.
#include "ascii_string.h"

class Rva0021294A
{
public:
	char m_pad[0x18];
	int m_18;
};
extern Rva0021294A *g_009FE1C8;

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr002BEF4B(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

class Rva002BEF4BRes;
class Rva002BEF4BObj
{
public:
	virtual void _00();
	virtual void _01();
	virtual void _02();
	virtual void _03();
	virtual void _04();
	virtual void _05();
	virtual void _06();
	virtual void _07();
	virtual void _08();
	virtual void _09();
	virtual void _10();
	virtual void _11();
	virtual void _12();
	virtual void _13();
	virtual void _14();
	virtual void _15();
	virtual void _16();
	virtual void _17();
	virtual void _18();
	virtual void _19();
	virtual void _20();
	virtual void _21();
	virtual void _22();
	virtual void _23();
	virtual void _24();
	virtual void _25();
	virtual void _26();
	virtual void _27();
	virtual void _28();
	virtual void _29();
	virtual void _30();
	virtual void _31();
	virtual Rva002BEF4BRes *Get(const char *s, int v);
};

class Rva002BEF4BRes
{
public:
	virtual void _00();
	virtual void _01();
	virtual void _02();
	virtual void _03();
	virtual void _04();
	virtual void _05();
	virtual void _06();
	virtual void _07();
	virtual void _08();
	virtual void _09();
	virtual void _10();
	virtual void _11();
	virtual void _12();
	virtual void _13();
	virtual void _14();
	virtual void _15();
	virtual void _16();
	virtual void _17();
	virtual void _18();
	virtual void _19();
	virtual void _20();
	virtual void _21();
	virtual void _22();
	virtual void _23();
	virtual void _24();
	virtual void _25();
	virtual void _26();
	virtual void _27();
	virtual void _28();
	virtual void _29();
	virtual void _30();
	virtual void _31();
	virtual void _32();
	virtual void _33();
	virtual void _34();
	virtual void _35();
	virtual void _36();
	virtual void _37();
	virtual void _38();
	virtual void _39();
	virtual void _40();
	virtual void _41();
	virtual void _42();
	virtual void _43();
	virtual void _44();
	virtual void _45();
	virtual void _46();
	virtual void _47();
	virtual void _48();
	virtual void _49();
	virtual void _50();
	virtual void _51();
	virtual void _52();
	virtual void _53();
	virtual void _54();
	virtual void _55();
	virtual void _56();
	virtual void _57();
	virtual void _58();
	virtual void _59();
	virtual void _60();
	virtual void _61();
	virtual void _62();
	virtual void _63();
	virtual void _64();
	virtual void _65();
	virtual void _66();
	virtual void _67();
	virtual void _68();
	virtual void _69();
	virtual void _70();
	virtual void _71();
	virtual void _72();
	virtual void _73();
	virtual void _74();
	virtual void _75();
	virtual void _76();
	virtual void _77();
	virtual void _78();
	virtual void _79();
	virtual void _80();
	virtual void _81();
	virtual void _82();
	virtual void _83();
	virtual void _84();
	virtual void _85();
	virtual void _86();
	virtual void _87();
	virtual void _88();
	virtual void _89();
	virtual void _90();
	virtual void _91();
	virtual void _92();
	virtual void _93();
	virtual void _94();
	virtual void _95();
	virtual void _96();
	virtual void _97();
	virtual void _98();
	virtual void _99();
	virtual void _100();
	virtual void Use(int v);
	int m_04;
};

// ?Rva002BEF4BGet@@YGXPAVRva002BEF4BObj@@@Z present-unmatched
void __stdcall Rva002BEF4BGet(Rva002BEF4BObj *obj)
{
	int cur = 0;
	int *pcount = &g_009FE1C8->m_18;
	if (*pcount <= 0)
		return;
	do
	{
		AsciiString tmp;
		tmp.format("LM_%02d", ++cur);
		const char *s = GetStr002BEF4B(tmp);
		Rva002BEF4BRes *res = obj->Get(s, 0);
		if (res)
		{
			res->Use(0);
			if (--res->m_04 == 0)
				res->_00();
		}
	} while (cur < *pcount);
}
