// ?iniParseEvaEventForwardReference@Eva@@SAXPAVINI@@@Z
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /DNDEBUG /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?iniParseEvaEventForwardReference@Eva@@SAXPAVINI@@@Z retail 0x001DF6A8 (484 bytes).
// NEAR (helper draft): WorldBuilder twin 0x00ACA200 Eva::iniParseEvaEventForwardReference
// (Eva.cpp:578..649). Standalone this body is 485 bytes and differs only in
// (1) the BfmePod52 status temp: retail calls the Eva.cpp-local clearer
// 0x001DCD3C and then reuses ECX (`mov eax,ecx`) because cl sees that
// function's register use in the same TU - here cl emits `lea eax,[ebp-0x58]`;
// (2) the order of `push eax` / `add ecx,0x34` before the +0x34 insert (the +0x48
// insert matches). Appending the body to Eva.cpp itself (bfme2_ascii include,
// real STLport vector with declared push_back specializations; tried in a temp
// copy) fixes (1) but cl then gives the status temp its own slot (frame 0x7c
// vs 0x4c). Needed shapes: INI::getLoadType() enum getter (not a raw member
// compare), entry/status as temporaries, the name pair as a named block local
// destroyed after the status push, the found-check before the +0x48 create.
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps = 0);

	enum LoadType { LOAD_CREATE_OVERRIDES = 2 };
	LoadType getLoadType() const { return m_loadType; }
	unsigned char m_pad00[0x08];
	LoadType m_loadType; // +0x08
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

class Rva001DCD3C
{
public:
	void rva001DCD3C();
};

struct BfmePod52
{
	BfmePod52() { reinterpret_cast<Rva001DCD3C *>(this)->rva001DCD3C(); }
	BfmePod52(const BfmePod52 &other);
	~BfmePod52() {}
	int a[13];
};

struct Rva001DF3F1Element
{
	int a[12];
};

struct Rva001DF88CEntry
{
	Rva001DF88CEntry();
	~Rva001DF88CEntry();
	int a[12];
};

struct NoCaseTreeValue4
{
	char m_body[4];
};

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
}

// The name table's entry: the name and the event's index in the info vector.
struct EvaNamedIndex
{
	EvaNamedIndex(const AsciiString &name, int index) : m_name(name), m_index(index) {}
	AsciiString m_name;
	int m_index;
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct InsertResult
{
	void *m_node;
	void *m_table;
	unsigned char m_inserted;
};

class Rva001DE556
{
public:
	InsertResult *rva001DE84F(InsertResult *out, const NocasePair &obj);
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *name);
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
	int size() const { return _M_finish - _M_start; }
	T &back() { return *(_M_finish - 1); }

	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

class Eva
{
public:
	static void iniParseEvaEventForwardReference(INI *ini);
	int rva001DE78E(const AsciiString *name);

	unsigned char m_pad00[0x1C];
	_STL::vector<Rva001DF3F1Element> m_allEventInfos; // +0x1C
	_STL::vector<Rva001DF3F1Element> m_forwardInfos; // +0x28
	unsigned char m_names34[0x14]; // +0x34
	unsigned char m_names48[0x14]; // +0x48
	_STL::vector<BfmePod52> m_eventStatus; // +0x5C
};

extern Eva *TheEva;

void Eva::iniParseEvaEventForwardReference(INI *ini)
{
	AsciiString name = ini->getNextToken();
	if (name.compareNoCase("None") == 0)
		throw INIException(3, "Cannot use 'None' as a new Eva event's name");

	if (ini->getLoadType() == INI::LOAD_CREATE_OVERRIDES)
	{
		int id = TheEva->rva001DE78E(&name);
		if (id == -1)
		{
			int index = TheEva->m_allEventInfos.size();
			TheEva->m_allEventInfos.push_back(*(Rva001DF3F1Element *)&Rva001DF88CEntry());
			((unsigned char *)&TheEva->m_allEventInfos.back())[0x2E] = 1;
			EvaNamedIndex entryName(name, index);
			InsertResult result;
			((Rva001DE556 *)TheEva->m_names34)->rva001DE84F(&result, *(const NocasePair *)&entryName);
			TheEva->m_eventStatus.push_back(BfmePod52());
		}
		else if (id < 0x16)
		{
			throw INIException(3, "'%s' is a predefined Eva event name, and cannot be used as a new event name", name.str());
		}
	}
	else
	{
		void *found = ((Rva00056F61 *)TheEva->m_names48)->rva00056F61(&name);
		if (found)
		{
			if (((int *)found)[2] < 0x16)
				throw INIException(3, "'%s' is a predefined Eva event name, and cannot be used as a new event name", name.str());
		}
		else
		{
			int index = TheEva->m_forwardInfos.size();
			TheEva->m_forwardInfos.push_back(*(Rva001DF3F1Element *)&Rva001DF88CEntry());
			((unsigned char *)&TheEva->m_forwardInfos.back())[0x2E] = 1;
			EvaNamedIndex entryName(name, index);
			InsertResult result;
			((Rva001DE556 *)TheEva->m_names48)->rva001DE84F(&result, *(const NocasePair *)&entryName);
		}
	}
}
