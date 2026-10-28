// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::vector(const vector &) for element types whose
// 96-byte copy constructor sits unclaimed in retail.  Same recipe as the
// rowed Rva00500DA0VectorCopy.cpp / vector<PrereqUnitRec> copy at 0x002CFE45:
// a non-trivial element (user-declared dtor) selects the EH-guarded path with
// out-of-line get_allocator, _Vector_base(n, alloc) and __uninitialized_copy.
// Element size is read from each body's own idiv; element names reuse the
// spelling the ledger already gives the same vector's helpers (push_back,
// _Construct or __uninitialized_copy rows); no layout beyond size is claimed.
// Callees spelled differently in the ledger are pinned at the addresses the
// retail REL32s prove.
//
//   ctor        stride  _Vector_base  __uninitialized_copy  element
//   0x002B9247   0x14   0x004FF36C    0x002B8385            Rva002B72C9 (_Construct 0x002B8226 inside the copy)
//   0x0032BF6B   0x0C   0x005C8C37    0x0032B5C5            vector<BfmeE8> (rowed uninitialized_copy type)
//   0x004244EE   0x0C   0x005C8C37    0x00423ED1            Rva00423A4A (rowed uninitialized_copy type)
//   0x0052CBC5   0x0C   0x005C8C37    0x0052C93B            Rva0052BDE6 (_Construct 0x0052C34D inside the copy)
//   0x0052CC64   0x14   0x004FF36C    0x0052C961            Rva0052BE33 (_Construct 0x0052C392 inside the copy)
//   0x0052CE7D   0x0C   0x005C8C37    0x0052C9D3            Rva0052BEF0 (_Construct 0x0052C431 inside the copy)
//   0x0052D417   0x0C   0x005C8C37    0x0052D3F1            Rva005668E9Element (rowed uninitialized_copy type)
#include <vector>
// Suppress this TU's non-retail copy of ??0?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE8;
namespace _STL { template <> vector<BfmeE8,allocator<BfmeE8> >::vector(vector<BfmeE8,allocator<BfmeE8> > const &); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva005668E9Element@@@_STL@@YAXPAURva005668E9Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005668E9Element;
namespace _STL { template <> void _Destroy<Rva005668E9Element *>(Rva005668E9Element *,Rva005668E9Element *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAVRva0052BE33@@@_STL@@YAXPAVRva0052BE33@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0052BE33;
namespace _STL { template <> void _Destroy<Rva0052BE33 *>(Rva0052BE33 *,Rva0052BE33 *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva002B72C9@@@_STL@@YAXPAURva002B72C9@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva002B72C9;
namespace _STL { template <> void _Destroy<Rva002B72C9 *>(Rva002B72C9 *,Rva002B72C9 *); }

struct Rva002B72C9
{
	unsigned int m_data[5];
	~Rva002B72C9() {}
};

struct BfmeE8
{
	unsigned int m_data[2];
	~BfmeE8() {}
};

struct Rva00423A4A
{
	unsigned int m_data[3];
	// Size-only view: use the vector-owning definition's copy constructor and
	// destructor (retail's _Construct 0x00423E83 calls the former).
	Rva00423A4A(const Rva00423A4A &o);
	~Rva00423A4A();
};

class Rva0052BDE6
{
public:
	unsigned int m_data[3];
	~Rva0052BDE6() {}
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Construct<Rva0052BDE6,Rva0052BDE6>(Rva0052BDE6 *, Rva0052BDE6 const &); }

class Rva0052BE33
{
public:
	unsigned int m_data[5];
	~Rva0052BE33() {}
};

class Rva0052BEF0
{
public:
	unsigned int m_data[3];
	~Rva0052BEF0() {}
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Construct<Rva0052BEF0,Rva0052BEF0>(Rva0052BEF0 *, Rva0052BEF0 const &); }

struct Rva005668E9Element
{
	unsigned int m_data[3];
	~Rva005668E9Element() {}
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Construct<Rva005668E9Element,Rva005668E9Element>(Rva005668E9Element *, Rva005668E9Element const &); }
// Keep the Rva0052BDE6/Rva0052BEF0 range destroys inline-only: nothing here
// calls them out of line, and this view's empty-destructor copies are not the
// bodies retail kept (the overflow units own them).
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void __destroy_aux<Rva0052BDE6 *>(Rva0052BDE6 *__first, Rva0052BDE6 *__last, const __false_type &)
{ for ( ; __first != __last; ++__first) _Destroy(&*__first); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void _Destroy<Rva0052BDE6 *>(Rva0052BDE6 *__first, Rva0052BDE6 *__last)
{ __destroy(__first, __last, (Rva0052BDE6 *)0); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void __destroy_aux<Rva0052BEF0 *>(Rva0052BEF0 *__first, Rva0052BEF0 *__last, const __false_type &)
{ for ( ; __first != __last; ++__first) _Destroy(&*__first); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void _Destroy<Rva0052BEF0 *>(Rva0052BEF0 *__first, Rva0052BEF0 *__last)
{ __destroy(__first, __last, (Rva0052BEF0 *)0); }
}

// These retail copy loops construct each destination element out of line.
namespace _STL {
template <> __declspec(noinline) inline Rva00423A4A *
__uninitialized_copy<const Rva00423A4A *, Rva00423A4A *>(const Rva00423A4A *first, const Rva00423A4A *last, Rva00423A4A *result, const __false_type &)
{
    Rva00423A4A *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
template <> __declspec(noinline) inline Rva0052BDE6 *
__uninitialized_copy<const Rva0052BDE6 *, Rva0052BDE6 *>(const Rva0052BDE6 *first, const Rva0052BDE6 *last, Rva0052BDE6 *result, const __false_type &)
{
    Rva0052BDE6 *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
template <> __declspec(noinline) inline Rva0052BEF0 *
__uninitialized_copy<const Rva0052BEF0 *, Rva0052BEF0 *>(const Rva0052BEF0 *first, const Rva0052BEF0 *last, Rva0052BEF0 *result, const __false_type &)
{
    Rva0052BEF0 *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
template <> __declspec(noinline) inline Rva005668E9Element *
__uninitialized_copy<const Rva005668E9Element *, Rva005668E9Element *>(const Rva005668E9Element *first, const Rva005668E9Element *last, Rva005668E9Element *result, const __false_type &)
{
    Rva005668E9Element *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
// vector<vector<BfmeE8> >'s copy loop too (retail 0x0032B5C5, the copy
// SidesListCastleBuildLists.cpp compiles): without it this /EHsc unit emits
// STLport's try/catch rollback, which retail's loop does not have.
template <> __declspec(noinline) inline vector<BfmeE8> *
__uninitialized_copy<const vector<BfmeE8> *, vector<BfmeE8> *>(const vector<BfmeE8> *first, const vector<BfmeE8> *last, vector<BfmeE8> *result, const __false_type &)
{
    vector<BfmeE8> *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
}

template _STL::vector<Rva002B72C9>::vector(const _STL::vector<Rva002B72C9> &);
template _STL::vector<_STL::vector<BfmeE8> >::vector(const _STL::vector<_STL::vector<BfmeE8> > &);
template _STL::vector<Rva00423A4A>::vector(const _STL::vector<Rva00423A4A> &);
template _STL::vector<Rva0052BDE6>::vector(const _STL::vector<Rva0052BDE6> &);
template _STL::vector<Rva0052BE33>::vector(const _STL::vector<Rva0052BE33> &);
template _STL::vector<Rva0052BEF0>::vector(const _STL::vector<Rva0052BEF0> &);
template _STL::vector<Rva005668E9Element>::vector(const _STL::vector<Rva005668E9Element> &);
