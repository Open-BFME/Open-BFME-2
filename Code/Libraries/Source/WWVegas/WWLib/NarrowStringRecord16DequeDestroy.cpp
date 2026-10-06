// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
// Native0x0041A3A3 /33: destroy a range of nontrivial16-byte records.
// Record dtor independently matches14B string teardown at7FAB3 and
// typed iterator increment independently matches38B at419DF6.
// Record layout comes from its existing recovered copy/assign and deque
// pop siblings; original semantic record identity remains unknown.
#include <string>
#include <deque>

#define BFME_NARROW_RECORD16_EXTERNAL_DTOR
#include "BfmeNarrowRecord0041A617.h"
typedef _STL::deque<BfmeNarrowRecord0041A617>::iterator BfmeNarrowRecord16Iterator;
template void _STL::__destroy_aux<BfmeNarrowRecord16Iterator>(BfmeNarrowRecord16Iterator, BfmeNarrowRecord16Iterator, const _STL::__false_type&);


// Native45-byte dispatch at0x0041A459 forwards the two iterator values
// and a false-type tag to the independently rowed33-byte loop.
template void _STL::__destroy<BfmeNarrowRecord16Iterator, BfmeNarrowRecord0041A617>(BfmeNarrowRecord16Iterator, BfmeNarrowRecord16Iterator, BfmeNarrowRecord0041A617*);

// Native41-byte public range-destroy wrapper at0x0041A4F1 calls41A459.
template void _STL::_Destroy<BfmeNarrowRecord16Iterator>(BfmeNarrowRecord16Iterator, BfmeNarrowRecord16Iterator);

// Native87-byte deque destructor41A57B calls public Destroy41A4F1
// then the independently full40-byte base cleanup54FAAC. EHs preserves
// the native unwind-state store around the potentially throwing teardown.
template _STL::deque<BfmeNarrowRecord0041A617>::~deque();
