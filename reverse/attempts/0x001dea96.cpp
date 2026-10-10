// ?Rva001DEA96Parse@@YAXPAVINI@@@Z
// partial score=0.8586070347076638 date=2026-10-10
template<class T> static __forceinline T p4Operand(const T &v) { return *(const volatile T*)&v; }
// ?Rva001DEA96Parse@@YAXPAVINI@@@Z
// partial score=0.93 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
// ?Rva001DEA96Parse@@YAXPAVINI@@@Z @0x001DEA96 243B evidence: donor BFME1 INIPredefinedEvaEvent.cpp parse plus callers none plus table g_00DFDC30 plus bound 0x16 plus Parse wrapper 0x001DCFC9
#include "ascii_string.h"

struct FieldParse;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	INILoadType getLoadType() const { return m_loadType; }
private:
	unsigned char m_pad[8];
	INILoadType m_loadType;
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

class Rva001DE727
{
public:
	Rva001DE727 &operator=(const Rva001DE727 &that);
private:
	char m_body[0x30];
};

struct EvaVec001DEA96
{
	Rva001DE727 *m_begin;
	Rva001DE727 *m_end;
	Rva001DE727 *m_capacity;
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
private:
	void *m_unused;
	void **m_begin;
	void **m_end;
};

struct Rva00056F61Node001DEA96
{
	void *m_next;
	AsciiString m_name;
	int m_message;
};

class Eva001DEA96
{
public:
	char m_head[0x1c];
	EvaVec001DEA96 m_current;
	EvaVec001DEA96 m_default;
	char m_side[0x14];
	Rva00056F61 m_names;
};

extern Eva001DEA96 *g_00DFDC30;
extern const char g_Rva0107301CEmptyString[];

void __stdcall Rva001DCFC9Parse(INI *ini, void *obj);

struct Rva001DEA96ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva001DEA96ThrowInfoAnchor rva001DEA96ThrowInfoAnchor = { 0, 0, 0, 0 };

// ?Rva001DEA96Parse@@YAXPAVINI@@@Z present-unmatched
void __cdecl Rva001DEA96Parse(INI *ini)
{
	AsciiString name(ini->getNextToken(0));
	void *found = g_00DFDC30->m_names.rva00056F61(&name);
	if (found == 0)
	{
		char *t = *(char **)&name;
		const char *s = t ? t + 8 : g_Rva0107301CEmptyString;
		INIException e(3, "'%s' is not a predefined Eva event name", s);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&rva001DEA96ThrowInfoAnchor); __assume(0);
	}
	int index = *(int *)((char *)found + 8);
	if (p4Operand(index) < 0 || index >= 0x16)
	{
		char *t = *(char **)&name;
		const char *s = t ? t + 8 : g_Rva0107301CEmptyString;
		INIException e(3, "'%s' is not a predefined Eva event name", s);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&rva001DEA96ThrowInfoAnchor); __assume(0);
	}
	Rva001DE727 *destination;
	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{
		if (index == 0)
		{
			INIException e(3, "You cannot redefine the default Eva event in a map.ini");
			_CxxThrowException(&e, (const _s__ThrowInfo *)&rva001DEA96ThrowInfoAnchor); __assume(0);
		}
		destination = g_00DFDC30->m_current.m_begin + index;
	}
	else
	{
		destination = g_00DFDC30->m_default.m_begin + index;
	}
	Rva001DE727 &record = *destination;
	if (index != 0)
	{
		__assume(destination != 0);
		const Rva001DE727 *source = g_00DFDC30->m_default.m_begin;
		record = *source;
	}
	Rva001DCFC9Parse(ini, &record);
}