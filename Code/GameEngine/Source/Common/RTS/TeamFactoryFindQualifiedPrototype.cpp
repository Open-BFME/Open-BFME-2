// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// TeamFactory::findTeamPrototype qualified-name overload; retail 0x003A2659 141B.
// Target identity: existing named pin and evaluateHasUnits caller 0x003E941A.
// Target ABI: splitter returns an 8-byte temporary in EAX; receiver is built
// inside the full assignment expression, preserving that return pointer.
// TeamFactory-style lookup: split BfmeWord on '/' via rowed 0x0032ABDA, assign
// both halves into two AsciiStrings through rowed Rva000DF920::operator=, then
// rowed two-name findTeamPrototype. Evidence: callees all rowed, caller 0x003E941A.
#include "ascii_string.h"

#include "../../../Include/Common/BfmeWordEL.h"

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

#include "../../../Include/Common/Rva0036CA00Str.h"

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
	Rva000DF920(AsciiString &asciiString, AsciiString &b) : m_00((Rva0036CA00Str *)&asciiString), m_04((Rva0036CA00Str *)&b) {}
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
	Rva000DF920 &operator=(const BfmePairEL &pair) { return operator=((const Rva0036CA00Str *)&pair); }
};

class TeamPrototype;
class Team;

struct BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);

#include "../../../Include/Common/TeamFactory.h"

TeamPrototype *TeamFactory::findTeamPrototype(const AsciiString &word)
{
	AsciiString playerName;
	AsciiString teamName;
	Rva000DF920(playerName, teamName) = Rva00194810((const BfmeWordEL &)word);
	return findTeamPrototype(playerName, teamName);
}

// Qualified team lookup (ZH TeamFactory::findTeam(name), 0x003A40F5):
// Object::restoreOriginalTeam calls this body using
// the original qualified team name. The two-name provider owns the prototype
// lookup, singleton reuse, and inactive-team creation semantics.
Team *TeamFactory::findTeam(const AsciiString &word)
{
	AsciiString playerName;
	AsciiString teamName;
	Rva000DF920(playerName, teamName) = Rva00194810((const BfmeWordEL &)word);
	return findTeam(playerName, teamName);
}
