// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Target copy constructs three sixteen-byte blocks; assignment uses a separate
// member operation. Original type names remain unknown.
#include <vector>
struct BfmeFixedBlock16 { unsigned int words[4]; BfmeFixedBlock16(); };
struct BfmeFixedObject60 {
 unsigned int word_00,word_04,word_08;
 BfmeFixedBlock16 blocks_0C[3];
 BfmeFixedObject60();
 BfmeFixedObject60(const BfmeFixedObject60& rhs);
 BfmeFixedObject60& operator=(const BfmeFixedObject60& rhs);
};
typedef char FixedObjectExtent[sizeof(BfmeFixedObject60) == 60 ? 1 : -1];

template class _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >;
