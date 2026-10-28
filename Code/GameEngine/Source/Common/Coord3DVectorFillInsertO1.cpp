// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport46
//
// Size-optimised (/O1) instantiation of vector<Coord3D>::_M_fill_insert.
//
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
#include "prerts.h"
#include "coord.h"
#include "bezier_segment.h"
#include "bez_fwd_iterator.h"
#include "d3dx8math.h"
#include "../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
// bfme link decl-only begin
namespace _STL { template <> Coord3D * __copy_backward<Coord3D *, Coord3D *, int>(Coord3D *, Coord3D *, Coord3D *, random_access_iterator_tag const &, int *); }
namespace _STL { template <> void fill<Coord3D *, Coord3D>(Coord3D *, Coord3D *, Coord3D const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end

// Retail's helper calls land on the bodies rowed for the 12-byte stand-ins
// BfmeE12 (copy/fill helpers) and PrereqUnitRec (_M_insert_overflow): this /O1
// vector body was folded onto that element type. The specialization below is
// STLport's _M_fill_insert with those calls spelled through the rowed types.
// Retail calls every helper out of line, including uninitialized_fill_n at
// 0x004E1ABA (compiled here) and __copy_backward_ptrs. A plain specialization
// would inline those two, so inline_depth(0) keeps them as calls.
struct BfmeE12
{
	float x, y, z;
};

struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};

struct BfmePrereqUnitRecVector : _STL::vector<PrereqUnitRec>
{
	using _STL::vector<PrereqUnitRec>::_M_insert_overflow;
};

#pragma inline_depth(0)
namespace _STL
{
template <>
void vector<Coord3D, allocator<Coord3D> >::_M_fill_insert(Coord3D *position, size_type n, const Coord3D &x)
{
	if (n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= n) {
			Coord3D x_copy = x;
			const size_type elems_after = this->_M_finish - position;
			Coord3D *old_finish = this->_M_finish;
			if (elems_after > n) {
				__uninitialized_copy((const BfmeE12 *)(this->_M_finish - n), (const BfmeE12 *)this->_M_finish,
					(BfmeE12 *)this->_M_finish, __false_type());
				this->_M_finish += n;
				__copy_backward_ptrs((BfmeE12 *)position, (BfmeE12 *)(old_finish - n), (BfmeE12 *)old_finish,
					__false_type());
				_STL::fill((BfmeE12 *)position, (BfmeE12 *)(position + n), (const BfmeE12 &)x_copy);
			}
			else {
				uninitialized_fill_n((BfmeE12 *)this->_M_finish, n - elems_after, (const BfmeE12 &)x_copy);
				this->_M_finish += n - elems_after;
				__uninitialized_copy((const BfmeE12 *)position, (const BfmeE12 *)old_finish,
					(BfmeE12 *)this->_M_finish, __false_type());
				this->_M_finish += elems_after;
				_STL::fill((BfmeE12 *)position, (BfmeE12 *)old_finish, (const BfmeE12 &)x_copy);
			}
		}
		else
			static_cast<BfmePrereqUnitRecVector *>(reinterpret_cast<vector<PrereqUnitRec> *>(this))->_M_insert_overflow(
				(PrereqUnitRec *)position, (const PrereqUnitRec &)x, __false_type(), n);
	}
}
}
#pragma inline_depth()

extern void (_STL::vector<Coord3D>::*const g_bfmeCoord3DFillInsertAnchor)(Coord3D *, unsigned int, const Coord3D &);
void (_STL::vector<Coord3D>::*const g_bfmeCoord3DFillInsertAnchor)(Coord3D *, unsigned int, const Coord3D &) = &_STL::vector<Coord3D>::_M_fill_insert;
