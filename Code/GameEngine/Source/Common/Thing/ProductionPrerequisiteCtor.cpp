// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ProductionPrerequisite default ctor / clear / dtor vein.
//
// Retail RE (all byte-measured with capstone + raw E8 scans):
// - ??0ProductionPrerequisite@@QAE@XZ @0x004F527A (81B): EH head
//   (mov eax,scope + call __EH_prolog @0x00629188), three empty
//   _Vector_base inits via the folded 29B base ctor @0x00211E58, then a call
//   to the clear helper below. Ends where addUnitPrereq @0x004F52CB begins.
// - ?clear@ProductionPrerequisite@@QAEXXZ @0x004F5227 (27B, frameless):
//   full-range erases of the +0x00 member via @0x004F50E2 and the +0x0C
//   member via the rowed ParticleSystemID erase @0x00532803. This is the
//   BFME1 donor ctor body (ProductionPrerequisiteCtorThunk.cpp calls
//   m_prereqUnits.clear() + m_prereqSciences.clear()) factored into a helper;
//   the BFME2 default ctor calls it instead of repeating the two clears.
// - erase<PrereqUnitRec> @0x004F50E2 (49B): copy-down via the rowed nested
//   __copy_ptrs @0x002CF594, destroy-range via @0x002D02A8, finish store.
// - destroy range @0x002D02A8 (25B): per-12-byte-element dtor loop, reached
//   with exactly 2 pushes (no tag) so it lives out of line as the 2-arg
//   _Destroy below, not the 3-arg __destroy_aux.
// - ??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ @0x00577998 (8B):
//   add ecx,8 + tail-jump to the AsciiString dtor @0x00036410, so the record
//   carries an AsciiString at +0x08 (12 bytes total).
// - ??1?$vector@UPrereqUnitRec@ProductionPrerequisite@@... @0x002D040C (63B):
//   EH teardown of the +0x00 member (destroy range + _free @0x00030830).
// - ??1ProductionPrerequisite@@QAE@XZ @0x004F5115 (80B): EH head, inline
//   null-checked _free of the +0x18 / +0x0C members (trivial elements),
//   then the +0x00 member teardown above. Ends where insert_aux @0x004F5165
//   begins.
//
// Flags: /GX, not /EHsc — the conservative EH model is what keeps the dtor
// and vector dtor frames plus the out-of-line dispatch calls; /EHsc folds
// them (/O1 + /EHsc gives a 39B frameless dtor). Stock STLport headers, not
// the bfmealloc shim — the shim forceinline-expands __copy_ptrs into erase
// and inlines memmove into the trivial erase, while retail calls both out
// of line. The two noinline specs below model exactly that.
//
// Layout (retail-proven, agrees with the copy-ctor + push_back TUs):
// +0x00 vector<PrereqUnitRec> (12-byte non-trivial elements),
// +0x0C vector<ScienceType> (4-byte trivial elements),
// +0x18 vector<unsigned int>, 0x24 bytes total.

#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#include "ascii_string.h"

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_first;
		unsigned int m_second;
		AsciiString m_name;
		~PrereqUnitRec();
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();
	void clear();

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<unsigned int> m_prereqUpgrades;
};

typedef char ProductionPrerequisiteVeinSizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

namespace _STL
{

template <> __declspec(dllimport) __forceinline
void allocator<ProductionPrerequisite::PrereqUnitRec>::deallocate(ProductionPrerequisite::PrereqUnitRec *__p, size_t __n) const
{ __malloc_alloc<0>::deallocate(__p, __n * sizeof(ProductionPrerequisite::PrereqUnitRec)); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >::deallocate(ProductionPrerequisite::PrereqUnitRec *__p, size_t __n)
{ __stl_alloc_rebind(static_cast<allocator<ProductionPrerequisite::PrereqUnitRec> &>(*this), (ProductionPrerequisite::PrereqUnitRec *)0).deallocate(__p, __n); }

// m_prereqUpgrades's empty vector<unsigned int> constructor is inlined and calls the
// out-of-line, ICF-folded _Vector_base constructor 0x00211E58 (rowed in
// stlport_vector_e16_o1.cpp); declare that base constructor and inline the
// vector constructor so this unit emits no non-retail copy of either.
template <>
_Vector_base<unsigned int, allocator<unsigned int> >::_Vector_base(const allocator<unsigned int> &__a) throw();
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::vector(const allocator<unsigned int> &__a)
	: _Vector_base<unsigned int, allocator<unsigned int> >(__a) {}

// Retail calls both STL dispatch layers directly instead of expanding them:
// the PrereqUnitRec destroy range takes exactly 2 pushes with no tag
// (rowed at 0x002D02A8) and the __copy_ptrs forwarder takes the const-ref
// tag (rowed at 0x002CF594). noinline keeps both out of line so erase and
// the vector dtor keep retail's shape; the bodies are verbatim generic.
template <>
inline __declspec(noinline) void _Destroy<ProductionPrerequisite::PrereqUnitRec *>(ProductionPrerequisite::PrereqUnitRec *__first, ProductionPrerequisite::PrereqUnitRec *__last)
{
	for ( ; __first != __last; ++__first)
		_Destroy(&*__first);
}

template <>
inline __declspec(noinline) ProductionPrerequisite::PrereqUnitRec *__copy_ptrs<ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *>(
	ProductionPrerequisite::PrereqUnitRec *__first, ProductionPrerequisite::PrereqUnitRec *__last, ProductionPrerequisite::PrereqUnitRec *__result, const __false_type &)
{
	return __copy(__first, __last, __result, random_access_iterator_tag(), (ptrdiff_t *)0);
}

}

inline __declspec(noinline) ProductionPrerequisite::PrereqUnitRec::~PrereqUnitRec()
{
}

void ProductionPrerequisite::clear()
{
	m_prereqUnits.clear();
	m_prereqSciences.clear();
}

ProductionPrerequisite::ProductionPrerequisite()
{
	clear();
}

ProductionPrerequisite::~ProductionPrerequisite()
{
}

#pragma inline_depth(0)
// ?bfmeEmitProductionPrerequisiteInlines@@YAXPAUPrereqUnitRec@ProductionPrerequisite@@@Z present-unmatched
void bfmeEmitProductionPrerequisiteInlines(ProductionPrerequisite::PrereqUnitRec *p)
{
	p->ProductionPrerequisite::PrereqUnitRec::~PrereqUnitRec();
	_STL::_Destroy(p, p);
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1TransitionDamageFXSlotA@@QAE@XZ=??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1TransitionDamageFXSlotB@@QAE@XZ=??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1TransitionDamageFXSlotC@@QAE@XZ=??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ")
