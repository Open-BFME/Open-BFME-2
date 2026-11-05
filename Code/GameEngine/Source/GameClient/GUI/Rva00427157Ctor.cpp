// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??0Rva00427157@@QAE@ABVAsciiString@@PBV0@@Z @0x00427157 62B ctor copies AsciiString at +0 via rowed StringBase copy 0x000365F0 fills 8 floats at +4 with 1.0f if src null else copies 8 floats from src+4 caller 0x004273FF
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// Inline bucket size without emitting a competing out-of-line copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(_M_finish - _M_start); }
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress the TU's non-retail const-begin copy (row 54 family-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
#include "ascii_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Keep the native allocator branch visible for inlining and bind any
// out-of-line call to the shared STLport provider.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Inline bucket indexing without emitting a competing out-of-line copy.
namespace _STL { template <> __declspec(dllimport) __forceinline
void *const &vector<void *>::operator[](size_t n) const { return _M_start[n]; } }

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

namespace rts
{
template <typename T> struct hash;
// Retail's folded 47-byte _M_find hashes the integer key inline.
template <> struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &v) const { return (unsigned int)v; }
};
}

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"

class Rva00427157
{
public:
	Rva00427157(const AsciiString &name, const Rva00427157 *src);
	float rva004270FA(int index);
	friend void Rva00427114Parse(class INI *ini, Rva00427157 *store);
private:
	AsciiString m_name;
	float m_vals[8];
};

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

#include "../../../Include/Common/INI/INI.h"

extern ConstCharPtr g_Va00DC85C4Names[];
extern "C" {
void __identifier("?Rva00427114Parse@@YAXPAVINI@@PAVRva00427157@@@Z")();
}
// The retail table at 0x0083C614: 1 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C3C614[2] = {
	{ "Armor", (FieldParseProc)&__identifier("?Rva00427114Parse@@YAXPAVINI@@PAVRva00427157@@@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};

Rva00427157::Rva00427157(const AsciiString &name, const Rva00427157 *src) : m_name(name)
{
	if (!src) {
		for (int i = 0; i < 8; ++i)
			m_vals[i] = 1.0f;
	} else {
		for (int i = 0; i < 8; ++i)
			m_vals[i] = src->m_vals[i];
	}
}

float Rva00427157::rva004270FA(int index)
{
	return m_vals[index];
}

void Rva00427114Parse(INI *ini, Rva00427157 *store)
{
	const char *key = ini->getNextToken(0);
	const char *val = ini->getNextToken(0);
	float f = ini->dup_002EE10(val);
	int idx = ini->scanIndexList(key, g_Va00DC85C4Names);
	store->m_vals[idx] = f;
}

typedef _STL::hash_map<NameKeyType, const Rva00427157 *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > ArmorMap;

class LivingWorldAutoResolveArmorStore
{
public:
	const Rva00427157 *find(const AsciiString &name);
	const Rva00427157 *getDefault();
	static void parseArmorDefinition(INI *ini);
private:
	char m_pad[0xC];
	ArmorMap m_map;
};

const Rva00427157 *LivingWorldAutoResolveArmorStore::find(const AsciiString &name)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorMap::const_iterator it = m_map.find(key);
	if (it != m_map.end())
		return it->second;
	return (const Rva00427157 *)it._M_cur;
}

const Rva00427157 *LivingWorldAutoResolveArmorStore::getDefault()
{
	AsciiString name("AutoResolve_DefaultArmor");
	return find(name);
}

extern LivingWorldAutoResolveArmorStore *TheLivingWorldAutoResolveArmorStore;

void LivingWorldAutoResolveArmorStore::parseArmorDefinition(INI *ini)
{
	const char *token = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(token);
	const Rva00427157 *defaultArmor = TheLivingWorldAutoResolveArmorStore->getDefault();
	ArmorMap &armorMap = TheLivingWorldAutoResolveArmorStore->m_map;
	ArmorMap::iterator it;
	it = armorMap.find(key);
	if (it != armorMap.end())
	{
		Rva00427157 local(AsciiString(token), defaultArmor);
		ini->initFromINI(&local, g_00C3C614);
		return;
	}
	Rva00427157 *armor = new Rva00427157(AsciiString(token), defaultArmor);
	TheLivingWorldAutoResolveArmorStore->m_map[key] = armor;
	ini->initFromINI(armor, g_00C3C614);
}


void __cdecl Rva00427294Parse(INI *ini, void *dummy1, void *instance, void *dummy2)
{
	const char *token = ini->getNextToken(0);
	*(const Rva00427157 **)instance = TheLivingWorldAutoResolveArmorStore->find(AsciiString(token));
	if (*(const Rva00427157 **)instance == 0)
	{
		throw INIException(1, "Unknown LivingWorldAutoResolveArmor %s", token);
	}
}
