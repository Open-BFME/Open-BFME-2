// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva004F691E@@QAE@XZ @0x004F691E 13B
// Holder dtor releasing TargetRef pointer at +8 via rowed fastcall 0x0007DEEF.
// Evidence: tail-jmp to ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z;
// callers are vector _Destroy loop stride 12 at 0x004F838C (add esi 0xC),
// deleting dtor 0x005677EB (push esi call test flag delete ret 4), and Unwind
// funclets. Same 13B shape as ??1Rva0027EA49@@QAE@XZ (release at +4).
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva004F691E
{
	~Rva004F691E();
	int m_00;
	int m_04;
	TargetRef00217D4C *m_08;
};

Rva004F691E::~Rva004F691E()
{
	if (m_08)
		ReleaseTreeHintRef00217D4C(m_08);
}
