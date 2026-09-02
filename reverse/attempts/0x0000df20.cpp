// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GABV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z
// partial score=0.8 date=2026-09-02
// ?do_put@?$money_put@G... (string_type), the wide twin
// partial score=0.8 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// Slot 1 of the wide money_put vtable, which vtable_gaps.py found as the one
// unnamed entry in a three-slot run - deleting destructor plus the two do_put
// overloads, the same shape as the money_get vtable two entries earlier. The
// vendored instantiation compiles to exactly 2610 bytes against 2610, which is
// what makes the slot assignment more than a guess.
//
// It is wrong from offset 0 all the same. Retail opens
//   push ebp / mov ebp, esp / and esp, -8
// - an ebp frame with the stack realigned to 8 - and then the EH prolog; the
// vendored build has no ebp frame at all and addresses everything off esp,
// which shifts the whole body. Something in retail's translation unit needs an
// 8-byte-aligned local that this one does not have.
//
// Refuted: /Zp8, /Zp16 and /GS give the identical 2610 bytes; /Oy- gives 2565
// and moves the first difference only from 0x00 to 0x03.

#include <locale>

template class _STL::money_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
