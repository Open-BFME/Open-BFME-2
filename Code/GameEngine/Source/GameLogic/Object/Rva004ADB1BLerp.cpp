// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?handlePackingProcessing@Rva004ADB1B@@QAE_NXZ @0x004ADB1B 188B.
// When the gate passes, lerp the drawable float at +0xb0 between 1.0f
// and the source float at +0xc8. Kind 2 uses the +0x88 denominator.
// ?handlePackingProcessing@Rva004B0164@@QAE_NXZ @0x004B0348: slot 20 of the
// Rva004B0164 table (SpecialAbilityUpdate-family handlePackingProcessing slot),
// same shape on the shared layout.

extern float g_00BBB8D8;

class Drawable
{
public:
	char m_pad[0xb0];
	float m_value;
};

#include "../../Common/Thing/thing.h"

class Src
{
public:
	char m_pad[0x84];
	unsigned int m_packTime;
	unsigned int m_unpackTime;
	char m_gap[0xc8 - 0x8c];
	float m_targetOpacity;
	float m_cc;
};

class Rva004ADB1B;
class SpecialAbilityUpdate { friend class Rva004ADB1B; friend class Rva004B0164; protected: bool handlePackingProcessing(); }; // rowed 0x0044F0B3
class Rva004ADB1B
{
public:
	bool handlePackingProcessing();

protected:
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

class Rva004B0164 : public Rva004ADB1B
{
public:
	bool handlePackingProcessing();
};

bool Rva004ADB1B::handlePackingProcessing()
{
	bool ok = ((SpecialAbilityUpdate*)this)->handlePackingProcessing();
	if (ok == 0)
		return ok;
	float base;
	float other;
	unsigned int denom;
	if (m_kind == 2) {
		base = g_00BBB8D8;
		denom = m_src->m_unpackTime;
		other = m_src->m_targetOpacity;
	} else {
		float targetOpacity = m_src->m_targetOpacity;
		denom = m_src->m_packTime;
		base = targetOpacity;
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
bool Rva004B0164::handlePackingProcessing()
{
	bool ok = ((SpecialAbilityUpdate*)this)->handlePackingProcessing();
	if (ok == 0)
		return ok;
	float base;
	float other;
	unsigned int denom;
	if (m_kind == 2) {
		base = g_00BBB8D8;
		denom = m_src->m_unpackTime;
		other = m_src->m_cc;
	} else {
		float disguiseOpacity = m_src->m_cc;
		denom = m_src->m_packTime;
		base = disguiseOpacity;
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
