// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ??0Rva00415B54@@QAE@ABVAsciiString@@@Z @0x00415B54 61B
// Evidence: leaf between set ctor 0x00415B15 and parseFromINI 0x00415C56;
// base AsciiString copy via StringBase narrow copy 0x000365F0 plus int +4 init 0x64
// plus set<Rva00415B15Element> at +8 via rowed set ctor; single caller unclaimed
// so honest address ctor name.
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

Rva00415B54::Rva00415B54(const AsciiString &that) : AsciiString(that), m_04(0x64)
{
}
