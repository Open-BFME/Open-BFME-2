// cl: /DNDEBUG /MD
// ??0Rva0046267A@@QAE@ABV0@@Z @0x0046267A 29B.
// Copy ctor just after Rva0046262D (0x0046262D) in the 00462xxx page: int at +0
// direct-copied then WeaponTemplateSetHead at +0x4 copy-constructed via the rowed
// 0x00045455. Init-list order gives the retail store-before-call schedule;
// nothrow callee keeps it frameless with push esi and this-return plus ret 4.
// Evidence: rowed callee plus single caller 0x00462D83 (null-checked placement
// wrapper) plus 0x60-byte list-node allocation at 0x004634BA (header 0x10 plus
// 0x50-byte object). Honest RVA class name; no invented class or method.
class WeaponTemplateSetHead
{
public:
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
};
class Rva0046267A
{
public:
	Rva0046267A(const Rva0046267A &that);
private:
	int m_00;
	WeaponTemplateSetHead m_04;
};
Rva0046267A::Rva0046267A(const Rva0046267A &that)
	: m_00(that.m_00), m_04(that.m_04)
{
}
