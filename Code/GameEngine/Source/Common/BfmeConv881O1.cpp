// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv881.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: XferSave::XferSave 0x0060D1F7 (86B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

class BfmeBaseR_009D83D0
{
public:
	virtual ~BfmeBaseR_009D83D0(void) {}
};

struct Gen_t_009d80b0_p12cd
{
	int words[3];
	Gen_t_009d80b0_p12cd(void);
	Gen_t_009d80b0_p12cd(const Gen_t_009d80b0_p12cd &);
	~Gen_t_009d80b0_p12cd(void);
	Gen_t_009d80b0_p12cd &operator=(const Gen_t_009d80b0_p12cd &);
};

struct Gen_t_009d8120_p12cd
{
	int words[3];
	Gen_t_009d8120_p12cd(void);
	Gen_t_009d8120_p12cd(const Gen_t_009d8120_p12cd &);
	~Gen_t_009d8120_p12cd(void);
	Gen_t_009d8120_p12cd &operator=(const Gen_t_009d8120_p12cd &);
};

typedef _STL::pair<const int, Gen_t_009d80b0_p12cd> BfmeHashPairA009D83D0;
typedef _STL::hash_map<int, Gen_t_009d80b0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<BfmeHashPairA009D83D0> >
	BfmeHashMapA009D83D0;
typedef _STL::pair<const int, Gen_t_009d8120_p12cd> BfmeHashPairB009D83D0;
typedef _STL::hash_map<int, Gen_t_009d8120_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<BfmeHashPairB009D83D0> >
	BfmeHashMapB009D83D0;

// XferSave: same primary vptr 0x00C7B010 as the rowed XferSave dtor 0x0060D0B3
// and its deleting wrapper 0x0060D24D (XferSaveDeletingDtor.cpp), which
// defines the dtor; this TU only declares it.
class XferSave : public BfmeBaseR_009D83D0
{
public:
	XferSave(void);
	virtual ~XferSave(void);

private:
	int m_bfmePad;
	unsigned char m_bfmeFlag;
	unsigned char m_bfmePadTail[3];
	_STL::vector<int> m_bfmeVector;
	BfmeHashMapA009D83D0 m_bfmeB;
	BfmeHashMapB009D83D0 m_bfmeC;
};

XferSave::XferSave(void)
	: m_bfmePad(0), m_bfmeFlag(false), m_bfmeVector()
{
}
