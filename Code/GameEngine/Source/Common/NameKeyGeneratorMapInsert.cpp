// cl: /DNDEBUG /MD
//
// NameKeyGenerator::KeyToBucketMap::insert, retail 0x004DA240, 36 bytes,
// NameKeyGenerator::KeyToBucketMap::do_insert, retail 0x0005574B, 112 bytes,
// and NameKeyGenerator::KeyToBucketMap::insertNode, retail 0x0053F3B1,
// 73 bytes. Dedicated TU so NameKeyGenerator.cpp cannot see these bodies.
// insert does resize then the hashtable insert; do_insert is the
// insert_unique_noresize half: bucket walk with early found-return, else
// allocate/link/count and an added-return. insertNode is the blind half
// used by lookup-map find-slots (ObjectLookupMap::findSlot 0x0041F4E5):
// resize, no walk, link, and the key slot back so the caller fills it.
// Count lives at +0x10.
//
// The class is STLport's hashtable shape (functors at +0 padding to four,
// the bucket vector's three pointers at +4/+8/+0x0C, count at +0x10), and the
// body is phrased through the same separate inline accessors STLport uses:
// tableSize() for the bucket count and tableAt(n) for indexing. That is what
// keeps retail's allocation: the start pointer reloads after the divide
// instead of staying live, the key stays in ecx across the divide and the
// chain walk, and this stays in esi. A flat member-access phrasing merges the
// start pointer into ecx and spills the key to a per-iteration reload.

struct NameKeyBucket
{
	NameKeyBucket *next;
	int key;
	void *value;
};

struct NameKeyBucketTable
{
	NameKeyBucket **start;
	NameKeyBucket **finish;
	NameKeyBucket **storageEnd;

	unsigned size() const { return (unsigned)(finish - start); }
	NameKeyBucket *&at(unsigned n) { return *(start + n); }
};

struct NameKeyHashInt
{
	unsigned operator()(int x) const { return (unsigned)x; }
};

struct BucketAlloc
{
	static void *allocate(unsigned int n, const void *hint);
};

namespace _STL
{

template <class Element>
void _Construct(Element *slot, const Element &source);

}

struct NameKeyEqualInt
{
	bool operator()(int a, int b) const { return a == b; }
};

class NameKeyGenerator
{
public:
	class KeyToBucketMap
	{
	public:
		struct value_type
		{
			int first;
			void *second;
		};

		typedef NameKeyBucket Bucket;

		struct insert_result
		{
			Bucket *first;
			KeyToBucketMap *second;
			bool inserted;

			insert_result(Bucket *f, KeyToBucketMap *s, bool i)
				: first(f), second(s), inserted(i)
			{
			}
		};

		struct equal_result
		{
			Bucket *first;
			KeyToBucketMap *second;

			equal_result(Bucket *f, KeyToBucketMap *s)
				: first(f), second(s)
			{
			}
		};

		insert_result insert(const value_type &value);
		equal_result rva0005559F(const value_type &value);
		equal_result rva00057C5C(const value_type &value);

	private:
		NameKeyHashInt m_hash;
		NameKeyEqualInt m_equals;
		char pad2[2];
		NameKeyBucketTable m_table;
		unsigned m_count;
		void resize(unsigned);
		void *allocateNode(const value_type &value);
		insert_result do_insert(const value_type &value);
		int *insertNode(const value_type &value);

		static int lookupKey(const value_type &v) { return v.first; }
		unsigned tableSize() const { return m_table.size(); }
		Bucket *&tableAt(unsigned n) { return m_table.at(n); }
		unsigned bkt_num_key(int key) const { return m_hash(key) % tableSize(); }
		unsigned bkt_num(const value_type &obj) const { return bkt_num_key(lookupKey(obj)); }
		bool keysEqual(int a, int b) const { return m_equals(a, b); }
	};
};

NameKeyGenerator::KeyToBucketMap::insert_result
NameKeyGenerator::KeyToBucketMap::insert(const value_type &value)
{
	resize(m_count + 1);
	return do_insert(value);
}

NameKeyGenerator::KeyToBucketMap::insert_result
NameKeyGenerator::KeyToBucketMap::do_insert(const value_type &value)
{
	const unsigned n = bkt_num(value);
	Bucket *first = (Bucket *)tableAt(n);

	for (Bucket *cur = first; cur != 0; cur = cur->next)
	{
		if (keysEqual(cur->key, lookupKey(value)))
		{
			return insert_result(cur, this, false);
		}
	}

	Bucket *tmp = (Bucket *)allocateNode(value);
	tmp->next = first;
	tableAt(n) = tmp;
	++m_count;

	return insert_result(tmp, this, true);
}

void *NameKeyGenerator::KeyToBucketMap::allocateNode(const value_type &value)
{
	Bucket *node = (Bucket *)BucketAlloc::allocate(sizeof(Bucket), 0);
	node->next = 0;
	_STL::_Construct((value_type *)&node->key, value);
	return node;
}

int *NameKeyGenerator::KeyToBucketMap::insertNode(const value_type &value)
{
	resize(m_count + 1);
	const unsigned n = (unsigned)lookupKey(value) % tableSize();
	Bucket *oldHead = tableAt(n);
	Bucket *node = (Bucket *)allocateNode(value);
	node->next = oldHead;
	tableAt(n) = node;
	++m_count;
	return &node->key;
}

// KeyToBucketMap::rva0005559F, retail 0x0005559F, 115 bytes: the
// insert_equal_noresize half beside do_insert: bucket walk with splice-after
// on a key hit, else head-link; ++count and a {node, this} result either way.
// Evidence: two calls to rowed KeyToBucketMap::allocateNode 0x003ED191, same
// bucket/table/counter layout as do_insert, sits just before it. Caller
// 0x00057C5C does resize-then-this like insert.
NameKeyGenerator::KeyToBucketMap::equal_result
NameKeyGenerator::KeyToBucketMap::rva0005559F(const value_type &value)
{
	const unsigned n = bkt_num(value);
	Bucket *first = (Bucket *)tableAt(n);

	for (Bucket *cur = first; cur != 0; cur = cur->next)
	{
		if (keysEqual(cur->key, lookupKey(value)))
		{
			Bucket *tmp = (Bucket *)allocateNode(value);
			tmp->next = cur->next;
			cur->next = tmp;
			++m_count;
			return equal_result(tmp, this);
		}
	}

	Bucket *tmp = (Bucket *)allocateNode(value);
	tmp->next = first;
	tableAt(n) = tmp;
	++m_count;

	return equal_result(tmp, this);
}

// ?rva00057C5C@KeyToBucketMap@NameKeyGenerator@@QAE?AUequal_result@12@ABUvalue_type@12@@Z @0x00057C5C 36B.
// Chain from 0x0005559F: resize-then-insert_equal like insert does resize-then-do_insert.
// Evidence: calls rowed hashtable resize 0x0053F1EC and rowed rva0005559F 0x0005559F,
// count at +0x10, callers at 0x00058A75 0x0005949A 0x000594FB.
NameKeyGenerator::KeyToBucketMap::equal_result
NameKeyGenerator::KeyToBucketMap::rva00057C5C(const value_type &value)
{
	resize(m_count + 1);
	return rva0005559F(value);
}
