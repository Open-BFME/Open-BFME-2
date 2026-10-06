// cl: /MD
// ?rva002CF1C9@Rva002CF1C9@@QAEXXZ @ 0x002CF1C9 25B.
// List iterate: head at this+0xC, walk next at node+0x484, call
// ?rva0033B9D1@Rva0033B9D1@@QAEXXZ on each node. Same head/next layout as
// sibling Rva002CF1FB (0x002CF1FB) in Rva002CF1FBFind.cpp.
// Evidence: callee 0x0033B9D1 row caller 0x001E3943 prev/next flags.
class Rva0033B9D1
{
public:
	void rva0033B9D1();
};

struct Rva002CF1C9Node
{
	unsigned char m_pad000[0x484];
	Rva002CF1C9Node *m_next;
};

struct Rva002CF1C9
{
	unsigned char m_pad00[12];
	Rva002CF1C9Node *m_head;
	void rva002CF1C9();
};

void Rva002CF1C9::rva002CF1C9()
{
	Rva002CF1C9Node *node = m_head;
	while (node != 0) {
		((Rva0033B9D1 *)node)->rva0033B9D1();
		node = node->m_next;
	}
}
