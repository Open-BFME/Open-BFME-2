// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// retail 0x002A1BEB 23B unlock: List_base CameraMarker dtor via rowed clear 0x002934A8 and free 0x00030830; same 23B shape as int 0x004EC395 and UnicodeString 0x00433BD7
#include <list>

#include "ascii_string.h"

struct CameraMarker
{
	~CameraMarker();
	CameraMarker &operator=(const CameraMarker &src);

	CameraMarker *m_next;
	AsciiString m_name;
};

bool operator==(const CameraMarker &a, const CameraMarker &b);
bool operator<(const CameraMarker &a, const CameraMarker &b);

template class _STL::list<CameraMarker, _STL::allocator<CameraMarker> >;
