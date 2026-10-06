// cl: /Oy- /DNDEBUG /MD /GX-
// ?Rva004FD77CParse@@YAXPAVINI@@PAVRva004FD3E2@@@Z @0x004FD77C 98B.
// TeamDefeatCondition ParseINI helper: new Rva004FCD49 0x14, initFromINI via
// table g_00C63640, then holder->rva004FD3E2. Throws INIException code 3 with
// retail literal when either pointer is null.
// Evidence: chain lane calls landed 0x004FD3E2; caller 0x004FD7B5 pattern;
// table VA 0x00C63640 no name yet; string "Invalid data in
// TeamDefeatCondition::ParseINI"; throwinfo anchor 0x00CFE2FC; neighbours
// Rva004135CDParse/Rva00413DCCParse same filler plus CxxThrow recipe.
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class ModuleData;

class Rva004FCD49
{
public:
	Rva004FCD49();
	virtual ~Rva004FCD49();
private:
	char m_pad[0x10];
};

class Rva004FD3E2
{
public:
	void rva004FD3E2(const ModuleData *p);
};

extern const FieldParse g_00C63640;
struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva004FD77CThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva004FD77CThrowInfoAnchor rva004FD77CThrowInfoAnchor = { 0, 0, 0, 0 };

void Rva004FD77CParse(INI *ini, Rva004FD3E2 *holder)
{
	if (!ini || !holder)
	{
		INIException exc(3, "Invalid data in TeamDefeatCondition::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva004FD77CThrowInfoAnchor); __assume(0);
	}
	Rva004FCD49 *p = new Rva004FCD49;
	ini->initFromINI(p, &g_00C63640);
	holder->rva004FD3E2((const ModuleData *)p);
}
