// ?do_get_time@?$time_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.9 date=2026-09-02
// ?do_get_time@?$time_get@G... at 0x0000eeb0
// partial score=0.9 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// The wide twin of the narrow bank at the matching address, and it behaves
// identically: 72 bytes out of 144 with the first difference at 0x0E, every
// instruction the same in the same place, and the only disagreements the
// stack slot each value lives in and the order of two pushes into
// __get_formatted_time. That the narrow and wide bodies fail the same way at
// the same offset is the strongest evidence the slot assignment is right.
//
// Refuted on this one: /O2 /Gy /G6 /Ox are identical to the default; /Ob0
// /Os and /Oy- all move the first difference back to 0x00.

#include <locale>

template class _STL::time_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
