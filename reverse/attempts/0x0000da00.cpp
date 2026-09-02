// ?do_get_date@?$time_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.9 date=2026-09-02
// ?do_get_date@?$time_get@D... at 0x0000da00
// partial score=0.9 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// Found by lining the narrow time_get vtable up against its two already-named
// slots. The seven slots are the destructor then do_date_order, do_get_time,
// do_get_date, do_get_weekday, do_get_monthname, do_get_year in declaration
// order, and weekday and monthname were already claimed, so the three gaps
// read off directly. do_date_order is the three-byte xor eax eax / ret at
// 0x0065CE90, folded with basic_streambuf::sync.
//
// A plain vendored instantiation of time_get<char> emits all three - the
// hand-written stlport_narrow_time_get_names.cpp does not - and this one is
// 92 bytes out of 160 with the first difference at 0x0E. Everything is the
// same instruction in the same place; what differs is which stack slot holds
// which value (retail reads [esp+0x10] and [esp+0x2C] where cl reads
// [esp+0x14] and [esp+0x28]) and the order of two pushes into
// __get_formatted_time, 50 51 53 57 against 50 53 51 57.
//
// __get_formatted_time at 0x0000D650 is now pinned from the REL32 here, which
// also identifies that 818-byte gen row.
//
// do_get_year at 0x00009C10 is NOT close - 187 of 192 - so it is not banked.

#include <locale>

template class _STL::time_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
