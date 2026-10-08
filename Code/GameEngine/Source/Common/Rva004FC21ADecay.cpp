// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FC21A (36B): flag-gated countdown decay. If the +0x34 flag is clear
// or the +0x20 field is null, returns; otherwise decrements +0x30 and
// returns while still positive; on expiry clears the flag and the count
// and tail-jumps to pinned 0x004E0CA3 on the field object. Identity of
// the owner is unproven; the callee uses its established ledger name.

class Rva004E0B60
{
public:
	void rva004E0CA3();
};

class Rva004FC21AOwner
{
public:
	void rva004FC21A();
	int rva004FC207();

private:
	char m_pad00[0x20];	// +0x00..0x1F
	Rva004E0B60 *m_20;	// +0x20
	char m_pad24[0x0C];	// +0x24..0x2F
	int m_30;		// +0x30 countdown
	unsigned char m_34;	// +0x34 flag
};

void Rva004FC21AOwner::rva004FC21A()
{
	if (!m_34)
		return;
	Rva004E0B60 *f = m_20;
	if (!f)
		return;
	if (--m_30 > 0)
		return;
	m_34 = 0;
	m_30 = 0;
	f->rva004E0CA3();
}

// WorldBuilder GetTurnsUntilConstructionComplete uses the same +20/+30/+34
// fields as its countdown update. Retail 004FC207..004FC21A is a complete
// nineteen-byte no-argument query. The existing opaque owner is retained.
int Rva004FC21AOwner::rva004FC207()
{
    if (m_34 && m_20)
        return m_30;
    return 0;
}
