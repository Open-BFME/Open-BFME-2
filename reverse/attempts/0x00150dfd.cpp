// ??0Rva00150DFD@@QAE@H@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00150DFD@@QAE@H@Z @0x00150DFD 87B.
// Subclass ctor: vtable g_00BD3A44 plus Vector_base<BfmeE16> via rowed
// 0x00211E58 plus tail stamps g_00BD385C and -1 plus grow via rowed 0x00150CD0.
// Evidence: rowed Vector_base plus rowed rva00150CD0 plus vtables
// g_00BD3A44 g_00BD385C; layout plus flags from Rva00150B8DFamily plus EH
// shape from Rva0021F804Ctor.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};
extern const void *const g_00BD3A44[];
extern const void *const g_00BD385C[];
class Rva00150CD0
{
public:
	void rva00150CD0(int n);
};
class EmptyBase00150DFD
{
public:
	EmptyBase00150DFD()
	{
	}
	~EmptyBase00150DFD();
};
class Tail00150DFD
{
public:
	Tail00150DFD(const void *vt, int v) : m_vt(vt), m_val(v)
	{
	}
	~Tail00150DFD();
	const void *m_vt;
	int m_val;
};
class Rva00150DFD : public EmptyBase00150DFD
{
public:
	Rva00150DFD(int n);
private:
	volatile const void *m_vtable;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	Tail00150DFD m_tail;
};
// ??0Rva00150DFD@@QAE@H@Z present-unmatched
Rva00150DFD::Rva00150DFD(int n) : m_vtable((const void *)g_00BD3A44), m_vec(), m_tail((const void *)g_00BD385C, -1)
{
	if (n > 0)
		((Rva00150CD0 *)this)->rva00150CD0(n);
}
