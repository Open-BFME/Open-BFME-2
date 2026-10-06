// cl: /MD
// ??0Rva003685CF@@QAE@ABVBfmeObject872Header@@0@Z @0x003685CF 43B
// Ctor with vtable 0x00817968 plus int 0 at +4 plus two BfmeObject872Header
// copies at +8/+0x18 via rowed ??0BfmeObject872Header@@QAE@ABV0@@Z @0x002CF108.
// Evidence: retail and [esi+4],0 plus lea +8/+0x18 plus vtable store plus two
// calls; callers pass two header refs (e.g. 0x0045ABA5 lea+push pattern).
// Owner unproven so honest address class name used.
class BfmeObject872Header
{
	char m_bytes[16];
public:
	BfmeObject872Header(const BfmeObject872Header &other);
};
class Rva003685CF
{
public:
	virtual ~Rva003685CF() {};
	Rva003685CF(const BfmeObject872Header &a, const BfmeObject872Header &b);
	int m_4;
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
};
Rva003685CF::Rva003685CF(const BfmeObject872Header &a, const BfmeObject872Header &b)
	: m_4(0), m_8(a), m_18(b)
{
}

// One more constructor of this shape, each installing its own vtable (the only
// differing operand): 0x002FDF1C (VA 0xc071cc). The virtual is declared inline and
// empty so the vtable the compiler emits resolves in this unit. Owners keep
// their addresses.

class Rva002FDF1C
{
public:
	virtual ~Rva002FDF1C() {}
	Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b);
	int m_4;
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
};

Rva002FDF1C::Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b)
	: m_4(0), m_8(a), m_18(b)
{
}
