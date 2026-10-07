// ?rva004D51A7@Transport@@QAEXPAXGPAH@Z
// partial score=0.96 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// ?rva004D51A7@Transport@@QAEXPAXGPAH@Z @0x004D51A7 70B: Transport slot setter
// at +0x40E0C. When index < 8 clears the slot via rowed clearSlot then
// stores object and two ints. Evidence: retail cmp word 8 jae plus call
// 0x004D5133 plus dual imul 0xC plus stores at +0x40E0C/+0x40E10/+0x40E14;
// ret 0xC proves 3 args; caller at 0x005A6E62.
struct SlotVals
{
	int x;
	int y;
};

class Transport
{
public:
	// Native calls target the verified TransportUpdate.cpp slot-removal provider.
	void RemoveSocketForSlot(unsigned short index);
	void rva004D51A7(void *obj, unsigned short index, int *vals);

private:
	char m_pad40E0C[0x40E0C];
	struct Slot
	{
		void *m_obj;
		SlotVals m_pair;
	};
	Slot m_slots[8];
};

void Transport::rva004D51A7(void *obj, unsigned short index, int *vals)
{
	if (index >= 8)
		return;
	RemoveSocketForSlot(index);
	m_slots[index].m_obj = obj;
	m_slots[index].m_pair = *(SlotVals *)vals;
}
