// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0?$_Rb_tree@HU?$pair@$$CBHPAX@_STL@@U?$_Select1st@U?$pair@$$CBHPAX@_STL@@@2@URva001FDAB0Less@@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@QAE@ABV01@@Z,
// retail 0x001FDAB0, 165 bytes. Chain lane: same map<int,void*>-layout copy
// ctor shape as 0x001FDA0B but calling the second twin copy at 0x001FD7C4
// (via the Rva001FDAB0Less _M_copy fold pin). The comparator is empty and
// never called by this body so codegen is identical; the address-scoped
// comparator name keeps the ledger row unique. Base ctor and get_allocator
// resolve through the existing HPAX pins.
#include <map>

struct Rva001FDAB0Less
{
	bool operator()(int a, int b) const;
};

typedef _STL::_Rb_tree<int, _STL::pair<const int, void *>, _STL::_Select1st<_STL::pair<const int, void *> >, Rva001FDAB0Less, _STL::allocator<_STL::pair<const int, void *> > > IntPtrCopyTree2;
template IntPtrCopyTree2::_Rb_tree(const IntPtrCopyTree2 &);
