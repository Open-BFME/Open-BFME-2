// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva004E35D5@Rva004E35D5@@QAEXABVAsciiString@@HH@Z @0x004E35D5 42B.
// Map-dispatch: find AsciiString key in map at +0, compare against end,
// load mapped pointer at node+0x14, null-check, virtual slot 0xC.
// Donor: reference/open-bfme-1/Code/GameEngine/Source/Common/V4LookupThenVirtualNotify.cpp
// (Rva003BAD00Owner::notify0C, same shape with int key, slots 4/8/0xC).
// Retail evidence: call to rowed _M_find at 0x001F8437, cmp eax,[esi],
// mov eax,[eax+0x14], call [edx+0xC], ret 0xC. Callers pass static
// AsciiStrings (BordersEffect etc at 0x00E02E64+) with (ptr, int).
// Map spelled map<AsciiString,AsciiString> so the emitted _M_find names
// the rowed worker (FontLibraryFindRecord precedent); second recast to target.
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

class Rva004E35D5Target
{
public:
	virtual void slot00();
	virtual void slot04(Int a);
	virtual void slot08(Int a);
	virtual void slot0C(Int a, Int b);
	virtual void slot10(Int a, Int b);
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, Int b);
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

class Rva004E3629
{
public:
	void rva004E3629(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

void Rva004E35AF::rva004E35AF(const AsciiString &key, Int a)
{
	_STL::map<AsciiString, AsciiString>::iterator it = m_map.find(key);
	if (it == m_map.end())
		return;
	Rva004E35D5Target *t = *(Rva004E35D5Target **)&it->second;
	if (t == 0)
		return;
	t->slot04(a);
}

void Rva004E35D5::rva004E35D5(const AsciiString &key, Int a, Int b)
{
	_STL::map<AsciiString, AsciiString>::iterator it = m_map.find(key);
	if (it == m_map.end())
		return;
	Rva004E35D5Target *t = *(Rva004E35D5Target **)&it->second;
	if (t == 0)
		return;
	t->slot0C(a, b);
}

void Rva004E35FF::rva004E35FF(const AsciiString &key, Int a, Int b)
{
	_STL::map<AsciiString, AsciiString>::iterator it = m_map.find(key);
	if (it == m_map.end())
		return;
	Rva004E35D5Target *t = *(Rva004E35D5Target **)&it->second;
	if (t == 0)
		return;
	t->slot10(a, b);
}

void Rva004E3629::rva004E3629(const AsciiString &key, Int a)
{
	_STL::map<AsciiString, AsciiString>::iterator it = m_map.find(key);
	if (it == m_map.end())
		return;
	Rva004E35D5Target *t = *(Rva004E35D5Target **)&it->second;
	if (t == 0)
		return;
	t->slot08(a);
}
