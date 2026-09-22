// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// ?initializeArray@BfmeThingCDE@@QAEXH@Z
//
// Array storage for the CDE node table: new[] of 0x10-byte slots through the
// game operator new[] plus ehvec construction, then per-slot init with a null
// active node plus the owner back-pointer up to count. Split from
// BfmeThingCDEDestructor.cpp: this body needs /EHsc for the array-new EH
// frame where its siblings verify under /EHs-c-.

struct CDEArraySlot
{
	CDEArraySlot();
	~CDEArraySlot();
	void *activeNode;
	void *m_owner;
	void *prevNode;
	void *nextNode;
};

class BfmeThingCDE
{
public:
	void initializeArray(int count);

	void *m_owner;
	void *m_ptr4;
	void *m_ptr8;
	void *m_link0;
	void *m_link1;
	void *m_prev;
	void *m_next;
	void *m_array;
	int m_count;
};

void *__cdecl operator new[](unsigned int);

void BfmeThingCDE::initializeArray(int count)
{
	m_count = count;
	CDEArraySlot *slots = new CDEArraySlot[count];
	m_array = slots;
	CDEArraySlot *endSlot = (CDEArraySlot *)((char *)slots + (m_count << 4));
	if (slots != endSlot)
	{
		do
		{
			slots->activeNode = 0;
			slots->m_owner = this;
			slots++;
		} while (slots != endSlot);
	}
}
