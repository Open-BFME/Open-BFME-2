// cl: /DNDEBUG /MD
// ?rva0023C902@Rva0023C902@@QAE_NXZ @0x0023C902 34B: thiscall bool check of +0xa8 plus Display slot 0x114.
// Evidence: cmp byte [ecx+0xa8] je false; TheDisplay row plus virtual +0x114 test je false else true; callers 0x0043CBB6 0x004E41E9 0x0050EC50 0x0051B3AE 0x005234D9 unblocks 4.
class Display
{
public:
	virtual void _00()=0; virtual void _01()=0; virtual void _02()=0; virtual void _03()=0;
	virtual void _04()=0; virtual void _05()=0; virtual void _06()=0; virtual void _07()=0;
	virtual void _08()=0; virtual void _09()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0; virtual void _31()=0;
	virtual void _32()=0; virtual void _33()=0; virtual void _34()=0; virtual void _35()=0;
	virtual void _36()=0; virtual void _37()=0; virtual void _38()=0; virtual void _39()=0;
	virtual void _40()=0; virtual void _41()=0; virtual void _42()=0; virtual void _43()=0;
	virtual void _44()=0; virtual void _45()=0; virtual void _46()=0; virtual void _47()=0;
	virtual void _48()=0; virtual void _49()=0; virtual void _50()=0; virtual void _51()=0;
	virtual void _52()=0; virtual void _53()=0; virtual void _54()=0; virtual void _55()=0;
	virtual void _56()=0; virtual void _57()=0; virtual void _58()=0; virtual void _59()=0;
	virtual void _60()=0; virtual void _61()=0; virtual void _62()=0; virtual void _63()=0;
	virtual void _64()=0; virtual void _65()=0;
	virtual void _66();
	virtual void _67()=0; virtual void _68()=0;
	virtual bool v114() = 0;
};
extern Display *TheDisplay;
class Rva0023C902
{
public:
	int rva0023C902();
private:
	char m_pad[0xa8];
	bool m_a8;
};

int Rva0023C902::rva0023C902()
{
	if (m_a8) {
		if (TheDisplay->v114())
			return 1;
	}
	return 0;
}
