// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?clear@?$_List_base@UCameraMarker@@V?$allocator@UCameraMarker@@@_STL@@@_STL@@QAEXXZ, retail 0x002934A8, 49 bytes.
// List_base clear for CameraMarker via rowed dtor 0x0029D7C2 and _free 0x00030830.
// Same 49B empty-check plus sentinel-reset shape as TreeHintOpaque 0x00434EC9 and Rva001EA443 0x001EA529.
// CameraMarker layout 8B proven by rowed dtor and copy assignment 0x0028876F; value at node+8.
// Callers at 0x00297BAC 0x002A1B49 0x002A1BEE 0x002A4337 0x002DE5BC; unblocks 0x002A42D8 0x002A1BEB 0x002A1B1D.
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
