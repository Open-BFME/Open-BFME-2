// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva001539ECCopyBackward@@YAPAURva00153729@@PAU1@00@Z retail 0x001539EC 50 bytes.
// Backward copy of Rva00153729 array via rowed 0x001539BC rva assign.
// Caller 0x00153A71 in 0x00153A5E; prev 0x001539BC assign next 0x00153A7B fill.
// Identity honest address free function __cdecl 3-pointer copy_backward shape.
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
struct Rva00153729 *__cdecl Rva001539ECCopyBackward(struct Rva00153729 *first, struct Rva00153729 *last, struct Rva00153729 *result)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (int i = n; i != 0; --i)
	{
		--last;
		--result;
		result->rva001539BC(*last);
	}
	return result;
}
