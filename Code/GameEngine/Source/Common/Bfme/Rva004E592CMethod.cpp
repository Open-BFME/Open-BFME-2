// cl: /O1 /MD
// ?rva004E592C@Rva004E592C@@QAEXPAURva004E592CPair@@@Z @0x004E592C (34B)
// __thiscall method over a node-pointer range [m_first, m_last): forwards to
// the rowed Rva004E588DFill with the pair's (init, stamp); the out[2] result
// is stack scratch. Evidence: chain lane, single caller 0x004E616F;
// callee row 0x004E588D; prev/next share // cl: /O1 /MD.
struct Rva004E588DNode {
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};
void __cdecl Rva004E588DFill(int *out, Rva004E588DNode **first, Rva004E588DNode **last, int acc, int stamp);
struct Rva004E592CPair {
	int m_0;
	int m_4;
};
class Rva004E592C {
	Rva004E588DNode **m_first;
	Rva004E588DNode **m_last;
public:
	void rva004E592C(Rva004E592CPair *pair);
};

void Rva004E592C::rva004E592C(Rva004E592CPair *pair)
{
	int out[2];
	Rva004E588DFill(out, m_first, m_last, pair->m_0, pair->m_4);
}

// Retail 0x004E5911/27B forwards [ecx+0,+4] and stack layout to rowed
// layoutRva0048E730, discarding its return. Evidence: single caller 0x004E6177;
// callee row 0x004E5867; prev/next share // cl: /O1 /MD.
struct Rva0048E730Element;
class Rva0048E730Layout
{
public:
    Rva0048E730Layout(int o) : m_offset(o) {}
    int m_offset;
};
Rva0048E730Layout __cdecl layoutRva0048E730(Rva0048E730Element **first, Rva0048E730Element **last, Rva0048E730Layout layout);
class Rva004E5911
{
    Rva0048E730Element **m_first;
    Rva0048E730Element **m_last;
public:
    void rva004E5911(Rva0048E730Layout layout);
};
void Rva004E5911::rva004E5911(Rva0048E730Layout layout)
{
    layoutRva0048E730(m_first, m_last, layout);
}
