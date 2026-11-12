// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// ??1strstreambuf@_STL@@UAE@XZ, retail 0x00602B50 (115 B).
// strstreambuf destructor, vtable 0x0087A878 already documented in
// stlport_strstreambuf.cpp. Donor STLport strstream.cpp
// strstreambuf::~strstreambuf { if (_M_dynamic && !_M_frozen) _M_free(eback()); }
// with _M_free inlined as retail does: eback is _M_get->_base at [esi+4]+8,
// free-fun at +0x58 or delete[] when null, dynamic/frozen bits at +0x5C.
// Callers are the derived dtors 0x00602DF0 0x00602E50 0x00602EB0 and the
// deleting dtor 0x00602F60. Base dtor rowed at 0x0001C6E0.

#include <strstream>

namespace _STL {

strstreambuf::~strstreambuf()
{
	if (_M_dynamic && !_M_frozen) {
		char *_P = eback();
		if (_P != 0) {
			if (_M_free_fun != 0)
				_M_free_fun(_P);
			else
				delete [] _P;
		}
	}
}

}
