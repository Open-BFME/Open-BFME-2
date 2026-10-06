// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003C6464SortHeap@@YAXPAPAURva003BD485Keyed@@0H@Z @0x003C6464 58B.
// Heap sort over the keyed array from Rva003BD485Median.cpp: while more than
// one slot remains, pop the top via the rowed 3-push PopHeap at 0x003C4B80
// then shrink last. Evidence: chain lane on 0x003C4B80, caller 0x003C6A01
// pushes (first, last, extra) with caller cleanup (cdecl), prev/next point
// at the heap TU. Shard, not graft: home TU verifies its rows under /O1 and
// a flag flip would perturb them; /G7 gives retail's byte-form threshold
// mask `and al,0xfc` over /O1's dword `and eax,0xfc` (introsort_loop precedent).
struct Rva003BD485Keyed
{
	char m_pad[0x20];
	int m_key;
};
void Rva003C4B80PopHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int extra);
void Rva003C6464SortHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int extra)
{
	for (; last - first > 1; --last)
		Rva003C4B80PopHeap(first, last, extra);
}
