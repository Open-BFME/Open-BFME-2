// cl: /Od /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_string<char>::erase(pos, count), RVA 0x00026660 / 130B.
// Target: native prologue through RET8 followed by int3 padding; calls rowed
// _M_throw_out_of_range (0x00023A40) and iterator erase (0x00012150).
// Algorithm is vendor stl/_string.h; the pair erase stays out of line here.
// Under /Od the target retains two unused inline frame slots. Preserve those
// slots with the same no-code helper pattern as BasicStringNarrowSizeCtor.cpp;
// this changes only stack allocation, without extra loads, stores or calls.
#include <string>
namespace _STL {
// ?eraseFrameSlot absent-from-retail
template <class T> __forceinline void eraseFrameSlot(T *) {}
// ?eraseFrameSlots absent-from-retail
__forceinline void eraseFrameSlots() {
    char first[4]; char last[4];
    eraseFrameSlot(first); eraseFrameSlot(last);
}
template <>
basic_string<char, char_traits<char>, allocator<char> >::iterator
basic_string<char, char_traits<char>, allocator<char> >::erase(iterator, iterator);
template <>
basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::erase(unsigned __pos, unsigned __n) {
    if (__pos > size()) this->_M_throw_out_of_range();
    erase(begin() + __pos, begin() + __pos + (min)(__n, size() - __pos));
    eraseFrameSlots();
    return *this;
}
}
// ?emitErase absent-from-retail
void emitErase(_STL::string &s, unsigned pos, unsigned n) { s.erase(pos, n); }
