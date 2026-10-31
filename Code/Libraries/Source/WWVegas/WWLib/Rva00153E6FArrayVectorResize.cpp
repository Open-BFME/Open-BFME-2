// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
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
namespace _STL { template<> vector<Rva005F8F96>::vector(const vector<Rva005F8F96>&); }
// The kept copies serve the link: no copy of these from this file.
namespace _STL {
template <> void _Construct<Rva00153729, Rva00153729>(Rva00153729 *, const Rva00153729 &);
}
class Rva00153E6FVector { Rva00153729*start,*finish,*end; public: void resize(unsigned,Rva00153729); void resize(unsigned); };
namespace _STL {
template<> Rva00153729*vector<Rva00153729>::erase(Rva00153729*,Rva00153729*);

}
void Rva00153E6FVector::resize(unsigned n) { resize(n,Rva00153729()); }
void Rva00153E6FVector::resize(unsigned n,Rva00153729 value) {
 _STL::vector<Rva00153729>*v=reinterpret_cast<_STL::vector<Rva00153729>*>(this);
 if(n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

template void _STL::vector<Rva00153729>::_M_fill_insert(Rva00153729*,unsigned,const Rva00153729&);

// Reference: pristine STLport4.5.3 fill_insert. Native 268B ret0C extent,
// 76B entry stride and constructor/helper calls establish this instantiation.
// Pristine algobase/uninitialized wrappers retain their native out-of-line
// reference-tag ABI; the bfmealloc allocator shim is still used.
