// ?rva00372BB9@AIGroup@@QAEXPBXH@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
// ?rva00372BB9@AIGroup@@QAEXPBXH@Z @0x00372BB9 76B
// Unlock over AIGroup pin 0x00372571 plus virtual 0x158.
// Evidence: calls pin 0x00372571; callees rowed/pinned; unblocks 0x004ED2ED.
struct Rva00372571Params
{
	const void *m_00;
	bool m_04;
	const void *m_08;
	const void *m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class V86
{
public:
	virtual void _0();
	virtual void _1();
	virtual void _2();
	virtual void _3();
	virtual void _4();
	virtual void _5();
	virtual void _6();
	virtual void _7();
	virtual void _8();
	virtual void _9();
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
	virtual void *f_158();
};

class AIGroup
{
public:
	void rva00372BB9(const void *a, int b);
	void rva00372571(Rva00372571Params *p, int v);
};

// ?rva00372BB9@AIGroup@@QAEXPBXH@Z present-unmatched
void AIGroup::rva00372BB9(const void *a, int b)
{
	(void)b;
	V86 *p = *(V86 *const *)((const char *)a + 0x250);
	if (p == 0)
		return;
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_0C = a;
	params.m_08 = a;
	params.m_04 = false;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	params.m_00 = p->f_158();
	rva00372571(&params, 0);
}
