// cl: /O1 /MD /GX-
// ?rva003B779C@ScriptList@@QAEXPAXPAURva003B31DF@@@Z @0x003B779C (118B):
// recursive group teardown on this ScriptList. Captures the node's group
// through the rowed Rva003B40A1Holder::captureGroup, drains its +4 chain
// with recursive self calls and its +8 chain through the rowed
// ScriptList::rva003B7389, then unlinks the node from the passed list head,
// drops its +0x0C subrecord entry through the rowed Rva003B573E::rva003B7096,
// clears it through the rowed Rva003B31DF::clear and deletes it. The +0x2C
// half lives in rva003B7389; this body is the +0x0C twin plus the capture
// and drain. Evidence: chain via rowed 7389, rowed captureGroup/7096/
// clear/delete callees, inline twin of the 7389 unlink loop.
void __cdecl operator delete(void *block);

struct Rva003B31DF
{
	void clear();
	Rva003B31DF *m_next; // +0x00
	int m_index; // +0x04
};

struct Rva003B3204
{
	void clear();
	Rva003B3204 *m_next; // +0x00
	int m_index; // +0x04
};

class Rva003B40A1Holder
{
public:
	void *captureGroup(void *p);
};

class Rva003B573E
{
public:
	void rva003B7096(int index);
};

class ScriptList
{
public:
	void rva003B7389(void *list, struct Rva003B3204 *node);
	void rva003B779C(void *list, struct Rva003B31DF *node);
};

// ?rva003B779C@ScriptList@@QAEXPAXPAURva003B31DF@@@Z
void ScriptList::rva003B779C(void *list, struct Rva003B31DF *node)
{
	void *cap = ((Rva003B40A1Holder *)this)->captureGroup(node);
	char *linkAddr = (char *)cap + 4;
	Rva003B31DF **head1 = (Rva003B31DF **)linkAddr;
	while (*head1)
		rva003B779C(linkAddr, *head1);
	Rva003B3204 **head2 = (Rva003B3204 **)((char *)cap + 8);
	while (*head2)
		rva003B7389(linkAddr, *head2);
	Rva003B31DF **link = (Rva003B31DF **)list;
	for (;;) {
		if (*link == node)
			break;
		link = (Rva003B31DF **)*link;
		if (link == 0)
			goto tail;
	}
	*link = node->m_next;
	node->m_next = 0;
tail:
	((Rva003B573E *)((char *)this + 0x0C))->rva003B7096(node->m_index);
	node->clear();
	operator delete(node);
}
