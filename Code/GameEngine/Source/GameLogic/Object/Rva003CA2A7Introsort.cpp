// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003CA2A7IntrosortLoop@@YAXPAPAURva003BD485Keyed@@0HHH@Z @0x003CA2A7 123B.
// Introsort loop over the same keyed array as Rva003BD485Median.cpp: while
// more than 16 slots remain, if depth is 0 partial-sort (first, last, last)
// via 0x003C75C2 and return, else decrement depth, pick median of (first,
// mid, last-1) via 0x003BD485 (called with extra dummy push like siblings),
// partition via 0x003C3A79, recurse on (cut, last) then loop on (first, cut).
// Chain lane on 0x003BD485/0x003C3A79/0x003C75C2; caller 0x003CA402; cdecl.
struct Rva003BD485Keyed
{
	char m_pad[0x20];
	int m_key;
};

Rva003BD485Keyed **Rva003BD485Median(Rva003BD485Keyed **a, Rva003BD485Keyed **b, Rva003BD485Keyed **c);
Rva003BD485Keyed **Rva003C3A79Partition(Rva003BD485Keyed **first, Rva003BD485Keyed **last, Rva003BD485Keyed *pivot, int);
void Rva003C75C2PartialSort(Rva003BD485Keyed **first, Rva003BD485Keyed **middle, Rva003BD485Keyed **last, int extra);

void Rva003CA2A7IntrosortLoop(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int, int depth, int extra)
{
	typedef Rva003BD485Keyed **(__cdecl *Median4)(Rva003BD485Keyed **, Rva003BD485Keyed **, Rva003BD485Keyed **, int);
	while ((((char *)last - (char *)first) & ~3) > 0x40)
	{
		if (depth == 0)
		{
			Rva003C75C2PartialSort(first, last, last, extra);
			return;
		}
		--depth;
		Rva003BD485Keyed **mid = first + (last - first) / 2;
		Rva003BD485Keyed **pivSlot = ((Median4)Rva003BD485Median)(first, mid, last - 1, extra);
		Rva003BD485Keyed **cut = Rva003C3A79Partition(first, last, *pivSlot, extra);
		Rva003CA2A7IntrosortLoop(cut, last, 0, depth, extra);
		last = cut;
	}
}
