// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /GX
// ?Rva004E17EBParse@@YAXPAVINI@@PAX@Z @0x004E17EB 129B
// ParseSpawnBuilding proc: throws INIException 3 on null ini or instance with retail literal then builds
// Rva004E179A record inline then INI::initFromINI with table g_00C61BE0 then append 0x0056653F.
// Evidence: table slot 0x0086CD94 neighbour SpawnBuilding plus string ParseSpawnBuilding plus vtable
// 0x00C61B78 plus dtor 0x004E179A plus DoXfer pattern.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

extern const FieldParse g_00C61BE0;

#include "ascii_string.h"

class Rva004E179A
{
public:
	virtual ~Rva004E179A();
private:
	AsciiString m_str04;
	AsciiString m_str08;
	AsciiString m_str0C;
	bool m_bool10;
};

class Rva0052BE33
{
	char m_pad[0x10];
};

class Rva0056653FOwner
{
public:
	void append(const Rva0052BE33 &record);
};

// ?Rva004E17EBParse@@YAXPAVINI@@PAX@Z
void Rva004E17EBParse(INI *ini, void *instance)
{
	if (ini && instance)
	{
		Rva004E179A record;
		ini->initFromINI(&record, &g_00C61BE0);
		((Rva0056653FOwner *)instance)->append(*(const Rva0052BE33 *)&record);
	}
	else
	{
		INIException e(3, "ParseSpawnBuilding::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}
