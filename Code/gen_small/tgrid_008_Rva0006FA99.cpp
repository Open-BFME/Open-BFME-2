// cl: -EHsc /Os -Ireference/open-bfme-1/game/gen_small
// stlport
// ?operator=@?$_Slist_base@HV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@@Z
// retail 0x0006FA99, 38 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/gen_small/tgrid_008.cpp (reference/open-bfme-1): the donor
// preamble and this one slist<int> instantiation (the donor's other containers
// omitted). The STLport slist header emits the allocator assignment operator
// for _Slist_base<int>; the payload is a real int, so the bytes are the vendor
// template over that payload.
#include <slist>

template class _STL::slist<int >;