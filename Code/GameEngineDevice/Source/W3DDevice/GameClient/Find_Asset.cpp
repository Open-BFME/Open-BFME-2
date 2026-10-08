// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// Open-BFME5: AssetRegistry::Find_Asset, the counted lookup reverse/symbols.csv
// already pins at 0x009EEC60 because Rva009EBEC0 returns its result.
//
// The layout is the one Render_Obj_Exists.cpp already proved for this class --
// the critical section at +0x34, the hash_map at +0x4C and the name-key
// generator at +0x1F8 -- and the AssetReference model is the one
// Rva009EBEC0.cpp already carries, with the raw-pointer constructor this body
// needs added: retail bumps the sixteen-bit count at +4 of the found asset
// WITHOUT a null test, which the copy constructor's guarded form cannot do.
//
// The destructor on AssetReference is load-bearing: it is what arms the second
// unwind state. Without it the same body compiles to 175 bytes and the state
// store ahead of EnterCriticalSection disappears.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

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

class CountedAsset
{
public:
	// Retail slot 0 (this TU only): the unsigned-key name lookup below returns
	// whatever this getter yields; miss path returns "<unknown>".
	virtual const char *rvaSlot0();
	virtual void enumerationSlot04();
	virtual void enumerationSlot08();
	virtual void enumerationSlot0C();
	virtual void enumerationSlot10();
	virtual void enumerationSlot14();
	virtual void enumerationSlot18();
	virtual void enumerationSlot1C();
	virtual void enumerationSlot20();
	virtual void enumerationSlot24();
	virtual void enumerationSlot28();
	virtual void enumerationSlot2C();
	virtual void enumerationSlot30();
	virtual int enumerationSlot34();
	void Release_Ref();
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

class AssetReference
{
public:
	AssetReference() : m_object( 0 ) {}
	AssetReference( CountedAsset *object ) : m_object( object )
	{
		++*(unsigned short *)((char *)object + 4);
	}
	AssetReference( const AssetReference &that ) : m_object( that.m_object )
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
	~AssetReference();

private:
	CountedAsset *m_object;
};

// Cursor payload and STL traversal from the complete BFME1 donor at
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f. Target node +8 is the asset.
struct Gen_t_009f14c0_p12cd
{
    CountedAsset *m_asset;
    int a[2];
    Gen_t_009f14c0_p12cd();
    Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
    ~Gen_t_009f14c0_p12cd();
    Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};
typedef _STL::hash_map<int, Gen_t_009f14c0_p12cd> GenAssetHash;

class AssetRegistry
{
public:
	AssetReference Find_Asset(const char *name);
	AssetReference Get_Current_Asset();
	const char *rva006213B0(unsigned int key);

private:
	unsigned char m_unmodelled_000[0x34];
	CRITICAL_SECTION m_lock;
	GenAssetHash m_map4c;
	GenAssetHash::iterator m_iterator60;
	unsigned char m_unmodelled_068[0x188];
	int m_filter1f0;
	unsigned char m_unmodelled_1f4[4];
	NameKeyGenerator *m_hash_context;
};

// ?Find_Asset@AssetRegistry@@QAE?AVAssetReference@@PBD@Z
AssetReference AssetRegistry::Find_Asset(const char *name)
{
	CriticalSectionLock lock((int)&m_lock);
	unsigned int key = (unsigned int)m_hash_context->nameToLowercaseKey(name);
	if (key == 0)
		return AssetReference();

	typedef _STL::hash_map<unsigned int, CountedAsset *> AssetRegistryHash;
	AssetRegistryHash *assets = (AssetRegistryHash *)((char *)this + 0x4C);
	AssetRegistryHash::iterator it = assets->find(key);
	if (it == assets->end())
		return AssetReference();

	return AssetReference((*it).second);
}

// ?rva006213B0@AssetRegistry@@QAEPBDI@Z — unsigned-key name lookup on the
// +0x4C asset map (same lock at +0x34 as Find_Asset). A miss returns the
// "<unknown>" literal; a hit returns the asset's slot-0 getter. Retail is
// 197 bytes at 0x006213B0, ret 4, reached by no named caller.
const char *AssetRegistry::rva006213B0(unsigned int key)
{
	CriticalSectionLock lock((int)&m_lock);

	typedef _STL::hash_map<unsigned int, CountedAsset *> AssetRegistryHash;
	AssetRegistryHash *assets = (AssetRegistryHash *)((char *)this + 0x4C);
	AssetRegistryHash::iterator it = assets->find(key);
	if (it == assets->end())
		return "<unknown>";

	return (*it).second->rvaSlot0();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva009EEC60_FindAsset@Rva009EEC60Registry@@QAE?AVRva009EBCE0AssetReference@@PBD@Z=?Find_Asset@AssetRegistry@@QAE?AVAssetReference@@PBD@Z")

// Retail 0x006214D0..0x006215B0, 224 bytes. Proven +8 donor layout:
// lock +34, map +4C, cursor +60/+64, filter +1F0, slot +34 and refcount +4.
// Get_Current_Asset is the existing caller-pin spelling; donor EnumAssets is
// a semantic lead, not independent proof of the original target class name.
AssetReference AssetRegistry::Get_Current_Asset()
{
    CriticalSectionLock lock((int)&m_lock);
    while (m_iterator60 != m_map4c.end())
    {
        CountedAsset *asset = (*m_iterator60).second.m_asset;
        ++m_iterator60;
        if (m_filter1f0 == 0 || m_filter1f0 == asset->enumerationSlot34())
            return AssetReference(asset);
    }
    return AssetReference();
}

