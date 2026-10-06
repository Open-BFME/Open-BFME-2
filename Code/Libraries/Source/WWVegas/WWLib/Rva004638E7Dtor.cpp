// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??1Rva004638E7@@QAE@XZ @0x004638E7 5B
// 5-byte dtor that is only jmp to rowed Rb_tree dtor 0x004636C6: class with single Rb_tree member at +0.
// Evidence: retail jmp 0x004636C6; callers are Unwind funclets; prev 0x004638C5 create_node next 0x004638EC dtor; per 4.8 novtable recipe and Rva005694C8Dtor precedent.
#include <map>

struct Rva00462D08Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const int, Rva00462D08Mapped> Rva00462D08Pair;
typedef _STL::_Rb_tree<int, Rva00462D08Pair, _STL::_Select1st<Rva00462D08Pair>, _STL::less<int>, _STL::allocator<Rva00462D08Pair> > Rva00462D08Tree;

class Rva004638E7
{
public:
	~Rva004638E7();
private:
	Rva00462D08Tree m_tree;
};

Rva004638E7::~Rva004638E7()
{
}
