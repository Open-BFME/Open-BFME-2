// cl: /O1 /arch:SSE
//
// LocomotorTemplate::validate, retail 0x001E38B9 (64 bytes); formerly the
// address-named Rva001E38B9::rva001E38B9 (Code/GameEngine/Source/Common/
// Rva001E38B9Fixup.cpp).
// Identity (target): WorldBuilder's debug Locomotor.cpp
// LocomotorTemplate::validate (asserts at lines 351..356, "WINGS should always
// have positive minSpeeds" / "... positive minTurnSpeed") has the same four
// steps on the same offsets: +0x30 defaults from +0x2C when zero, +0x4C from
// +0x48 when negative, and for appearance 3 (+0x74) non-positive +0x28 and
// +0x54 become 0.01f. Retail's single caller is 0x001E8C07 (wb-lead 1/callsite).
// Field names: minSpeed (+0x28) and minTurnSpeed (+0x54) come from the WB
// assert text; the +0x2C/+0x30 and +0x48/+0x4C fallback pairs are not named
// by target evidence and stay offset-named (Zero Hour's validate makes damaged
// values fall back to undamaged ones, an unverified donor reading).

typedef float Real;

enum LocomotorAppearance
{
	LOCO_WINGS = 3 // retail-measured value of +0x74 tested here
};

class LocomotorTemplate
{
public:
	void validate();

private:
	char m_pad00[0x28];
	Real m_minSpeed; // +0x28
	int m_2c; // +0x2C
	int m_30; // +0x30 falls back to +0x2C when zero
	char m_pad34[0x48 - 0x34];
	Real m_48; // +0x48
	Real m_4c; // +0x4C falls back to +0x48 when negative
	char m_pad50[0x54 - 0x50];
	Real m_minTurnSpeed; // +0x54
	char m_pad58[0x74 - 0x58];
	LocomotorAppearance m_appearance; // +0x74
};

void LocomotorTemplate::validate()
{
	if (m_30 == 0)
		m_30 = m_2c;

	if (m_4c < 0.0f)
		m_4c = m_48;

	if (m_appearance == LOCO_WINGS)
	{
		if (m_minSpeed <= 0.0f)
			m_minSpeed = 0.01f;
		if (m_minTurnSpeed <= 0.0f)
			m_minTurnSpeed = 0.01f;
	}
}
