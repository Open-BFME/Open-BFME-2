// cl: /DNDEBUG /MD
//
// ?rva00462785@Rva00462785@@QAEHXZ, retail 0x00462785, 23 bytes.
// Leaf just after SlaughterHordeContain slot81 (0x0046274C) in the 00462xxx
// page: returns 1 only when the byte at +0xE1 is nonzero and the byte at
// +0x83 of the object at +0x4 is nonzero, else 0. Int return (xor eax plus
// inc eax) not bool. Evidence: address neighbours plus three unclaimed
// callers at 0x00477B88/0x00478E1A/0x00479CFF plus no callees; class identity
// unproven so honest RVA class name, no invented class or method.

struct Inner00462785 {
	char pad[0x83];
	unsigned char flag83;
};

class Rva00462785
{
public:
	virtual void s0();
	virtual void s1();

	Inner00462785 *m_ptr04;
	char m_pad08[0xE1 - 0x8];
	unsigned char m_flagE1;

	int rva00462785();
};

int Rva00462785::rva00462785()
{
	int r = 0;
	if (m_flagE1 != 0 && m_ptr04->flag83 != 0)
		r = 1;
	return r;
}
