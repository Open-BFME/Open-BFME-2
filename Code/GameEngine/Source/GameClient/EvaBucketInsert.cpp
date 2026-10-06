// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003F78A9@Rva000427195@@QAEPAV<out>@@PAXPBVAsciiString@@@Z @0x003F78A9 124B
// Hash-table find-or-insert for the Eva bucket map. Evidence: calls rowed
// bucketIndex 0x00223149, rowed StringBase compare 0x000069D6 and the just
// landed new-node 0x003F7737; bucket table {unused+0 begin+4 end+8 size+10h}
// read off EvaBucketIndex/Advance siblings; landing this unblocks 0x003F797C.
#include "ascii_string.h"

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	void *rva003F78A9(void *out, const AsciiString *key);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	int m_pad0C;
	int m_size;
};

struct EvaBucketNode
{
	EvaBucketNode *m_next;
	AsciiString m_name;
	int m_val0;
	int m_val1;
};

struct EvaBucketOut
{
	void *m_node;
	void *m_owner;
	unsigned char m_inserted;
};

class Rva003F7737
{
public:
	void *rva003F7737(const void *obj);
};

void *Rva000427195::rva003F78A9(void *out, const AsciiString *key)
{
	EvaBucketOut *result = (EvaBucketOut *)out;
	int index = bucketIndex(key);
	EvaBucketNode *head = (EvaBucketNode *)m_beginBuckets[index];
	EvaBucketNode *cur = head;
	if (cur != 0)
	{
		do
		{
			const StringBase<char> &a = (const StringBase<char> &)cur->m_name;
			const StringBase<char> &b = *(const StringBase<char> *)key;
			if (a.compare(b) == 0)
			{
				result->m_node = cur;
				result->m_owner = this;
				result->m_inserted = 0;
				return result;
			}
			cur = cur->m_next;
		} while (cur != 0);
	}
	EvaBucketNode *fresh = (EvaBucketNode *)((Rva003F7737 *)this)->rva003F7737((const void *)key);
	fresh->m_next = head;
	m_beginBuckets[index] = fresh;
	++m_size;
	result->m_node = fresh;
	result->m_owner = this;
	result->m_inserted = 1;
	return result;
}
