// cl: /MD
//
// ?rva001E48E8@Rva001E48E8@@QAEPAXI@Z @0x001E48E8 42B
// __thiscall void *(unsigned): scan pointer range [this+4,this+8) for the first
// non-null entry whose sub-object at +4 has mask bit(s) set at +0x14; else null.
// Evidence: self-contained loop shape; callers 0x00263FA7 0x002E74C6;
// neighbours Rva001E3E43Dtor Rva001E4912Init.
struct Rva001E48E8Inner
{
	char _00[0x14];
	unsigned m_14;
};
struct Rva001E48E8Elem
{
	char _00[4];
	Rva001E48E8Inner *m_04;
};
class Rva001E48E8
{
public:
	void *rva001E48E8(unsigned mask);
	char _00[4];
	Rva001E48E8Elem **m_04;
	Rva001E48E8Elem **m_08;
};
void *Rva001E48E8::rva001E48E8(unsigned mask)
{
	Rva001E48E8Elem **it = m_04;
	Rva001E48E8Elem **end = m_08;
	for (; it != end; ++it) {
		Rva001E48E8Elem *p = *it;
		if (p && (p->m_04->m_14 & mask))
			return p;
	}
	return 0;
}
