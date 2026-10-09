// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// TeamFactory::findTeamPrototype qualified-name overload; retail 0x003A2659 141B.
// Target identity: existing named pin and evaluateHasUnits caller 0x003E941A.
// Target ABI: splitter returns an 8-byte temporary in EAX; receiver is built
// inside the full assignment expression, preserving that return pointer.
// TeamFactory-style lookup: split BfmeWord on '/' via rowed 0x0032ABDA, assign
// both halves into two AsciiStrings through rowed Rva000DF920::operator=, then
// rowed findPrototype. Evidence: callees all rowed, caller 0x003E941A.
#include "ascii_string.h"

class BfmeWordEL
{
	void *m_data;
};

namespace _STL
{
	template <class T1, class T2> struct pair
	{
		T1 first;
		T2 second;
		~pair();
	};
}

// ??1BfmePairEL@@QAE@XZ present-unmatched
struct BfmePairEL
{
	BfmeWordEL first;
	BfmeWordEL second;
	~BfmePairEL() { ((:: _STL::pair<const AsciiString, AsciiString> *)this)->~pair(); }
};

class Rva0036CA00Str
{
	void *m_item;
};

struct HelperInit
{
	Rva0036CA00Str *m_00;
	Rva0036CA00Str *m_04;
};

class Rva000DF920
{
	Rva0036CA00Str *m_00;
	Rva0036CA00Str *m_04;
public:
	Rva000DF920(AsciiString &a, AsciiString &b) : m_00((Rva0036CA00Str *)&a), m_04((Rva0036CA00Str *)&b) {}
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
	Rva000DF920 &operator=(const BfmePairEL &pair) { return operator=((const Rva0036CA00Str *)&pair); }
};

class TeamPrototype;
class Team;

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
	Team *rva003A3E37(const AsciiString &a, const AsciiString &b);

};

struct BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &word);
	Team *rva003A40F5(const AsciiString &word);
};

TeamPrototype *TeamFactory::findTeamPrototype(const AsciiString &word)
{
	AsciiString a;
	AsciiString b;
	Rva000DF920(a, b) = Rva00194810((const BfmeWordEL &)word);
	return ((Rva0039FE6COwner *)this)->findPrototype(a, b);
}

// Qualified team lookup: Object::restoreOriginalTeam calls this body using
// the original qualified team name. The two-name provider owns the prototype
// lookup, singleton reuse, and inactive-team creation semantics.
Team *TeamFactory::rva003A40F5(const AsciiString &word)
{
	AsciiString a;
	AsciiString b;
	Rva000DF920(a, b) = Rva00194810((const BfmeWordEL &)word);
	return ((Rva0039FE6COwner *)this)->rva003A3E37(a, b);
}
