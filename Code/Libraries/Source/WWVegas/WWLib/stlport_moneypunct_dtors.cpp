// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The four moneypunct instantiations the image carries. STLport specialises on
// the international flag, so <char,false> and <char,true> are separate classes
// with separate vftables at 0x007BC810, 0x007BC83C, 0x007BC868 and 0x007BC894,
// and each needs its own destructor body.
//
// Every one is the same eleven bytes as the other trivial facets: the class's
// own vftable store and a tail jump into locale::facet::~facet at 0x000072E0.
// The pattern members are two four-char arrays with nothing to release, so
// there is no teardown beyond the base call - which is also why defining the
// destructor is enough to make MSVC emit the vftable and the scalar deleting
// destructor beside it.

#include <locale>

namespace _STL
{

moneypunct<char, true>::~moneypunct()
{
}

moneypunct<char, false>::~moneypunct()
{
}

moneypunct<wchar_t, true>::~moneypunct()
{
}

moneypunct<wchar_t, false>::~moneypunct()
{
}

}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?init@Rva00019D90StringInit@@QAEPAXPAX@Z")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?init@Rva00019D90StringInit@@QAEPAXPAX@Z")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?init@Rva00019D90StringInit@@QAEPAXPAX@Z")
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?init@Rva00019D30StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?init@Rva00019D90StringInit@@QAEPAXPAX@Z")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?init@Rva00019D90StringInit@@QAEPAXPAX@Z")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?init@Rva00019D90StringInit@@QAEPAXPAX@Z")
