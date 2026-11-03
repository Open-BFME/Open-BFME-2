// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ArmyDetailsPanel Populate passes its army context as the comparator word.
// Native median5E4534 and partition5E459F invoke the stateful5E4300 comparator,
// which dereferences that word. These are not greater<int> instantiations.
// STLport4.5.3 introsort control flow; the existing pointer-median provider
// describes the same reference addresses without introducing another alias.
struct Rva005E4300Context;
#include "Rva005E4300Cmp.h"
namespace _STL {
template<class It,class Compare> It __median(It,It,It,Compare);
template<class It,class T,class Compare> It __unguarded_partition(It,It,T,Compare);
template<class It,class T,class Compare> void __partial_sort(It,It,It,T*,Compare);
template<class It,class Compare> void __final_insertion_sort(It,It,Compare);
template<class It,class Compare>
void partial_sort(It first,It middle,It last,Compare comp) {
 __partial_sort(first,middle,last,(int*)0,comp);
}
template<class It,class T,class Size,class Compare>
void __introsort_loop(It first,It last,T*,Size depth,Compare comp) {
 while(last-first>16) {
  if(depth==0) {partial_sort(first,last,last,comp);return;}
  --depth;
  It cut=__unguarded_partition(first,last,T(*__median(first,first+(last-first)/2,last-1,comp)),comp);
  __introsort_loop(cut,last,(T*)0,depth,comp);
  last=cut;
 }
}
template<class Size> inline Size __lg(Size n) {
 Size k;for(k=0;n!=1;n>>=1)++k;return k;
}
template<class It,class Compare>
void sort(It first,It last,Compare comp) {
 if(first!=last) {
  __introsort_loop(first,last,(int*)0,__lg(last-first)*2,comp);
  __final_insertion_sort(first,last,comp);
 }
}
template void partial_sort<int*,Rva005E4300Cmp>(int*,int*,int*,Rva005E4300Cmp);
template void __introsort_loop<int*,int,int,Rva005E4300Cmp>(int*,int*,int*,int,Rva005E4300Cmp);
template void sort<int*,Rva005E4300Cmp>(int*,int*,Rva005E4300Cmp);
}
