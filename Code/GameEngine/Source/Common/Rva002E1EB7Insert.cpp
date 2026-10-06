// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva002E1EB7Insert@@YAXPAPAX0PAX1@Z @0x002E1EB7 58B.
// Guarded linear insert over void* elements keyed at +0xC. If new key exceeds
// first key shifts via rowed __copy_trivial_backward at 0x620840 and stores
// at first, else delegates to rowed Rva002E08A2Insert at 0x002E08A2.
// Evidence: caller 0x002E2167; prev/next share /O1; mirrors Rva005B639FGuarded.
namespace _STL
{
void *__copy_trivial_backward(const void *first, const void *last, void *result);
}

void Rva002E08A2Insert(void **pos, void *val, void *extra);

void Rva002E1EB7Insert(void **first, void **last, void *val, void *extra)
{
	if (((int *)val)[3] > ((int *)(*first))[3]) {
		_STL::__copy_trivial_backward(first, last, last + 1);
		*first = val;
	}
	else {
		Rva002E08A2Insert(last, val, extra);
	}
}

// ?Rva002E214ESort@@YAXPAPAX0PAX@Z @0x002E214E 45B.
// Insertion sort via guarded insert: for each slot from begin+1 to end call
// Rva002E1EB7Insert with (begin slot value extra). Evidence: callers
// 0x002E2307 0x002E2325; callee rowed 0x002E1EB7.
void Rva002E214ESort(void **begin, void **end, void *extra)
{
	if (begin == end)
		return;
	for (void **p = begin + 1; p != end; ++p)
		Rva002E1EB7Insert(begin, p, *p, extra);
}

void Rva002E180DReinsert(void **begin, void **end, void *extra);

// ?Rva002E22EBSort@@YAXPAPAX0PAX@Z @0x002E22EB 68B.
// Hybrid sort: insertion sort directly for 16 or fewer slots, else sort the
// first 16 then reinsert the tail. Evidence: caller 0x002E2D82; callees
// rowed 0x002E214E 0x002E180D.
void Rva002E22EBSort(void **begin, void **end, void *extra)
{
	if ((((char *)end - (char *)begin) & ~3) > 0x40) {
		void **mid = (void **)((char *)begin + 0x40);
		Rva002E214ESort(begin, mid, extra);
		Rva002E180DReinsert(mid, end, extra);
		return;
	}
	Rva002E214ESort(begin, end, extra);
}

void Rva002E1EF1MakeHeap(void **first, void **last, void *extra);
void Rva002E1824Reinsert(void **base, void **end, void **out, void *value, void *extra);
void Rva002E217BSort(void **base, void **end, void *extra);

// ?Rva002E232FSort@@YAXPAPAX00PAX1@Z @0x002E232F 87B.
// Partial heap sort: heapify [base mid) then selective reinsert from [mid end)
// where key exceeds base key then pop-sort [base mid). Evidence: same +0xC key
// and 6-push Reinsert adapter as 0x002E1889; caller 0x002E2771; shares /O1.
void Rva002E232FSort(void **base, void **mid, void **end, void *unused, void *extra)
{
	typedef void (__cdecl *Reinsert6)(void **, void **, void **, void *, void *, int);
	Rva002E1EF1MakeHeap(base, mid, extra);
	for (void **p = mid; p < end; ++p) {
		if (((int *)*p)[3] > ((int *)*base)[3])
			((Reinsert6)Rva002E1824Reinsert)(base, mid, p, *p, extra, 0);
	}
	Rva002E217BSort(base, mid, extra);
}

// ?Rva002E275FSort@@YAXPAPAX00PAX@Z @0x002E275F 27B.
// Adapter to rowed 0x002E232F as (base mid end 0 extra).
// Evidence: frameless 5-push with 0 fourth like 0x002E1F0A precedent;
// caller 0x002E2CE7; shares /O1.
void Rva002E275FSort(void **base, void **mid, void **end, void *extra)
{
	Rva002E232FSort(base, mid, end, 0, extra);
}
