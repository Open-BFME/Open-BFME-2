// ?cleanup@NestedAt0C@@QAEXXZ
// partial score=0.9071853910281859 date=2026-10-10
// ?cleanup@NestedAt0C@@QAEXXZ
// partial score=0.9 date=2026-10-10
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?cleanup@NestedAt0C@@QAEXXZ @0x003B70CA 116B and ?cleanup@NestedAt2C@@QAEXXZ
// @0x003B71E8 116B: the two same-shaped record-list cleanups nested in
// Gen0035B3A0 (rowed Gen0035B3A0Cleanup.cpp, which calls them at +0x0C / +0x2C
// by these pinned names). Each walks the chain of 0x14-byte records from the
// head index at +0x1C (record array at +0x0C, next index in the record's first
// word): a released record (+0x0C) goes back through the rowed release method
// (0x003B7096 / 0x003B71B4 on the Rva003B573E family), otherwise every node
// after the first on its list (+0x10) is destroyed and freed and the record's
// reference count (+0x0E) is reset to 1. The node types are the rowed
// destructors 0x003B448C / 0x003B3F5E. Evidence: retail bodies and callees
// read at the REL32s; record layout as rowed by ScriptListSubrecordRemove.cpp.
// Method roles are address-derived.

class Rva003B448C
{
public:
	~Rva003B448C();
	Rva003B448C *m_next;
};

class BfmeNodeZ
{
public:
	~BfmeNodeZ();
	BfmeNodeZ *m_next;
};

struct Rva003B7096Record
{
	int m_previous;
	int m_next;
	int m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva003B573E
{
public:
	void rva003B7096(int index);
	void rva003B71B4(int index);

protected:
	void *m_sorted[3];
	Rva003B7096Record *m_records;
	char m_pad10[0x1C - 0x10];
	int m_head;
};

class NestedAt0C : public Rva003B573E
{
public:
	void cleanup(void);
};

class NestedAt2C : public Rva003B573E
{
public:
	void cleanup(void);
};

void NestedAt0C::cleanup(void)
{
	int index = m_head;
	while (index != -1)
	{
		Rva003B7096Record *rec = &m_records[index];
		int next = rec->m_previous;
		if (rec->m_released)
		{
			rva003B7096(index);
		}
		else
		{
			Rva003B448C *first = (Rva003B448C *)rec->m_nodes;
			while (first->m_next)
			{
				Rva003B448C *node = first->m_next;
				Rva003B448C *after = (node?node:node)->m_next;
				delete node;
				first->m_next = after;
			}
			rec->m_references = 1;
		}
		index = next;
	}
}

void NestedAt2C::cleanup(void)
{
	int index = m_head;
	while (index != -1)
	{
		Rva003B7096Record *rec = &m_records[index];
		int next = rec->m_previous;
		if (rec->m_released)
		{
			rva003B71B4(index);
		}
		else
		{
			BfmeNodeZ *first = (BfmeNodeZ *)rec->m_nodes;
			while (first->m_next)
			{
				BfmeNodeZ *node = first->m_next;
				BfmeNodeZ *after = node->m_next;
				delete node;
				first->m_next = after;
			}
			rec->m_references = 1;
		}
		index = next;
	}
}
