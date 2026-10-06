// cl: /Oy- /DNDEBUG /MD /GX-
// Six TeamDefeatCondition-style ParseINI helpers recovered from the
// ?Rva004FD77CParse@@YAXPAVINI@@PAVRva004FD3E2@@@Z recipe at 0x004FD77C.
// Same operand-masked shape: null-check the INI and holder, new a record,
// INI::initFromINI it against a per-type FieldParse table, then append it to
// the holder, else throw INIException(3) with that type's literal. Only the
// record size, its constructor, the FieldParse table, the holder method and
// the literal differ. Evidence: each member's retail literal names its type
// (Tutorial/PlayerDefeatCondition/TeamDefeatCondition/SpawnGenericBuilding/
// SpawnGenericArmy/OwnershipSet), and the ctor and holder call displacements
// are read from the retail bodies.
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
struct Rva003F9258ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva003F9258ThrowInfoAnchor rva003F9258ThrowInfoAnchor = { 0, 0, 0, 0 };

// 0x003F9258 Tutorial::ParseINI, record size 0x24.
class Rva003F9258Data
{
public:
	Rva003F9258Data();
	virtual ~Rva003F9258Data();
private:
	char m_pad[0x20];
};

class Rva003F7BE9
{
public:
	void rva003F7BE9(const ModuleData *p);
};

extern const FieldParse g_00C37560;

void Rva003F9258Parse(INI *ini, Rva003F7BE9 *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in Tutorial::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F9258ThrowInfoAnchor); __assume(0);
	}
	Rva003F9258Data *p = new Rva003F9258Data;
	ini->initFromINI(p, &g_00C37560);
	holder->rva003F7BE9((const ModuleData *)p);
}

// 0x004FD719 PlayerDefeatCondition::ParseINI, record size 0x18.
class Rva004FD719Data
{
public:
	Rva004FD719Data();
	virtual ~Rva004FD719Data();
private:
	char m_pad[0x14];
};

class Rva004FD37F
{
public:
	void rva004FD37F(const ModuleData *p);
};

extern const FieldParse g_00C635D0;

void Rva004FD719Parse(INI *ini, Rva004FD37F *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in PlayerDefeatCondition::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F9258ThrowInfoAnchor); __assume(0);
	}
	Rva004FD719Data *p = new Rva004FD719Data;
	ini->initFromINI(p, &g_00C635D0);
	holder->rva004FD37F((const ModuleData *)p);
}

// 0x004FD7FB TeamDefeatCondition::ParseINI, record size 0x24.
class Rva004FD7FBData
{
public:
	Rva004FD7FBData();
	virtual ~Rva004FD7FBData();
private:
	char m_pad[0x20];
};

class Rva004FD448
{
public:
	void rva004FD448(const ModuleData *p);
};

extern const FieldParse g_00C636D0;

void Rva004FD7FBParse(INI *ini, Rva004FD448 *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in TeamDefeatCondition::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F9258ThrowInfoAnchor); __assume(0);
	}
	Rva004FD7FBData *p = new Rva004FD7FBData;
	ini->initFromINI(p, &g_00C636D0);
	holder->rva004FD448((const ModuleData *)p);
}

// 0x0059E436 SpawnGenericBuilding::ParseINI, record size 0x14.
class Rva0059E436Data
{
public:
	Rva0059E436Data();
	virtual ~Rva0059E436Data();
private:
	char m_pad[0x10];
};

class Rva0059E390
{
public:
	void rva0059E390(const ModuleData *p);
};

extern const FieldParse g_00C70FFC;

void Rva0059E436Parse(INI *ini, Rva0059E390 *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in SpawnGenericBuilding::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F9258ThrowInfoAnchor); __assume(0);
	}
	Rva0059E436Data *p = new Rva0059E436Data;
	ini->initFromINI(p, &g_00C70FFC);
	holder->rva0059E390((const ModuleData *)p);
}

// 0x0059E511 SpawnGenericArmy::ParseINI, record size 0x14.
class Rva0059E511Data
{
public:
	Rva0059E511Data();
	virtual ~Rva0059E511Data();
private:
	char m_pad[0x10];
};

class Rva0059E3A7
{
public:
	void rva0059E3A7(const ModuleData *p);
};

extern const FieldParse g_00C71064;

void Rva0059E511Parse(INI *ini, Rva0059E3A7 *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in SpawnGenericArmy::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F9258ThrowInfoAnchor); __assume(0);
	}
	Rva0059E511Data *p = new Rva0059E511Data;
	ini->initFromINI(p, &g_00C71064);
	holder->rva0059E3A7((const ModuleData *)p);
}

// 0x0059E6D3 OwnershipSet::ParseINI, record size 0x2c.
class Rva0059E6D3Data
{
public:
	Rva0059E6D3Data();
	virtual ~Rva0059E6D3Data();
private:
	char m_pad[0x28];
};

class Rva004FD4AE
{
public:
	void rva004FD4AE(const ModuleData *p);
};

extern const FieldParse g_00C710E8;

void Rva0059E6D3Parse(INI *ini, Rva004FD4AE *holder)
{
	if (!ini || !holder) {
		INIException exc(3, "Invalid data in OwnershipSet::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F9258ThrowInfoAnchor); __assume(0);
	}
	Rva0059E6D3Data *p = new Rva0059E6D3Data;
	ini->initFromINI(p, &g_00C710E8);
	holder->rva004FD4AE((const ModuleData *)p);
}
