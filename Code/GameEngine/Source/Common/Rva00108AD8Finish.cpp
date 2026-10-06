// ?rva00108AD8@Rva00108AD8@@QAEXXZ
// cl: /O1 /arch:SSE /EHsc /DNDEBUG /MD
// ?rva00108AD8@Rva00108AD8@@QAEXXZ @0x00108AD8 95B
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
	IterBase(HashTableClass *t) : m_table(t) {}
};
#pragma optimize("s", off)
class HashTableIteratorClass : public IterBase
{
	int m_index;
	HashableClass *m_cur;
	HashableClass *m_next;
public:
	HashTableIteratorClass(HashTableClass *t) : IterBase(t) {}
	virtual ~HashTableIteratorClass() {}
	void First();
	void Next();
	bool Is_Done();
	HashableClass *Get_Current() { return m_cur; }
};
#pragma optimize("", on)
// ?Is_Done@HashTableIteratorClass@@QAE_NXZ present-unmatched
inline bool HashTableIteratorClass::Is_Done() { return m_cur == 0; }
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
	void rva00108AD8();
};
void Rva00108AD8::rva00108AD8()
{
	HashTableClass *t = m_table;
	HashTableIteratorClass it(t);
	it.First();
	while (!it.Is_Done())
	{
		Rva00108AD8Entry *e = static_cast<Rva00108AD8Entry *>(it.Get_Current());
		float *p = &e->m_x;
		p[0] = 0.0f;
		p[1] = 0.0f;
		p[2] = 0.0f;
		it.Next();
	}
}