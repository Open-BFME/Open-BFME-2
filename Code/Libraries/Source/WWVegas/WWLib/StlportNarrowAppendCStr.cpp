// cl: /Od /Ob2 /DNDEBUG /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 reference at BFME1 revision6583b3c1; retail2A930..2A96A58B.
// The native helper obtains length via rowed char_traits<char>::length6F30
// and forwards its range to the pinned forward-iterator append1B3E0. The
// existing bfmeLen1153 spelling is a linker alias of that rowed length helper.
// /Od /Ob2 retains64 unused inline bytes while spilling this/end at-4C/-48;
// the no-code stack-slot pattern is established by the matched erase sibling.
// Explicit category construction preserves both native tag temporaries.
#include <string>
extern "C" unsigned int bfmeLen1153(const char *);
namespace _STL {
// ?retainAppendInlineSlot absent-from-retail
template<class T> __forceinline void retainAppendInlineSlot(T *) {}
// ?retainAppendInlineFrame absent-from-retail
__forceinline void retainAppendInlineFrame() { char slots[64]; retainAppendInlineSlot(slots); }
// ?basic_string::_M_append_dispatch absent-from-retail
template <> template <> inline string &string::_M_append_dispatch<const char *>(const char *first, const char *last, const __false_type &) {
    forward_iterator_tag category;
    retainAppendInlineFrame();
    return append(first, last, category);
}
template <> string &string::append(const char *source) {
    return append(source, source + bfmeLen1153(source));
}
}
#pragma inline_depth(0)
// ?emitAppend absent-from-retail
void emitAppend(_STL::string &s, const char *p) { s.append(p); }
#pragma inline_depth()
