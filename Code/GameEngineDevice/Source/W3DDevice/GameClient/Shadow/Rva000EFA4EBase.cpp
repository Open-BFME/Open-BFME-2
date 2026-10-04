// cl: /O1 /arch:SSE /GX- /MD
// Target EFA4E/132 initializes the observed 0x58-byte object prefix.
// Native return is zero in EAX; all witnessed constructor callers ignore it.
// Use a void address-derived initializer rather than assert a C++ constructor.
// F0F2B/F0F19 and109D8C reuse this prefix; F0F2B extends through64 and
// stores the BCEFA0 dispatch table. Shadow-family relation is an inference
// from those callers and the separately recovered buffer-owner units.
// Target facts: Vec3 copies at8/14, scalar/flag stores4..54, float1.0
// at BBB8D8. Original class name and complete object size remain unknown.
// Adapted from banked native reconstruction reverse/attempts/0x000efa4e.cpp;
// two-byte constructor-return mismatch resolved by the target's void ABI.
#include "BfmeShadowPrefix.h"
void Rva000EFA4E::initialize()
{
	BfmeShadowVectorPrefix tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 0.0f;
	m_fields.m_28 = -1;
	m_fields.m_24 = -1;
	m_fields.m_08 = tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 1.0f;
	m_fields.m_14 = tmp;
	m_fields.m_04 = 1;
	m_fields.m_05 = 0;
	m_fields.m_20 = 0.0f;
	m_fields.m_2C = 0xFF;
	m_fields.m_30 = 1;
	m_fields.m_34 = 0;
	m_fields.m_38 = 0;
	m_fields.m_3C = -1;
	m_fields.m_40 = 0;
	m_fields.m_44 = 0;
	m_fields.m_48 = 0;
	m_fields.m_4C = 0;
	m_fields.m_50 = 0;
	m_fields.m_54 = 0;
}
