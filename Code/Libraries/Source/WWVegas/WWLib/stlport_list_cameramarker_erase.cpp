// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?erase@?$list@UCameraMarker@@V?$allocator@UCameraMarker@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UCameraMarker@@U?$_Nonconst_traits@UCameraMarker@@@_STL@@@2@U32@@Z retail 0x002A12B7 42B
// Evidence: identical 42B unlink plus destroy plus free shape to list<AsciiString>::erase at 0x000BC67A;
// here destroys CameraMarker at node+8 via rowed dtor 0x0029D7C2 then frees via _free 0x00030830;
// caller 0x00293FA7; CameraMarker layout 8B proven by rowed dtor and copy assignment 0x0028876F.
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
