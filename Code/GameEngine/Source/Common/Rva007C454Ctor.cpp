// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva007C454@@QAE@XZ @0x0007C3CD 43B:
// Constructor for the Camera-derived class with vptr 0x007C6C58/0x007C6C54
// (same vtables as the pinned dtor at 0x0007C454) and a vector<BfmeE16> at
// +0x3FC. Retail calls the rowed CameraClass ctor at 0x00134AB0, stores the
// derived vtables, then constructs the vector through the rowed Vector_base
// at 0x00211E58. Caller at 0x0007C538 (in 0x0007C50B) proves the 0x408-byte
// new size; the dtor at 0x0007C454 frees the +0x3FC storage then calls the
// rowed Camera dtor. CamBase0/CamBase1 reproduce Camera's two-vptr MI layout;
// BfmeE16 is the 16-byte POD from stlport_vector_e16_o1.cpp.
#include <vector>

struct BfmeE16
{
	float x, y, z, w;
};

class CamBase0
{
public:
	CamBase0();
	~CamBase0();
	virtual void f0();

private:
	int m_04;
};

class CamBase1
{
public:
	CamBase1();
	virtual void g0();
};

class CameraClass : public CamBase0, public CamBase1
{
public:
	CameraClass();
	~CameraClass();

private:
	char m_pad[0x3FC - 12];
};

class Rva007C454 : public CameraClass
{
public:
	Rva007C454();

private:
	_STL::vector<BfmeE16> m_3FC;
};

Rva007C454::Rva007C454()
{
}
