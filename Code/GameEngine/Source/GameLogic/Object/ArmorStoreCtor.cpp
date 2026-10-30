// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// Retail RVA 0x00360BB8, 70 bytes.
// ArmorStore::ArmorStore: base SubsystemInterface init (retail 0x001B4E63,
// which installs vtable 0xBD77A0 and zeroes +4/+8, proving the BFME2 base is
// 0xC bytes, not the ZH 8), derived vtable 0xC16988, member hash_map default
// construction (retail 0x00360B99) then hashtable clear (rowed 0x001DBCDC).
// Shard: Armor.cpp sees the ZH 8-byte SubsystemInterface, which puts the map
// at +0x8; the TU-local base below carries the retail-proven extra members.

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
#include <cstddef>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
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
	size_t operator()(const T &value) const { return (size_t)value; }	// Zero Hour's rts::hash<NameKeyType>, inline
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38]; // DAMAGE_NUM_TYPES, ZH count
};

#include "ascii_string.h"
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Inline STLport's const access while leaving the external copy to its owner.
namespace _STL { template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t n) const { return *(begin() + n); } }

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

namespace _STL {
typedef hashtable<pair<const NameKeyType, ArmorTemplate>, NameKeyType,
    rts::hash<NameKeyType>, _Select1st<pair<const NameKeyType, ArmorTemplate> >,
    equal_to<NameKeyType>, allocator<pair<const NameKeyType, ArmorTemplate> > > ArmorTable;
// XferSaveOpen.cpp supplies the retail table-clear instantiation.
template <> void ArmorTable::clear();
}

class ArmorStore : public SubsystemInterface
{
public:
	ArmorStore();
	virtual ~ArmorStore();
	void init() { }
	void reset() { }
	void update() { }
	const ArmorTemplate *findArmorTemplate(AsciiString name) const;

private:
	ArmorTemplateMap m_armorTemplates; // +0x0C
};

ArmorStore::ArmorStore()
{
	m_armorTemplates.clear();
}

ArmorStore::~ArmorStore()
{
	m_armorTemplates.clear();
}

const ArmorTemplate *ArmorStore::findArmorTemplate(AsciiString name) const
{
	NameKeyType namekey = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::const_iterator it = m_armorTemplates.find(namekey);
	if (it == m_armorTemplates.end())
	{
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}
