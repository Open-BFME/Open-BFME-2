// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040CFC7@Rva0040CFC7@@QAEXPAVRva0040CFC7Pred@@@Z, retail 0x0040CFC7, 56 bytes.
// Vector-count loop over 8-byte entries at +0x40/+0x44 calling pred slot0.
// Evidence: sar 3 count, [eax+ebx*8+4] entry field, call [edx] virtual slot 0,
// callers 0x00220E30 0x005FEF11, early-out on false predicate.
class Rva0040CFC7Pred
{
public:
	virtual bool check(int v);
};

struct Rva0040CFC7Entry
{
	int m_00;
	int m_04;
};

class Rva0040CFC7
{
	int m_pad[0x40 / 4];
	Rva0040CFC7Entry *m_40;
	Rva0040CFC7Entry *m_44;
public:
	void rva0040CFC7(Rva0040CFC7Pred *p);
};

void Rva0040CFC7::rva0040CFC7(Rva0040CFC7Pred *p)
{
	int n = m_44 - m_40;
	for (int i = 0; i < n; ++i) {
		int v = m_40[i].m_04;
		if (!p->check(v))
			break;
	}
}
