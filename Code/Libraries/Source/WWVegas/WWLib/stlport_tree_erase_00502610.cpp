// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// ?_M_erase for map<int Rva00501776> @0x00502610 53B: Rb_tree erase recursing
// right then walking left via rowed pair dtor 0x005017AC and free 0x00030830.
// Evidence: retail lea ecx [esi+0x10] calls 0x005017AC then free; self-call
// at 0x00502622; caller at 0x005027BE; neighbours in
// stlport_map_int_vector_vector_pod88.cpp. Mapped Rva00501776 is 0x2C with
// vectors at +0x14/+0x20 per Rva00501776Dtor.cpp; pair dtor ICF-folds onto
// Rva005017AC 8B tail-jmp.
#include <map>

struct Rva00501776
{
	char m_pad[0x2C];
	~Rva00501776();
};

typedef _STL::pair<const int, Rva00501776> Erase00502610Value;
typedef _STL::_Rb_tree<int, Erase00502610Value, _STL::_Select1st<Erase00502610Value>, _STL::less<int>, _STL::allocator<Erase00502610Value> > Erase00502610Tree;

template void Erase00502610Tree::_M_erase(Erase00502610Tree::_Link_type);
template void Erase00502610Tree::clear();
