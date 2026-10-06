// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva005F8F96@@QAE@XZ, RVA 0x005F8F96, 12 bytes.
// Holder dtor releasing TargetRef pointer at +0 via rowed fastcall 0x0007DEEF.
// Evidence: tail-jmp to ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z;
// callers include deleting dtor 0x005CCCB4 (push esi; mov esi ecx; call; test flag; delete; ret 4),
// list-node cleanup 0x004F7731 (lea ecx [edi+8]; call; free), and vector _Destroy loops stride 8/12.
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
};

Rva005F8F96::~Rva005F8F96()
{
	if (m_00)
		ReleaseTreeHintRef00217D4C(m_00);
}
