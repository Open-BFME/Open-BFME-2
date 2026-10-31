// ?invalidateCachedLightPositions@Rva00108AD8@@QAEXXZ
// cl: /O1 /arch:SSE /EHsc /DNDEBUG /MD
// ?invalidateCachedLightPositions@Rva00108AD8@@QAEXXZ @0x00108AD8 95B
// Walks the member hash table and zeroes the three trailing floats of every
// entry, via rowed First 0x00613DB0 and Next 0x00613D70.
// The banked body declared HashTableIteratorClass with a `const HashTableClass
// &Table` reference member (the upstream header's spelling) and came out 95B
// with only the vptr constant store and the table store swapped. Retail keeps
// the table in a non-virtual IterBase as a POINTER, which is what the matched
// sibling Rva000F1AD8Clear.cpp already does; with that shape the two stores
// land in retail's order and all 95 bytes match.
class HashTableClass;
class HashableClass
{
public:
	virtual void release();
	virtual const char *Get_Key() = 0;
	HashableClass *NextHash;
};
struct IterBase
{
	const HashTableClass *m_table;
	IterBase(HashTableClass *hashTable) : m_table(hashTable) {}
};
// Current region flags already preserve the native95B loop. As in the
// verified Rva000F1AD8Clear peer, leave iterator support under those flags
// so its deleting destructor is the same kept28B body, not the old30B copy.
class HashTableIteratorClass : public IterBase
{
	int m_index;
	HashableClass *m_cur;
	HashableClass *m_next;
public:
	HashTableIteratorClass(HashTableClass *hashTable) : IterBase(hashTable) {}
	virtual ~HashTableIteratorClass() {}
	void First();
	void Next();
	bool Is_Done() { return m_cur == 0; }
	HashableClass *Get_Current() { return m_cur; }
};
// ?Is_Done@HashTableIteratorClass@@QAE_NXZ present-unmatched
// The loop walks the table through the texture manager's iterator subclass
// (target facts): the inline ctor stores VA 0x00BCF9AC, the one-slot table
// whose deleting dtor 0x00108D17 calls 0x00108650, and that destructor stores
// HashTableIteratorClass's own table 0x00BCEF9C (Rva000F1AD8Clear.cpp gives
// the evidence). Zero Hour and BFME 1 spell it W3DShadowTextureManagerIterator.
class W3DShadowTextureManagerIterator : public HashTableIteratorClass
{
public:
	W3DShadowTextureManagerIterator(HashTableClass *hashTable) : HashTableIteratorClass(hashTable) {}
};
class Base8
{
public:
	virtual ~Base8() {}
	int m_pad;
};
struct Rva00108AD8Entry : public Base8, public HashableClass
{
	const char *Get_Key() { return 0; }
	char m_pad2[0x24];
	float m_x;
	float m_y;
	float m_z;
};
class Rva00108AD8
{
public:
	HashTableClass *m_table;
	void invalidateCachedLightPositions();
};
void Rva00108AD8::invalidateCachedLightPositions()
{
	HashTableClass *hashTable = m_table;
	W3DShadowTextureManagerIterator it(hashTable);
	it.First();
	while (!it.Is_Done())
	{
		Rva00108AD8Entry *entry = static_cast<Rva00108AD8Entry *>(it.Get_Current());
		float *position = &entry->m_x;
		position[0] = 0.0f;
		position[1] = 0.0f;
		position[2] = 0.0f;
		it.Next();
	}
}