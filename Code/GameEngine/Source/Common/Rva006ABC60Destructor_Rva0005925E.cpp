// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS -DNDEBUG -MD -EHsc /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Retail 0x0005925E is the non-virtual destructor for an owner containing
// six 12-byte vector headers, an AsciiString tree, and a trailing helper.
// The member extents are taken from the three destructor calls and the
// eh-vector arguments in the retail body.

// stlport
#include <vector>
#include <set>
#include "ascii_string.h"

// The independently matched constructor establishes six request vectors of
// trivial eight-byte records at +0x4c and an AsciiString set at +0xa0.
// Use their existing providers instead of a private 12-byte cleanup class.
struct BfmePod8 { int m_at00, m_viewType; };
namespace _STL {
template <> vector<BfmePod8>::~vector();
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>,
    less<AsciiString>, allocator<AsciiString> > Rva006ABC60Tree;
template <> Rva006ABC60Tree::~_Rb_tree();
}

#include "../../Include/Common/Rva00056CF8.h"
class Rva006ABC60TrailingMember
{
public:
	// Destruction is the rowed ??1Rva00056CF8, reached by a qualified call.
	__declspec(dllimport) __forceinline ~Rva006ABC60TrailingMember() { ((Rva00056CF8 *)this)->Rva00056CF8::~Rva00056CF8(); }
};

typedef _STL::Rva006ABC60Tree Rva006ABC60Tree;

class Rva006ABC60
{
public:
	~Rva006ABC60();

private:
	char m_pad4c[0x4c];
	_STL::vector<BfmePod8> m_elements[6];
	char m_pad94[0x0c];
	Rva006ABC60Tree m_tree;
	char m_padac[0x10c];
	Rva006ABC60TrailingMember m_trailing;
};

Rva006ABC60::~Rva006ABC60()
{
}
