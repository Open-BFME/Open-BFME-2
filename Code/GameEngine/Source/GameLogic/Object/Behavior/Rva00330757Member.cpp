// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00330757Member@@QAE@XZ, retail 0x00330757, 23 bytes. Homeless
// vector-plus-flags member: a 12-byte vector at +0 built through the
// ICF-folded BfmeE16 Vector_base at 0x00211E58 (allocator temp on esp+7)
// plus an int at +0xC defaulted with the `|= -1` idiom (Prone precedent:
// the OR form emits the leading OR under /O1). The StancesBehavior ctor TU
// constructs this member out of line at +0x20 through the pin, so this
// shard carries the byte-exact body and the row supersedes the pin. The
// address-derived name is honest: identity beyond the vector-plus-flags
// shape is not recovered. Element type is the 16-byte stand-in (BfmeE16)
// whose vector_base is the rowed 0x211E58 body.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00330757Member
{
public:
	Rva00330757Member();

private:
	_STL::vector<BfmeE16> m_items; // +0
	int m_flags; // +0xC
};

// ??0Rva00330757Member@@QAE@XZ @0x330757
Rva00330757Member::Rva00330757Member()
	: m_items(_STL::allocator<BfmeE16>())
{
	m_flags |= -1;
}
