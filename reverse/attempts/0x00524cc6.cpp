// ?Rva00524CC6@@YAXH@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD
// Range-27 lookup touch-and-erase.
// ?Rva00524CC6@@YAXH@Z @0x00524CC6 59B
// Cdecl free function over the 0x00E04938 ObjectLookupMap: finds the
// slot for a local copy of the key through rowed findSlot 0x0041F4E5,
// bails on an empty slot, clears the entry's +0xC dword and the low two
// bits at +0x24, refreshes the key copy from the saved arg, and erases
// through pinned eraseSlot 0x0054883B. Views are TU-local; callee names
// are the rowed/pinned ones.
class Object;

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
	void eraseSlot(int *key);
};

void Rva00524CC6(int a)
{
	int b = a;
	ObjectLookupMap *map = (ObjectLookupMap *)0xE04938;
	Object **slot = map->findSlot(&b);
	Object *o = *slot;
	if (o == 0)
		return;
	*(int *)((char *)o + 0xC) &= 0;
	*(unsigned char *)((char *)o + 0x24) &= 0xFC;
	b = a;
	map->eraseSlot(&b);
}
