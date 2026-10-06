// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00542067@Rva00542225@@QAEXXZ @0x00542067 70B. Leaf via caller 0x00542256
// in Rva00542225 ctor. Trims vector at +0x10 to one element via rowed
// rva00541883 then appends default Rva00540FCB as Rva00541021 via rowed
// push_back. Evidence: rowed callees, pin name, prev/next flags.
#include <vector>

struct Region3D
{
	Region3D(const Region3D &that);
	float x_min;
	float y_min;
	float z_min;
	float x_max;
	float y_max;
	float z_max;
};

struct Rva00541021
{
	int m_field0;
	Region3D m_region;
	Rva00541021();
	Rva00541021(const Rva00541021 &other);
};

class Rva00540D67
{
public:
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
};

class Rva00540FCB
{
public:
	Rva00540FCB();
	int m_00;
	Rva00540D67 m_04;
};

class Rva00541579
{
public:
	void rva00541883(int key);
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Rva00541021Vec
{
	Rva00541021 *m_begin;
	Rva00541021 *m_end;
	Rva00541021 *m_cap;
};

class Rva00542225
{
public:
	void rva00542067();
private:
	char m_pad00[0x10];
	Rva00541021Vec m_vec10;
};

void Rva00542225::rva00542067()
{
	Rva00541021Vec *vec = &m_vec10;
	while ((unsigned)(((char *)vec->m_end - (char *)vec->m_begin) / 28) > 1) {
		_ReadWriteBarrier();
		int key = *(int *)((char *)vec->m_begin + 28);
		((Rva00541579 *)this)->rva00541883(key);
	}
	Rva00540FCB tmp;
	tmp.m_00 = 0;
	((_STL::vector<Rva00541021, _STL::allocator<Rva00541021> > *)&m_vec10)->push_back(reinterpret_cast<const Rva00541021 &>(tmp));
}
