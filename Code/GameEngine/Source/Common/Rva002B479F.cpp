// cl: /MD /O1 /arch:SSE /G7
// ?rva002B479F@LivingWorldLogic@@QAEHXZ @0x002B479F 18B: address-derived getter name.
// Retail reads the index at global+0x10, then the table at global+0x14,
// selects one pointer, and returns its field at +0x3C. Layout is inferred
// from those retail offsets. Caller 0x002B076F supplies TheLivingWorldLogic
// in ECX, then deposits the integer return into Player money; these
// bytes do not read the receiver. TheCampaignManager is the existing
// global owner; the source-level getter name remains unknown.
struct Rva002B479FItem
{
	char padding[0x3C];
	int result;
};

struct Rva002B479FGlobal
{
	char padding[0x10];
	int index;
	Rva002B479FItem **items;
};

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;

class LivingWorldLogic { public: int rva002B479F(); };

int LivingWorldLogic::rva002B479F()
{
	int index = ((Rva002B479FGlobal *)TheCampaignManager)->index;
	Rva002B479FItem **items = ((Rva002B479FGlobal *)TheCampaignManager)->items;
	return items[index]->result;
}
