// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva002D2DF6@Rva002D2DF6@@QAEXXZ @0x002D2DF6 58B: virtual touch plus
// sub-struct init. Retail calls virtual slot 9 (call [eax+0x24], no args) on
// the member at +0x78 when non-null, zeroes an xmm reg, sets flag +0x7C,
// initializes the sub-struct at +0x98 (+8=0, +0xC/+0x10/+0x14=-2 loaded once
// via push -2 / pop ecx, +0x18=0.0f via movss), and sets flag +0x128. The
// slot-9 target is unproven (pure-virtual slot names); member bytes outside
// the observed offsets are unclaimed pad. Boundary abuts 0x002D2E30 at +58.
// Honest address-derived names.

class Rva002D2DF6Slot
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
};

struct Rva002D2DF6Sub
{
	int m_pad00[2]; // +0x00..+0x08 untouched
	unsigned char m_b08; // +0x08 = 0 (byte store)
	unsigned char m_pad09[3]; // +0x09..+0x0C untouched
	int m_a0C; // +0x0C = -2
	int m_a10; // +0x10 = -2
	int m_a14; // +0x14 = -2
	float m_f18; // +0x18 = 0.0f
};

class Rva002D2DF6
{
public:
	void rva002D2DF6();
private:
	unsigned char m_pad00[0x78]; // +0x00..+0x78 unclaimed
	Rva002D2DF6Slot *m_obj; // +0x78
	unsigned char m_flag7C; // +0x7C
	unsigned char m_pad7D[0x98 - 0x7D]; // +0x7D..+0x98 unclaimed
	Rva002D2DF6Sub m_sub; // +0x98
	unsigned char m_padB4[0x128 - 0xB4]; // +0xB4..+0x128 unclaimed
	unsigned char m_flag128; // +0x128
};

// ?rva002D2DF6@Rva002D2DF6@@QAEXXZ
void Rva002D2DF6::rva002D2DF6()
{
	if (m_obj)
		m_obj->s09();
	Rva002D2DF6Sub *s = &m_sub;
	m_flag7C = 1;
	int neg = -2;
	s->m_b08 = 0;
	s->m_a0C = neg;
	s->m_a10 = neg;
	s->m_a14 = neg;
	s->m_f18 = 0.0f;
	m_flag128 = 1;
}
