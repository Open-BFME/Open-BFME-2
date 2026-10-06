// cl: /DNDEBUG /MD
//
// ?Rva00330E15@RadiusDecal@@QAEXABUCoord3D@@@Z, retail 0x00330E15, 24 bytes.
// Dedicated TU.
//
// Opaque row: same shape as RadiusDecal::setPosition (0x330DFD, 24B) but
// copying the Coord3D into the shadow's second slot at +0x14 instead of +0x08.
// Class evidence: caller 0xB3198 invokes both bodies back-to-back on the same
// member at +0x1D0 (lea esi,[ecx+0x1D0]; call 0x330DFD; call 0x330E15).
// Signature evidence: identical (this, const Coord3D&) shape to setPosition.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct RadiusDecalShadowSecond
{
	unsigned char m_pad[0x14];
	Coord3D m_position; // +0x14
};

class RadiusDecal
{
	int m_decalTemplate; // +0x00
	RadiusDecalShadowSecond *m_shadow; // +0x04
	bool m_empty; // +0x08

public:
	void Rva00330E15(const Coord3D &pos);
};

// ?Rva00330E15@RadiusDecal@@QAEXABUCoord3D@@@Z
void RadiusDecal::Rva00330E15(const Coord3D &pos)
{
	if (m_shadow)
	{
		m_shadow->m_position = pos;
	}
}
