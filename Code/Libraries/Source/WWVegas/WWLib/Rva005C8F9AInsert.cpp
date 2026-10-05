// cl: /O1 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva005C8F9A@Rva005C8F9A@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@@_STL@@_N@_STL@@ABU?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@3@@Z @0x005C8F9A 35B
// __thiscall wrapper that forwards to the rowed _Rb_tree<float,pair<const
// float,opaque>>::insert_unique 0x005AD1A7 and repackages the returned
// pair<iterator,bool> through a hidden-pointer tmp. this = embedded tree at
// caller+0x2c (caller 0x005C902A: lea ecx,[esi+0x2c]); [ebp+8] = hidden ret
// ptr, [ebp+0xc] = const value ref. Declarations spell the rowed callee name
// exactly (copied from stlport_rb_tree_float_00372ff4.cpp); BfmeE-size opaque
// stand-in kept consistent with that TU.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;

class Rva005C8F9A
{
public:
	_STL::pair<Tree00372FF4::iterator, bool> rva005C8F9A(const TreeValue00372FF4 &v);
private:
	Tree00372FF4 m_tree; // +0
};

_STL::pair<Tree00372FF4::iterator, bool> Rva005C8F9A::rva005C8F9A(const TreeValue00372FF4 &v)
{
	_STL::pair<Tree00372FF4::iterator, bool> tmp = m_tree.insert_unique(v);
	return tmp;
}
