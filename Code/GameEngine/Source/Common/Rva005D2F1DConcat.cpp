// cl: /O1 /MD
// ??0Rva005D2F1D@@QAE@ABURvaS16@@ABURvaS08@@@Z @0x005D2F1D 34B and
// ??0Rva005D2F3F@@QAE@ABURvaS24@@ABURvaS08@@@Z @0x005D2F3F 35B: concat ctors
// building S24 from S16+pair and S32 from S24+pair via init lists. Evidence:
// 4x movsd / rep-movsd-6 shapes identical to rowed 0x005D2F96 build family;
// ctor init-list form required (member assignment delves 32B). Neighbours
// 0x005D2F1D+34=0x005D2F3F adjacent. Honest address names.
struct RvaS16 { int m0, m1, m2, m3; };
struct RvaS08 { int m0, m1; };
struct RvaS24 { int m0, m1, m2, m3, m4, m5; };
class Rva005D2F1D
{
public:
	Rva005D2F1D(const RvaS16 &a, const RvaS08 &b);
private:
	RvaS16 m_a;
	RvaS08 m_b;
};
Rva005D2F1D::Rva005D2F1D(const RvaS16 &a, const RvaS08 &b) : m_a(a), m_b(b)
{
}
class Rva005D2F3F
{
public:
	Rva005D2F3F(const RvaS24 &a, const RvaS08 &b);
private:
	RvaS24 m_a;
	RvaS08 m_b;
};
Rva005D2F3F::Rva005D2F3F(const RvaS24 &a, const RvaS08 &b) : m_a(a), m_b(b)
{
}
