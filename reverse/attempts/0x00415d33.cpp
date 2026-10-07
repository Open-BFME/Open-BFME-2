// ?Rva00415D33Parse@@YAXPAVINI@@@Z
// partial score=0.99 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ?Rva00415D33Parse@@YAXPAVINI@@@Z @0x00415D33 314B chain via rowed 0x00415B54 ctor.
// CrowdResponse INI block parse: null-store and map.ini guards then tokenize,
// new Rva00415B54, hashtable insert at store+0xC via rowed 0x0041557A, duplicate
// override through rowed assignMembers 0x00415C84 when load type is 5 else throw,
// then rowed parseFromINI 0x00415C56. Evidence: callers none (BlockParse
// CrowdResponse node VA 0x00DC20E0 parse 0x00415D33), strings at 0x0083A3A0
// 0x0083A35C 0x0083A334, ThrowInfo 0x00CFE2FC, rowed getNextToken 0x0002DF97
// set 0x000055F5 new 0x0002FDA0 StringBase copy 0x000365F0 releaseBuffer
// 0x00036410 dtor 0x00415AE0 delete 0x0002FD60.
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
	int getLoadType() const { return m_type; }
	int m_00;
	int m_04;
	int m_type;
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
	InsertRet0041539F(void *node, void *owner, unsigned char found)
		: m_node(node), m_owner(owner), m_found(found) {}
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

class Rva000427195
{
public:
	InsertRet0041539F rva0041557A(const void *key);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

struct CrowdResponseStore00415D33
{
	char _00[0xC];
	Rva000427195 m_table0C;
};

extern CrowdResponseStore00415D33 *g_00E0307C;

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

void __cdecl Rva00415D33Parse(INI *ini)
{
	if (g_00E0307C == 0)
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
	((StringBase<char> *)&name)->set(token);
	Rva00415B54 *fresh = new Rva00415B54(name);
	InsertRet0041539F res = g_00E0307C->m_table0C.rva0041557A((const void *)&_STL::pair<const AsciiString, Rva00415B54 *>(name, fresh));
	if (!res.m_found)
	{
		if (ini->m_type == 5)
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
