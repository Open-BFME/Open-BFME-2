// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PAURva00153729@@PAU1@H@_STL@@YAPAURva00153729@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z retail 0x00153A98 50 bytes.
// Forward copy of Rva00153729 array via rowed 0x001539BC rva assign.
// Caller 0x00153BAC.
// Identity honest address free function.
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
template <>
Rva00153729 *_STL::__copy<Rva00153729 *, Rva00153729 *, int>(
    Rva00153729 *first, Rva00153729 *last, Rva00153729 *result,
    const _STL::random_access_iterator_tag &, int *)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (int i = n; i != 0; --i)
	{
		result->rva001539BC(*first);
		++first;
		++result;
	}
	return result;
}
