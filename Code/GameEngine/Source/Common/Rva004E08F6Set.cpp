// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004E08F6@Rva004E0790@@QAEXPAURva004E0790Inner@@@Z @0x004E08F6 34B
// Ref-counted holder assignment for Rva004E0790: if (p != m_ptr) {
// rva004E0790(); m_ptr = p; if (p) ++p->m_ref.references; } where references
// is at +0xB0 (TargetRef at +0xAC plus 4). Retail is push esi / mov esi,[esp+8]
// / push edi / mov edi,ecx / cmp esi,[edi] / je pop / call 0x004E0790 /
// test esi,esi / mov [edi],esi / je pop / inc [esi+0xB0] / pop edi / pop esi /
// ret 4 (34B).
// Evidence: chain lane (calls 0x004E0790 landed in Rva004E0790Release.cpp);
// same this plus same m_ptr proves same class Rva004E0790; callers at
// 0x004E0C1F 0x004E1111 0x004E1272.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct Rva004E0790Inner
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ref;
};
class Rva004E0790
{
public:
	void rva004E0790();
	void rva004E08F6(Rva004E0790Inner *p);
	Rva004E0790Inner *m_ptr;
};
void Rva004E0790::rva004E08F6(Rva004E0790Inner *p)
{
	if (p != m_ptr) {
		rva004E0790();
		m_ptr = p;
		if (p)
			++p->m_ref.references;
	}
}
