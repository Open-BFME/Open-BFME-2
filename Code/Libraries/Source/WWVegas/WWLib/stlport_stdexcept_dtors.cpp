// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// The nine standard exception classes, whose vftables sit consecutively at
// 0x007BDA44..0x007BDA98 with nothing claimed but the what() they all share.
// STLport declares each destructor in <stdexcept> and leaves the body to the
// library, so this unit supplies them; defining them is also what makes MSVC
// emit each class's vftable and the scalar deleting destructor beside it,
// which is the row that matters - the image parks all nine of those together
// at 0x00024B00..0x00024C00, one every 32 bytes.

#include <stdexcept>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(char const *, allocator<char> const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t, const void*);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

namespace _STL
{


// Retail builds these destructors /Od (rowed here); the deleting destructors
// below stay /O2.
#pragma optimize("", off)
// Shared base destructor: retail uses the unoptimised body folded with
// std::bad_alloc at 0x00023850.
// ?__Named_exception::~__Named_exception present-unmatched
__Named_exception::~__Named_exception() _STLP_NOTHROW_INHERENTLY
{
}

logic_error::~logic_error() _STLP_NOTHROW_INHERENTLY
{
}

runtime_error::~runtime_error() _STLP_NOTHROW_INHERENTLY
{
}

domain_error::~domain_error() _STLP_NOTHROW_INHERENTLY
{
}

invalid_argument::~invalid_argument() _STLP_NOTHROW_INHERENTLY
{
}

length_error::~length_error() _STLP_NOTHROW_INHERENTLY
{
}

out_of_range::~out_of_range() _STLP_NOTHROW_INHERENTLY
{
}

range_error::~range_error() _STLP_NOTHROW_INHERENTLY
{
}

overflow_error::~overflow_error() _STLP_NOTHROW_INHERENTLY
{
}

underflow_error::~underflow_error() _STLP_NOTHROW_INHERENTLY
{
}
#pragma optimize("", on)

// STLport 4.5.3 builds with _STLP_EXTERN_RANGE_ERRORS, so <stl/_range_errors.h>
// only declares these and src/dll_main.cpp defines them. Every container's
// range check references them, but retail never constructs an out_of_range
// (its vftable at 0x007BDA80 is stored only by the destructor), so the linker
// dead-stripped all three.

// ?__stl_throw_range_error absent-from-retail
void _STLP_CALL __stl_throw_range_error(const char *__msg)
{
	throw range_error(string(__msg));
}

// ?__stl_throw_out_of_range absent-from-retail
void _STLP_CALL __stl_throw_out_of_range(const char *__msg)
{
	throw out_of_range(string(__msg));
}

// ?__stl_throw_length_error absent-from-retail
void _STLP_CALL __stl_throw_length_error(const char *__msg)
{
	throw length_error(string(__msg));
}

}
