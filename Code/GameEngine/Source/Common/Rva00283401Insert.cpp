// cl: /O1 /MD
// ?Rva00283401Insert@@YGPAPAURva00283401Node@@PAPAU1@PAU1@PBX@Z, RVA 0x00283401, 37 bytes.
// List insert helper: creates node via rowed 0x00282FE0 then splices between
// pos and pos->m_next; stores node to *out and returns out.
// Evidence: callee rowed CreateNode; caller 0x00283C76 passes (&arg, edx, arg).
struct Rva00283401Node {
	Rva00283401Node *m_prev;
	Rva00283401Node *m_next;
};

void *__stdcall Rva00282FE0CreateNode(void const *src);

Rva00283401Node **__stdcall Rva00283401Insert(Rva00283401Node **out, Rva00283401Node *pos, void const *val)
{
	Rva00283401Node *node = (Rva00283401Node *)Rva00282FE0CreateNode(val);
	Rva00283401Node *next = pos->m_next;
	node->m_prev = pos;
	node->m_next = next;
	next->m_prev = node;
	pos->m_next = node;
	*out = node;
	return out;
}

// ?rva00283426@Rva00283426@@QAEXXZ @0x00283426 23B: list teardown calling clear 0x00283002 then freeing sentinel via 0x00030830. Evidence: chain from just-landed 0x00283002; abuts Insert 0x00283401; callers at 0x0028420E plus 0x00283C92.
class Rva00283002 {
public:
	void rva00283002();
};
class Rva00283426 {
public:
	void rva00283426();
private:
	void *m_head;
};
extern "C" void __cdecl free(void *block);
void Rva00283426::rva00283426()
{
	((Rva00283002 *)this)->rva00283002();
	void *head = m_head;
	if (head != 0)
		free(head);
}
