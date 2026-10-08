// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// CrowdResponse INI block parse (retail 0x00415D33, 314 bytes): the parse
// function of theCrowdResponseBlockParse (VA 0x00DC20E0 "CrowdResponse").
// Target evidence: the three INIException texts at 0x0083A3A0, 0x0083A35C and
// 0x0083A334 with ThrowInfo 0x00CFE2FC; TheCrowdResponseStore is the global
// GameEngine::init registers under that name (0x00A0307C, SubsystemInterface.cpp);
// rowed callees getNextToken 0x0002DF97, new 0x0002FDA0, the entry ctor
// 0x00415B54, hashtable insert 0x0041557A on the store's table at +0xC, the
// override copy 0x00415C84, entry dtor 0x00415AE0 and parseFromINI 0x00415C56.
// WorldBuilder places the body in CrowdResponseSystem.cpp (strings only, no
// name). Structure carried from the banked 0.99 attempt; the insert goes
// through an inline table member, which puts the hidden return push ahead of
// the +0xC this adjustment as retail has it.
#include "ascii_string.h"
#include <set>

struct Rva00415B15Element
{
	Rva00415B15Element();
	Rva00415B15Element(const Rva00415B15Element &that);
	~Rva00415B15Element();
	Rva00415B15Element &operator=(const Rva00415B15Element &that);
	char bytes[8];
};

bool operator<(const Rva00415B15Element &a, const Rva00415B15Element &b);

class Rva00415B54 : public AsciiString
{
public:
	Rva00415B54(const AsciiString &that);
private:
	int m_04;
	_STL::set<Rva00415B15Element> m_set;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	int getLoadType() const { return m_loadType; }
private:
	int m_00;
	int m_04;
	int m_loadType;
};

class CrowdResponseTemplate
{
public:
	void parseFromINI(INI *ini);
};

class Rva00415C84
{
public:
	Rva00415C84 *assignMembers(const Rva00415C84 &other);
};

class Rva00415AE0
{
public:
	~Rva00415AE0();
};

#pragma pack(push, 1)
struct InsertRet0041539F
{
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

typedef _STL::pair<const AsciiString, Rva00415B54 *> CrowdResponseEntry;

class Rva000427195
{
public:
	InsertRet0041539F rva0041557A(const void *key);
	InsertRet0041539F insert(const CrowdResponseEntry &entry) { return rva0041557A(&entry); }
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

class Rva0022A809Subsystem
{
public:
	Rva000427195 &getTable() { return m_table0C; }
private:
	char m_base[0xC];
	Rva000427195 m_table0C;
};

extern Rva0022A809Subsystem *TheCrowdResponseStore;

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

// Retail throws the constructed local itself (no copy into a throw temporary),
// which a throw expression does not reproduce.
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

void __cdecl Rva00415D33Parse(INI *ini)
{
	if (TheCrowdResponseStore == 0)
	{
		INIException e(8, "Attemping to parse a CrowdResponse block before TheCrowdResponseStore is set up");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	if (ini->getLoadType() == 2)
	{
		INIException e(3, "You cannot define or override a CrowdResponse block in map.ini");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	AsciiString name;
	const char *token = ini->getNextToken(0);
	name.set(token);
	Rva00415B54 *fresh = new Rva00415B54(name);
	InsertRet0041539F res = TheCrowdResponseStore->getTable().insert(CrowdResponseEntry(name, fresh));
	if (!res.m_found)
	{
		if (ini->getLoadType() == 5)
		{
			Rva00415B54 *existing = *(Rva00415B54 **)((char *)res.m_node + 8);
			((Rva00415C84 *)existing)->assignMembers(*(Rva00415C84 *)fresh);
			delete (Rva00415AE0 *)fresh;
			fresh = existing;
		}
		else
		{
			INIException e(3, "Multiple CrowdResponse blocks named %s", token);
			_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
			__assume(0);
		}
	}
	((CrowdResponseTemplate *)fresh)->parseFromINI(ini);
}
