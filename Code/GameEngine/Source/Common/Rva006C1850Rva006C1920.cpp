//
// ?rva006C1920@Rva006C1850@@QAE_NI@Z, retail 0x006c1920, 204 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// The hash lookup 0x006C1850 is owned by Rva006C3AB0DebugSetter.cpp,
// whose caller needs its definition visible for retail slot-reload ordering.
#include "../../Include/Common/Rva006C1850Node.h"
#include <string.h>
class Rva006C1850
{
public:
	bool rva006C1850(unsigned int key, void **out);
	bool rva006C18A0(unsigned int key, bool freeValue);
	bool rva006C1920(unsigned int newSize);
	// Inline presence test: retail 0x006C1D60 inlines the 0x006C1850 walk
	// without the out parameter.
	__forceinline bool containsKey(unsigned int key)
	{
		Rva006C1850Node *node = 0;
		if (m_table != 0)
		{
			int h = (key >> 3) % m_bucketCount;
			node = m_table[h];
			while (node != 0 && node->m_key != key)
				node = node->m_next;
		}
		if (node != 0)
			return true;
		return false;
	}
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

// Retail 0x006C1D60 93B (WB 0x70CEC0): the owner's guarded unlock lane. When the
// table at +0x684 is enabled (+0x680) the key is looked up (find inlined; WB names
// the result bReturnValue) and removed through 0x006C18A0; the lookup result is
// the return value. The found path knows the result is true, which is where
// retail's `mov bl,1` before the call and `mov al,bl` after it come from.
class Rva006C1D60
{
public:
	bool rva006C1D60(unsigned int key, bool freeValue);
private:
	unsigned char m_pad[0x680];
	bool m_enabled;
	unsigned char m_pad681[3];
	Rva006C1850 m_table;
};

bool Rva006C1D60::rva006C1D60(unsigned int key, bool freeValue)
{
	bool ret;
	if (m_enabled)
	{
		ret = m_table.containsKey(key);
		if (ret)
			m_table.rva006C18A0(key, freeValue);
	}
	else
		ret = false;
	return ret;
}
