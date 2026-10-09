// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include "../../../../GameEngine/Source/Common/RegionIconSlotResizeView.h"
// Native005EFDE9..005EFE52 RET8; existing byte-verified value-fill ABI.
void _STL::vector<Rva005EFDE9Element,_STL::allocator<Rva005EFDE9Element> >::resize(size_type newSize,Rva005EFDE9Element value) {
 if(newSize<(_M_finish-_M_start)) erase(_M_start+newSize,_M_finish);
 else {
  Rva005EFDE9Element *finish=_M_finish;
  const size_type count=newSize-(_M_finish-_M_start);
  _M_fill_insert(finish,count,value);
 }
}
// Native005EFE6E..005EFE87 RET4; invoked by icon slot-count005EFE87.
void _STL::vector<Rva005EFDE9Element,_STL::allocator<Rva005EFDE9Element> >::resize(size_type n) { resize(n,Rva005EFDE9Element()); }
