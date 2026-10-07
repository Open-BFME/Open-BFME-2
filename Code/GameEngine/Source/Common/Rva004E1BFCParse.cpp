// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?Rva004E1BFCParse@@YAXPAVINI@@PAX@Z @0x004E1BFC 126B
// ParseMoveArmyBlockAndAddToLivingWorldCampaignAct proc: throws INIException 3 on null ini or instance
// with retail literal then builds TracerFXNugget record inline then INI::initFromINI with table
// g_00C61830 then append 0x00566537. Evidence: table slot 0x0086CD84 neighbour MoveArmy plus string
// ParseMoveArmyBlockAndAddToLivingWorldCampaignAct plus sibling LivingWorld append thunks plus vtable
// ??_7TracerFXNugget@@6B@ at 0x00861DB4 plus dtor row ??1TracerFXNugget@@MAE@XZ at 0x004E1B00 plus DoXfer
// 0x004E1302 with GetSnapshotName MoveArmy. Record uses the rowed names so the vptr store and the dtor
// call resolve by address. Minimal local view: vptr plus two strings is all this body touches.

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

class TracerFXNugget
{
protected:
	virtual ~TracerFXNugget();
private:
	AsciiString m_str04;
	AsciiString m_str08;
	friend void Rva004E1BFCParse(INI *ini, void *instance);
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
		TracerFXNugget record;
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
