// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00440B64Insert@@YAXPAPAXPAXVRva0043FE9A@@@Z @0x00440B64 47B.
// Unguarded linear insert with stateful comparator rowed at 0x0043FE9A.
// Shifts while comp(val next) then stores val. Evidence: callers 0x00441968
// 0x00441986; prev shares /O1; mirrors Rva005B6324Insert 47B.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00440B64Insert(void **last, void *val, Rva0043FE9A comp)
{
	void **next = last - 1;
	while (comp.rva0043FE9A((MapMetaData *)val, (MapMetaData *)*next)) {
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

namespace _STL
{
void *__copy_trivial_backward(const void *first, const void *last, void *result);
}

// ?Rva0044192FGuarded@@YAXPAPAX0PAXVRva0043FE9A@@@Z @0x0044192F 69B.
// Guarded insert: if comp(first val) shift via copy_backward and store at
// first else delegate to unguarded insert. Evidence: caller 0x00441D90;
// callees rowed 0x0043FE9A 0x00620840 0x00440B64; mirrors Rva005B639FGuarded.
void Rva0044192FGuarded(void **first, void **last, void *val, Rva0043FE9A comp)
{
	if (comp.rva0043FE9A((MapMetaData *)val, (MapMetaData *)*first)) {
		_STL::__copy_trivial_backward(first, last, last + 1);
		*first = val;
	}
	else {
		Rva00440B64Insert(last, val, comp);
	}
}

// ?Rva00441974Sort@@YAXPAPAX0PAXVRva0043FE9A@@@Z @0x00441974 37B.
// Reinsert sweep via unguarded insert for each slot. Evidence: caller
// 0x00441DB6; callee rowed 0x00440B64.
void Rva00441974Sort(void **begin, void **end, void *unused, Rva0043FE9A comp)
{
	for (void **p = begin; p != end; ++p)
		Rva00440B64Insert(p, *p, comp);
}

// ?Rva00441DA4Sort@@YAXPAPAX0VRva0043FE9A@@@Z @0x00441DA4 27B.
// Wrapper passing zero unused through to reinsert sweep. Evidence: caller
// 0x00442856; callee rowed 0x00441974.
void Rva00441DA4Sort(void **begin, void **end, Rva0043FE9A comp)
{
	Rva00441974Sort(begin, end, 0, comp);
}

// ?Rva00441D74Sort@@YAXPAPAX0VRva0043FE9A@@@Z @0x00441D74 48B.
// Insertion sort via guarded insert for each slot from begin+1. Evidence:
// callers 0x00442847 0x0044286B; callee rowed 0x0044192F.
void Rva00441D74Sort(void **begin, void **end, Rva0043FE9A comp)
{
	if (begin == end)
		return;
	for (void **p = begin + 1; p != end; ++p)
		Rva0044192FGuarded(begin, p, *p, comp);
}
