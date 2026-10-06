// cl: /MD
// ?rva002CF1FB@Rva002CF1FB@@QAEPAURva002CF1FBNode@@G@Z @0x002CF1FB 32B.
// List search: head at this+0xC, walk next at node+0x484, compare word at
// node+0x5D8 to the key arg, return the match or 0, ret 4. Callers in
// 0x00777613 and 0x0077BE15 unblocks 0x0037BE15.
struct Rva002CF1FBNode
{
	unsigned char m_pad000[0x484];
	Rva002CF1FBNode *m_next;
	unsigned char m_pad488[0x5D8 - 0x488];
	unsigned short m_key;
};

struct Rva002CF1FB
{
	unsigned char m_pad00[12];
	Rva002CF1FBNode *m_head;
	Rva002CF1FBNode *rva002CF1FB(unsigned short key);
};

Rva002CF1FBNode *Rva002CF1FB::rva002CF1FB(unsigned short key)
{
	Rva002CF1FBNode *node = m_head;
	while (node != 0) {
		if (node->m_key == key)
			break;
		node = node->m_next;
	}
	return node;
}
