// cl: /O1 /DNDEBUG /MD
//
// RadiusDecal.cpp: the two shadow-position setters retail links from this TU
// (tu_map approved), folded from two split units with these exact flags.
// The shadow holder at +0x04 carries both Coord3D slots the setters write
// (+0x08 and +0x14).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/RadiusDecal.cpp,
// setPosition matched 33 bytes there): when the shadow holder at +0x04 is
// present, copy the world-space centre into its Coord3D at +0x08.

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct RadiusDecalShadow
{
	unsigned char m_pad[8];
	Coord3D m_position; // +0x08
	Coord3D m_position2; // +0x14
};

class RadiusDecal
{
	int m_decalTemplate; // +0x00
	RadiusDecalShadow *m_shadow; // +0x04
	bool m_empty; // +0x08

public:
	void setPosition(const Coord3D &pos);
	void Rva00330E15(const Coord3D &pos);
};

// ?setPosition@RadiusDecal@@QAEXABUCoord3D@@@Z, retail 0x00330DFD, 24 bytes.
void RadiusDecal::setPosition(const Coord3D &pos)
{
	if (m_shadow)
	{
		m_shadow->m_position = pos;
	}
}

// ?Rva00330E15@RadiusDecal@@QAEXABUCoord3D@@@Z, retail 0x00330E15, 24 bytes.
// Opaque row: same shape as RadiusDecal::setPosition (0x330DFD, 24B) but
// copying the Coord3D into the shadow's second slot at +0x14 instead of +0x08.
// Class evidence: caller 0xB3198 invokes both bodies back-to-back on the same
// member at +0x1D0 (lea esi,[ecx+0x1D0]; call 0x330DFD; call 0x330E15).
// Signature evidence: identical (this, const Coord3D&) shape to setPosition.
void RadiusDecal::Rva00330E15(const Coord3D &pos)
{
	if (m_shadow)
	{
		m_shadow->m_position2 = pos;
	}
}
