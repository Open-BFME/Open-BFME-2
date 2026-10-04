// cl: /O1 /MD /GX-
// ?rva003B7389@ScriptList@@QAEXPAXPAURva003B3204@@@Z @0x003B7389 (60B):
// unlink a node from the +4 link chain of the passed list head, then drop
// its subrecord entry through the rowed Rva003B573E::rva003B71B4 on this+0x2c
// (layout-compatible 0x20B subrecord per ScriptListCtor), clear it through
// the rowed Rva003B3204::clear and delete it. Twin of the inline +0x0C half
// in the 118B caller at 0x003B779C (which calls this body for its +0x2C
// half). Evidence: caller 0x003B77CD, rowed 71B4/clear/delete callees.
void __cdecl operator delete(void *block);

struct Rva003B3204
{
	void clear();
	Rva003B3204 *m_next; // +0x00
	int m_index; // +0x04
};

class Rva003B573E
{
public:
	void rva003B71B4(int index);
};

class ScriptList
{
public:
	void rva003B7389(void *list, struct Rva003B3204 *node);
};

// ?rva003B7389@ScriptList@@QAEXPAXPAURva003B3204@@@Z
void ScriptList::rva003B7389(void *list, struct Rva003B3204 *node)
{
	Rva003B3204 **link = (Rva003B3204 **)((char *)list + 4);
	for (;;) {
		if (*link == node)
			break;
		link = (Rva003B3204 **)*link;
		if (link == 0)
			goto tail;
	}
	*link = node->m_next;
	node->m_next = 0;
tail:
	((Rva003B573E *)((char *)this + 0x2C))->rva003B71B4(node->m_index);
	node->clear();
	operator delete(node);
}
