// ?rva0033EC93@Rva0033EC93@@QAE_NPBXPAM@Z
// partial score=0.7709 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva0033EC93@Rva0033EC93@@QAE_NPBXPAM@Z @0x0033EC93 402B state-machine updater.
// Evidence: switch on +0x24 (0..4) with float ramps using unsigned-to-float
// max-with-1.0 divisor; callers 0x003A44C6 (same pointer twice) and 0x000C9951;
// prev ThingTemplate and next ProjectileStreamUpdate share /O1.

class Rva0033EC93
{
public:
	bool rva0033EC93(void const *unused, float *out);
private:
	float m_00; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	int m_0C; // +0x0C counter
	int m_10; // +0x10 limit0
	unsigned int m_14; // +0x14 total1
	unsigned int m_18; // +0x18 total2
	int m_1C; // +0x1C limit3
	unsigned int m_20; // +0x20 total4
	int m_state; // +0x24
};

// ?rva0033EC93@Rva0033EC93@@QAE_NPBXPAM@Z present-unmatched
bool Rva0033EC93::rva0033EC93(void const * /*unused*/, float *out)
{
	switch (m_state)
	{
	case 0:
	{
		int cur = m_0C;
		m_0C = cur + 1;
		if ((unsigned int)cur < (unsigned int)m_10)
		{
			*out = 0.0f;
			return true;
		}
		m_0C &= 0;
		m_state = 1;
		*(int *)out = *(int *)&m_00;
		*out = 0.0f;
		return true;
	}
	case 1:
	{
		float div = (float)m_14;
		if (div < 1.0f)
			div = 1.0f;
		float step = (m_04 - m_00) / div;
		float v = *out + step;
		*out = v;
		if (m_04 > v)
			return true;
		*(int *)out = *(int *)&m_04;
		m_state = 2;
		return true;
	}
	case 2:
	{
		float div = (float)m_18;
		if (div < 1.0f)
			div = 1.0f;
		float step = (m_04 - m_08) / div;
		float v = *out - step;
		*out = v;
		if (v > m_08)
			return true;
		*(int *)out = *(int *)&m_08;
		m_state = 3;
		m_0C &= 0;
		return true;
	}
	case 3:
	{
		int cur = m_0C;
		m_0C = cur + 1;
		if ((unsigned int)cur >= (unsigned int)m_1C)
			m_state = 4;
		*out = m_08;
		return true;
	}
	case 4:
	{
		float div = (float)m_20;
		if (div < 1.0f)
			div = 1.0f;
		float step = m_08 / div;
		float v = *out - step;
		*out = v;
		if (v > 0.0f)
			return true;
		*out = 0.0f;
		m_state = 5;
		m_0C &= 0;
		return true;
	}
	default:
		*out = 0.0f;
		return false;
	}
}
