// cl: /DNDEBUG /MD
//
// ??0RadiusDecal@@QAE@XZ, retail 0x00330DA4, 22 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/RadiusDecal.cpp,
// matched 17 bytes there): null template/shadow, empty true, extra dword at
// +0x0C zeroed. Retail zeroes the extra through xmm0 (SSE float store).

class RadiusDecal
{
	int m_decalTemplate; // +0x00
	void *m_shadow; // +0x04
	bool m_empty; // +0x08
	float m_extra; // +0x0C

public:
	RadiusDecal();
};

// ??0RadiusDecal@@QAE@XZ
RadiusDecal::RadiusDecal() :
	m_decalTemplate(0),
	m_shadow(0),
	m_empty(true),
	m_extra(0.0f)
{
}
