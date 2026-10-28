// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport46
// ?rva0055A7DB@Rva0055A246@@QAEXHPAX@Z @0x0055A7DB (176B): Bezier tessellation fill of Coord3D vector via Rva005C76C0 forward-difference iterator. Evidence: prev 0x0055A627 same flags Rva0055A246; rowed ctor 0x005C7448 int plus Rva0055A246 source; rowed rva005C74B1 init plus rva005C743B done plus rva005C7636 advance plus LeaField get 0x0053998C at +0x38; rowed erase Gen_p12pod plus resize Coord3D; ret 8 two stack args; callers 0x003904DE 0x0045B8E1 0x0048DF3A.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Gen_p12pod { int a[3]; };

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
// bfme link decl-only begin
namespace _STL { template <> Coord3D *__copy<Coord3D *, Coord3D *, int>(Coord3D *, Coord3D *, Coord3D *, const random_access_iterator_tag &, int *); }  // rowed 0x002C97AC (BfmeTwoHundredFortyThree.cpp)
namespace _STL { template <> Coord3D * __copy_backward<Coord3D *, Coord3D *, int>(Coord3D *, Coord3D *, Coord3D *, random_access_iterator_tag const &, int *); }
namespace _STL { template <> void fill<Coord3D *, Coord3D>(Coord3D *, Coord3D *, Coord3D const &); }
namespace _STL { template <> void vector<Coord3D, allocator<Coord3D> >::_M_fill_insert(Coord3D *, unsigned int, Coord3D const &); }
namespace _STL { template <> void vector<Coord3D, allocator<Coord3D> >::_M_insert_overflow(Coord3D *, Coord3D const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<Coord3D, allocator<Coord3D> >::resize(unsigned int); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end

class Rva0055A246
{
public:
	Rva0055A246();
	void rva0055A7DB(int count, void *outVec);
	Coord3D m_arr[4];
};

class Rva005C76C0
{
public:
	Rva005C76C0(int count, const Rva0055A246 *source);
	void rva005C74B1();
	void rva005C7636();
	int m_00;
	int m_04;
	Rva0055A246 m_08;
	float m_38[12];
};

class Rva005C743B
{
public:
	bool rva005C743B() const;
	int m_00;
	int m_04;
};

class Rva0053998CLeaField
{
public:
	void *get() const;
};

void Rva0055A246::rva0055A7DB(int count, void *outVec)
{
	if (outVec == 0)
		return;
	((::_STL::vector<Gen_p12pod> *)outVec)->clear();
	((::_STL::vector<Coord3D> *)outVec)->resize((unsigned int)count);
	Rva005C76C0 it(count, this);
	it.rva005C74B1();
	if (!((Rva005C743B *)&it)->rva005C743B()) {
		count = 0;
		do {
			Coord3D *base = *(Coord3D **)outVec;
			void *src = ((Rva0053998CLeaField *)&it)->get();
			int old = count;
			count += 12;
			Coord3D *dst = (Coord3D *)((char *)base + old);
			*dst = *(Coord3D *)src;
			it.rva005C7636();
		} while (!((Rva005C743B *)&it)->rva005C743B());
	}
}

// resize(n) binds to the rowed retail copy (declared above), so the two rowed
// helpers its stock body used to pull in are instantiated explicitly.
template void _STL::vector<Coord3D, _STL::allocator<Coord3D> >::insert(Coord3D *, unsigned int, const Coord3D &);
namespace _STL {
template Coord3D *__copy_ptrs(Coord3D *, Coord3D *, Coord3D *, const __false_type &);
}
