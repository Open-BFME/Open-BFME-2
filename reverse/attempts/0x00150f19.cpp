// ??0Rva00150F19@@QAE@H@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00150F19@@QAE@H@Z @0x00150F19 87B.
// Subclass ctor: vtable g_00BD3A4C plus Vector_base<BfmeE16> via rowed
// 0x00211E58 plus tail stamps g_00BD3864 and -1 plus grow via rowed 0x00150D09.
// Evidence: rowed Vector_base plus rowed rva00150D09 plus vtables
// g_00BD3A4C g_00BD3864; layout plus flags from Rva00150B8DFamily plus 0x00150DFD stash.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};
extern const void *const g_00BD3A4C[];
extern const void *const g_00BD3864[];
class Rva00150D09
{
public:
	void rva00150D09(int n);
};
class EmptyBase00150F19
{
public:
	EmptyBase00150F19()
	{
	}
	~EmptyBase00150F19();
};
class Tail00150F19
{
public:
	Tail00150F19(const void *vt, int v) : m_vt(vt), m_val(v)
	{
	}
	~Tail00150F19();
	const void * volatile m_vt;
	volatile int m_val;
};
class Rva00150F19 : public EmptyBase00150F19
{
public:
	Rva00150F19(int n);
private:
	volatile const void *m_vtable;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	Tail00150F19 m_tail;
};
// ??0Rva00150F19@@QAE@H@Z present-unmatched
Rva00150F19::Rva00150F19(int n) : m_vtable((const void *)g_00BD3A4C), m_vec(), m_tail((const void *)g_00BD3864, -1)
{
	if (n > 0)
		((Rva00150D09 *)this)->rva00150D09(n);
}
