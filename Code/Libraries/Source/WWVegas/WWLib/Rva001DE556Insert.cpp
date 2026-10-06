// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001DE556@Rva001DE556@@QAEPAUInsertResult@@PAU2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x001DE556 124B hash insert buckets plus count via rowed bucketIndex 0x00223149 plus rowed compare 0x000069D6 plus pinned thiscall alloc 0x001DD8C9.
// Evidence: chain lane every callee rowed; caller 0x001DE84F resize-then-insert; same pair layout as alloc TU.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

template <typename T> class StringBase
{
public:
	int compare(const StringBase &other) const;
private:
	char *m_text;
};

class AsciiString : public StringBase<char>
{
};

struct NoCaseTreeValue4
{
	char m_body[4];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct HashNode
{
	HashNode *m_next;
	AsciiString m_key;
	NoCaseTreeValue4 m_value;
};

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
};

struct InsertResult
{
	HashNode *m_node;
	void *m_table;
	unsigned char m_inserted;
};

class Rva001DE556
{
public:
	InsertResult *rva001DE556(InsertResult *out, const NocasePair &obj);
	void *rva001DD8C9(const NocasePair &src);
private:
	void *m_00;
	HashNode **m_buckets04;
	void *m_08;
	void *m_0C;
	int m_size10;
};

InsertResult *Rva001DE556::rva001DE556(InsertResult *out, const NocasePair &obj)
{
	int bucket = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)&obj);
	HashNode *head = m_buckets04[bucket];
	HashNode *cur = head;
	while (cur != 0)
	{
		if (((const AsciiString *)&cur->m_key)->compare((const StringBase<char> &)obj.first) == 0)
		{
			out->m_node = cur;
			out->m_table = this;
			out->m_inserted = 0;
			return out;
		}
		cur = cur->m_next;
	}
	HashNode *fresh = (HashNode *)rva001DD8C9(obj);
	fresh->m_next = head;
	m_buckets04[bucket] = fresh;
	++m_size10;
	out->m_node = fresh;
	out->m_table = this;
	out->m_inserted = 1;
	return out;
}
