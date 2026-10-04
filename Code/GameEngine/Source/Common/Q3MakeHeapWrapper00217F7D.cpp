// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva00217F7DMake@@YAXPAUQ3SortElem16@@0UQ3SortCompare@@@Z @0x00217F7D 25B
// Unlock thin __cdecl wrapper forwarding to rowed __make_heap at 0x00217BAE
// with null tail args. Evidence: push-0 push-0 plus three pushes plus call
// plus add esp 0x14; caller at 0x002188F5.
struct Q3SortElem16;
struct Q3SortCompare
{
	void *m_state;
};

void __cdecl __make_heap(Q3SortElem16 *first, Q3SortElem16 *last,
	Q3SortCompare comp, Q3SortElem16 *result, int *extra);

void __cdecl Rva00217F7DMake(Q3SortElem16 *first, Q3SortElem16 *last,
	Q3SortCompare comp)
{
	__make_heap(first, last, comp, 0, 0);
}
