// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



// Retail's value destructor 0x005011B4 is `add ecx,4; jmp 0x00500E3D`: the
// mapped record's only non-trivial member is the vector rowed as
// ??1Rva00500E3D@@QAE@XZ (RvaVectorDtorFamily.cpp), spelled as
// RvaMemberDtorForwarders.cpp spells it.
struct Rva00500E3D { ~Rva00500E3D(); void *m_start; void *m_finish; void *m_end; };
struct Rva005026B6Record { Rva00500E3D m_00; };
// Emit only the verified destructor and its required dependencies.
typedef _STL::pair<int const, Rva005026B6Record> Rva005026B6Pair;
typedef _STL::_Rb_tree<int, Rva005026B6Pair, _STL::_Select1st<Rva005026B6Pair>,
 _STL::less<int>, _STL::allocator<Rva005026B6Pair> > Rva005026B6Tree;
template Rva005026B6Tree::~_Rb_tree();
