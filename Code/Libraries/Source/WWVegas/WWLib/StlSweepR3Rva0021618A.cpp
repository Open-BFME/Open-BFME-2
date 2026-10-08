// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <stl/_algobase.h>
struct BfmePod28 {int a[7];};
namespace _STL {
template<class It,class T> It __find(It first,It last,T val,const random_access_iterator_tag &);
}
BfmePod28 *Rva0021618AFind(BfmePod28 *first,BfmePod28 *last,int key) {
 typedef BfmePod28 *(*FindByValue)(BfmePod28 *,BfmePod28 *,int,const _STL::random_access_iterator_tag &);
 FindByValue find=&_STL::__find<BfmePod28 *,int>;
 return find(first,last,key,_STL::random_access_iterator_tag());
}

// Target evidence: WB B6FF20 and native21618A..2161A5 call existing28-byte record search215F83 with begin end and by-value key plus iterator tag; prior fill identity refuted by WB and native search; no writes or count argument.
// The record view models only seven native words; original field names
// and source-level template spelling remain unknown.
