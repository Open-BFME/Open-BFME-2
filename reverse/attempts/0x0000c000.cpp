// ?do_get@?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.9 date=2026-09-02
// ?do_get@?$money_get@... (long double & units), the narrow twin
// partial score=0.9 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// The vendored instantiation is enough - no hand-written body is needed.
// Identified from the facet vtable rather than from any caller: nothing calls
// this address directly because it is a virtual. The three-slot vtable holding
// it is the money_get shape - deleting destructor plus the two do_get
// overloads - and the slot next to it is the string_type overload, whose
// derived boundary the ledger splits in two. The body confirms it against
// _monetary.c line 156: default-construct string_type __buf, call the other
// do_get through the vtable, push_back(0), hand __b/__e to
// __get_decimal_integer, or eofbit in when __s == __end, and free __buf.
// The two _M_getc calls with the [esp+0x3e]/[esp+0x46] byte compare after
// them are istreambuf_iterator::equal inlined.
//
// 277 bytes against 277, and the instruction sequence is the same instruction
// for instruction. The whole difference is which callee-saved register holds
// which value: retail loads [esp+0x50] into edi and [esp+0x40] into ebp, cl
// 13.10 loads them into ebp and ebx. Both push the same four registers in the
// same order, so the prologue matches and the first difference is at 0x28.
//
// Refuted: /O2, /O1, /Ox, /Og, /Ob2, /Gy, -D_STLP_USE_MALLOC and -D_CRTIMP=
// all give the identical 277 bytes with the identical renaming (/O1 is worse,
// 202 bytes). The source is upstream STLport and cannot be reordered to move
// the allocation without diverging from it.

#include <locale>

template class _STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
