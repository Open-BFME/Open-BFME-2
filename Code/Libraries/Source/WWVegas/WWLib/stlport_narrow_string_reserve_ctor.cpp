// cl: /Od /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_string<char> reserve-tag constructor, 0x00027150 / 129B.
// Native target ignores the first stack argument, allocates count+1 through
// rowed _M_allocate_block (0x00007460), and writes only the final NUL.
// This is _String_reserve_t, not the const-char/count copying constructor:
// no input range is read or copied. Native callers at 0x001F94D2 and
// 0x001F9569 pass a one-byte empty tag from their frame plus the capacity.
// The vendor header instantiated verbatim produces the full 129-byte body,
// including the SEH frame, allocator proxy construction and RET12 boundary.
#include <string>
namespace _STL {
template basic_string<char, char_traits<char>, allocator<char> >::basic_string(_Reserve_t, unsigned, const allocator<char> &);
}
