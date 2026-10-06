// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva002E08A2Insert@@YAXPAPAXPAX1@Z @0x002E08A2 37B.
// Sorted pointer-array insert: shifts slots backwards while the new element's
// key at +0xC exceeds the scanned element's key at +0xC, then stores it.
// Evidence: callers 0x002E0E7C (array sweep) and 0x002E1EB7 (vector insert
// with __copy_trivial_backward fast path); prev/next share /O1.
void Rva002E08A2Insert(void **pos, void *val, void *unused)
{
	void **src = pos - 1;
	while (((int *)val)[3] > ((int *)(*src))[3]) {
		*pos = *src;
		pos = src;
		--src;
	}
	*pos = val;
}

// ?Rva002E0E7CReinsert@@YAXPAPAX0PAX1@Z @0x002E0E7C 33B.
// Array re-sort sweep: re-inserts each slot from begin to end via
// Rva002E08A2Insert passing the extra arg through.
// Evidence: sole caller 0x002E180D; callee rowed 0x002E08A2.
void Rva002E0E7CReinsert(void **begin, void **end, void *unused, void *extra)
{
	for (void **p = begin; p != end; ++p)
		Rva002E08A2Insert(p, *p, extra);
}

// ?Rva002E180DReinsert@@YAXPAPAX0PAX@Z @0x002E180D 23B.
// Wrapper passing (begin end 0 extra) through to Rva002E0E7CReinsert.
// Evidence: sole caller 0x002E2313; callee rowed 0x002E0E7C.
void Rva002E180DReinsert(void **begin, void **end, void *extra)
{
	Rva002E0E7CReinsert(begin, end, 0, extra);
}

void **Rva002E0864Median(void **a, void **b, void **c)
{
	if (((int *)(*a))[3] > ((int *)(*b))[3])
	{
		if (((int *)(*b))[3] > ((int *)(*c))[3])
			return b;
		if (((int *)(*a))[3] <= ((int *)(*c))[3])
			return a;
		return c;
	}
	else
	{
		if (((int *)(*a))[3] > ((int *)(*c))[3])
			return a;
		if (((int *)(*b))[3] > ((int *)(*c))[3])
			return c;
		return b;
	}
}

// ?Rva002E08C7SiftUp@@YAXPAPAXHHPAX@Z @0x002E08C7 63B.
// Heap sift-up over void* elements keyed at +0xC (min-heap): bubbles pivot
// up from idx while the parent key exceeds it, stopping at top or a parent
// key at or below it. Sibling of the median/insert family above (same +0xC
// key, same /O1); caller at 0x002E0E9D is the adjust-heap that tail-calls
// this with 5 pushes like the 0x003BD4E8 precedent. Unlock lane, unblocks
// 0x002E0E9D.
void Rva002E08C7SiftUp(void **base, int idx, int top, void *pivot)
{
	int parent = (idx - 1) / 2;
	while (idx > top) {
		void *p = base[parent];
		if (((int *)p)[3] <= ((int *)pivot)[3])
			break;
		base[idx] = p;
		idx = parent;
		parent = (parent - 1) / 2;
	}
	base[idx] = pivot;
}

// ?Rva002E0E9DAdjustHeap@@YAXPAPAXHHPAX1@Z @0x002E0E9D 90B.
// Heap adjust over void* elements keyed at +0xC (min-heap): sifts the hole
// down picking the smaller child, drops the last slot in when the child runs
// even with len, then tail-calls the 5-push sift-up at 0x002E08C7. Chain lane
// on 0x002E08C7; callers 0x002E1824/0x002E184D; cdecl with caller cleanup like
// the 0x003BE553 precedent (same 90B size, opposite min-heap direction).
typedef void (__cdecl *Rva002E08C7SiftUp5)(void **, int, int, void *, void *);
void Rva002E0E9DAdjustHeap(void **base, int hole, int len, void *value, void *extra)
{
	int top = hole;
	int child = hole * 2 + 2;
	while (child < len) {
		if (((int *)base[child])[3] > ((int *)base[child - 1])[3])
			--child;
		base[hole] = base[child];
		hole = child;
		child = child * 2 + 2;
	}
	if (child == len) {
		base[hole] = base[child - 1];
		hole = child - 1;
	}
	((Rva002E08C7SiftUp5)Rva002E08C7SiftUp)(base, hole, top, value, extra);
}

// ?Rva002E1824Reinsert@@YAXPAPAX00PAX1@Z @0x002E1824 41B.
// Pop-front plus adjust: *out = *base, then AdjustHeap(base, 0, end-base,
// value, extra). Evidence: 5-push cdecl call to rowed 0x002E0E9D with hole 0;
// callers 0x002E1889 0x002E232F; prev shares /O1.
void Rva002E1824Reinsert(void **base, void **end, void **out, void *value, void *extra)
{
	*out = *base;
	Rva002E0E9DAdjustHeap(base, 0, (int)(end - base), value, extra);
}

// ?Rva002E184DMakeHeap@@YAXPAPAX0PAX@Z @0x002E184D 60B.
// Heapify range: len = end-base; if len<2 return; for hole=(len-2)/2 down to
// 0 call AdjustHeap(base, hole, len, base[hole], extra). Evidence: 5-push
// cdecl call to rowed 0x002E0E9D; caller 0x002E1EF1; prev shares /O1.
void Rva002E184DMakeHeap(void **base, void **end, void *extra)
{
	int len = (int)(end - base);
	if (len < 2)
		return;
	int hole = (len - 2) / 2;
	for (;;) {
		Rva002E0E9DAdjustHeap(base, hole, len, base[hole], extra);
		if (hole == 0)
			break;
		--hole;
	}
}

// ?Rva002E1EF1MakeHeap@@YAXPAPAX0PAX@Z @0x002E1EF1 25B.
// Heap make-aux over void* elements keyed at +0xC: forwards (first, last,
// extra) to the 3-arg MakeHeap at 0x002E184D with two trailing zero pushes
// (5-push cdecl adapter like the 0x003C4B67 precedent). Chain lane on
// 0x002E184D; caller 0x002E232F; cdecl with caller cleanup.
void Rva002E1EF1MakeHeap(void **first, void **last, void *extra)
{
	typedef void (__cdecl *MakeHeap5)(void **, void **, void *, int, int);
	((MakeHeap5)Rva002E184DMakeHeap)(first, last, extra, 0, 0);
}

// ?Rva002E1889Reinsert@@YAXPAPAX0PAX1@Z @0x002E1889 30B.
// Heap push-tail adapter: last=end-1 then 6-push cdecl call to rowed Reinsert
// 0x002E1824 as (base last last *last extra 0). Evidence: frameless 6-push
// with trailing 0 like MakeHeap5 above; third arg dead; caller 0x002E1F0A;
// abuts MakeHeap sharing /O1.
void Rva002E1889Reinsert(void **base, void **end, void *unused, void *extra)
{
	typedef void (__cdecl *Reinsert6)(void **, void **, void **, void *, void *, int);
	void **last = end - 1;
	((Reinsert6)Rva002E1824Reinsert)(base, last, last, *last, extra, 0);
}

// ?Rva002E1F0AReinsert@@YAXPAPAX0PAX@Z @0x002E1F0A 23B.
// Pass-through adapter to rowed 0x002E1889 as (first last 0 extra).
// Evidence: frameless 4-push with 0 third like 0x002E180D precedent;
// caller 0x002E219A; abuts MakeHeap aux sharing /O1.
void Rva002E1F0AReinsert(void **first, void **last, void *extra)
{
	Rva002E1889Reinsert(first, last, 0, extra);
}
