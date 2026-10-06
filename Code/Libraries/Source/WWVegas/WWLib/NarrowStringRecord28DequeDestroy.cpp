// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
// Native41A382/33 destroys two iterator values' range using independently
// rowed record dtor41A200 and full36-byte verified increment419DD2.
// Layout and node stride come from target copy/assign/pop/push bodies;
// STLport template semantics are reference source. Original record name unknown.
#include <deque>
#include "BfmeNarrowRecord0041A5D2.h"
typedef _STL::deque<BfmeNarrowRecord0041A5D2>::iterator BfmeNarrowRecord28Iterator;
template void _STL::__destroy_aux<BfmeNarrowRecord28Iterator>(BfmeNarrowRecord28Iterator, BfmeNarrowRecord28Iterator, const _STL::__false_type&);

// Native45-byte dispatch41A42C forwards two iterator values and false tag
// to the independently rowed33-byte loop41A382.
template void _STL::__destroy<BfmeNarrowRecord28Iterator, BfmeNarrowRecord0041A5D2>(BfmeNarrowRecord28Iterator, BfmeNarrowRecord28Iterator, BfmeNarrowRecord0041A5D2*);

// Native direct entry41A4C8 is called by the Ghidra-bounded deque dtor
//41A51F at41A554; full41 bytes end inret and dispatch to41A42C.
template void _STL::_Destroy<BfmeNarrowRecord28Iterator>(BfmeNarrowRecord28Iterator, BfmeNarrowRecord28Iterator);

// Native87-byte deque destructor41A51F calls public Destroy41A4C8
// then the independently full40-byte base cleanup54FAAC. EHs preserves
// the native unwind-state store around the potentially throwing teardown.
template _STL::deque<BfmeNarrowRecord0041A5D2>::~deque();
