// cl: /I. /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva001F8CC2@@QAEAAV0@ABV0@@Z, retail 0x001F8CC2..0x001F8D70 (174 bytes).
// The 0x001F9CCA assignment chain calls this second-base assignment at +4;
// the original application class is unknown. Target instructions establish
// a three-pointer vector at +0, 4-byte elements obtained through virtual
// slot 1, swap 0x00567ECD, and explicit deletion of the old elements after
// the swap (virtual destructor flag 0, scalar delete 0x0002FD60).
// The temporary's unwind state protects its storage through that deletion
// loop, then releases it through 0x00030830. Its full EH graph is exact.
// BfmeE16/BfmeE12 are existing folded STLport codegen views, not claims about
// element sizes: reserve/push_back and iteration use the pointer-vector view.
// The visible noinline swap is STLport's real three-field swap; its allocator
// proxy copy escapes the buffer home, preserving retail's cached begin.
// A private max overload avoids an unrelated external max COMDAT.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "Code/Libraries/Include/Lib/BfmeE16.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::end()const  { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }

struct BfmeE12 { float x, y, z; };
namespace _STL {
template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
}
// bfme link decl-only BfmeE16
namespace _STL {
template <> vector<BfmeE16, allocator<BfmeE16> >::~vector();

template <> __declspec(noinline)
void vector<BfmeE12, allocator<BfmeE12> >::swap(vector<BfmeE12, allocator<BfmeE12> > &x)
{
	_STL::swap(this->_M_start, x._M_start);
	_STL::swap(this->_M_finish, x._M_finish);
	_STL::swap(this->_M_end_of_storage, x._M_end_of_storage);
}

}

#include "../../../Include/Common/ModuleData.h"

class Rva001F8CC2Iface
{
public:
	virtual void dummy0();
	virtual ModuleData *slot1();
};

// This wrapper owns only the buffer; element deletion is explicit below.
class Rva001F8CC2Storage : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva001F8CC2Storage() : _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()) {}
	ModuleData **begin() const { return (ModuleData **)_M_start; }
	ModuleData **end() const { return (ModuleData **)_M_finish; }
	__forceinline ~Rva001F8CC2Storage() {}
};

class Rva001F8CC2
{
public:
	Rva001F8CC2 &operator=(const Rva001F8CC2 &other);
private:
	_STL::vector<BfmeE12> m_vec;
};

Rva001F8CC2 &Rva001F8CC2::operator=(const Rva001F8CC2 &other)
{
	const _STL::vector<void *> &src = reinterpret_cast<const _STL::vector<void *> &>(other.m_vec);
	Rva001F8CC2Storage tmp;
	((_STL::vector<const ModuleData *> &)tmp).reserve(src.size());
	for (void *const *it = (void *const *)src.begin(); it != (void *const *)src.end(); ++it) {
		Rva001F8CC2Iface *obj = (Rva001F8CC2Iface *)*it;
		const ModuleData *md = obj->slot1();
		((_STL::vector<const ModuleData *> &)tmp).push_back(md);
	}
	((_STL::vector<BfmeE12> &)tmp).swap(m_vec);
	for (ModuleData **p = tmp.begin(); p != tmp.end(); ++p)
		::delete *p;
	return *this;
}

// The complete 18-byte body at 0x001F90C3 ends at the next entry 0x001F90D5.
// It forwards the same this and reference argument to the verified assignment
// at 0x001F8CC2, then returns the original this. There are no surviving callers
// or original class names; this zero-offset base view is a structural inference.
class Rva001F90C3 : public Rva001F8CC2
{
public:
	Rva001F90C3 &operator=(const Rva001F90C3 &other);
};
Rva001F90C3 &Rva001F90C3::operator=(const Rva001F90C3 &other)
{
	Rva001F8CC2::operator=(other);
	return *this;
}
