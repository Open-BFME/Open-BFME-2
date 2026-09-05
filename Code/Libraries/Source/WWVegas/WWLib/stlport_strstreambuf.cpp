// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// strstreambuf, vftable 0x0087A878. seekpos is the standard forwarder onto
// seekoff with ios_base::beg, and the image confirms it is not devirtualised:
// retail calls it through [vptr+8], slot 2, the same slot seekoff occupies.

#include <locale>
#include <strstream>

namespace _STL
{

strstreambuf::int_type strstreambuf::pbackfail(int_type __c)
{
	if (gptr() != eback()) {
		if (__c == _Traits::eof()) {
			gbump(-1);
			return _Traits::not_eof(__c);
		}
		else if (__c == gptr()[-1]) {
			gbump(-1);
			return __c;
		}
		else if (!_M_constant) {
			gbump(-1);
			*gptr() = _Traits::to_char_type(__c);
			return __c;
		}
	}
	return _Traits::eof();
}

strstreambuf::pos_type
strstreambuf::seekpos(pos_type __pos, ios_base::openmode __mode)
{
	return this->seekoff(__pos - pos_type(off_type(0)), ios_base::beg, __mode);
}

}
