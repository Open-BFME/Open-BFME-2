// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_string<char> substring constructor, RVA 0x00029FB0 / 218B.
// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_substring_ctor.cpp.
// Target boundary: Ghidra FUN_00429fb0, RET16 followed by int3 padding.
// Target calls the const-char range initializer at 0x000078C0, unlike the
// donor's mutable-char initializer. Keep the mutable-copy adaptation inside
// that helper: MSVC 7.1 retains its abandoned inline temporaries under /Od,
// producing the target's 0x30 frame. The casts do not modify the source range.
// String identity comes from the donor algorithm plus both independently
// recovered target callees; every byte of the constructor verifies.

#include <string>

namespace _STL
{

// ?basic_string::_M_range_initialize present-unmatched
template <> template <>
inline void basic_string<char, char_traits<char>, allocator<char> >::
	_M_range_initialize<const char *>(const char *__f, const char *__l,
		const forward_iterator_tag &)
{
	difference_type __n = __l - __f;
	this->_M_allocate_block(__n + 1);
	this->_M_finish = uninitialized_copy(const_cast<char *>(__f), const_cast<char *>(__l), this->_M_start);
	*this->_M_finish = 0;
}

}

namespace _STL {
template <>
basic_string<char, char_traits<char>, allocator<char> >::basic_string(
    const basic_string<char, char_traits<char>, allocator<char> > &__s,
    size_type __pos, size_type __n, const allocator_type &__a)
    : _String_base<char, allocator<char> >(__a) {
    if (__pos > __s.size())
        this->_M_throw_out_of_range();
    else
        _M_range_initialize(static_cast<const char *>(__s._M_start) + __pos,
            static_cast<const char *>(__s._M_start) + __pos + (min)(__n, __s.size() - __pos));
}
}
// ?bfmeEmitSubstringCtor absent-from-retail
void bfmeEmitSubstringCtor(void *storage, const _STL::string &source,
    unsigned pos, unsigned count, const _STL::allocator<char> &allocator)
{
    new (storage) _STL::string(source, pos, count, allocator);
}
