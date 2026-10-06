// cl: /Oy- /DNDEBUG /MD /GX-
// ?Rva003F2576Parse@@YAXPAVINI@@PAURva003F2576Outer@@@Z @0x003F2576 104B
// BuildingRestriction ParseINI helper: null-check INI and holder, new Rva003F1FB6
// 0x10, initFromINI via table g_00C36EE0, then holder at +0x14 -> rva003F255C.
// Throws INIException code 3 with retail literal on null.
// Evidence: chain lane calls landed 0x003F1FB6; callee rows initFromINI 0x0002DE78
// new 0x0002FDA0 ctor 0x003F1FB6 holder 0x003F255C INIException 0x0002F681
// CxxThrow 0x00629094; table VA 0x00C36EE0; string_xrefs literal
// Invalid data in LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI;
// neighbours Rva003F255C Rva003F26AAFinish give TU dir; precedent Rva004FD77CParse.
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class ModuleData;

class Rva003F1FB6
{
public:
	Rva003F1FB6();
private:
	char m_pad[0x10];
};

class Rva003F255C
{
public:
	void rva003F255C(const ModuleData *p);
};

struct Rva003F2576Outer
{
	char _pad[0x14];
	Rva003F255C m_holder;
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

extern const FieldParse g_00C36EE0;

void Rva003F2576Parse(INI *ini, Rva003F2576Outer *outer)
{
	if (!ini || !outer)
	{
		INIException exc(3, "Invalid data in LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F2576ThrowInfoAnchor); __assume(0);
	}
	Rva003F255C *holder = &outer->m_holder;
	Rva003F1FB6 *p = new Rva003F1FB6;
	ini->initFromINI(p, &g_00C36EE0);
	holder->rva003F255C((const ModuleData *)p);
}
