// ?Rva004E1BFCParse@@YAXPAVINI@@PAX@Z
// partial score=0.99 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?Rva004E1BFCParse@@YAXPAVINI@@PAX@Z @0x004E1BFC 126B
// ParseMoveArmyBlockAndAddToLivingWorldCampaignAct proc: throws INIException 3 on null ini or instance
// with retail literal then builds Rva004E1B00 record inline then INI::initFromINI with table
// g_00C61830 then append 0x00566537. Evidence: table slot 0x0086CD84 neighbour MoveArmy plus string
// ParseMoveArmyBlockAndAddToLivingWorldCampaignAct plus sibling LivingWorld append thunks plus vtable
// 0x00C61DB4 plus DoXfer 0x004E1302 with GetSnapshotName MoveArmy.

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

extern const FieldParse g_00C61830;

#include "ascii_string.h"

class Rva004E1B00
{
public:
	virtual ~Rva004E1B00();
private:
	AsciiString m_str04;
	AsciiString m_str08;
};

class Rva0052BDE6
{
	char m_pad[0xC];
};

class Rva00566537Owner
{
public:
	void append(const Rva0052BDE6 &record);
};

// ?Rva004E1BFCParse@@YAXPAVINI@@PAX@Z
void Rva004E1BFCParse(INI *ini, void *instance)
{
	if (ini && instance)
	{
		Rva004E1B00 record;
		ini->initFromINI(&record, &g_00C61830);
		((Rva00566537Owner *)instance)->append(*(const Rva0052BDE6 *)&record);
	}
	else
	{
		INIException e(3, "ParseMoveArmyBlockAndAddToLivingWorldCampaignAct::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}
