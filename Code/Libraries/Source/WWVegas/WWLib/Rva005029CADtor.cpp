// cl: /O1 /arch:SSE /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$_Rb_tree@HU?$pair@$$CBHURva00501776@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501776@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501776@@@_STL@@@2@@_STL@@QAE@XZ
// retail 0x005029CA 56B: _Rb_tree<int pair<const int Rva00501776>> dtor calling
// rowed clear 0x005027B0 then null-checked header free 0x00030830 under one EH
// state. Evidence: same 56B EH shell as rowed int-Pod52 tree dtor 0x00425FB4
// and StlportRbTreeDtorFamily siblings; clear callee rowed in
// stlport_tree_erase_00502610.cpp.
#include <map>

struct Rva00501776
{
	char m_pad[0x2C];
	~Rva00501776();
};

typedef _STL::pair<const int, Rva00501776> Erase00502610Value;
typedef _STL::_Rb_tree<int, Erase00502610Value, _STL::_Select1st<Erase00502610Value>, _STL::less<int>, _STL::allocator<Erase00502610Value> > Erase00502610Tree;

// These members are defined by the verified erase/clear provider.
extern template void Erase00502610Tree::clear();
extern template void Erase00502610Tree::_M_erase(Erase00502610Tree::_Link_type);
template Erase00502610Tree::~_Rb_tree();

// Native5029C5..5029CA forwards unchanged ECX to the owned clear5027B0.
// Pointer-only outer view; no original application identity inferred.
class Rva005029C5TreeClearForward { public: void cleanup(); };
void Rva005029C5TreeClearForward::cleanup()
{ reinterpret_cast<Erase00502610Tree *>(this)->clear(); }
