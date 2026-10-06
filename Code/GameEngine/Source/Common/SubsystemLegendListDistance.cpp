// cl: /DNDEBUG /MD /EHs-c- -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/vendor/stlport -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
//
// ??$__distance@U?$_List_iterator@USubsystemLegendEntry@@U?$_Const_traits@USubsystemLegendEntry@@@_STL@@@_STL@@@_STL@@YAHABU?$_List_iterator@USubsystemLegendEntry@@U?$_Const_traits@USubsystemLegendEntry@@@_STL@@@0@0ABUinput_iterator_tag@0@@Z
//
// retail 0x004534C3, 22 bytes.
//
// This is NOT a body a donor TU can be copied from.  The BFME 1 donor sweep
// credits the symbol to a HEADER the translation unit includes, not to the
// TU: 632 of its records place these exact bytes at 0x004534C3 and every one
// has defined_by_source false, so no TU "owns" it and land.py refuses to
// prepare one ("came from a header the TU includes and cannot be landed by
// copying this file").
//
// It is therefore instantiated here from the definition itself, at /Os, and
// it is the same conversion the other bodies in this batch are: compile the
// donor's source under BFME 2's toolchain and let it emit retail's bytes.
//
// WHAT IT IS.  stlport's _STLP_CALL __distance
// (stl/_iterator_base.h:355) for a random-access iterator is
// `return __last - __first;`, and a _List_iterator's difference is its node
// pointer difference divided by sizeof(_List_node<_Tp>) -- one shift.  So the
// whole 22-byte body is the subtract and the halve.
//
// The two parameters are `const _List_iterator&` and `const input_iterator_tag&`
// (the explicit fourth argument is the tag overload's parameter; the mangled
// `@0` after it is the null userdata marker, not a type).  Nothing dereferences
// either: the body reads only the two node pointers, so their element type is
// never instantiated and no SubsystemLegendEntry member is touched.
//
// WHICH INSTANTIATION IS WHICH, since retail's name and this one differ and
// only the node arithmetic is shared.  This file instantiates the NAME the
// order gave -- SubsystemLegendEntry, so the recorded bytes are the ones
// verified.  Retail's own tree also carries the same function over
// _List_iterator<PAX,...> (`_List_iterator<void*>`), whose node is smaller, so
// the halving shift differs; that twin is a separate body at a separate
// address and is NOT claimed here.  The element type only fixes the shift, not
// the byte sequence.
//
// Includes are ordered the way SubsystemLegend.cpp orders them, and the
// reason is load-bearing: `<list>` must come before PreRTS.h so STLport's
// node_alloc is used rather than NEWALLOC.  The struct below is a standalone
// declaration of the element type rather than the donor's real
// subsystem_legend.h, because including that header would drag the BFME-native
// ascii_string/subsystem_interface interfaces into a TU whose only definition
// must be the one below, and the element type is never dereferenced here.

#define __PLACEMENT_VEC_NEW_INLINE
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)
#include <vector>
#include "PreRTS.h"

// The retail element type.  Only its SIZE reaches the emitted code -- the
// node divide -- so a forward declaration would instantiate the same way;
// the empty struct is spelled out to keep that dependency from silently
// changing the shift.
struct SubsystemLegendEntry
{
};

// The one use the donor TU makes of std::list<Entry>::size(): the only STLport
// operation that reaches __distance for a list iterator, and the reason the
// function is instantiated at all.
void bfmeLegendEntryCountUsesDistance(std::list<SubsystemLegendEntry> *entries)
{
	(void)entries->size();
}