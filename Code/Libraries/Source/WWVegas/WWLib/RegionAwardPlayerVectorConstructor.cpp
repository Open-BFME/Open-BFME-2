// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// Native5ED9A9..5EDA14 creates a20-byte-record vector of the requested count.
// Its owning752B RegionAwardMovieClip constructor requests two players;
// inline record defaults are read from the native stack temporary. The
// actual STLport4.5.3 count constructor is exact107B. Its11B allocation proxy
// and60B base are full relocation twins of the existing14F3C4/4FF36C owners;
// authentic template instantiations provide those folds without new pins.
#include "unicode_string.h"
#include <vector>
struct BfmeStringRecord005ED5F3 {
 UnicodeString text;
 unsigned int word0,word1,word2,word3;
 BfmeStringRecord005ED5F3():word0(0),word1(0),word2(-1),word3(-1){}
 BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3&);
};
namespace _STL{
template<> void _Construct<BfmeStringRecord005ED5F3,BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3*,const BfmeStringRecord005ED5F3&);
template<> BfmeStringRecord005ED5F3 *uninitialized_fill_n<BfmeStringRecord005ED5F3*,unsigned int,BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3*,unsigned int,const BfmeStringRecord005ED5F3&);
}
typedef _STL::vector<BfmeStringRecord005ED5F3,_STL::allocator<BfmeStringRecord005ED5F3> > Records;
template Records::vector(unsigned int);

template _STL::_Vector_base<BfmeStringRecord005ED5F3,_STL::allocator<BfmeStringRecord005ED5F3> >::_Vector_base(unsigned int,const _STL::allocator<BfmeStringRecord005ED5F3>&);

template _STL::_STLP_alloc_proxy<BfmeStringRecord005ED5F3*,BfmeStringRecord005ED5F3,_STL::allocator<BfmeStringRecord005ED5F3> >::_STLP_alloc_proxy(const _STL::allocator<BfmeStringRecord005ED5F3>&,BfmeStringRecord005ED5F3*);
