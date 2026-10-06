// cl: /EHsc /MD
// ?rva005C8E2C@HostClass005C8E0A@@QAE?AVBfmePoolRef10@@XZ @0x005C8E2C 135B
// Take the pool ref at +8: if null return null, else copy to a local,
// clear the member, clear byte +0x46, adjust via LargeGroupAudioGridCell(false) and
// HostClass005C8E0A::method_005C8E0A, then return the saved ref.
// Evidence: calls to 0x51950 copy-ctor, 0x519BD clear, 0x5C87F8 bool,
// 0x5C8E0A method, Release_Ref at 0x50ED3; caller 0x56A430.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BfmePoolHolder88
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef10
{
public:
	BfmePoolHolder88 *m_target;
	__forceinline BfmePoolRef10() : m_target(0) {}
	BfmePoolRef10(const BfmePoolRef10 &other);
	void rva000519BD();
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
};

class LargeGroupAudioGridCell
{
public:
	void setOverlappedLocking(bool flag);
};

class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	BfmePoolRef10 rva005C8E2C();
private:
	char m_pad00[8];
	BfmePoolRef10 m_pool08;
	char m_pad0C[0x3A];
	unsigned char m_byte46;
};

BfmePoolRef10 HostClass005C8E0A::rva005C8E2C()
{
	if (m_pool08.m_target == 0)
		return BfmePoolRef10();
	BfmePoolRef10 tmp = m_pool08;
	m_pool08.rva000519BD();
	m_byte46 = 0;
	((LargeGroupAudioGridCell *)this)->setOverlappedLocking(false);
	method_005C8E0A();
	return tmp;
}
