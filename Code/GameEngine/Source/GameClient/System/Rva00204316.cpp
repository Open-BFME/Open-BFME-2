// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00204316@Rva00204316@@QAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z,
// retail 0x00204316 (112 bytes, RET 8): a vtable slot (table 0x007E39E8)
// that registers a copy of a particle system template under a name: the
// 0xD4-byte copy (rowed ParticleSystemTemplate copy constructor 0x001FCE6B)
// and the name as a temporary string go to TheParticleSystemManager
// (0x00DFDD04) through 0x001FCF11 (pinned by address). The receiver is
// unused.
#include "ascii_string.h"

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);
private:
	unsigned char m_bytes[0xD4];
};
}

#include "../../../Include/GameClient/ParticleSys.h"

extern ParticleSystemManager *TheParticleSystemManager;

struct Rva00204316
{
	void rva00204316(const char *name, const FXParticleSystem::ParticleSystemTemplate &src);
};

void Rva00204316::rva00204316(const char *name, const FXParticleSystem::ParticleSystemTemplate &src)
{
	FXParticleSystem::ParticleSystemTemplate *tmpl = new FXParticleSystem::ParticleSystemTemplate(src);
	TheParticleSystemManager->rva001FCF11(AsciiString(name), tmpl);
}

// ??0Rva00203EFD@@QAE@XZ, retail 0x00203EFD (17B): the constructor of the
// object whose vtable 0x00BE39F4 holds the registration slot above
// (0x00204316) first, then the rowed 0x00204386, 0x00204C21, 0x00206DA4 and
// 0x002082F1 bodies. It clears the dword at +4 and the byte at +8. The
// vtable store is also inlined at 0x00204057, 0x00204C18 and 0x0020A31A.
// Owner unresolved; the slots' parameter types beyond slot 0 are not modelled.
class Rva00203EFD
{
public:
	Rva00203EFD();
	virtual void slot00(const char *name, const FXParticleSystem::ParticleSystemTemplate &src);
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
private:
	int m_04;
	bool m_08;
};

Rva00203EFD::Rva00203EFD()
{
	m_04 = 0;
	m_08 = false;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot00@Rva00203EFD@@UAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z=?rva00204316@Rva00204316@@QAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z")
#pragma comment(linker, "/alternatename:?slot04@Rva00203EFD@@UAEXXZ=?Rva00204386Get@@YGPAVParticleSystemTemplate@@PBD@Z")
#pragma comment(linker, "/alternatename:?slot08@Rva00203EFD@@UAEXXZ=?rva00204C21@Rva00204C21@@QAEXPBD@Z")
#pragma comment(linker, "/alternatename:?slot0C@Rva00203EFD@@UAEXXZ=?Rva00206DA4Enumerate@@YGXPAVRva002082F1Visitor@@@Z")
#pragma comment(linker, "/alternatename:?slot10@Rva00203EFD@@UAEXXZ=?Rva002082F1Enumerate@@YGXPAVRva002082F1Visitor@@@Z")
