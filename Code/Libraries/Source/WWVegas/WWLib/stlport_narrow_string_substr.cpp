// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_string<char>::substr, target 0x0002AD50 / 251B.
// Reference: inputs/vendor/stlport/stl/_string.h at BFME1 1281192f682.
// Target range initializer 0x000078C0 establishes const-char dispatch.
// Use the verified substring-constructor sibling's range helper adaptation;
// MSVC retains its inline temporaries under /Od, fixing the 0x40 frame.

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
template <> string string::substr(unsigned int pos, unsigned int n) const {
 if (pos > size()) this->_M_throw_out_of_range();
 return string(static_cast<const char *>(this->_M_start) + pos,
 static_cast<const char *>(this->_M_start) + pos + (min)(n, size() - pos));
}
}
_STL::string (_STL::string::*bfmeEmitNarrowSubstr)(unsigned int,unsigned int) const = &_STL::string::substr;
