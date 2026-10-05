// ?rva0006DE3D@Rva0006DE3DHost@@QAEXXZ
// partial score=0.5 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// 0x0006DE3D (324B): envelope-ratio applier. Guards on the byte at +0x144,
// forms the ratio xmm3 from the unsigned counter pairs (+0x14C/+0x154 or
// +0x148/+0x150) through x87 unsigned conversion plus fdivp, defaulting to
// 1.0f, then optionally max-mixes +0x158/+0x100 into +0x104 and scales the
// two float triples (+0x15C/+0x168) by the ratio into +0xD4/+0xE0.
// Address names; shared 1.0f and 2^32 are compiler literals.

class Rva0006DE3DHost
{
public:
	void rva0006DE3D();
private:
	char m_pad00[0xD4];
	float m_d4; // +0xD4
	float m_d8; // +0xD8
	float m_dc; // +0xDC
	float m_e0; // +0xE0
	float m_e4; // +0xE4
	float m_e8; // +0xE8
	char m_padEC[0x100 - 0xEC];
	float m_100; // +0x100
	float m_104; // +0x104
	char m_pad108[0x144 - 0x108];
	unsigned char m_144; // +0x144
	unsigned char m_145; // +0x145
	unsigned char m_146; // +0x146
	char m_pad147;
	int m_148; // +0x148
	unsigned m_14c; // +0x14C
	int m_150; // +0x150
	unsigned m_154; // +0x154
	float m_158; // +0x158
	float m_15c; // +0x15C
	float m_160; // +0x160
	float m_164; // +0x164
	float m_168; // +0x168
	float m_16c; // +0x16C
	float m_170; // +0x170
};

void Rva0006DE3DHost::rva0006DE3D()
{
	if (m_144 == 0)
		return;
	float r;
	unsigned *p = &m_14c;
	if (*p <= 0u)
		goto alt;
	unsigned s = m_154;
	if (s <= 0u)
		goto alt;
	unsigned e = *p;
	e--;
	*p = e;
	{
		int num = (int)(s - e);
		r = (float)(unsigned)num / (float)(unsigned)s;
	}
	goto second;
alt:
	{
		int d = m_150;
		if (d == 0)
		{
			r = 1.0f;
		}
		else
		{
			m_148--;
			int c = m_148;
			if (c == 0)
			{
				m_144 = 0;
				return;
			}
			r = (float)(unsigned)c / (float)(unsigned)d;
		}
	}
second:
	if (m_145 != 0)
	{
		float v = m_158 * r;
		m_104 = v;
		if (m_100 > v)
			m_104 = m_100;
	}
	if (m_146 != 0)
	{
		float a = m_15c;
		float b = m_160;
		float c = m_164;
		m_d4 = a * r;
		m_d8 = b * r;
		m_dc = c * r;
		float d = m_16c;
		float f = m_170;
		float g = r * m_168;
		m_e0 = g;
		m_e4 = d * r;
		m_e8 = f * r;
	}
}
