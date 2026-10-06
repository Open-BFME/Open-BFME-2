// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??1Rva005694C8@@QAE@XZ @0x005694C8 5B
// 5-byte dtor that is only jmp to rowed Rb_tree dtor 0x5693D4: novtable class with single Rb_tree member at +0.
// Evidence: retail jmp 0x5693D4; prev partial_sort next teardown; no vptr stores.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct Rva00568FE4Key { float x; float y; unsigned short w; unsigned short pad; };
struct Rva00568FE4Less {
  bool operator()(const Rva00568FE4Key &a, const Rva00568FE4Key &b) const {
    if (a.x < b.x) return false;
    if (a.x > b.x) return true;
    if (a.y < b.y) return false;
    if (a.y > b.y) return true;
    return a.w < b.w;
  }
};
typedef _STL::_Rb_tree<Rva00568FE4Key, Rva00568FE4Key, _STL::_Identity<Rva00568FE4Key>, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Tree;

class Rva005694C8
{
public:
	~Rva005694C8();
private:
	Rva00568FE4Tree m_tree;
};

Rva005694C8::~Rva005694C8()
{
}
