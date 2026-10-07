// cl: /MD /O1 /arch:SSE /G7
// ?Rva002B479FGet@@YAPAXXZ @0x002B479F 18B: address-derived getter name.
// Retail reads the index at global+0x10, then the table at global+0x14,
// selects one pointer, and returns its field at +0x3C. Layout is inferred
// from those retail offsets; the global's meaning and donor identity are unknown.
struct Rva002B479FItem
{
	char padding[0x3C];
	void *result;
};

struct Rva002B479FGlobal
{
	char padding[0x10];
	int index;
	Rva002B479FItem **items;
};

extern Rva002B479FGlobal *g_00E02D6C;

void *Rva002B479FGet()
{
	int index = g_00E02D6C->index;
	Rva002B479FItem **items = g_00E02D6C->items;
	return items[index]->result;
}
