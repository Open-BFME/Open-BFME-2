// cl: /MD
// ?Rva002E373CClear@@YAXXZ, retail 0x002E373C, 42 bytes.
// Leaf __cdecl clear of global list at 0x00DBD0F4 plus counter reset at
// 0x00DBD0F0 to 1. Head in ECX cleared via AND plus virtual slot-0 call
// with 0 then operator delete; null head deletes null. Callers 0x00283589
// 0x002E3E13 0x00328DCE. Owning class unproven so honest Rva names.
extern int g_Va00DBD0F0;

struct Rva002E373CNode
{
	virtual void *func(int x);
	unsigned char m_pad[0x38];
	Rva002E373CNode *m_next3C;
};
struct Rva002E373CHolder
{
	Rva002E373CNode *m_head;
};

struct Rva002E36D5Node;
extern Rva002E36D5Node *g_00DFF0B8;
// g_Va00DBD0F4: VA 0x00DBD0F4 (.data); retail stores 0x00DFF0B8, the address
// of the rowed zero-filled list head g_00DFF0B8.
Rva002E373CHolder *g_Va00DBD0F4 = (Rva002E373CHolder *)&g_00DFF0B8;

#define Rva00DBD0F0Counter g_Va00DBD0F0

void Rva002E373CClear(void)
{
	Rva002E373CNode *head = g_Va00DBD0F4->m_head;
	g_Va00DBD0F4->m_head = 0;
	Rva00DBD0F0Counter = 1;
	void *toDelete;
	if (head != 0)
		toDelete = head->func(0);
	else
		toDelete = 0;
	operator delete(toDelete);
}
