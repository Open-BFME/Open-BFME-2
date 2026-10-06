// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva003F751A@Rva003F751A@@QAEPAURva003F751ANode@@PBH@Z 0x003F751A 37B
// Evidence: unlock lane; tree traversal header->root with key compare at +0x10 vs *key, children at +8/+C, returns header/end or last <=key; callers 0x3F75DC 0x3F7A9B 0x503180; prev Rva003F74F5Fill /O1.
struct Rva003F751ANode
{
	int m_c0;
	Rva003F751ANode *m_parent;
	Rva003F751ANode *m_left;
	Rva003F751ANode *m_right;
	int m_key;
};

struct Rva003F751AHeader
{
	int m_c0;
	Rva003F751ANode *m_root;
	Rva003F751ANode *m_leftmost;
	Rva003F751ANode *m_rightmost;
};

class Rva003F751A
{
public:
	Rva003F751ANode *rva003F751A(const int *key);
private:
	Rva003F751AHeader *m_header;
};

Rva003F751ANode *Rva003F751A::rva003F751A(const int *key)
{
	Rva003F751AHeader *h = m_header;
	Rva003F751ANode *res = (Rva003F751ANode *)h;
	Rva003F751ANode *cur = h->m_root;
	if (cur == 0)
		return res;
	int k = *key;
	do
	{
		if (cur->m_key <= k)
		{
			res = cur;
			cur = cur->m_left;
		}
		else
			cur = cur->m_right;
	} while (cur != 0);
	return res;
}
