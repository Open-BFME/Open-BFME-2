// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport

// ?rva004E1F97@Rva004E1F97@@QAEXPAURva004E1F97Node@@@Z, RVA 0x004E1F97, 53B.
// Unlock lane: tree erase recurse-right via [esi+0x0C] walk-left via
// [esi+0x08] clearing StringBase at node+0x10 via rowed clear 0x0048BA39
// then freeing via rowed _free 0x00030830 ret 4. Prev TreeHint family so
// same flags. Caller at 0x004E220C plus self recursion. Owner unknown so
// honest address-derived names.
template <typename T>
class StringBase
{
public:
	void clear();
private:
	void *m_data;
};
extern "C" void __cdecl free(void *p);
struct Rva004E1F97Node
{
	char m_pad00[8];
	Rva004E1F97Node *m08;
	Rva004E1F97Node *m0c;
	StringBase<char> m10;
	int m14;
};
struct Rva004E1F97
{
	void rva004E1F97(Rva004E1F97Node *node);
};

void Rva004E1F97::rva004E1F97(Rva004E1F97Node *node)
{
	if (node == 0)
		return;
	do {
		rva004E1F97(node->m0c);
		Rva004E1F97Node *left = node->m08;
		node->m10.clear();
		free(node);
		node = left;
	} while (node != 0);
}

// ?rva004E21FE@Rva004E21FE@@QAEXXZ, RVA 0x004E21FE, 41B. Chain lane: if
// count at this+4 nonzero erase header-parent via rowed 0x004E1F97 then
// reset header left/parent/right to self/0/self and count to 0; /O1 and
// idioms. Callers at 0x004E29A5/0x004E2E9E/0x004E298B. Owner unknown so
// honest address-derived names.
struct Rva004E21FEHeader
{
	int m00;
	Rva004E1F97Node *m04;
	Rva004E1F97Node *m08;
	Rva004E1F97Node *m0c;
};
struct Rva004E21FE : Rva004E1F97
{
	Rva004E21FEHeader *m_header;
	int m_count;
	void rva004E21FE();
};

void Rva004E21FE::rva004E21FE()
{
	if (m_count != 0) {
		rva004E1F97(m_header->m04);
		m_header->m08 = (Rva004E1F97Node *)m_header;
		m_header->m04 = 0;
		m_header->m0c = (Rva004E1F97Node *)m_header;
		m_count = 0;
	}
}
