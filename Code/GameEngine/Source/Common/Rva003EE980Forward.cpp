// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva003EE980@Rva003EE980@@QAEXH@Z @0x003EE980 87B. Unlock lane: three-call
// forward with string g_Rva00E02E84 and triple-float struct from
// 0.95f; arg+0x44; caller at 0x004FF21E. Prev/next are the
// Rva003EE966/A1A family (// cl: /O1 /MD) plus /arch:SSE for movss.
#include <map>

typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35FF
{
public:
	void rva004E35FF(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

// Matched DIR32 witness places this one-pointer AsciiString at VA 0x00E02E84
// in the zero-filled .data tail; the shared BFME2 header establishes its
// four-byte layout and the retail initial bytes are zero.
AsciiString g_Rva00E02E84;

class Rva003EE980
{
public:
	void rva003EE980(Int a);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE980::rva003EE980(Int a)
{
	char *p = (char *)a + 0x44;
	float f = 0.95f;
	float tmp[3];
	tmp[0] = f;
	tmp[1] = f;
	tmp[2] = f;
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E84, (Int)p, (Int)&tmp[0]);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E84, 1);
}
