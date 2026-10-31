// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ?Rva004E1A33Parse@@YAXPAVINI@@PAX1PBX@Z @0x004E1A33 134B
// ParseAnimObjectUpdate proc: throws INIException 3 on null ini or instance with retail literal then builds
// Rva004E1A04 record inline then INI::initFromINI with table g_00C61D84 then push_back 0x005666BA.
// Evidence: table slot 0x0086CE14 neighbour UpdateAnimObject plus string ParseAnimObjectUpdate plus dtor
// 0x004E1A04 plus vector push_back 0x00566575 via 0x005666BA. Record is 0x10 bytes: pointer plus three
// floats zeroed inline matching retail xor eax plus xorps zeroing. Honest address-derived free-function name.

class INI;

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse
{
    const char *token;
    FieldParseProc parse;
    const void *userData;
    int offset;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void dup_002F0F7(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseAsciiString( INI *, void *, void *, const void * );
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E3816Parse(INI *, void *, void *, const void *);
};

// Retail VA 0x00C61D84 (.rdata, file offset 0x0085DD84): the AnimObjectUpdate
// block's two field records plus the zero sentinel - AnimObjectName through the
// rowed INI::parseAsciiString (0x0002F11E) at +0 and WorldPos through the rowed
// INI::parseCoord3D (0x0002F507) at +4, both with a null user-data column. Those
// are exactly the pointer and the three floats of the 0x10-byte record the rowed
// parser below builds inline and zeroes with xorps, and the 48-byte extent is
// the ledger's own bound.
// Symbol ?g_00C61D84@@3UFieldParse@@B, transcribed below.
extern const struct FieldParse g_00C61D84[] =
{
	{ "AnimObjectName", &INI::parseAsciiString, 0, 0x0 },
	{ "WorldPos",        &INI::parseCoord3D,      0, 0x4 },
	{ 0, 0, 0, 0 }
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


class Rva004E1A04
{
public:
	Rva004E1A04() : m_ptr(0), m_f1(0.0f), m_f2(0.0f), m_f3(0.0f) {}
	~Rva004E1A04();
private:
	void *m_ptr;
	float m_f1;
	float m_f2;
	float m_f3;
};

struct Rva00566575Element
{
	char m_pad[0x10];
};

class Rva005666BA
{
public:
	void rva005666BA(const Rva00566575Element &e);
};

// ?Rva004E1A33Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004E1A33Parse(INI *ini, void *instance, void *, const void *)
{
	if (ini && instance)
	{
		Rva004E1A04 record;
		ini->initFromINI(&record, g_00C61D84);
		((Rva005666BA *)instance)->rva005666BA(*(const Rva00566575Element *)&record);
	}
	else
	{
		INIException e(3, "ParseAnimObjectUpdate::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}

// Native C6CD50 FieldParse registration uses the four-argument callback ABI.
// Preserve the witnessed body and existing address binding; both trailing
// parameters are unused. No function-pointer cast or alternate callee pin.
