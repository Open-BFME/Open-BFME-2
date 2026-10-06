// cl: /MD
// ??1Rva0027EA49@@QAE@XZ, RVA 0x0027EA49, 13 bytes.
// Holder dtor releasing TargetRef pointer at +4 via rowed fastcall 0x0007DEEF.
// Evidence: tail-jmp to ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z;
// callers are Rb_tree _M_erase loop (lea ecx [esi+0x10] value at node+16),
// vector _Destroy range stride 8, and deleting dtor 0x005C66F0 (push esi;
// mov esi ecx; call; test flag; delete; ret 4). First word untouched so int pad.
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0027EA49
{
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};

Rva0027EA49::~Rva0027EA49()
{
	if (m_04)
		ReleaseTreeHintRef00217D4C(m_04);
}
