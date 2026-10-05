// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// strstreambuf, vftable 0x0087A878. seekpos is the standard forwarder onto
// seekoff with ios_base::beg, and the image confirms it is not devirtualised:
// retail calls it through [vptr+8], slot 2, the same slot seekoff occupies.
// underflow (slot 7, 0x00602BD0) and overflow (slot 12, 0x00602F80) are the
// STLport 4.5.3 bodies; overflow's _M_alloc/_M_free resolve to the
// allocator shims at 0x006026E0/0x00602710 (read +0x54/+0x58).

#include <locale>
#include <strstream>

class Rva006026E0
{
public:
	void *alloc(unsigned n);
	void free(void *p);
};

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


strstreambuf::int_type strstreambuf::underflow()
{
	if (gptr() == egptr() && pptr() && pptr() > egptr())
		setg(eback(), gptr(), pptr());

	if (gptr() != egptr())
		return (unsigned char) *gptr();
	else
		return _Traits::eof();
}

strstreambuf::int_type strstreambuf::overflow(int_type c)
{
	if (c == traits_type::eof())
		return traits_type::not_eof(c);

	// Try to expand the buffer.
	if (pptr() == epptr() && _M_dynamic && !_M_frozen && !_M_constant) {
		ptrdiff_t old_size = epptr() - pbase();
		ptrdiff_t new_size = (max)(2 * old_size, ptrdiff_t(1));

		char* buf = (char*)((Rva006026E0*)this)->alloc(new_size);
		if (buf) {
			memcpy(buf, pbase(), old_size);

			char* old_buffer = pbase();
			bool reposition_get = false;
			ptrdiff_t old_get_offset;
			if (gptr() != 0) {
				reposition_get = true;
				old_get_offset = gptr() - eback();
			}

			setp(buf, buf + new_size);
			pbump((int)old_size);

			if (reposition_get)
				setg(buf, buf + old_get_offset, buf + (max)(old_get_offset, old_size));

			((Rva006026E0*)this)->free(old_buffer);
		}
	}

	if (pptr() != epptr()) {
		*pptr() = c;
		pbump(1);
		return c;
	}
	else
		return traits_type::eof();
}

}
