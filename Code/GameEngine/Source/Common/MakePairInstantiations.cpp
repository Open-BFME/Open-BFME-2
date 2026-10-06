// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Include/Precompiled -Ireference/open-bfme-1/game/GameEngine/Source/Common/System -Ireference/open-bfme-1/game/GameEngine/Source/Common -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
#include <utility>

// The three byte-identical 22-byte bodies at 0x000699D0, 0x000E7090 and
// 0x0058CCA0 are STLport's `_STL::make_pair`.  IDENTITY RECOVERED.
//
//     mov eax,[esp+8] / mov ecx,[eax] / mov eax,[esp+4] / mov edx,[esp+0xC]
//     mov [eax],ecx / mov cl,[edx] / mov [eax+4],cl / ret
//
// WHAT THE BYTES SHOW.  __cdecl with three arguments, of which the FIRST is only
// ever stored through and then left in eax: the hidden return pointer of a class
// returned by value.  The other two are each dereferenced exactly once, so both
// arrive by const reference -- which is make_pair's signature and not the
// constructor's, since a constructor would take `this` in ecx and end in
// `ret 8`.  (That constructor is also in the image, at 136 addresses; it is a
// different body and is not claimed here.)
//
// The returned object is built as a DWORD at +0 and a single BYTE at +4, so the
// pair is <four-byte, one-byte> with the second field's own alignment padding
// left untouched -- the canonical `pair<T, bool>` that STLport's associative
// insert returns.
//
// NOT RECOVERED: `_T1`.  It is four bytes and is copied without being
// dereferenced, which fits a pointer and equally fits an integer; a pointer is
// written below because that is what the insert-result pair carries.  `_T2` is
// pinned to a one-byte type by the `mov cl` / `mov [eax+4],cl` pair.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Duplicate COMDATs of one template symbol
// fold to a single address, so three addresses mean three different `_T1`.
// The element names are address-derived and disclaim identity.

class Rva000699D0Elem;

// ?$make_pair@PAVRva000699D0Elem@@_N@_STL@@YA?AU?$pair@PAVRva000699D0Elem@@_N@0@ABQAVRva000699D0Elem@@AB_N@Z
// retail 0x001FF591, 22 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/MakePairInstantiations.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other two instantiations are omitted.
template _STL::pair<Rva000699D0Elem *, bool> _STL::make_pair<Rva000699D0Elem *, bool>(
	Rva000699D0Elem *const &, const bool & );
