//
// ?rva006C1920@Rva006C1850@@QAE_NI@Z, retail 0x006c1920, 204 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// ?rva006C1850@Rva006C1850@@QAE_NIPAPAX@Z, retail 0x006C1850, 70 bytes.
// Hash-chain find: bucket = (key>>3) % bucketCount, walk next at +8,
// compare key at +0, on hit store node+4 to *out when out non-null.
// Evidence: unlock lane calls from 0x006C259D 0x006C268C 0x006C3B6D
// 0x006C4969; div plus shr 3 plus edx*4 table load; ret 8 two args.
struct Rva006C1850Node
{
	unsigned int m_key;
	void *m_value;
	Rva006C1850Node *m_next;
};
extern "C" void *__cdecl memset(void *dst, int c, unsigned int n);
class Rva006C1850
{
public:
	bool rva006C1850(unsigned int key, void **out);
	bool rva006C18A0(unsigned int key, bool freeValue);
	bool rva006C1920(unsigned int newSize);
private:
	Rva006C1850Node **m_table;
	bool m_flag;
	char _pad04[3];
	unsigned int m_bucketCount;
	int m_pad0C;
	int m_count;
	void *(__cdecl *m_allocFn)(unsigned int bytes, void *allocator);
	void (__cdecl *m_freeFn)(void *block, void *allocator);
	void *m_allocator;
};
bool Rva006C1850::rva006C1850(unsigned int key, void **out)
{
	Rva006C1850Node **table = m_table;
	Rva006C1850Node *node = 0;
	if (table) {
		int h = (key >> 3) % m_bucketCount;
		node = table[h];
		while (node && node->m_key != key)
			node = node->m_next;
	if (node) {
		if (out)
			*out = &node->m_value;
		return true;
	}
	}
	return false;
}

// Retail 0x006C18A0 125B: hash-chain remove, same table as find.
// Evidence: same (key>>3)%bucketCount div, next at +8, key at +0,
// value at +4 freed via +0x18 callback with +0x1C allocator when bool
// arg true, node freed always, count at +0x10 decremented.
bool Rva006C1850::rva006C18A0(unsigned int key, bool freeValue)
{
	Rva006C1850Node **table = m_table;
	if (table)
	{
		unsigned int h = (key >> 3) % m_bucketCount;
		Rva006C1850Node *node = table[h];
		Rva006C1850Node *prev = 0;
		while (node)
		{
			if (node->m_key == key)
				break;
			prev = node;
			node = node->m_next;
		}
		if (node)
		{
			if (prev)
				prev->m_next = node->m_next;
			else
				table[h] = node->m_next;
			void *value = node->m_value;
			if (value && freeValue)
				m_freeFn(value, m_allocator);
			m_freeFn(node, m_allocator);
			--m_count;
			return true;
		}
	}
	return false;
}

// rehash via +0x14 alloc +0x18 free. Evidence: flag at +4, alloc bytes
// ebx*4, div shr 3, table edx*4 rehash, caller 0x006C21E3.
bool Rva006C1850::rva006C1920(unsigned int newSize)
{
	bool ok = true;
	if (!m_flag) {
		m_flag = true;
		unsigned int oldCount = m_bucketCount;
		Rva006C1850Node **oldTable = m_table;
		Rva006C1850Node **newTable = (Rva006C1850Node **)m_allocFn(newSize * 4, m_allocator);
		ok = newTable != 0;
		if (newTable) {
			memset(newTable, 0, newSize * 4);
			m_bucketCount = newSize;
			m_table = newTable;
			for (unsigned int i = 0; oldCount > i; ++i) {
				Rva006C1850Node *node = oldTable[i];
				while (node) {
					int h = (node->m_key >> 3) % m_bucketCount;
					Rva006C1850Node *next = node->m_next;
					node->m_next = newTable[h];
					newTable[h] = node;
					node = next;
				}
			}
			if (oldTable)
				m_freeFn(oldTable, m_allocator);
		}
		m_flag = false;
	}
	return ok;
}

// Address-derived shim for 0x006C1A50: a self-or-other dispatch with one
// argument passed through by tail jumps. Both callees are pinned by address.
class Rva00033150
{
public:
	void rva00033150(int v);
};

class Rva000338F0
{
public:
	void rva000338F0(int v);
};

class Rva006C1A50Owner
{
public:
	void rva006C1A50(int v);

private:
	char m_pad00[0x510];
	unsigned char m_510;
	char m_pad511[0x678 - 0x511];
	void *m_678;
};

// ?rva006C1A50@Rva006C1A50Owner@@QAEXH@Z
void Rva006C1A50Owner::rva006C1A50(int v)
{
	if (m_678 == (void *)this) {
		if (m_510)
			((Rva00033150 *)this)->rva00033150(v);
	} else {
		((Rva000338F0 *)m_678)->rva000338F0(v);
	}
}
