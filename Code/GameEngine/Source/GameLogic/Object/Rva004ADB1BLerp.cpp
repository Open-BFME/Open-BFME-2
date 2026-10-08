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
	float m_cc;
};

class Rva004ADB1B
{
public:
	bool rva004ADB1B();
	bool rva004B0348();
	bool rva0044F0B3();

private:
	char m_pad0[4];
	Src *m_src;
	Thing *m_thing;
	char m_padc[0x28 - 0x0c];
	unsigned int m_num;
	char m_pad2c[4];
	int m_kind;
	char m_pad34[0x8C - 0x34];
	float m_result8C;
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

// Native 0x004B0348..0x004B0414: same guard and ratio as the rowed
// sibling, but source value +CC and result retained at receiver +8C before
// copying it to the drawable +B0. RET0 returns the guard bool unchanged.
bool Rva004ADB1B::rva004B0348()
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
		other = m_src->m_cc;
	} else {
		float c8 = m_src->m_cc;
		denom = m_src->m_84;
		base = c8;
		other = g_00BBB8D8;
	}
	float ratio = (float)m_num / (float)denom;
	m_result8C = base + (other - base) * (g_00BBB8D8 - ratio);
	if (m_thing->getDrawable() != 0) {
		float value = m_result8C;
		Drawable *drawable = m_thing->getDrawable();
		drawable->m_value = value;
	}
	return ok;
}
