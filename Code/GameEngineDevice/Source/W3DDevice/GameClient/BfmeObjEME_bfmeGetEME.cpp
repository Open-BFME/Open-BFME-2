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

struct CRITICAL_SECTION
{
	unsigned char m_data[0x1c];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
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
	unsigned char m_unmodelled_048[0x1a8];
	NameKeyGenerator *m_hash_context;
};

// ?bfmeGetEME@BfmeObjEME@@QAEPAXPAX@Z
void *BfmeObjEME::bfmeGetEME(void *name)
{
	CriticalSectionLock lock((int)&m_lock);
	unsigned int key =
		(unsigned int)m_hash_context->nameToLowercaseKey((const char *)name);
	if (key == 0)
		return 0;
	typedef _STL::hash_map<unsigned int, void *> AssetRegistryHash;
	AssetRegistryHash *assets =
		(AssetRegistryHash *)((char *)this + 0x4C);
	AssetRegistryHash::iterator it = assets->find(key);
	if (it == assets->end())
		return 0;
	return (void *)key;
}
