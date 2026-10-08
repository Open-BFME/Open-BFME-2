// Retail 0x0034F9D0, 25 bytes.  Insert a node after the requested position
// or at the head of the singly linked list when the position is null.

struct Rva0034F9D0Node
{
	Rva0034F9D0Node *m_next;
};

struct Rva0034F9D0Head
{
	Rva0034F9D0Node *m_first;
};

void __stdcall rva0034f9d0Insert(
	Rva0034F9D0Head *head,
	Rva0034F9D0Node *node,
	Rva0034F9D0Node *after)
{
	if (after != 0)
	{
		node->m_next = after->m_next;
		after->m_next = node;
	}
	else
	{
		node->m_next = head->m_first;
		head->m_first = node;
	}
}

// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 W3DVolumetricShadow.cpp
// addDynamicShadowTask is an operation lead, not proof of the target owner.
// Native EFB14/27 ends RET8 at EFB2C; EFB2F..EFB3E is a complete RET4 leaf.
// It replaces the pointer at receiver+4, then writes the old pointer into
// node+0. Preserve that order even if node overlaps the receiver's storage.
// Original class and higher-level role remain unresolved.
struct Rva000EFB2FNode { Rva000EFB2FNode *m_next; };
class Rva000EFB2FList {
public:
 void prepend(Rva000EFB2FNode *node);
 char m_pad00[4];
 Rva000EFB2FNode *m_head;
};
void Rva000EFB2FList::prepend(Rva000EFB2FNode *node) {
 Rva000EFB2FNode *old=m_head;
 m_head=node;
 node->m_next=old;
}
