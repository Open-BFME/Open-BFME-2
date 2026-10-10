// ?Rva003F907BParse@@YAXPAVINI@@PAURva003F9004@@@Z
// partial score=0.97 date=2026-10-10
// cl: /Oy- /DNDEBUG /MD /GX-
// Seat Z1 (w5-z1) near-exact bank for 0x003F907B (104B), the second twin of the
// rowed Rva003F2576Parse body (the 0x003F8F2B bank documents the shared
// register-allocation delta). Frame size pushed to 0x98 by the 0x1c allocation,
// 0x1c bytes for Rva003F7EC7, FieldParse table VA 0x00C37468, holder
// 0x003F9004 and the literal "Invalid data in LogicTurn::ParseINI".
// Callee placeholders already admitted by address: ??0Rva003F7EC7@@QAE@H@Z
// (0x003F7E9D), ?rva003F9004@Rva003F9004@@QAEXPAX@Z (0x003F9004).
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class ModuleData;

class Rva003F7EC7
{
public:
	Rva003F7EC7(int field);
private:
	char m_pad[0x1c];
};

struct Rva003F9004
{
	char m_pad[4];
	int m_04;
	void rva003F9004(void *p);
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva003F2576ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva003F2576ThrowInfoAnchor rva003F2576ThrowInfoAnchor = { 0, 0, 0, 0 };

extern const FieldParse g_00C37468;

void Rva003F907BParse(INI *ini, Rva003F9004 *outer)
{
	if (!ini || !outer)
	{
		INIException exc(3, "Invalid data in LogicTurn::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F2576ThrowInfoAnchor); __assume(0);
	}
	Rva003F7EC7 *p = new Rva003F7EC7(outer->m_04);
	ini->initFromINI(p, &g_00C37468);
	outer->rva003F9004(p);
}
