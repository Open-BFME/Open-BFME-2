// ?rva00337DEF@LuaScriptEngine@@QAEPAURva00336283Element@@ABVAsciiString@@@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00337DEF@LuaScriptEngine@@QAEPAURva00336283Element@@ABVAsciiString@@@Z @0x00337DEF 187B.
// Identity (target): a LuaScriptEngine member reached through the global
// TheLuaScriptEngine (VA 0x00E01DBC) at 0x0039F18E (Team update) and from
// 0x00268436, 0x0026ED77, 0x0029572E and 0x00337F51; the WorldBuilder twin
// (0x00C02360) is unnamed, so the name is address-derived.
// Target facts: an empty name (rowed isEmpty 0x00001E2F) finds nothing; the
// 20-byte record vector at +0xB0/+0xB4 is sorted once (rowed sort driver
// 0x00337DA9, sorted flag +0xAC); a key record is built from the name
// (rowed ctor 0x003323AD, dtor 0x003372B7), binary-searched through the
// pinned STLport __lower_bound 0x00335CAE and accepted only when its name
// compares equal (rowed StringBase compare 0x000069D6).
#include "ascii_string.h"

struct S4SortElem20
{
	char m_bfmeBytes[20];
};

struct S4Cmp002EB8E0
{
};

void Rva002EBEF0(S4SortElem20 *first, S4SortElem20 *last, S4Cmp002EB8E0 comp);

struct Rva00336283Element
{
	const AsciiString &name() const { return *(const AsciiString *)this; }
	char m_bytes[20];
};

namespace _STL
{
template <class T> struct less
{
};

template <class ForwardIter, class T, class Compare, class Distance>
ForwardIter __lower_bound(ForwardIter first, ForwardIter last, const T &val, Compare comp, Distance *) throw();

template <class ForwardIter, class T, class Compare>
inline ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T &val, Compare comp)
{
	return __lower_bound(first, last, val, comp, (int *)0);
}
}

struct Rva00336283Vector
{
	Rva00336283Element *begin() const { return m_start; }
	Rva00336283Element *end() const { return m_finish; }

	Rva00336283Element *m_start;
	Rva00336283Element *m_finish;
};

class Rva003371B1
{
public:
	~Rva003371B1();
private:
	char m_bytes[20];
};

class Rva003323AD : public Rva003371B1
{
public:
	Rva003323AD(const StringBase<char> &s);
};

class LuaScriptEngine
{
public:
	Rva00336283Element *rva00337DEF(const AsciiString &name);

private:
	char m_pad00[0xAC];
	bool m_sorted; // +0xAC
	Rva00336283Vector m_records; // +0xB0
};

Rva00336283Element *LuaScriptEngine::rva00337DEF(const AsciiString &name)
{
	if (((const StringBase<char> &)name).isEmpty())
		return 0;

	if (!m_sorted)
	{
		Rva002EBEF0((S4SortElem20 *)m_records.begin(), (S4SortElem20 *)m_records.end(), S4Cmp002EB8E0());
		m_sorted = true;
	}

	Rva003323AD key((const StringBase<char> &)name);
	Rva00336283Element *it = _STL::lower_bound(m_records.begin(), m_records.end(), *(const Rva00336283Element *)&key,
		_STL::less<Rva00336283Element>());
	if (it == m_records.end() || ((const StringBase<char> &)it->name()).compare((const StringBase<char> &)name) != 0)
		it = 0;
	return it;
}
