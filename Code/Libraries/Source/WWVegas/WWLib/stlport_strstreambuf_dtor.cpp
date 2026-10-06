// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
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

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?setbuf@strstreambuf@_STL@@MAEPAV?$basic_streambuf@DV?$char_traits@D@_STL@@@2@PADH@Z=?setbuf@?$basic_streambuf@GV?$char_traits@G@_STL@@@_STL@@MAEPAV12@PAGH@Z")
