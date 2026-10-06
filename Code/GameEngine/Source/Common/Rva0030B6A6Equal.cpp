// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030B6A6Equal@@YAHPBURva0030B6A6Range@@0@Z @0x0030B6A6 61B
// Two-range float-pair equality via size xor then rowed 0x0030B395.
// Evidence: size sub xor test F8; calls rowed Rva0030B395Equal; caller 0x0030B83D tests al; unblocks 0x0030B831.
// Precedent Rva0030B395Equal 60B same file pattern.
struct Rva0030B6A6Range
{
	const float *begin;
	const float *end;
};
bool __cdecl Rva0030B395Equal(const float *first1, const float *last1, const float *first2);
int __cdecl Rva0030B6A6Equal(const Rva0030B6A6Range *a, const Rva0030B6A6Range *b)
{
	int size1 = (const char *)a->end - (const char *)a->begin;
	int size2 = (const char *)b->end - (const char *)b->begin;
	if ((((size1 ^ size2) & ~7) == 0) && Rva0030B395Equal(a->begin, a->end, b->begin))
		return 1;
	return 0;
}
