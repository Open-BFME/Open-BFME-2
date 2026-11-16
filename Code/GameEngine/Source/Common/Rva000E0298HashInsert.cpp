// cl: /O1 /G7 /MD /EHsc
// Native E0298..E0321: find-or-insert on the two-word-key hash table whose find is the rowed
// Rva000E01B0::rva000E01B0 (Rva000E01B0HashFind.cpp). Bucket = (key0 ^ key1) % bucketCount, the
// chain is walked with the rowed pair equality Rva000E007DEqual; a miss allocates a node through
// the rowed NameKeyGenerator::KeyToBucketMap::allocateNode (0x3ED191), links it at the bucket
// head, bumps the element count (+0x14) and returns {node, this, inserted}. The concrete
// container identity is unproven (STLport hashtable::insert_unique is the structural guide).
//
// Schedule note (W7-S2 r14): retail loads the bucket array pointer AFTER the modulus divide and
// sinks the EDI callee-save push to the first write of EDI. A compiler barrier pins the load but
// also pins the push (a store) ahead of the divide; a volatile read of the member into a local
// pointer pins only the load, and the named pointer base also gives retail's [index+base] address
// order. (See wave7/PLAYBOOK.md section 6.)
struct Rva000E007DPair { unsigned a, b; };
int __stdcall Rva000E007DEqual(const Rva000E007DPair *, const Rva000E007DPair *);
#include "../../Include/Common/NameKeyGenerator.h"

class NameKeyGenerator::KeyToBucketMap
{
public:
	struct value_type { int first; void *second; };
	void *storageNode(const Rva000E007DPair &k) { return allocateNode(*(const value_type *)&k); }
private:
	void *allocateNode(const value_type &);
};
struct NativeNode { NativeNode *next; Rva000E007DPair key; };
class NativeHashEqual
{
public:
	bool equal(const Rva000E007DPair *a, const Rva000E007DPair *b)
	{
		union Call
		{
			int (__stdcall *fn)(const Rva000E007DPair *, const Rva000E007DPair *);
			bool (NativeHashEqual::*mem)(const Rva000E007DPair *, const Rva000E007DPair *);
		} c;
		c.fn = &Rva000E007DEqual;
		return (this->*c.mem)(a, b);
	}
};
class Rva000E01B0;
struct NativeInsertResult
{
	NativeNode *node;
	Rva000E01B0 *owner;
	bool inserted;
	NativeInsertResult(NativeNode *nativeNode, Rva000E01B0 *o, bool i) : node(nativeNode), owner(o), inserted(i) {}
};
class Rva000E01B0
{
public:
	NativeInsertResult rva000E0298(const Rva000E007DPair &key);
private:
	char hash;
	NativeHashEqual eq;
	char pad[2];
	NativeNode **begin, **end, **capacity;
	unsigned count;
};

NativeInsertResult Rva000E01B0::rva000E0298(const Rva000E007DPair &key)
{
	unsigned n = end - begin;
	unsigned i = (key.a ^ key.b) % n;
	NativeNode **buckets = *(NativeNode ** volatile *)&begin;
	NativeNode *first = buckets[i];
	for (NativeNode *nativeNode = first; nativeNode; nativeNode = nativeNode->next)
		if (eq.equal(&nativeNode->key, &key))
			return NativeInsertResult(nativeNode, this, false);
	NativeNode *nativeNode = (NativeNode *)((NameKeyGenerator::KeyToBucketMap *)this)->storageNode(key);
	nativeNode->next = first;
	begin[i] = nativeNode;
	++count;
	return NativeInsertResult(nativeNode, this, true);
}
