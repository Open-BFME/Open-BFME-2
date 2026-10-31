// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002BFD6F@Rva002BFD6F@@QAEXXZ @0x002BFD6F 63B.
// Reset-like __thiscall: zeroes the dword at +0x88, clears the Rva002BF75A
// member at +0xAC via rowed 0x002BF7BE, clears the ArmorTemplate hashtable at
// +0x98 via rowed 0x001DBCDC, then zeroes bytes +0x19/+0x24/+0x25/+0x78/+0x94
// and the float at +0x7C (xorps/movss). Evidence: REL32 callees match this
// TU's own call graph; map typedef copied from neighbour ArmorStoreCtor.cpp
// (same rowed hashtable clear); chain lane: calls 0x002BF7BE now rowed;
// caller is unclaimed 0x0009AB6B 26B which this unblocks.
#include <hash_map>
#include <cstddef>
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
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

struct Rva002C00C1Element
{
public:
	bool operator<(const Rva002C00C1Element&)const;
	bool operator==(const Rva002C00C1Element&)const;
	char bytes[1]; // +0x00
};

typedef _STL::hash_map<int, Rva002C00C1Element, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, Rva002C00C1Element> > > LivingWorldTable;

struct Rva002BF75A { LivingWorldTable m_table; ~Rva002BF75A(); void rva002BF75A(void *p); void rva002BF7BE(); };

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva002BFD6F
{
public:
	void rva002BFD6F();

private:
	char m_pad00[0x19];
	unsigned char m_19; // +0x19
	char m_pad1A[0x24 - 0x1A];
	unsigned char m_24; // +0x24
	unsigned char m_25; // +0x25
	char m_pad26[0x78 - 0x26];
	unsigned char m_78; // +0x78
	char m_pad79[0x7C - 0x79];
	float m_7C; // +0x7C
	char m_pad80[0x88 - 0x80];
	unsigned int m_88; // +0x88
	char m_pad8C[0x94 - 0x8C];
	unsigned char m_94; // +0x94
	char m_pad95[0x98 - 0x95];
	ArmorTemplateMap m_map; // +0x98
	Rva002BF75A m_thing; // +0xAC
};

void Rva002BFD6F::rva002BFD6F()
{
	m_88 = 0;
	m_thing.rva002BF7BE();
	m_map.clear();
	m_24 = 0;
	m_25 = 0;
	m_78 = 0;
	m_94 = 0;
	m_19 = 0;
	m_7C = 0.0f;
}
// bfme link decl-only begin
namespace _STL { template <> void hashtable<_STL::pair<NameKeyType const,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<_STL::pair<NameKeyType const,ArmorTemplate> >,_STL::equal_to<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,ArmorTemplate> > >::clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<unsigned int,_STL::_Hashtable_node<_STL::pair<NameKeyType const,ArmorTemplate> >,_STL::allocator<_STL::_Hashtable_node<_STL::pair<NameKeyType const,ArmorTemplate> > > >::deallocate(_STL::_Hashtable_node<_STL::pair<NameKeyType const,ArmorTemplate> > *,unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Hashtable_node<_STL::pair<NameKeyType const,ArmorTemplate> > >::deallocate(_STL::_Hashtable_node<_STL::pair<NameKeyType const,ArmorTemplate> > *,unsigned int) const; }
// bfme link decl-only end
