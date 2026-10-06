// cl: /DNDEBUG /MD /EHsc
// ?rva004D5046@Transport@@QBEMXZ @0x004D5046 68B: Transport unsigned average
// over m_stats5[30] at +0x410CC skipping index m_int40E6C. Sums via fild
// with 2^32 fixup at 0x007C26EC for high-bit values then fmul by
// 0x008601E0. Evidence: retail lea/count/array plus fild/test/jge/fadd plus
// 30-iteration loop plus fmul; layout per Transport.cpp m_int40E6C and six
// 30-int stats with target at +0x410CC; caller at 0x0025DDE9.
extern float g_007C26EC;
extern float g_008601E0;
// g_008601E0: matched references place it at VA 0xc601e0 (retail .rdata value 0.03448276f).
float g_008601E0 = 0.03448276f;

class Transport
{
	char m_pad40E6C[0x40E6C];
	int m_skip40E6C;
	int m_40E70;
	unsigned int m_dummy[30 * 5];
	unsigned int m_vals410CC[30];

public:
	float rva004D5046() const;
	float rva004D5002() const;
	float rva004D508A() const;
	float rva004D4FBE() const;
	float rva004D4F7A() const;
};

float Transport::rva004D5046() const
{
	float sum = 0.0f;
	for (int i = 0; i < 30; ++i)
	{
		if (i == m_skip40E6C)
			continue;
		sum += (float)m_vals410CC[i];
	}
	return sum * g_008601E0;
}

float Transport::rva004D5002() const
{
	float sum = 0.0f;
	for (int i = 0; i < 30; ++i)
	{
		if (i == m_skip40E6C)
			continue;
		sum += (float)m_dummy[60 + i];
	}
	return sum * g_008601E0;
}

float Transport::rva004D508A() const
{
	float sum = 0.0f;
	for (int i = 0; i < 30; ++i)
	{
		if (i == m_skip40E6C)
			continue;
		sum += (float)m_dummy[30 + i];
	}
	return sum * g_008601E0;
}

float Transport::rva004D4FBE() const
{
	float sum = 0.0f;
	for (int i = 0; i < 30; ++i)
	{
		if (i == m_skip40E6C)
			continue;
		sum += (float)m_dummy[90 + i];
	}
	return sum * g_008601E0;
}

float Transport::rva004D4F7A() const
{
	float sum = 0.0f;
	for (int i = 0; i < 30; ++i)
	{
		if (i == m_skip40E6C)
			continue;
		sum += (float)m_dummy[i];
	}
	return sum * g_008601E0;
}
