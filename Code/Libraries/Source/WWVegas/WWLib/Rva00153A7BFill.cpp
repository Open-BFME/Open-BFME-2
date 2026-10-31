// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00153A7BFill@@YAXPAURva00153729@@0ABU1@@Z retail 0x00153A7B 29 bytes.
// Fill range with value via rowed 0x001539BC rva assign.
// Callers 0x00153DE5 0x00153E25 in 0x00153D5E.
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
void __cdecl Rva00153A7BFill(struct Rva00153729 *first, struct Rva00153729 *last, const struct Rva00153729 &value)
{
	for (; first != last; ++first)
		first->rva001539BC(value);
}
