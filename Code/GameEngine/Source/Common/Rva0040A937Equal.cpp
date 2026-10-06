// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0040A937Equal@@YA_NPBVRva0040A7D5@@0@Z @0x0040A937 99B
// Evidence: chain lane; equal-size non-empty element-wise compare via 0x0040A7D5 row; callers at 0x0040ABBF 0x0040ABD4 0x0040ABE5 0x0040ABF6.
class Rva0040A7D5
{
public:
	int rva0040A7D5(int index) const;
	friend bool Rva0040A937Equal(const Rva0040A7D5 *, const Rva0040A7D5 *);
private:
	const int *m_begin;
	const int *m_end;
};

bool Rva0040A937Equal(const Rva0040A7D5 *a, const Rva0040A7D5 *b)
{
	unsigned int na = (unsigned int)(a->m_end - a->m_begin);
	unsigned int nb = (unsigned int)(b->m_end - b->m_begin);
	if (na != nb)
		return false;
	if (na == 0)
		return false;
	for (unsigned int i = 0; i < na; ++i) {
		if (a->rva0040A7D5((int)i) != b->rva0040A7D5((int)i))
			return false;
	}
	return true;
}
