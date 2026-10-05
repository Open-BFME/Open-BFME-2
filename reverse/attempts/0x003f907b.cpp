// ?Rva003F907BParse@@YAXPAVINI@@PAVRva003F9004@@@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /Oy- /DNDEBUG /MD /GX-
// ?Rva003F907BParse@@YAXPAVINI@@PAVRva003F9004@@@Z @0x003F907B 104B LogicTurn::ParseINI helper.
// Evidence: calls rowed ??0Rva003F7EC7@@QAE@H@Z 0x003F7E9D with int at holder+4 after 0x1C new plus rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z 0x0002DE78 with table g_00C37468 plus rowed ?rva003F9004@Rva003F9004@@QAEXPBVModuleData@@@Z 0x003F9004 plus rowed ??0INIException@@QAA@HPBDZZ 0x0002F681 with literal Invalid data in LogicTurn::ParseINI; same shape as Rva003F9258Siblings Parse helpers.
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class ModuleData;

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva003F907BThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva003F907BThrowInfoAnchor rva003F907BThrowInfoAnchor = { 0, 0, 0, 0 };

class Rva003F7EC7
{
public:
	Rva003F7EC7(int v);
private:
	char m_pad[0x1C];
};

class Rva003F9004
{
public:
	void rva003F9004(const ModuleData *p);
	char m_pad00[4];
	int m_04;
private:
	char m_pad08[4];
	char m_pad0C_pad[0xC - 8];
};

extern const FieldParse g_00C37468;

// ?Rva003F907BParse@@YAXPAVINI@@PAVRva003F9004@@@Z present-unmatched
void Rva003F907BParse(INI *ini, Rva003F9004 *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in LogicTurn::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F907BThrowInfoAnchor); __assume(0);
	}
	Rva003F7EC7 *p = new Rva003F7EC7(holder->m_04);
	ini->initFromINI(p, &g_00C37468);
	holder->rva003F9004((const ModuleData *)p);
}
