// cl: /O1 /DNDEBUG /MD
//
// ?rva003C6437@@YAXPAX00@Z @0x003C6437 45B (dump range 18).
// Cdecl reinsert sweep: walks (begin+4, end) by 4 and forwards each slot
// to the rowed 0x003C4B2D insert as (begin, slot, *slot, extra).
void rva003C4B2D(void *a, void *b, void *c, void *d);

void __cdecl rva003C6437(void *begin, void *end, void *extra)
{
	if (begin == end)
		return;
	for (void *it = (char *)begin + 4; it != end; it = (char *)it + 4)
		rva003C4B2D(begin, it, *(void **)it, extra);
}
