// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00524436@@QAE@XZ @0x00524436 65B evidence: dtor via rowed clear 0x00523F8C plus vector CameraMarker at +0xc via dup 0x005243BB plus vector AsciiString at +0 via 0x0002CC70; precedent Rva00524265Dtor single-vector shape; callers 0x005248D0 0x0052634F 0x0052936C 0x005C7954
#include <vector>

#include "ascii_string.h"

class CameraMarker
{
public:
	~CameraMarker();
};

class Rva00524021
{
public:
	void rva00523F8C();
};

class Rva00524436
{
public:
	~Rva00524436();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
	_STL::vector<CameraMarker, _STL::allocator<CameraMarker> > m_0c;
};

Rva00524436::~Rva00524436()
{
	((Rva00524021 *)this)->rva00523F8C();
}
