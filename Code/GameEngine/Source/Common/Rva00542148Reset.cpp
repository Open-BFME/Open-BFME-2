// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 00542148..0054218E RET0. Constructor005422CF calls this
// reset of its 20-byte record vector at +0x10. Same operation as the
// matched sibling00542067, with 20-byte Region2D records instead of
// 28-byte Region3D records; direct target callees prove remover5418CB,
// default record540FF6, and vector<Rva0054103E>::push_back541DA8.
// Original method name is unresolved; target offsets and ABI are measured.
#include <vector>

struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Rva0054103E
{
public:
	int m_field0;
	Region2D m_region;
	Rva0054103E();
	Rva0054103E(const Rva0054103E &other);
};

class Rva00540E82
{
public:
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
};

class Rva00540FF6
{
public:
	Rva00540FF6();
	int m_00;
	Rva00540E82 m_04;
};

class Rva005418CB
{
public:
	void rva005418CB(int key);
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0054103EVec
{
	Rva0054103E *m_begin;
	Rva0054103E *m_end;
	Rva0054103E *m_cap;
};

class Rva005422CF
{
public:
	void rva00542148();
private:
	char m_pad00[0x10];
	Rva0054103EVec m_vec10;
};

void Rva005422CF::rva00542148()
{
	Rva0054103EVec *vec = &m_vec10;
	while ((unsigned)(((char *)vec->m_end - (char *)vec->m_begin) / 20) > 1) {
		_ReadWriteBarrier();
		int key = *(int *)((char *)vec->m_begin + 20);
		((Rva005418CB *)this)->rva005418CB(key);
	}
	Rva00540FF6 tmp;
	tmp.m_00 = 0;
	((_STL::vector<Rva0054103E, _STL::allocator<Rva0054103E> > *)&m_vec10)->push_back(reinterpret_cast<const Rva0054103E &>(tmp));
}
