// ?rva003A2659@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVBfmeWordEL@@@Z
// partial score=0.96 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// ?rva003A2659@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVBfmeWordEL@@@Z @0x003A2659 141B
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
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
};

class TeamPrototype;

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
	TeamPrototype *rva003A2659(const BfmeWordEL &word);
};

struct BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);

// ?rva003A2659@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVBfmeWordEL@@@Z present-unmatched
TeamPrototype *Rva0039FE6COwner::rva003A2659(const BfmeWordEL &word)
{
	AsciiString a;
	AsciiString b;
	{
		BfmePairEL tmp = Rva00194810(word);
		HelperInit helper = { (Rva0036CA00Str *)&a, (Rva0036CA00Str *)&b };
		((Rva000DF920 *)&helper)->operator=((const Rva0036CA00Str *)&tmp);
	}
	return findPrototype(a, b);
}
