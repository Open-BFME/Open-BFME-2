// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 src/strstream.cpp: freeze, str and pcount of strstreambuf
// and of the three strstream classes, which all reach their _M_buf. Retail
// keeps them in that file's order: strstreambuf freeze 0x00602680, str
// 0x006026A0, pcount 0x006026C0 (then _M_alloc/_M_free 0x006026E0/0x00602710
// and _M_setup 0x00602740); istrstream::str 0x006027B0; ostrstream freeze
// 0x006027D0, str 0x006027F0, pcount 0x00602810; strstream freeze 0x00602830,
// pcount 0x00602850, str 0x00602870. The flag byte (_M_dynamic bit 0,
// _M_frozen bit 1) sits at strstreambuf +0x5C, so at +0x64/+0x60/+0x68 in
// istrstream/ostrstream/strstream, whose _M_buf follows basic_istream,
// basic_ostream and basic_iostream.

#include <strstream>

namespace _STL
{

void strstreambuf::freeze(bool frozenflag)
{
	if (_M_dynamic)
		_M_frozen = frozenflag;
}

char *strstreambuf::str()
{
	freeze(true);
	return eback();
}

int strstreambuf::pcount() const
{
	return int(pptr() ? pptr() - pbase() : 0);
}

char *istrstream::str()
{
	return _M_buf.str();
}

void ostrstream::freeze(bool freezeflag)
{
	_M_buf.freeze(freezeflag);
}

char *ostrstream::str()
{
	return _M_buf.str();
}

int ostrstream::pcount() const
{
	return _M_buf.pcount();
}

void strstream::freeze(bool freezeflag)
{
	_M_buf.freeze(freezeflag);
}

int strstream::pcount() const
{
	return _M_buf.pcount();
}

char *strstream::str()
{
	return _M_buf.str();
}

}
