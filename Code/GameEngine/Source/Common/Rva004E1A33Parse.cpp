// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ?Rva004E1A33Parse@@YAXPAVINI@@PAX@Z @0x004E1A33 134B
// ParseAnimObjectUpdate proc: throws INIException 3 on null ini or instance with retail literal then builds
// Rva004E1A04 record inline then INI::initFromINI with table g_00C61D84 then push_back 0x005666BA.
// Evidence: table slot 0x0086CE14 neighbour UpdateAnimObject plus string ParseAnimObjectUpdate plus dtor
// 0x004E1A04 plus vector push_back 0x00566575 via 0x005666BA. Record is 0x10 bytes: pointer plus three
// floats zeroed inline matching retail xor eax plus xorps zeroing. Honest address-derived free-function name.

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

extern const FieldParse g_00C61D84;

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

// ?Rva004E1A33Parse@@YAXPAVINI@@PAX@Z
void Rva004E1A33Parse(INI *ini, void *instance)
{
	if (ini && instance)
	{
		Rva004E1A04 record;
		ini->initFromINI(&record, &g_00C61D84);
		((Rva005666BA *)instance)->rva005666BA(*(const Rva00566575Element *)&record);
	}
	else
	{
		INIException e(3, "ParseAnimObjectUpdate::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}
