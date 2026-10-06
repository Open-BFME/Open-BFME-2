// cl: /DNDEBUG /MD

// ?rva0042FD55@Rva0042FD55@@QAEPAUUIntBoolPair0042FD55@@PBX@Z @0x0042FD55 73B: blind hashtable insert (resize then link) returning key slot. Evidence: calls rowed hashtable resize 0x0053F1EC (folded) plus rowed new-node 0x0042FCAC plus caller 0x0042FE6C; same shape as rowed KeyToBucketMap::insertNode 0x0053F3B1 73B.
struct UIntBoolPair0042FD55
{
	unsigned int first;
	bool second;
	char m_pad05[3];
};

struct UIntBoolBucket0042FD55
{
	UIntBoolBucket0042FD55 *next;
	UIntBoolPair0042FD55 pair;
};

struct UIntBoolBucketTable0042FD55
{
	UIntBoolBucket0042FD55 **start;
	UIntBoolBucket0042FD55 **finish;
	UIntBoolBucket0042FD55 **storageEnd;

	unsigned size() const { return (unsigned)(finish - start); }
	UIntBoolBucket0042FD55 *&at(unsigned n) { return *(start + n); }
};

class Rva0042FCAC
{
public:
	void *rva0042FCAC(const void *obj);
};

class NameKeyGenerator
{
public:
	class KeyToBucketMap
	{
		friend class Rva0042FD55;
		void resize(unsigned n);
	};
};

class Rva0042FD55
{
public:
	unsigned int *rva0042FD55(const void *value);

private:
	char m_pad00[4];
	UIntBoolBucketTable0042FD55 m_table;
	unsigned m_count;
	static unsigned lookupKey(const UIntBoolPair0042FD55 &v) { return v.first; }
	unsigned tableSize() const { return m_table.size(); }
	UIntBoolBucket0042FD55 *&tableAt(unsigned n) { return m_table.at(n); }
};

unsigned int *Rva0042FD55::rva0042FD55(const void *value)
{
	((NameKeyGenerator::KeyToBucketMap *)this)->resize(m_count + 1);
	const unsigned n = lookupKey(*(const UIntBoolPair0042FD55 *)value) % tableSize();
	UIntBoolBucket0042FD55 *oldHead = tableAt(n);
	UIntBoolBucket0042FD55 *node = (UIntBoolBucket0042FD55 *)((Rva0042FCAC *)this)->rva0042FCAC(value);
	node->next = oldHead;
	tableAt(n) = node;
	++m_count;
	return &node->pair.first;
}
