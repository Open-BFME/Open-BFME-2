// ?rva004AC9FA@PartTheHeavensUpdate@@AAEXH@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva004AC9FA@PartTheHeavensUpdate@@AAEXH@Z @0x004AC9FA 176B.
// Private thiscall void(int). A null shadow at +0x24 returns. Otherwise the
// unsigned elapsed frame count samples three curves on the module data at +4:
// the doubled first sample fills both shadow children at +0x58/+0x5c, the
// second sample scaled by radians-per-degree is stored at child +0x20 (negated
// on the second child), and the third sample scaled by 255 becomes setOpacity.

extern "C" float RADS_PER_DEGREE;
extern float g_00BC2900;

class Rva00504BA9Curve
{
public:
	float rva00504BA9(float t);
};

class PartModuleData
{
public:
	char m_pad0[0x10];
	Rva00504BA9Curve m_10;
	char m_pad1[0x3c - 0x11];
	Rva00504BA9Curve m_3c;
	char m_pad2[0x68 - 0x3d];
	Rva00504BA9Curve m_68;
};

class ShadowChild
{
public:
	char m_pad0[0x20];
	float m_20;
	char m_pad24[0x58 - 0x24];
	float m_58;
	float m_5c;
};

class Shadow
{
public:
	void setOpacity(int value);

	char m_pad0[0x58];
	ShadowChild *m_58;
	ShadowChild *m_5c;
};

class PartTheHeavensUpdate
{
private:
	char m_pad0[4];
	PartModuleData *m_moduleData;
	char m_pad8[0x24 - 8];
	Shadow *m_shadow;

	void rva004AC9FA(int elapsed);
};

void PartTheHeavensUpdate::rva004AC9FA(int elapsed)
{
	if (m_shadow == 0)
		return;
	PartModuleData *data = m_moduleData;
	float t = (float)(unsigned)elapsed;
	float doubled = data->m_10.rva00504BA9(t);
	doubled = doubled + doubled;
	float rads = data->m_68.rva00504BA9(t) * RADS_PER_DEGREE;
	ShadowChild *first = m_shadow->m_58;
	first->m_58 = doubled;
	first->m_5c = doubled;
	ShadowChild *second = m_shadow->m_5c;
	second->m_58 = doubled;
	second->m_5c = doubled;
	m_shadow->setOpacity((int)(data->m_3c.rva00504BA9(t) * g_00BC2900));
	float neg = -rads;
	*(int *)&m_shadow->m_58->m_20 = *(int *)&rads;
	m_shadow->m_5c->m_20 = neg;
}
