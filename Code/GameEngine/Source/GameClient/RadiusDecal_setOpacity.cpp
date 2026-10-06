// cl: /DNDEBUG /MD
//
// ?setOpacity@RadiusDecal@@QAEXM@Z, retail 0x00330DDB, 34 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/RadiusDecal.cpp,
// matched 35 bytes there): when the shadow holder at +0x04 is present, scale
// the opacity by 255.0f and forward the truncated integer to the shadow.

typedef float Real;
typedef int Int;

class Shadow
{
public:
	void setOpacity(Int value);
};

class RadiusDecal
{
	int m_decalTemplate; // +0x00
	Shadow *m_shadow; // +0x04
	bool m_empty; // +0x08

public:
	void setOpacity(Real o);
};

// ?setOpacity@RadiusDecal@@QAEXM@Z
void RadiusDecal::setOpacity(Real o)
{
	if (m_shadow)
	{
		m_shadow->setOpacity((Int)(o * 255.0f));
	}
}
