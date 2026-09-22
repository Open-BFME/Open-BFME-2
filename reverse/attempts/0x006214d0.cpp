// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
// partial score=0.85 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ, retail 0x006214D0, 224 bytes.
// Filtered current-asset iterator: lock at +0x34, current entry at +0x60,
// buckets at +0x64, context filter at +0x1F0. Entries carry next at +0,
// key at +4 and object at +8; buckets hold begin at +4 and end at +8.
// Returns the old object while advancing current to the next entry whose
// type (virtual slot 13) matches the context, or null when exhausted.
// Shape follows Find_Asset (lock + AssetReference with raw-ptr ctor).
// Work in progress.

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

class CountedAsset
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual int Get_Type();
	void Release_Ref();

private:
	int m_refcount;
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
	~AssetReference()
	{
		if ( m_object )
		{
			m_object->Release_Ref();
		}
	}

private:
	CountedAsset *m_object;
};

struct AssetEntry
{
	AssetEntry *m_next;
	int m_key;
	CountedAsset *m_object;
};

struct AssetBuckets
{
	int m_pad0;
	AssetEntry **m_begin;
	AssetEntry **m_end;
};

class AssetRegistry
{
public:
	AssetReference Get_Current_Asset();

private:
	unsigned char m_unmodelled_000[0x34];
	CRITICAL_SECTION m_lock;
	unsigned char m_unmodelled_050[0x10];
	AssetEntry *volatile m_current;
	AssetBuckets *m_buckets;
	unsigned char m_unmodelled_068[0x188];
	int m_context;
};

AssetReference AssetRegistry::Get_Current_Asset()
{
	CriticalSectionLock lock((int)&m_lock);
	if (m_current != 0) {
	for (;;) {
		CountedAsset *object = m_current->m_object;
		AssetEntry *next = m_current->m_next;
		if (next != 0) {
			m_current = next;
		}
		else {
			AssetEntry **begin = m_buckets->m_begin;
			AssetEntry **end = m_buckets->m_end;
			unsigned count = (unsigned)(end - begin);
			unsigned start = (unsigned)m_current->m_key % count;
			unsigned i = start + 1;
			AssetEntry *found = 0;
			while (i < count) {
				if (begin[i] != 0) {
					found = begin[i];
					break;
				}
				++i;
			}
			m_current = found;
		}
		if (m_context == 0)
			return AssetReference(object);
		if (object->Get_Type() == m_context)
			return AssetReference(object);
		if (m_current == 0)
			return AssetReference();
	}
	}
	return AssetReference();
}
