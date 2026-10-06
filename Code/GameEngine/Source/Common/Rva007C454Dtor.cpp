// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva007C454@@UAE@XZ @0x0007C454 75B (existing pin): destructor of the
// CameraClass-derived Rva007C454 (ctor 0x0007C3CD, copy 0x0007C404). It
// reinstalls both vptrs (0x00BC6C58 at +0, 0x00BC6C54 at +8), frees the
// vector<BfmeE16> storage at +0x3FC (inlined STLport vector/_Vector_base
// destructors, malloc allocator -> free 0x00030830) and calls the rowed
// CameraClass destructor 0x00133A00. Layout follows Rva007C454Ctor.cpp.
// /EHs (not /EHsc): retail keeps an EH state around the free call, so the
// extern "C" free must be treated as possibly throwing.
#include <vector>

struct BfmeE16
{
	float x, y, z, w;
};

class CamBase0
{
public:
	virtual ~CamBase0();

private:
	int m_04;
};

class CamBase1
{
public:
	virtual void g0();
};

class CameraClass : public CamBase0, public CamBase1
{
public:
	virtual ~CameraClass();

private:
	char m_pad[0x3FC - 12];
};

class Rva007C454 : public CameraClass
{
public:
	virtual ~Rva007C454();

private:
	_STL::vector<BfmeE16> m_3FC;
};

Rva007C454::~Rva007C454()
{
}
