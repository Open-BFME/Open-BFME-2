// cl: /MD
//
// ??0BfmeOpaqueOwnedRecord1408@@QAE@ABU0@@Z @0x00556450 155B
// Copy ctor for the 1408-byte (0x580) opaque deque record. Layout from retail:
// +0/+4 head dwords, +8 subobject (0x548 bytes via pinned
// ??0Rva005564EBSub@@QAE@ABU0@@Z @0x0038630B), +0x550 5-dword block
// (rep movsd), six dwords at +0x564/+0x568/+0x56C/+0x570/+0x574/+0x578,
// bytes at +0x57C/+0x57D. Total 0x580=1408. No EH (single non-POD Sub first).
// Evidence: callers 0x00557C7F (_Construct) and 0x00558E2C (push_back_aux_v)
// name it ??0BfmeOpaqueOwnedRecord1408@@QAE@ABU0@@Z; shares +8 Sub with 1432.
struct Rva005564EBSub
{
	char m_body[0x548];
	Rva005564EBSub(const Rva005564EBSub &o);
	~Rva005564EBSub();
};

struct Tail5
{
	unsigned int v[5];
};

struct BfmeOpaqueOwnedRecord1408
{
	unsigned int m_00;
	unsigned int m_04;
	Rva005564EBSub m_08;
	Tail5 m_550;
	unsigned int m_564;
	unsigned int m_568;
	unsigned int m_56c;
	unsigned int m_570;
	unsigned int m_574;
	unsigned int m_578;
	unsigned char m_57c;
	unsigned char m_57d;
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &o);
};

BfmeOpaqueOwnedRecord1408::BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
	, m_08(o.m_08)
	, m_550(o.m_550)
	, m_564(o.m_564)
	, m_568(o.m_568)
	, m_56c(o.m_56c)
	, m_570(o.m_570)
	, m_574(o.m_574)
	, m_578(o.m_578)
	, m_57c(o.m_57c)
	, m_57d(o.m_57d)
{
}
