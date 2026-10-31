// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001539BC@Rva00153729@@QAEAAU1@ABU1@@Z retail 0x001539BC 48 bytes.
// Copies int at +0 then 6 vector<Rva005F8F96> at +4 via rowed assign 0x001537D8.
// Callers 0x001539EC 0x00153A7B 0x00153A98; unblocks 3.
// Identity honest address method __thiscall returns *this.
#include <vector>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };

struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};

typedef const char *D3DXHANDLE;

// One per technique, 0x4C bytes: the handle and six binding vectors.
struct Rva00153729
{
	Rva00153729();
	~Rva00153729() {}
	Rva00153729 &rva001539BC(const Rva00153729 &other);

	D3DXHANDLE m_technique;			// +0
	_STL::vector<Rva005F8F96> m_vec[6];	// +4
};

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> vector<Rva005F8F96,allocator<Rva005F8F96> > & vector<Rva005F8F96,allocator<Rva005F8F96> >::operator=(vector<Rva005F8F96,allocator<Rva005F8F96> > const &); }
Rva00153729 &Rva00153729::rva001539BC(const Rva00153729 &other)
{
	m_technique = other.m_technique;
	for (int i = 0; i < 6; i++)
		m_vec[i] = other.m_vec[i];
	return *this;
}
