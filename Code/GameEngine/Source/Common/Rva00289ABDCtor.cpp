// cl: /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00289ABD@@QAE@XZ retail 0x00289ABD 263 bytes v3.
// Ctor with baseConstruct then vector<BfmeE16> at +0x14 plus bool at +0x24 plus map at +0x28,
// new Rva00288BBA NOTFOUND then push 1.0f onto its ModuleData vector then two new Armor hash_maps.
// Evidence: rowed baseConstruct 0x001B4E63 plus Vector_base<BfmeE16> 0x00211E58 plus map 0x0033C432
// plus StringBase PBD 0x00037BA0 plus Rva00288BBA 0x00288BBA plus push_back ModuleData 0x004DFCB0
// plus hash_map default 0x002898E3 times two plus float g_Va00BBB8D8; vtable 0x007FB8F4.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>
#include <map>
#include <hash_map>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../Include/GameLogic/Armor.h"

inline bool operator==(const ArmorTemplate &x, const ArmorTemplate &y)
{
	return x.m_damageCoefficient[0] == y.m_damageCoefficient[0];
}

namespace rts
{

template <class _Key>
struct hash
{
};

template <>
struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &key) const
	{
		const unsigned int *words = (const unsigned int *)&key;
		return (words[1] << 16) + words[0];
	}
};

template <class _Key>
struct equal_to
{
	bool operator()(const _Key &left, const _Key &right) const
	{
		return left == right;
	}
};

}

typedef _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorRtsMap;

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void hashtable<pair<NameKeyType const ,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,ArmorTemplate> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,ArmorTemplate> > >::_M_initialize_buckets(unsigned int); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> hashtable<pair<NameKeyType const ,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,ArmorTemplate> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,ArmorTemplate> > >::~hashtable(); }
// Bind to the kept retail copy 0x002896AA (ArmorHashtableRtsCtor.cpp) instead of emitting this unit's own.
namespace _STL { template <> hashtable<pair<NameKeyType const ,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,ArmorTemplate> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,ArmorTemplate> > >::hashtable(unsigned int, rts::hash<NameKeyType> const &, rts::equal_to<NameKeyType> const &, allocator<pair<NameKeyType const ,ArmorTemplate> > const &); }
namespace _STL { template <> hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType>, allocator<pair<NameKeyType const ,ArmorTemplate> > >::hash_map(); }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class ModuleData;

class Rva00288BBA
{
public:
	_STL::vector<const ModuleData *> m_vec;
	AsciiString m_str;
	Rva00288BBA(const AsciiString &s);
};

extern const float g_Va00BBB8D8;

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) BFME2NativeNetwork
{
public:
	__declspec(dllimport) __forceinline BFME2NativeNetwork() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
private:
	virtual void rva00289180() = 0;
	char m_flag;
	int m_value;
};

class ExperienceLevelSystem : public BFME2NativeNetwork
{
public:
	ExperienceLevelSystem();
	ArmorRtsMap *m_hash0C;
	ArmorRtsMap *m_hash10;
	_STL::vector<BfmeE16> m_vec14;
	Rva00288BBA *m_rva20;
	unsigned char m_b24;
	_STL::map<int, void *> m_map28;
public:
	virtual ~ExperienceLevelSystem();	// rowed elsewhere; declared so this unit binds to it
	virtual void rva00289180();	// slot 1, rowed in Rva00289180Finish.cpp (0x00289180)
};
ExperienceLevelSystem::ExperienceLevelSystem()
	: m_vec14(_STL::allocator<BfmeE16>()), m_b24(0)
{
	m_rva20 = new Rva00288BBA("NOTFOUND_DEFAULT_ScalarTable");
	float f = g_Va00BBB8D8;
	((_STL::vector<const ModuleData *> *)m_rva20)->push_back(*(const ModuleData **)&f);
	m_hash0C = new ArmorRtsMap;
	m_hash10 = new ArmorRtsMap;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_Va00BBB8D8@@3MB=?g_Va00BBB8D8@@3MA")
