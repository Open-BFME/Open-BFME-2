// cl: /MD
//
// ?rva001F3C9A@Rva001F3C9A@@QAE_NXZ, retail 0x001F3C9A, 105 bytes.
// Bool predicate over a large object (>=0x1A5 bytes): nullable helper at
// +0xA4 (slot 0x28 notify then slot 0x1C int test), int at +0xC against 8,
// bytes at +0x1A4/+0x1A2, retry counter at +0x128 that is decremented when
// nonzero before the second slot-0x1C test. Final fallthrough returns
// (m_128 != 0). Only caller is the unclaimed 0x001FAB59 body, so the owner
// is unknown and the name is an honest address; /O1 matches the sibling
// Rva001F3C20Slots.cpp TU on the same page.

class Rva001F3C9AHelper
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual int v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
};

class Rva001F3C9A
{
public:
	bool rva001F3C9A();
private:
	char m_pad00[0x0C];
	int m_0C;
	char m_pad10[0x94];
	Rva001F3C9AHelper *m_A4;
	char m_padA8[0x80];
	int m_128;
	char m_pad12C[0x76];
	bool m_1A2;
	char m_pad1A3[1];
	bool m_1A4;
};

bool Rva001F3C9A::rva001F3C9A()
{
	if (m_A4)
		m_A4->v28();
	if (m_0C == 8)
		return true;
	if (m_1A4 && m_A4->v1C() == 0)
		return false;
	if (m_1A2)
		return true;
	if (m_128)
		--m_128;
	if (m_A4->v1C() != 0 || m_128 != 0)
		return true;
	return false;
}
