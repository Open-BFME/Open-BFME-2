// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// Open-BFME2: BfmeObjEME::bfmeGetEME, the raw key-returning twin of the
// AssetRegistry lookups this directory already proved (Find_Asset 188B,
// Render_Obj_Exists_Impl 170B). Same class layout as the verified BFME2
// family -- the critical section at +0x34, the hash_map at +0x4C and the
// name-key generator at +0x1F8 (BFME1 donor has +0x2c/+0x44/+0x1F0) -- and
// the BFME1 donor body verbatim: lock, lowercase key, null-key null,
// hash find, not-found null, found returns the key itself.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
// Keep hash_map<unsigned, void *>::find and the hashtable lookups under it
// inline-only: the lookup below inlines all three, and this TU's COMDAT copies
// are not the bodies the link keeps.
namespace _STL {
typedef hashtable<pair<const unsigned int, void *>, unsigned int, hash<unsigned int>,
	_Select1st<pair<const unsigned int, void *> >, equal_to<unsigned int>,
	allocator<pair<const unsigned int, void *> > > BfmeUIntPtrTable;
template <> template <> __declspec(dllimport) __forceinline
_Hashtable_node<pair<const unsigned int, void *> > *BfmeUIntPtrTable::_M_find<unsigned int>(const unsigned int &__key) const
{
	size_type __n = _M_hash(__key) % _M_buckets.size();
	_Node *__first;
	for (__first = (_Node *)_M_buckets[__n];
	     __first && !_M_equals(_M_get_key(__first->_M_val), __key);
	     __first = __first->_M_next)
		{}
	return __first;
}
template <> template <> __declspec(dllimport) __forceinline
BfmeUIntPtrTable::iterator BfmeUIntPtrTable::find<unsigned int>(const unsigned int &__key)
{ return iterator(_M_find(__key), this); }
template <> __declspec(dllimport) __forceinline
hash_map<unsigned int, void *>::iterator hash_map<unsigned int, void *>::find(const unsigned int &__key)
{ return _M_ht.find(__key); }
}

struct CRITICAL_SECTION
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey(const char *name);
};

class BfmeObjEME
{
public:
	void *bfmeGetEME(void *name);

private:
	unsigned char m_unmodelled_000[0x34];
	CRITICAL_SECTION m_lock;
	_STL::hash_map<unsigned int, void *> m_assets;
	unsigned char m_gap[0x1f8 - 0x4c - sizeof(_STL::hash_map<unsigned int, void *>)];
	NameKeyGenerator *m_hash_context;
};

// ?bfmeGetEME@BfmeObjEME@@QAEPAXPAX@Z
void *BfmeObjEME::bfmeGetEME(void *name)
{
	CriticalSectionLock lock(&m_lock);
	unsigned int key =
		(unsigned int)m_hash_context->nameToLowercaseKey((const char *)name);
	if (key == 0)
		return 0;
	typedef _STL::hash_map<unsigned int, void *> AssetRegistryHash;
	AssetRegistryHash *assets = &m_assets;
	AssetRegistryHash::iterator it = assets->find(key);
	if (it == assets->end())
		return 0;
	return (void *)key;
}
