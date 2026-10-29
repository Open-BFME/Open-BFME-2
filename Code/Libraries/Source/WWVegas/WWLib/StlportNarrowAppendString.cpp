// cl: /Od /Ob2 /DNDEBUG /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.5.3 basic_string<char>::append(const basic_string&), retail
// 0x0002B250 57B: the header body append(__s._M_start, __s._M_finish),
// forwarding the char* range to the pinned forward-iterator append 0x0001B3E0.
// Identity: it loads the argument's start/finish (+0x00/+0x04) and calls that
// range append; Thread_Function 0x0038EDD7 calls it to append the temporary
// that WideCharStringToMultiByte returns. This row was formerly the inline-asm
// placeholder BfmeStrVMX::bfmeFwdVMX (BfmeConv1445.cpp).
// Built like the append(const char*) sibling StlportNarrowAppendCStr.cpp:
// /Od /Ob2 inlines the template append and _M_append_dispatch; the explicit
// category temporary and a 76-byte retained inline slot reproduce retail's
// frame (range at -0x58/-0x54, category -2, _Integral() temporary -1).
#include <string>
// Suppress this TU's non-retail copy of ?_M_throw_length_error@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QBEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_throw_length_error() const; }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
namespace _STL {
// ?retainAppendStringSlot absent-from-retail
template<class T> __forceinline void retainAppendStringSlot(T *) {}
// ?retainAppendStringFrame absent-from-retail
__forceinline void retainAppendStringFrame() { char slots[76]; retainAppendStringSlot(slots); }
// ?basic_string::_M_append_dispatch absent-from-retail
template <> template <> inline string &string::_M_append_dispatch<char *>(char *first, char *last, const __false_type &) {
    forward_iterator_tag category;
    retainAppendStringFrame();
    return append(first, last, category);
}
template <> string &string::append(const string &s) {
    return append(s._M_start, s._M_finish);
}
}
#pragma inline_depth(0)
// ?emitAppendString absent-from-retail
void emitAppendString(_STL::string &s, const _STL::string &t) { s.append(t); }
#pragma inline_depth()
