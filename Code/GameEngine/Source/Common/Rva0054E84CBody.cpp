// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0054E84C@Rva0054E84C@@QAE_NXZ @0x0054E84C 33B: honest-address list scan.
// Evidence: callers 8x in 0x0054E8DC; no callees; circular list via [ecx] next and [ecx+8] string byte; returns OR over nodes.

struct ScanNode
{
	ScanNode *m_next;
	char m_pad[4];
	unsigned char *m_text;
};

class Rva0054E84C
{
public:
	bool rva0054E84C();

private:
	ScanNode *m_sentinel;
};

bool Rva0054E84C::rva0054E84C()
{
	ScanNode *end = m_sentinel;
	ScanNode *cur = end->m_next;
	bool found = false;
	while (cur != end)
	{
		found = found || (*cur->m_text != 0);
		cur = cur->m_next;
	}
	return found;
}
