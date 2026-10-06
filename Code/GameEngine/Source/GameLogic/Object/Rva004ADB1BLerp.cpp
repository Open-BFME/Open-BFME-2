// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva004ADB1B@Rva004ADB1B@@QAE_NXZ @0x004ADB1B 188B.
// When the gate passes, lerp the drawable float at +0xb0 between 1.0f
// and the source float at +0xc8. Kind 2 uses the +0x88 denominator.

extern float g_00BBB8D8;

class Drawable
{
public:
	char m_pad[0xb0];
	float m_value;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Src
{
public:
	char m_pad[0x84];
	unsigned int m_84;
	unsigned int m_88;
	char m_gap[0xc8 - 0x8c];
	float m_c8;
};

class Rva004ADB1B
{
public:
	bool rva004ADB1B();
	bool rva0044F0B3();

private:
	char m_pad0[4];
	Src *m_src;
	Thing *m_thing;
	char m_padc[0x28 - 0x0c];
	unsigned int m_num;
	char m_pad2c[4];
	int m_kind;
};

bool Rva004ADB1B::rva004ADB1B()
{
	bool ok = rva0044F0B3();
	if (ok == 0)
		return ok;
	float base;
	float other;
	unsigned int denom;
	if (m_kind == 2) {
		base = g_00BBB8D8;
		denom = m_src->m_88;
		other = m_src->m_c8;
	} else {
		float c8 = m_src->m_c8;
		denom = m_src->m_84;
		base = c8;
		other = g_00BBB8D8;
	}
	float ratio = (float)m_num / (float)denom;
	float result = base + (other - base) * (g_00BBB8D8 - ratio);
	if (m_thing->getDrawable() != 0)
		m_thing->getDrawable()->m_value = result;
	return ok;
}
