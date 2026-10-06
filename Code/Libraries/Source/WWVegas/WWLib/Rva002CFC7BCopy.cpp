// cl: /MD
// ?rva002CFC7B@Rva002CFC7B@@QAEPAURva002CFA30Node@@PAU2@0@Z @0x002CFC7B 115B.
// Tree copy for the Rva002CF120-node tree: clones the top through the rowed
// stdcall 0x002CFA30, links the parent, recurses right, then walks the left
// spine cloning. Same 115B shape as the rowed map<int,int> _M_copy 0x002CF6CF.
// Node layout (color +0 parent +4 left +8 right +12 value +10) proven by the
// retail offsets and the 0x24 alloc in 0x002CF84D. Callers at 0x002CFCA4
// 0x002CFCD1 (self) and 0x002D016D.
struct Rva002CFA30Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva002CFA30Node *m_parent;
	Rva002CFA30Node *m_left;
	Rva002CFA30Node *m_right;
	unsigned char m_value[20];
};

struct Rva002CFC7B
{
	Rva002CFA30Node *rva002CFA30(const Rva002CFA30Node *src);
	Rva002CFA30Node *rva002CFC7B(Rva002CFA30Node *x, Rva002CFA30Node *p);
};

// ?rva002CFA30@Rva002CFC7B@@QAEPAURva002CFA30Node@@PBU2@@Z is the thiscall twin of the rowed stdcall 0x002CFA30 (same 30B body, ecx ignored); caller 0x002CFCB8 reloads ecx proof.

Rva002CFA30Node *Rva002CFC7B::rva002CFC7B(Rva002CFA30Node *x, Rva002CFA30Node *p)
{
	Rva002CFA30Node *top = rva002CFA30(x);
	top->m_parent = p;
	if (x->m_right != 0)
		top->m_right = rva002CFC7B(x->m_right, top);
	p = top;
	x = x->m_left;
	while (x != 0) {
		Rva002CFA30Node *y = rva002CFA30(x);
		p->m_left = y;
		y->m_parent = p;
		if (x->m_right != 0)
			y->m_right = rva002CFC7B(x->m_right, y);
		p = y;
		x = x->m_left;
	}
	return top;
}
