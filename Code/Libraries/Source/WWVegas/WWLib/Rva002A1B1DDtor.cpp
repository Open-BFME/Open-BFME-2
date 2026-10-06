// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva002A1B1D@@QAE@XZ, retail 0x002A4355, 8 bytes. Dtor of Rva002A1B1D chunk holder: four 12B chunks then list<CameraMarker> at +0x30; empty dtor tail-jmps to List_base CameraMarker dtor 0x002A1BEB. Evidence: add ecx 0x30 then jmp 0x002A1BEB; chain via 0x002A1BEB; layout from Rva002A1B1D.cpp.
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

struct Rva002A1B1DChunk
{
	int a;
	int b;
	int c;
};

class Rva002A1B1D
{
public:
	~Rva002A1B1D();
	Rva002A1B1DChunk m0;
	Rva002A1B1DChunk m1;
	Rva002A1B1DChunk m2;
	Rva002A1B1DChunk m3;
	_STL::list<CameraMarker, _STL::allocator<CameraMarker> > m_list;
};

Rva002A1B1D::~Rva002A1B1D()
{
}
