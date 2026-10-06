// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030B831Equal@@YAHPBURva0030B831Item@@0@Z @0x0030B831 41B
// Range-plus-int equality via rowed 0x0030B6A6 then field 0x28.
// Evidence: calls rowed Rva0030B6A6Equal; cmp [+0x28]; caller none; unblocks none.
// Precedent Rva0030B6A6Equal 61B same shape with xor/inc.
struct Rva0030B6A6Range
{
	const float *begin;
	const float *end;
};
struct Rva0030B831Item
{
	Rva0030B6A6Range range;
	char m_pad[0x28 - 8];
	int m_28;
};
int __cdecl Rva0030B6A6Equal(const Rva0030B6A6Range *a, const Rva0030B6A6Range *b);
int __cdecl Rva0030B831Equal(const Rva0030B831Item *a, const Rva0030B831Item *b)
{
	if ((unsigned char)Rva0030B6A6Equal(&a->range, &b->range) && a->m_28 == b->m_28)
		return 1;
	return 0;
}
