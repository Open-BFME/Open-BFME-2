// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
// partial score=0.9 date=2026-10-05
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
// Retail 0x006214D0, 224B, ret 4. AssetRegistry cursor lookup: nodes carry
// next at +0, key at +4, entry at +8; exhausted chains resume at the next
// non-empty bucket past the node's key; cursor advances past the hit; a
// nonzero +0x1F0 tag skips entries whose vtable slot 0x34 disagrees; miss
// returns empty. Identity: symbols.csv pins Get_Current_Asset here, layout
// (+0x34 lock, +0x4C map, +0x60/+0x64 cursor, +0x1F0 tag, +0x1F8 nametable)
// matches Find_Asset.cpp's proven AssetRegistry model, neighbors are
// Find_Asset/Begin/Add_Prototype_Impl.
// This v5 bank reproduces 221/224B: SEH prolog, this->edi, lock->ebx,
// inline guard, bucket div/scan, shared LeaveCriticalSection tail all match.
// Remaining gap is one frame dword (sub esp,8 + a duplicated guard spill):
// retail keeps node/entry/next/i in regs with a single lock spill, this
// shape spills twice. Next levers: fewer named locals (merge next into node
// was tried and kept the frame), or a guard variant whose dtor shares the
// funclet spill. Worked in Find_Asset.cpp (which owns AssetReference +
// the +0x4C map model); the TU additions needed are the AssetLockGuard,
// Rva6214D0Entry (13 pad virtuals + slot34), the cursor/tag members and the
// method below.
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

struct AssetLockGuard
{
	AssetLockGuard(CRITICAL_SECTION *section) : m_section(section)
	{
		EnterCriticalSection(section);
	}
	~AssetLockGuard()
	{
		LeaveCriticalSection(m_section);
	}
	CRITICAL_SECTION *m_section;
};

class CountedAsset
{
public:
	virtual const char *rvaSlot0();
	void Release_Ref();
};

class Rva6214D0Entry
{
public:
	virtual int rvaV00();
	virtual int rvaV01();
	virtual int rvaV02();
	virtual int rvaV03();
	virtual int rvaV04();
	virtual int rvaV05();
	virtual int rvaV06();
	virtual int rvaV07();
	virtual int rvaV08();
	virtual int rvaV09();
	virtual int rvaV10();
	virtual int rvaV11();
	virtual int rvaV12();
	virtual int rvaSlot34();
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

class AssetRegistry
{
public:
	AssetReference Get_Current_Asset();

private:
	unsigned char m_unmodelled_000[0x34];
	CRITICAL_SECTION m_lock;
	unsigned char m_unmodelled_050[0x60 - 0x50];
	void *m_cachedNode; // +0x60
	void *m_cachedTable; // +0x64
	unsigned char m_unmodelled_068[0x1F0 - 0x68];
	unsigned m_tag; // +0x1F0
	unsigned char m_unmodelled_1F4[0x1F8 - 0x1F4];
	void *m_hash_context;
};

// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
AssetReference AssetRegistry::Get_Current_Asset()
{
	AssetLockGuard guard((CRITICAL_SECTION *)((char *)this + 0x34));

	void *node = m_cachedNode;
	if (!node)
		return AssetReference();

	for (;;)
	{
		Rva6214D0Entry *entry = *(Rva6214D0Entry **)((char *)node + 8);
		node = *(void **)m_cachedNode;
		if (!node)
		{
			unsigned i = *(unsigned *)((char *)m_cachedNode + 4) % (int)((*(char **)((char *)m_cachedTable + 8) - *(char **)((char *)m_cachedTable + 4)) >> 2);
			node = 0;
			while (++i < (unsigned)((*(char **)((char *)m_cachedTable + 8) - *(char **)((char *)m_cachedTable + 4)) >> 2) && (node = *(void **)(*(char **)((char *)m_cachedTable + 4) + i * 4)) == 0)
				;
		}
		m_cachedNode = node;
		if (m_tag == 0 || entry->rvaSlot34() == (int)m_tag)
			return AssetReference((CountedAsset *)entry);
		node = m_cachedNode;
		if (!node)
			return AssetReference();
	}
}
