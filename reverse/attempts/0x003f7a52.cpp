// ?rva003F7A52@Rva003F7A52@@QAEXPAM00@Z
// partial score=0.9671 date=2026-10-06
// ?rva003F7A52@Rva003F7A52@@QAEXPAM00@Z
// partial score=0.94 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva003F7A52@Rva003F7A52@@QAEXPAM00@Z, retail 0x003F7A52 (188B).
// Evidence: chain lane; callees begin 0x427195 first-pin alias, rva003F751A 0x3F751A, next 0x411084; float init g_Va00BBB8D8; hashtable at +8 floats at +0x20.

extern float g_Va00BBB8D8;

class Rva000411084
{
public:
	void *next();
	void *m_current;
	void *m_owner;
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iter);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
};

struct Rva003F751ANode
{
	int m_00;
	void *m_04;
	void *m_08;
	void *m_0C;
	int m_10;
	float m_14;
	float m_18;
	float m_1C;
};

class Rva003F751A
{
public:
	Rva003F751ANode *rva003F751A(const int *key);
private:
	void *m_header;
};

struct Rva003F7A52HtNode
{
	void *m_next;
	int m_04;
	Rva003F751A *m_tree;
	int m_key;
};

class Rva003F7A52
{
public:
	void rva003F7A52(float *a, float *b, float *c);
private:
	char m_00[8];
	Rva000427195 m_table;
	char m_14[12];
	float m_20;
	float m_24;
	float m_28;
};

// ?rva003F7A52@Rva003F7A52@@QAEXPAM00@Z present-unmatched
void Rva003F7A52::rva003F7A52(float *a, float *b, float *c)
{
	float init = g_Va00BBB8D8;
	*a = init;
	*b = init;
	*c = init;
	Rva000411084 iter;
	m_table.first(&iter);
	while (iter.m_current != 0)
	{
		Rva003F7A52HtNode *node = (Rva003F7A52HtNode *)iter.m_current;
		int key = node->m_key;
		Rva003F751A *tree = node->m_tree;
		Rva003F751ANode *found = tree->rva003F751A(&key);
		if (found != *(Rva003F751ANode **)tree)
		{
			*a *= found->m_14;
			*b *= found->m_18;
			*c *= found->m_1C;
		}
		iter.next();
	}
	*a *= m_20;
	*b *= m_24;
	*c *= m_28;
}
