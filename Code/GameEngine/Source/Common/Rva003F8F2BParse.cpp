// cl: /Oy- /DNDEBUG /MD /GX- /G7 /arch:SSE /O1
// ?Rva003F8F2BParse@@YAXPAVINI@@PAURva003F7C0C@@@Z
// ?Rva003F907BParse@@YAXPAVINI@@PAURva003F9004@@@Z (0x003F907B, 104B): the
// LogicTurn twin, same shape with the 0x1c Rva003F7EC7 (0x003F7E9D), table
// 0x00C37468 and the rowed holder Rva003F9004::rva003F9004 (0x003F9004).
// Seat Z1 (w5-z1) near-exact bank for 0x003F8F2B (104B), twin of the rowed
// Rva003F2576Parse body in the same unit. Verified difference: retail parks the
// receiver in ESI and the {null, new-result} pair in EDI, pushing BOTH saved
// registers in the prologue; every source spelling tried (member holder local,
// holder in the guard, reference view, char* cast, ==0 guard, two locals in all
// orders) makes MSVC park the {null, new-result} pair in ESI instead, with the
// receiver in a lazily-saved EDI. Nothing else differs: all four callee targets,
// the 0x20 allocation, the push [esi+4] ctor argument, the FieldParse table VA
// 0x00C373D8 and the "Invalid data in SessionTask::ParseINI" literal match.
// Source kept in the attempt file for the next seat.
// Callee placeholders already admitted by address: ??0Rva003F8ED6@@QAE@H@Z
// (0x003F8EA2), ?rva003F7C0C@Rva003F7C0C@@QAEXPAX@Z (0x003F7C0C).
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class ModuleData;

class Rva003F8ED6
{
public:
	Rva003F8ED6(int field);
private:
	char m_pad[0x20];
};

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
	void rva003F9004(const ModuleData *p);
};

struct Rva003F7C0C
{
	char m_pad[4];
	int m_04;
	void rva003F7C0C(void *p);
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

extern const FieldParse g_00C373D8;
extern const FieldParse g_00C37468;

void Rva003F8F2BParse(INI *ini, Rva003F7C0C *outer)
{
	if (!ini || !outer)
	{
		INIException exc(3, "Invalid data in SessionTask::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F2576ThrowInfoAnchor); __assume(0);
	}
	Rva003F8ED6 *p = new Rva003F8ED6((outer->m_04?outer->m_04:outer->m_04));
	ini->initFromINI(p, &g_00C373D8);
	outer->rva003F7C0C(p);
}

void Rva003F907BParse(INI *ini, Rva003F9004 *outer)
{
	if (!ini || !outer)
	{
		INIException exc(3, "Invalid data in LogicTurn::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F2576ThrowInfoAnchor); __assume(0);
	}
	Rva003F7EC7 *p = new Rva003F7EC7((outer->m_04?outer->m_04:outer->m_04));
	ini->initFromINI(p, &g_00C37468);
	outer->rva003F9004((const ModuleData *)p);
}
