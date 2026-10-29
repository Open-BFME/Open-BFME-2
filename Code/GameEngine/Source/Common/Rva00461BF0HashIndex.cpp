// cl: /Ireference/open-bfme-1/inputs/reference/shims/stringinline /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva00461BF0HashIndex.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ??A?$hash_map@VAsciiString@@VRva0045EF90 0x00411205 (155B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
// Open-BFME: STLport hash_map index for the Rva0045EF90Object value.
// stlport46

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

#include "StringInline.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }

class Rva0045EF90Base
{
public:
	Rva0045EF90Base() : m_value( -1 ) {}
	Rva0045EF90Base( const Rva0045EF90Base &source ) : m_value( source.m_value ) {}
	virtual ~Rva0045EF90Base();

private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object();
	Rva0045EF90Object( const Rva0045EF90Object &source );
	virtual ~Rva0045EF90Object();

private:
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	float m_value14;
	float m_value18;
	float m_value1c;
	float m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[ 3 ];
	AsciiString m_last;
};


namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()( T value ) const;
	};

	template <class T> struct equal_to
	{
		bool operator()( const T &left, const T &right ) const;
	};
}

typedef _STL::hash_map<AsciiString, Rva0045EF90Object,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva00461BF0Map;

// Retail 411205 calls the rowed find (41534B) and insert (410E23).
// These declarations retain the providers' pointer/iterator ABI. They do
// not identify the opaque native insert payload with the donor value type.
struct TreeHintPayload00410E23 { unsigned char m_body[4]; };
class Rva000427195 {
public:
 _STL::pair<const AsciiString, TreeHintPayload00410E23> *rva00410E23(
  const _STL::pair<const AsciiString, TreeHintPayload00410E23> *);
};
class Rva00056F61;
struct Rva0041534BIter { void *m_node; Rva00056F61 *m_table; };
class Rva00056F61 {
public:
 __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
};
typedef _STL::pair<const AsciiString, Rva0045EF90Object> Rva00461BF0Value;

// ??A?$hash_map@VAsciiString@@VRva0045EF90Object@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@_STL@@@_STL@@QAEAAVRva0045EF90Object@@ABVAsciiString@@@Z
template <> Rva0045EF90Object &Rva00461BF0Map::operator[](const AsciiString &key)
{
 void *node;
 { Rva0041534BIter found = reinterpret_cast<Rva00056F61 *>(this)->rva0041534B(&key); node = found.m_node; }
 return !node ? *reinterpret_cast<Rva0045EF90Object *>(
  reinterpret_cast<char *>(reinterpret_cast<Rva000427195 *>(this)->rva00410E23(
   reinterpret_cast<const _STL::pair<const AsciiString, TreeHintPayload00410E23> *>(
    &static_cast<const Rva00461BF0Value &>(Rva00461BF0Value(key, Rva0045EF90Object()))))) + 4)
  : *reinterpret_cast<Rva0045EF90Object *>(reinterpret_cast<char *>(node) + 8);
}

template Rva0045EF90Object &Rva00461BF0Map::operator[](const AsciiString &key);
