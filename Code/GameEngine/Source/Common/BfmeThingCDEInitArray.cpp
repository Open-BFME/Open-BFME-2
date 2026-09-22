// cl: /EHsc /O2 /Ob2 /DNDEBUG /MD
// ?initializeArray@BfmeThingCDE@@QAEXH@Z retail 0x0073A3C0 148 bytes.
// Array construction over 0x10-byte CDE slots: operator new[] through the
// rowed 0x2FDE0, element construction through the ehvec at 0x629512, then a
// pointer loop stamping each slot empty with its owner. Layout follows the
// banked CDEArraySlot and BfmeThingCDE notes: m_array at 1C and m_count at
// 20 with the slot linking its neighbours at 08 and 0C. The <new> header is
// load-bearing: without it array new lowers to scalar new instead of the
// rowed array operator.

#include <new>

struct CDEArraySlot
{
	CDEArraySlot();
	~CDEArraySlot();

	void *activeNode;
	int unused04;
	void *prevNode;
	void *nextNode;
};

class BfmeThingCDE
{
public:
	void initializeArray(int count);

private:
	char m_pad00[0x1C];
	void *m_array;
	int m_count;
};

// ?initializeArray@BfmeThingCDE@@QAEXH@Z @0x0073A3C0
void BfmeThingCDE::initializeArray(int count)
{
	m_count = count;
	CDEArraySlot *slots = new CDEArraySlot[count];
	CDEArraySlot *end = slots + m_count;
	m_array = slots;
	for (CDEArraySlot *slot = slots; slot != end; ++slot)
	{
		slot->activeNode = 0;
		slot->unused04 = (int)this;
	}
}
