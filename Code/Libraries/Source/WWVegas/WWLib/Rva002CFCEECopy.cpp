// cl: /MD
// ?rva002CFCEE@Rva002CFCEE@@QAEPAURva002CFA4ENode@@PAU2@0@Z @0x002CFCEE 115B.
// Tree copy for the Rva002CF13B-node tree: clones the top through the rowed
// stdcall 0x002CFA4E, links the parent, recurses right, then walks the left
// spine cloning. Same 115B shape as the rowed 0x002CFC7B copy.
// Node layout (color +0 parent +4 left +8 right +12 value +10) proven by the
// retail offsets and the 0x18 alloc in 0x002CF86F. Callers at 0x002CFD17
// 0x002CFD44 (self) and 0x002D01E0.
struct Rva002CFA4ENode
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva002CFA4ENode *m_parent;
	Rva002CFA4ENode *m_left;
	Rva002CFA4ENode *m_right;
	unsigned char m_value[8];
};

struct Rva002CFCEE
{
	Rva002CFA4ENode *rva002CFA4E(const Rva002CFA4ENode *src);
	Rva002CFA4ENode *rva002CFCEE(Rva002CFA4ENode *x, Rva002CFA4ENode *p);
};

// ?rva002CFA4E@Rva002CFCEE@@QAEPAURva002CFA4ENode@@PBU2@@Z is the thiscall twin of the rowed stdcall 0x002CFA4E (same 30B body, ecx ignored); caller 0x002CFD2B reloads ecx proof.

Rva002CFA4ENode *Rva002CFCEE::rva002CFCEE(Rva002CFA4ENode *x, Rva002CFA4ENode *p)
{
	Rva002CFA4ENode *top = rva002CFA4E(x);
	top->m_parent = p;
	if (x->m_right != 0)
		top->m_right = rva002CFCEE(x->m_right, top);
	p = top;
	x = x->m_left;
	while (x != 0) {
		Rva002CFA4ENode *y = rva002CFA4E(x);
		p->m_left = y;
		y->m_parent = p;
		if (x->m_right != 0)
			y->m_right = rva002CFCEE(x->m_right, y);
		p = y;
		x = x->m_left;
	}
	return top;
}
