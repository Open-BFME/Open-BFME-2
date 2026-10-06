// cl: /MD
// ?rva0051732A@Rva0051732A@@QAEPAU1@PAUTargetRef00217D4C@@@Z @0x0051732A 27B
// Refcounted-pointer setter: store raw TargetRef pointer at +0, if non-null
// AddRef at +4 then call rowed fastcall Release at 0x0007DEEF, return this.
// Callers at 0x0044C0DB and 0x005178C8; sole callee rowed.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0051732A
{
	TargetRef00217D4C *m_ptr;
	Rva0051732A *rva0051732A(TargetRef00217D4C *p);
};

Rva0051732A *Rva0051732A::rva0051732A(TargetRef00217D4C *p)
{
	m_ptr = p;
	if (p) {
		++p->references;
		ReleaseTreeHintRef00217D4C(p);
	}
	return this;
}
