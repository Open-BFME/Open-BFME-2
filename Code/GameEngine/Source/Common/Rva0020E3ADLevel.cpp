// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0020E3AD@Rva0020E3AD@@QAEHH@Z, retail 0x0020E3AD, 41 bytes.
// Three-threshold level via pointer at +0x08 with ints at +0x10/+0x14/+0x18
// returning 0/1/2/3. Caller jmp at 0x002B2B61.
struct Rva0020E3ADThresholds
{
	char m_pad[0x10];
	int m_t0;
	int m_t1;
	int m_t2;
};

class Rva0020E3AD
{
public:
	int rva0020E3AD(int v);

private:
	char m_pad[8];
	Rva0020E3ADThresholds *m_ptr;
};

int Rva0020E3AD::rva0020E3AD(int v)
{
	Rva0020E3ADThresholds *t = m_ptr;
	if (v <= t->m_t0)
		return 0;
	if (v <= t->m_t1)
		return 1;
	return 2 + (v > t->m_t2);
}
