// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport46

// STLport's hash_map index over the pair<int, int> table whose lookup and
// insertion bodies are already recovered at 0x00927800 and 0x00928590.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *, allocator<void *> >::size() const { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <hash_map>
#include <cstddef>
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *, allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
// bfme link decl-only end
namespace _STL { template <> void advance<unsigned int const *, int>(unsigned int const * &, int); }
namespace _STL { template <> void __advance<unsigned int const *, int>(unsigned int const * &, int, random_access_iterator_tag const &); }
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }
namespace _STL { template <> __declspec(dllimport) __forceinline void **allocator<void *>::allocate(size_t __n, const void *)
{ return __n != 0 ? (void **)__sgi_alloc::allocate(__n * sizeof(void *)) : 0; } }
namespace _STL { template <> __declspec(dllimport) __forceinline vector<void *>::const_iterator vector<void *>::begin() const { return _M_start; } }
namespace _STL { template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t n) const { return *(begin() + n); } }
namespace _STL { template <> void **vector<void*>::begin(); }
namespace _STL { template <> void **vector<void*>::end(); }

typedef unsigned int UnsignedInt;

typedef _STL::pair<int, int> Rva00928590Key;
typedef _STL::pair<const Rva00928590Key, int> Rva00928590Value;

struct Rva00928590Hash
{
	UnsignedInt operator()( const Rva00928590Key &key ) const
	{
		return ( static_cast<UnsignedInt>( key.second ) << 16 )
			+ static_cast<UnsignedInt>( key.first );
	}
};

struct Rva00928590Eq
{
	bool operator()( const Rva00928590Key &left,
		const Rva00928590Key &right ) const
	{
		return left.first == right.first && left.second == right.second;
	}
};

typedef _STL::hash_map<Rva00928590Key, int, Rva00928590Hash,
	Rva00928590Eq,
	_STL::allocator<_STL::pair<const Rva00928590Key, int> > >
	Rva00928620Map;

namespace _STL {
typedef pair<const Rva00928590Key, int> EdgeValue;
typedef hashtable<EdgeValue, Rva00928590Key, Rva00928590Hash,
    _Select1st<EdgeValue>, Rva00928590Eq, allocator<EdgeValue> > EdgeTable;
template <> EdgeValue &EdgeTable::_M_insert(const EdgeValue &);
template void EdgeTable::resize(unsigned int);
}

template int &Rva00928620Map::operator[]( const Rva00928590Key & );
