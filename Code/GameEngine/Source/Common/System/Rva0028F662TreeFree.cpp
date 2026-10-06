// cl: /DNDEBUG /MD
//
// ?rva0028F662@Rva0028F662@@QAEXPAURva0028F662Node@@@Z -- retail 0x0028F662, 45 bytes.
// Tree free: recurses on child at +0xC with the same owner, frees the node
// through the rowed free at 0x30830, then iterates the sibling at +0x8.
// Caller 0x002913F9 passes head from [eax+4] with owner in ecx and resets
// the head afterwards; self-recursion at 0x0028F674 proves the shape.
// Plain void free(void*) keeps the retail E8-to-row call shape.

extern "C" void __cdecl free(void *block);

struct Rva0028F662Node
{
	char m_pad[8];
	Rva0028F662Node *m_next;
	Rva0028F662Node *m_child;
};

class Rva0028F662
{
public:
	void rva0028F662(Rva0028F662Node *node);
};

void Rva0028F662::rva0028F662(Rva0028F662Node *node)
{
	Rva0028F662Node *cur = node;
	if (cur == 0)
		return;
	while (cur != 0) {
		rva0028F662(cur->m_child);
		Rva0028F662Node *next = cur->m_next;
		free(cur);
		cur = next;
	}
}
