// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FC21A (36B): flag-gated countdown decay. If the +0x34 flag is clear
// or the +0x20 field is null, returns; otherwise decrements +0x30 and
// returns while still positive; on expiry clears the flag and the count
// and tail-jumps to pinned 0x004E0CA3 on the field object. Identity of
// both the owner and the callee unproven; honest address-derived names.

class Rva004E0CA3
{
public:
	void rva004E0CA3();
};

class Rva004FC21AOwner
{
public:
	void rva004FC21A();

private:
	char m_pad00[0x20];	// +0x00..0x1F
	Rva004E0CA3 *m_20;	// +0x20
	char m_pad24[0x0C];	// +0x24..0x2F
	int m_30;		// +0x30 countdown
	unsigned char m_34;	// +0x34 flag
};

void Rva004FC21AOwner::rva004FC21A()
{
	if (!m_34)
		return;
	Rva004E0CA3 *f = m_20;
	if (!f)
		return;
	if (--m_30 > 0)
		return;
	m_34 = 0;
	m_30 = 0;
	f->rva004E0CA3();
}
