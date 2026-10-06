// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004E0790@Rva004E0790@@QAEXXZ @0x004E0790 25B
// Guarded TreeHint release: if Inner at +0x00 != 0 release its TargetRef at
// +0xAC via rowed fastcall 0x0007DEEF then null the holder. Retail is push esi
// / mov esi,ecx / mov eax,[esi] / test eax,eax / je pop / lea ecx,[eax+0xAC] /
// call Release / and [esi],0 / pop esi / ret (25B). /O1 selects and [esi],0
// (defaults give mov [esi],0).
// Evidence: unlock lane; callees all rowed; callers at 0x004E0902 0x004E10DB;
// same Release pattern as Rva005EEFD2Assign (offset 0x04 there, 0xAC here).
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva004E0790Inner
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ref;
};
class Rva004E0790
{
public:
	void rva004E0790();
	Rva004E0790Inner *m_ptr;
};
void Rva004E0790::rva004E0790()
{
	Rva004E0790Inner *p = m_ptr;
	if (p) {
		ReleaseTreeHintRef00217D4C(&p->m_ref);
		m_ptr = 0;
	}
}
