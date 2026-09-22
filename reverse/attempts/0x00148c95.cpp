// ?keyToName@NameKeyGenerator@@QAEABVAsciiString@@W4NameKeyType@@@Z
// partial score=0.89 date=2026-09-22
// cl: /O1 /DNDEBUG /MD /GX- /Oi-
// stlport
// PROBE V2 (build/ scratch, never committed): keyToName 107B, no-end null-test.

class AsciiString
{
public:
	char* m_text;
	static AsciiString TheEmptyString;
};

class CriticalSection
{
public:
	virtual ~CriticalSection();
	void* m_handle;
	char m_win[24];
	bool m_disabled;
};

#pragma optimize("s", off)
class ScopedCriticalSection
{
	CriticalSection* m_cs;
	bool m_locked;
	__declspec(noinline) void Lock();
	__declspec(noinline) void Unlock();
public:
	__forceinline ScopedCriticalSection(CriticalSection* cs) : m_cs(cs), m_locked(false) { Lock(); }
	__forceinline ~ScopedCriticalSection() { if (m_locked) Unlock(); }
};
#pragma optimize("s", on)

struct Bucket
{
	void* m_vtable;
	Bucket* m_nextInSocket;
	int m_key;
	AsciiString m_nameString;
};

struct MapNode
{
	void* m_next;
	int m_key;
	Bucket* m_bucket;
};

typedef int NameKeyType;

class KeyToBucketMap
{
public:
	MapNode* find(const NameKeyType& key) const;
private:
	unsigned m_storage[5];
};

class NameKeyGenerator
{
public:
	const AsciiString& keyToName(NameKeyType key);
	char m_pad[0x2BF4C];
	KeyToBucketMap m_map;
	CriticalSection m_mutex;
	KeyToBucketMap& keyToBucketMap() { return m_map; }
};

const AsciiString& NameKeyGenerator::keyToName(NameKeyType key)
{
	ScopedCriticalSection lock(&m_mutex);
	KeyToBucketMap* map = &keyToBucketMap();
	MapNode* node = map->find(key);
	if (!node)
		return AsciiString::TheEmptyString;
	return node->m_bucket->m_nameString;
}
