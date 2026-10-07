// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <string>

// Native base cleanup is supplied by the independently verified B3C0 owner.
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
// The canonical default constructor is verified at retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }


namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

template <>
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(
        char*, size_t);

template <>
basic_string<char, char_traits<char>, allocator<char> >&
basic_string<char, char_traits<char>, allocator<char> >::assign(
        const basic_string<char, char_traits<char>, allocator<char> >&);

// The retail-proven reserve body is emitted by stlport_narrow_string_reserve.cpp.
template <>
void basic_string<char, char_traits<char>, allocator<char> >::reserve(
        unsigned int);
}

template class _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeFillV16@@YAPADPADID@Z=?assign@?$char_traits@D@_STL@@SAPADPADID@Z")
#pragma comment(linker, "/alternatename:?bfmeFillV14@@YAPADPADID@Z=?assign@?$char_traits@D@_STL@@SAPADPADID@Z")
#pragma comment(linker, "/alternatename:?rva0082ADB0Fill@@YAXPAD0ABD@Z=?fill@_STL@@YAXPAD0ABD@Z")
#pragma comment(linker, "/alternatename:?bfmeCallVMC@@YAXHHH@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAssignPL@BfmeThingPL@@QAEXPAD0@Z=?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD0@Z")
#pragma comment(linker, "/alternatename:?rva0082C6E0CopyValues@@YAPAURva0082C6E0Value@@PAU1@00@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")
