// cl: /O1 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ??0Rva002BB7AA@@QAE@HH@Z @0x002BB7AA 44B.
// Two-int ctor with hash_map and vector members.
// Evidence: unlock plus caller 0x002BCA7D; hash_map row 0x002BB686 plus Vector_base row 0x00211E58; prev next STL same alloc flags.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "../../Include/Common/PlayerAITypeEntry.h"

#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <vector>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// vector<void*> operator[] otherwise instantiates a per-TU COMDAT (one
// byte shape per TU flags); an explicit dllimport+forceinline specialization
// takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

struct Rva002BB686Element
{
	char m_data[1];
};


class Rva002BB7AA
{
public:
	Rva002BB7AA(int a, int b);

private:
	int m_0;
	int m_4;
	_STL::hash_map<int, Rva002BB686Element> m_8;
	char m_pad1C[0x10];
	_STL::vector<PlayerAITypeEntry> m_2c;
};

// ??0Rva002BB7AA@@QAE@HH@Z
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<PlayerAITypeEntry *>(PlayerAITypeEntry *,PlayerAITypeEntry *); }
namespace _STL { template <> void _Destroy<PlayerAITypeEntry>(PlayerAITypeEntry *); }
namespace _STL { template <> _STL::_OKToMemCpy<void *,void *> _IsOKToMemCpy<void *,void *>(void * *,void * *); }
namespace _STL { template <> template <> void * * vector<void *,_STL::allocator<void *> >::_M_allocate_and_copy<void * *>(unsigned int,void * *,void * *); }
namespace _STL { template <> void __destroy<PlayerAITypeEntry *,PlayerAITypeEntry>(PlayerAITypeEntry *,PlayerAITypeEntry *,PlayerAITypeEntry *); }
namespace _STL { template <> void __destroy_aux<PlayerAITypeEntry *>(PlayerAITypeEntry *,PlayerAITypeEntry *,_STL::__false_type const &); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::_Vector_base(_STL::allocator<void *> const &); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::vector(_STL::allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> _Vector_base<PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::~_Vector_base(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> hashtable<_STL::pair<int const,Rva002BB686Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002BB686Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > >::~hashtable(); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::~vector(); }
namespace _STL { template <> vector<PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::~vector(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_fill_insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_insert_overflow(void * *,void * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> unsigned int hashtable<_STL::pair<int const,Rva002BB686Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002BB686Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > >::_M_next_size(unsigned int) const; }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_set(void * *,void * *,void * *); }
namespace _STL { template <> _STL::__true_type _OKToMemCpy<void *,void *>::_Ret(); }
namespace _STL { template <> void * * _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::allocate(unsigned int); }
namespace _STL { template <> void * * allocator<void *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> unsigned int vector<void *,_STL::allocator<void *> >::capacity() const; }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva002BB686Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002BB686Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > >::clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<PlayerAITypeEntry *,PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::deallocate(PlayerAITypeEntry *,unsigned int); }
namespace _STL { template <> void allocator<PlayerAITypeEntry>::deallocate(PlayerAITypeEntry *,unsigned int) const; }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva002BB686Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002BB686Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > >::_M_initialize_buckets(unsigned int); }
namespace _STL { template <> hashtable<_STL::pair<int const,Rva002BB686Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva002BB686Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > >::hashtable(unsigned int,_STL::hash<int> const &,_STL::equal_to<int> const &,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > const &); }
namespace _STL { template <> hash_map<int,Rva002BB686Element,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva002BB686Element> > >::hash_map(); }
// bfme link decl-only end
Rva002BB7AA::Rva002BB7AA(int a, int b) : m_0(a), m_4(b), m_8(), m_2c()
{
}
