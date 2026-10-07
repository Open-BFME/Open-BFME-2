// cl: /DNDEBUG /MD /EHsc
// Target evidence: 0x00213A85 0x00213B88 and 0x00213C30 each obtain an iterator
// through the table view at receiver+0x204 and read a callback receiver at node+8.
// 0x00213BBE and 0x00213C30 share the same caller receiver across a branch.
// Shared class ownership with 0x00213A85/0x00213B88 is inferred from the offset.
// The exact table specialization key type and mapped payload semantics remain unknown.

class Rva000427195;
class Rva000411084
{
public:
	void *m_node;
	Rva000427195 *m_table;
	void *next();
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iterator);
};

class Rva003FAC83
{
public:
	void rva003FACB4();
	void rva003FAD4A(void *value);
	void rva003FADA3();
};

class Rva00211589
{
public:
	void rva002110DF(int value);
};

class Rva00DFE1C8Host
{
};
extern Rva00DFE1C8Host *g_00DFE1C8;

class Rva00213A85
{
public:
	void rva00213A85();
	void rva00213B88(void *value);
	void rva00213C30();

private:
	char m_pad[0x204];
	Rva000427195 m_table;
};

void Rva00213A85::rva00213A85()
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FACB4();
		iterator.next();
	}
}

void Rva00213A85::rva00213B88(void *value)
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FAD4A(value);
		iterator.next();
	}
}

void Rva00213A85::rva00213C30()
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FADA3();
		iterator.next();
	}
	((Rva00211589 *)g_00DFE1C8)->rva002110DF(0);
}
