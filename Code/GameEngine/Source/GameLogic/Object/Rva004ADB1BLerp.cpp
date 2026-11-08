// cl: /O1 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?handlePackingProcessing@Rva004AD9B0@@UAE_NXZ @0x004ADB1B 188B.
// When the gate passes, lerp the drawable float at +0xb0 between 1.0f
// and the source float at +0xc8. Kind 2 uses the +0x88 denominator.
// ?handlePackingProcessing@Rva004B0164@@UAE_NXZ @0x004B0348: slot 20 of the
// Rva004B0164 table (SpecialAbilityUpdate-family handlePackingProcessing slot),
// same shape on the shared layout.

extern float g_00BBB8D8;

#include "../../../Include/GameClient/Drawable.h"

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

#include "../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva004AD9B0 : public SpecialAbilityUpdate
{
public:
	virtual bool handlePackingProcessing();

protected:
	char m_pad88[0x8C - 0x88];
	float m_result8C;
};

class Rva004B0164 : public Rva004AD9B0
{
public:
	virtual bool handlePackingProcessing();
};

bool Rva004AD9B0::handlePackingProcessing()
{
	bool ok = SpecialAbilityUpdate::handlePackingProcessing();
	if (ok == 0)
		return ok;
	float base;
	float other;
	unsigned int denom;
	if (m_packingState == 2) {
		base = g_00BBB8D8;
		denom = ((const Src *)m_moduleData)->m_unpackTime;
		other = ((const Src *)m_moduleData)->m_targetOpacity;
	} else {
		float targetOpacity = ((const Src *)m_moduleData)->m_targetOpacity;
		denom = ((const Src *)m_moduleData)->m_packTime;
		base = targetOpacity;
		other = g_00BBB8D8;
	}
	float ratio = (float)m_animFrames / (float)denom;
	float result = base + (other - base) * (g_00BBB8D8 - ratio);
	if (((Thing *)m_object)->getDrawable() != 0)
		((Thing *)m_object)->getDrawable()->field_0b0 = result;
	return ok;
}

// Native 0x004B0348..0x004B0414: same guard and ratio as the rowed
// sibling, but source value +CC and result retained at receiver +8C before
// copying it to the drawable +B0. RET0 returns the guard bool unchanged.
bool Rva004B0164::handlePackingProcessing()
{
	bool ok = SpecialAbilityUpdate::handlePackingProcessing();
	if (ok == 0)
		return ok;
	float base;
	float other;
	unsigned int denom;
	if (m_packingState == 2) {
		base = g_00BBB8D8;
		denom = ((const Src *)m_moduleData)->m_unpackTime;
		other = ((const Src *)m_moduleData)->m_cc;
	} else {
		float disguiseOpacity = ((const Src *)m_moduleData)->m_cc;
		denom = ((const Src *)m_moduleData)->m_packTime;
		base = disguiseOpacity;
		other = g_00BBB8D8;
	}
	float ratio = (float)m_animFrames / (float)denom;
	m_result8C = base + (other - base) * (g_00BBB8D8 - ratio);
	if (((Thing *)m_object)->getDrawable() != 0) {
		float value = m_result8C;
		Drawable *drawable = ((Thing *)m_object)->getDrawable();
		drawable->field_0b0 = value;
	}
	return ok;
}
