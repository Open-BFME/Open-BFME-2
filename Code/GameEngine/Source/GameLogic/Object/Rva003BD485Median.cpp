// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD485Median@@YAPAPAURva003BD485Keyed@@PAPAU1@00@Z @0x003BD485 62B.
// Median-of-three pivot picker (retail 0x003BD485, 62 B): each arg is a
// pointer to a keyed element whose sort key sits at +0x20 through a second
// indirection; returns whichever arg carries the median key. Caller at
// 0x003CA2DF passes array slots (quicksort-style mid computation with sar
// halves just above the call). Class layout is honest-address only; the
// identity of the sorted type is unproven. Unlock lane.
struct Rva003BD485Keyed
{
	char m_pad[0x20];
	int m_key;
};

Rva003BD485Keyed **Rva003BD485Median(Rva003BD485Keyed **a, Rva003BD485Keyed **b, Rva003BD485Keyed **c)
{
	int ka = (*a)->m_key;
	int kb = (*b)->m_key;
	if (ka < kb)
	{
		int kc = (*c)->m_key;
		if (kb < kc)
			return b;
		if (ka >= kc)
			return a;
		return c;
	}
	int kc = (*c)->m_key;
	if (ka < kc)
		return a;
	if (kb < kc)
		return c;
	return b;
}

// ?Rva003BD4E8SiftUp@@YAXPAPAURva003BD485Keyed@@HHPAU1@@Z @0x003BD4E8 63B.
// Heap sift-up over the same keyed array: bubbles pivot up from idx while
// the parent key is below the pivot key, stopping at top or a parent key at
// or above it. Sibling of the median picker above (same +0x20 key, same
// quicksort/heap family); caller at 0x003BE5A1. Unlock lane, makes
// 0x003BE553 ready.
void Rva003BD4E8SiftUp(Rva003BD485Keyed **base, int idx, int top, Rva003BD485Keyed *pivot)
{
	int parent = (idx - 1) / 2;
	while (idx > top)
	{
		Rva003BD485Keyed *p = base[parent];
		if (p->m_key >= pivot->m_key)
			break;
		base[idx] = p;
		idx = parent;
		parent = (parent - 1) / 2;
	}
	base[idx] = pivot;
}

// ?Rva003BE553AdjustHeap@@YAXPAPAURva003BD485Keyed@@HHPAU1@H@Z @0x003BE553 90B.
// Heap adjust over the same keyed array: sifts the hole down picking the
// larger child, drops the last slot in when the child runs even with len,
// then tail-calls the 5-push sift-up at 0x003BD4E8. Chain lane on 0x003BD4E8;
// callers 0x003C3AC7/0x003C3AF0 push 5 args (cdecl, ret with caller cleanup).
typedef void (__cdecl *Rva003BD4E8SiftUp5)(Rva003BD485Keyed **, int, int, Rva003BD485Keyed *, int);

void Rva003BE553AdjustHeap(Rva003BD485Keyed **base, int hole, int len, Rva003BD485Keyed *value, int extra)
{
	int top = hole;
	int child = hole * 2 + 2;
	while (child < len)
	{
		if (base[child]->m_key < base[child - 1]->m_key)
			--child;
		base[hole] = base[child];
		hole = child;
		child = child * 2 + 2;
	}
	if (child == len)
	{
		base[hole] = base[child - 1];
		hole = child - 1;
	}
	((Rva003BD4E8SiftUp5)Rva003BD4E8SiftUp)(base, hole, top, value, extra);
}

// ?Rva003C3AF0MakeHeap@@YAXPAPAURva003BD485Keyed@@0H@Z @0x003C3AF0 60B.
// Heap make over the same keyed array: count = last - first; for holes from
// (count - 2) / 2 down to 0 run AdjustHeap with the slot value. Chain lane
// on 0x003BE553; caller 0x003C4B77; cdecl with caller cleanup like siblings.

void Rva003C3AF0MakeHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int extra)
{
	int count = last - first;
	if (count < 2)
		return;
	int hole = (count - 2) / 2;
	while (true)
	{
		Rva003BE553AdjustHeap(first, hole, count, first[hole], extra);
		if (hole == 0)
			break;
		--hole;
	}
}

// ?Rva003C3AC7PopHeap@@YAXPAPAURva003BD485Keyed@@00PAU1@H@Z @0x003C3AC7 41B.
// Heap pop over the same keyed array: moves the top slot to the result, then
// adjusts from hole 0 over last - first with the given value. Chain lane on
// 0x003BE553; callers 0x003C3B41/0x003C69EC; cdecl with caller cleanup.

void Rva003C3AC7PopHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, Rva003BD485Keyed **result, Rva003BD485Keyed *value, int extra)
{
	*result = *first;
	Rva003BE553AdjustHeap(first, 0, last - first, value, extra);
}

// ?Rva003C3B2CPopHeap@@YAXPAPAURva003BD485Keyed@@0HH@Z @0x003C3B2C 30B.
// Heap pop-aux over the same keyed array: shrinks last by one slot then pops
// the top into that slot via the 6-push PopHeap at 0x003C3AC7. Chain lane on
// 0x003C3AC7; caller 0x003C4B8E; cdecl with caller cleanup like siblings.
void Rva003C3B2CPopHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int, int extra)
{
	typedef void (__cdecl *PopHeap6)(Rva003BD485Keyed **, Rva003BD485Keyed **, Rva003BD485Keyed **, Rva003BD485Keyed *, int, int);
	Rva003BD485Keyed **newLast = last - 1;
	((PopHeap6)Rva003C3AC7PopHeap)(first, newLast, newLast, *newLast, extra, 0);
}

// ?Rva003C4B67MakeHeap@@YAXPAPAURva003BD485Keyed@@0H@Z @0x003C4B67 25B.
// Heap make-aux over the same keyed array: forwards (first, last, extra) to
// the 3-arg MakeHeap at 0x003C3AF0 with two trailing zero pushes (5-push
// cdecl adapter like the PopHeap6 sibling above). Chain lane on 0x003C3AF0;
// caller 0x003C69C8; cdecl with caller cleanup.
void Rva003C4B67MakeHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int extra)
{
	typedef void (__cdecl *MakeHeap5)(Rva003BD485Keyed **, Rva003BD485Keyed **, int, int, int);
	((MakeHeap5)Rva003C3AF0MakeHeap)(first, last, extra, 0, 0);
}

// ?Rva003C4B80PopHeap@@YAXPAPAURva003BD485Keyed@@0H@Z @0x003C4B80 23B.
// Heap pop-aux adapter over the same keyed array: forwards (first, last,
// extra) to the 4-arg PopHeap aux at 0x003C3B2C as (first, last, 0, extra).
// Chain lane on 0x003C3B2C; caller 0x003C6483; cdecl with caller cleanup.
void Rva003C4B80PopHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int extra)
{
	Rva003C3B2CPopHeap(first, last, 0, extra);
}

// ?Rva003C3A79Partition@@YAPAPAURva003BD485Keyed@@PAPAU1@0PAU1@H@Z @0x003C3A79 55B.
// Quicksort unguarded partition over the same keyed array: scans first up
// while its key is below the pivot key and last down while the pivot key is
// below its key, swapping on cross and returning the split. Unlock lane;
// caller 0x003CA2EB passes (first, last, *median, extra); cdecl.
Rva003BD485Keyed **Rva003C3A79Partition(Rva003BD485Keyed **first, Rva003BD485Keyed **last, Rva003BD485Keyed *pivot, int)
{
	while (true)
	{
		while ((*first)->m_key < pivot->m_key)
			++first;
		--last;
		while (pivot->m_key < (*last)->m_key)
			--last;
		if (!(first < last))
			return first;
		Rva003BD485Keyed *tmp = *first;
		*first = *last;
		*last = tmp;
		++first;
	}
}

void Rva003C6464SortHeap(Rva003BD485Keyed **first, Rva003BD485Keyed **last, int extra);
// ?Rva003C69B7PartialSort@@YAXPAPAURva003BD485Keyed@@00HH@Z @0x003C69B7 87B.
// Heap partial sort over the same keyed array: make a heap over [first,
// middle), then for each slot in [middle, last) keep the smaller key via
// the 6-push PopHeap at 0x003C3AC7, then sort the heap via 0x003C6464.
// Chain lane on 0x003C4B67/0x003C3AC7/0x003C6464; caller 0x003C75D4 passes
// (first, middle, last, 0, extra) with caller cleanup (cdecl, 5 pushes).
void Rva003C69B7PartialSort(Rva003BD485Keyed **first, Rva003BD485Keyed **middle, Rva003BD485Keyed **last, int, int extra)
{
	typedef void (__cdecl *PopHeap6)(Rva003BD485Keyed **, Rva003BD485Keyed **, Rva003BD485Keyed **, Rva003BD485Keyed *, int, int);
	Rva003C4B67MakeHeap(first, middle, extra);
	for (Rva003BD485Keyed **p = middle; p < last; ++p)
	{
		if ((*p)->m_key < (*first)->m_key)
			((PopHeap6)Rva003C3AC7PopHeap)(first, middle, p, *p, extra, 0);
	}
	Rva003C6464SortHeap(first, middle, extra);
}

// ?Rva003C75C2PartialSort@@YAXPAPAURva003BD485Keyed@@00H@Z @0x003C75C2 27B.
// Heap partial-sort adapter over the same keyed array: forwards (first,
// middle, last, extra) to the 5-arg PartialSort at 0x003C69B7 as (first,
// middle, last, 0, extra). Chain lane on 0x003C69B7; caller 0x003CA315;
// cdecl with caller cleanup like siblings.
void Rva003C75C2PartialSort(Rva003BD485Keyed **first, Rva003BD485Keyed **middle, Rva003BD485Keyed **last, int extra)
{
	Rva003C69B7PartialSort(first, middle, last, 0, extra);
}
