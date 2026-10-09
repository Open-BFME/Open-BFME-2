// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// Retail's generic-widening init is owned by stlport_basic_ios_init.cpp.
// Leave this specialization declared so this unit does not emit a different copy.
namespace _STL {
template <> void basic_ios<char, char_traits<char> >::init(
    basic_streambuf<char, char_traits<char> > *);
}


template class _STL::basic_fstream<char, _STL::char_traits<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeEraseV44@BfmeStrV44@@QAEXPAD0@Z=?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeCopyChV24@@YAXPAD0@Z=?assign@?$char_traits@D@_STL@@SAXAADABD@Z")
#pragma comment(linker, "/alternatename:?bfmeEraseV24@BfmeStrV24@@QAEXPAD0@Z=?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeEraseV16@BfmeStrV16@@QAEXPAD0@Z=?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeEraseV14@BfmeStrV14@@QAEXPAD0@Z=?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeEraseVME@BfmeStrVME@@QAEXPAD0@Z=?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z")
