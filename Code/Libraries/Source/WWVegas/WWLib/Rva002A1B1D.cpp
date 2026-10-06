// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002A1B1D@Rva002A1B1D@@QAEXPBURva002A1B1DChunk@@000@Z, retail 0x002A1B1D, 54 bytes. Four 12B chunk copies then List_base CameraMarker clear at +0x30 via rowed 0x002934A8. Caller 0x002A4A2F passes this+0x8d4 with four chunk pointers. Evidence: call to 0x002934A8, ret 0x10, movsd x12 pattern.
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
	Rva002A1B1DChunk m0;
	Rva002A1B1DChunk m1;
	Rva002A1B1DChunk m2;
	Rva002A1B1DChunk m3;
	_STL::list<CameraMarker, _STL::allocator<CameraMarker> > m_list;
	void rva002A1B1D(const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4);
};

void Rva002A1B1D::rva002A1B1D(const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4)
{
	m0 = *p2;
	m1 = *p1;
	m2 = *p3;
	m3 = *p4;
	m_list.clear();
}
