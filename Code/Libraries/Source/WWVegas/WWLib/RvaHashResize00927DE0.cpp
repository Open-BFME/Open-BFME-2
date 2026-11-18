// cl: /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: STLport hashtable<V, K>::resize, near-twin of the 20-body family
// in RvaHashResize.cpp (twin 0x00067270). Every one of those computes the
// bucket index from a single dword key field at value+0 (node+4): "mov eax,
// [ecx+4]; xor edx,edx; div [esp+0x10]". This body (0x00927DE0) instead reads
// TWO dword fields, node+4 and node+8, and combines them before the div:
// "mov eax,[ecx+8]; mov edx,[ecx+4]; shl eax,0x10; add eax,edx; xor edx,edx;
// div [esp+0x10]" -- i.e. key = (value.a[1] << 16) + value.a[0]. The caller
// at 0x00928590 and the landed neighbour ??_$_Rb_tree<Gen_p16pod,...>::_M_insert
// (0x00927C30, RvaTreeMInsert00927C30.cpp) show a 16-byte Gen_p16pod{int a[4]}
// POD already in use one function below this one in the same source file, so
// this table is spelled with the same POD and a hash functor that folds two
// of its four ints into the bucket key.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> void __advance<unsigned int const *,int>(unsigned int const * &,int,_STL::random_access_iterator_tag const &); }
namespace _STL { template <> unsigned int const * __lower_bound<unsigned int const *,unsigned int,_STL::less<unsigned int>,int>(unsigned int const *,unsigned int const *,unsigned int const &,_STL::less<unsigned int>,int *); }
namespace _STL { template <> void * * __uninitialized_fill_n<void * *,unsigned int,void *>(void * *,unsigned int,void * const &,_STL::__true_type const &); }
namespace _STL { template <> void advance<unsigned int const *,int>(unsigned int const * &,int); }
namespace _STL { template <> void * * fill_n<void * *,unsigned int,void *>(void * *,unsigned int,void * const &); }
namespace _STL { template <> void swap<_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > >(_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > &,_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > &); }
namespace _STL { template <> void * * uninitialized_fill_n<void * *,unsigned int,void *>(void * *,unsigned int,void * const &); }
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::_STLP_alloc_proxy(_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > const &); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::_Vector_base(unsigned int,_STL::allocator<void *> const &); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::vector(unsigned int,void * const &,_STL::allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::~vector(); }
namespace _STL { template <> void * * _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> void * * allocator<void *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::deallocate(void * *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<void *>::deallocate(void * *,unsigned int) const; }
namespace _STL { template <> _STL::allocator<void *> vector<void *,_STL::allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::swap(_STL::vector<void *,_STL::allocator<void *> > &); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"

struct Gen_p16pod { int a[4]; };

struct Gen_p16podExtractKey
{
	UnsignedInt operator()( const Gen_p16pod &x ) const
	{
		return ( static_cast<UnsignedInt>( x.a[1] ) << 16 ) + static_cast<UnsignedInt>( x.a[0] );
	}
};

typedef _STL::hashtable<Gen_p16pod, UnsignedInt, _STL::hash<UnsignedInt>,
	Gen_p16podExtractKey, _STL::equal_to<UnsignedInt>,
	_STL::allocator<Gen_p16pod> > Rva00927DE0Table;

// retail 0x00927DE0
void BfmeHashResizeAnchor00927DE0( Rva00927DE0Table &table, UnsignedInt count )
{
	table.resize( count );
}
