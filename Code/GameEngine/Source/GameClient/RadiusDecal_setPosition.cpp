// cl: /DNDEBUG /MD
//
// ?setPosition@RadiusDecal@@QAEXABUCoord3D@@@Z, retail 0x00330DFD, 24 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/RadiusDecal.cpp,
// matched 33 bytes there): when the shadow holder at +0x04 is present, copy
// the world-space centre into its Coord3D at +0x08.

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct RadiusDecalShadow
{
	unsigned char m_pad[8];
	Coord3D m_position; // +0x08
};

class RadiusDecal
{
	int m_decalTemplate; // +0x00
	RadiusDecalShadow *m_shadow; // +0x04
	bool m_empty; // +0x08

public:
	void setPosition(const Coord3D &pos);
};

// ?setPosition@RadiusDecal@@QAEXABUCoord3D@@@Z
void RadiusDecal::setPosition(const Coord3D &pos)
{
	if (m_shadow)
	{
		m_shadow->m_position = pos;
	}
}
