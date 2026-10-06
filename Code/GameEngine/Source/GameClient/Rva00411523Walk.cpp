// cl: /DNDEBUG /MD /EHsc
// ?rva00411523@Rva00411523@@QAEXXZ, retail 0x00411523 (44B).
// Eva-table walk over global at 0x00E02FE4 via pinned first 0x00427195 and
// rowed next 0x00411084, clearing byte at node+0x2C. Same first/next shape
// as ?messageToName@Eva in EvaMessageName.cpp; owner unproven so
// honest-address thiscall with unused this.

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
};

struct Rva004114EFGlobalTable
{
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

extern Rva004114EFGlobalTable g_Va00E02FE4;

struct Rva00411523Node
{
	char m_pad[0x2C];
	unsigned char m_flag2C;
};

class Rva00411523
{
public:
	void rva00411523();
};

void Rva00411523::rva00411523()
{
	Rva000411084 iter;
	reinterpret_cast<Rva000427195 *>(&g_Va00E02FE4)->first(&iter);
	while (iter.m_current != 0) {
		((Rva00411523Node *)iter.m_current)->m_flag2C = 0;
		iter.next();
	}
}
