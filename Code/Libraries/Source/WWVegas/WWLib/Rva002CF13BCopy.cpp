// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva002CF13B@@QAE@ABU0@@Z @0x002CF13B 27B.
// Copy ctor for an 8-byte record: copy-constructs the leading 4-byte fixed
// storage through the rowed 0x002CF0F0, copies the dword at +4, returns this
// in eax with ret 4. Same return-this shape as the rowed 0x002CF120 copy ctor.
// Owner class unproven so honest Rva holder. Caller at 0x002CF37A unblocks 0x002CF36E.
class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other);
};

struct Rva002CF13B
{
	BfmeFixedStorage002CF0F0 m_head;
	int m_field04;
	Rva002CF13B(const Rva002CF13B &other);
};

Rva002CF13B::Rva002CF13B(const Rva002CF13B &other) : m_head(other.m_head)
{
	m_field04 = other.m_field04;
}
