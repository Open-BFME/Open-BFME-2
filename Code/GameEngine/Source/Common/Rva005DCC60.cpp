// cl: /DNDEBUG /MD /EHsc
// ?rva005DCC60@Rva005DCC60@@QAEXXZ, retail 0x005DCC60, 38 bytes.
// Range loop over pointer array at this+4..this+8; for each element with
// +0x10 == 0 call virtual slot at vtable+0x18 with (this+0x14, 0).
// Evidence: virtual call offset 0x18, callees rowed/pinned, caller 0x005DCCFB.
// Honest address name; owner unproven.

class Elem
{
public:
	virtual void dummy0();
	virtual void dummy1();
	virtual void dummy2();
	virtual void dummy3();
	virtual void dummy4();
	virtual void dummy5();
	virtual void target(int a, int b);
	char m_pad4[0x10 - 4];
	int m_10; // +0x10
};

class Rva005DCC60
{
public:
	void rva005DCC60();
private:
	char m_pad0[4];
	Elem **m_begin; // +0x4
	Elem **m_end; // +0x8
	char m_padC[0x14 - 0xC];
	int m_14; // +0x14
};

void Rva005DCC60::rva005DCC60()
{
	for (Elem **it = m_begin; it != m_end; ++it)
	{
		Elem *e = *it;
		if (e->m_10 != 0)
			continue;
		e->target(m_14, 0);
	}
}
