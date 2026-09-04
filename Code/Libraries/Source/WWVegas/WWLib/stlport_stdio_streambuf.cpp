// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// STLport's stdio_streambuf extension. The image names all three classes in
// its own RTTI, in the SGI namespace the vendored header opens:
// _SgI::stdio_streambuf_base at vftable 0x007BCCAC, _SgI::stdio_istreambuf at
// 0x007BBC6C and _SgI::stdio_ostreambuf at 0x007BBCA8. The FILE they wrap sits
// at this+0x54.
//
// Every body here is a thin cover over one C stdio call, and the image names
// which one by its import slot: 0x00BBA658 fflush, 0x00BBA654 setvbuf,
// 0x00BBA638 getc, 0x00BBA63C ungetc.
//
// Two of them carry a comparison that does nothing at runtime - cmp eax,-1
// then a branch over an or eax,eax. That is the eof round-trip written out:
// the source really does say "if this is eof, return eof", and eof and the
// value it came from are the same -1.

#include <locale>
#include <stdio_streambuf>
#include <sys/types.h>
#include <sys/stat.h>

namespace _SgI
{

stdio_streambuf_base::~stdio_streambuf_base()
{
	fflush(_M_file);
}

_STLP_STD::basic_streambuf<char, _STLP_STD::char_traits<char> > *
stdio_streambuf_base::setbuf(char *__s, streamsize __n)
{
	setvbuf(_M_file, __s, (__s == 0 && __n == 0) ? _IONBF : _IOFBF, __n);
	return this;
}

stdio_streambuf_base::pos_type
stdio_streambuf_base::seekoff(off_type __off, _STLP_STD::ios_base::seekdir __dir,
                              _STLP_STD::ios_base::openmode)
{
	int __whence;
	switch (__dir) {
	case _STLP_STD::ios_base::beg:
		__whence = SEEK_SET;
		break;
	case _STLP_STD::ios_base::cur:
		__whence = SEEK_CUR;
		break;
	case _STLP_STD::ios_base::end:
		__whence = SEEK_END;
		break;
	default:
		return pos_type(-1);
	}

	if (fseek(_M_file, __off, __whence) == 0) {
		fpos_t __pos;
		fgetpos(_M_file, &__pos);
		return pos_type(__pos);
	}
	return pos_type(-1);
}

stdio_streambuf_base::pos_type
stdio_streambuf_base::seekpos(pos_type __pos, _STLP_STD::ios_base::openmode)
{
	fpos_t __fpos = __pos;
	if (fsetpos(_M_file, &__fpos) == 0)
		return __pos;
	return pos_type(-1);
}

int stdio_streambuf_base::sync()
{
	return fflush(_M_file) == 0 ? 0 : -1;
}

streamsize stdio_istreambuf::showmanyc()
{
	if (feof(_M_file))
		return -1;

	streamsize __size;
	struct _stat __buf;
	if (_fstat(_STLP_STD::_FILE_fd(_M_file), &__buf) == 0 && (__buf.st_mode & _S_IFREG))
		__size = __buf.st_size > 0 ? __buf.st_size : 0;
	else
		__size = 0;

	streamsize __pos = ftell(_M_file);
	return (__pos >= 0 && __size > __pos) ? __size - __pos : 0;
}

stdio_istreambuf::int_type stdio_istreambuf::underflow()
{
	int __c = getc(_M_file);
	if (__c != EOF) {
		ungetc(__c, _M_file);
		return __c;
	}
	return _STLP_STD::char_traits<char>::eof();
}

stdio_istreambuf::int_type stdio_istreambuf::pbackfail(int_type __c)
{
	if (__c != _STLP_STD::char_traits<char>::eof()) {
		int __r = ungetc(__c, _M_file);
		return __r == EOF ? _STLP_STD::char_traits<char>::eof() : __r;
	}
	else if (eback() < gptr()) {
		gbump(-1);
		return _STLP_STD::char_traits<char>::not_eof(__c);
	}
	else
		return _STLP_STD::char_traits<char>::eof();
}

stdio_istreambuf::int_type stdio_istreambuf::uflow()
{
	int __c = getc(_M_file);
	return __c == EOF ? _STLP_STD::char_traits<char>::eof() : __c;
}

stdio_ostreambuf::int_type stdio_ostreambuf::overflow(int_type __c)
{
	if (__c == _STLP_STD::char_traits<char>::eof()) {
		ptrdiff_t __n = pptr() - pbase();
		if (__n != 0) {
			fflush(_M_file);
			return pptr() - pbase() < __n
			       ? _STLP_STD::char_traits<char>::not_eof(__c)
			       : _STLP_STD::char_traits<char>::eof();
		}
		return _STLP_STD::char_traits<char>::not_eof(__c);
	}

	int __r = putc(__c, _M_file);
	return __r == EOF ? _STLP_STD::char_traits<char>::eof() : __r;
}

}
