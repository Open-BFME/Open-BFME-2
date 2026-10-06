// cl: /Ob0

struct Rva00751B90Slot
{
	char a[0x1C];
};

class Rva00751B90
{
	// BFME2 retail indexes slots from +0xEC (BFME1 donor has +0xDC);
	// stride 0x1C is proven by retail's imul. TU-local layout only.
	char pad[0xEC];
	Rva00751B90Slot m_slots[1];

public:
	void *get(int i);
};

void *Rva00751B90::get(int i)
{
	return &m_slots[i];
}
