// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva00204386Get@@YGPAVParticleSystemTemplate@@PBD@Z @0x00204386 111B
// slot 1 of vtable 0x00BE39F4 (RVA 0x007E39F4) but body uses no this: free __stdcall
// clone helper like Rva002043F5Get plus new(0xD4) and FXParticleSystem copy ctor.
// Evidence: StringBase PBD 0x00037BA0, TheParticleSystemManager 0x009FDD04,
// findTemplate 0x001F90DA, releaseBuffer 0x00036410, new 0x0002FDA0,
// ParticleSystemTemplate copy ctor 0x001FCE6B, EH prolog 0x00629188, ret 4.
#include "ascii_string.h"

class ParticleSystemTemplate;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};

extern ParticleSystemManager *TheParticleSystemManager;

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);

private:
	char m_pad[0xD4];
};

}

ParticleSystemTemplate * __stdcall Rva00204386Get(const char *name)
{
	ParticleSystemTemplate *found;
	{
		AsciiString tmp(name);
		found = TheParticleSystemManager->findTemplate(tmp);
	}
	if (!found)
		return 0;
	return (ParticleSystemTemplate *)new FXParticleSystem::ParticleSystemTemplate(*(FXParticleSystem::ParticleSystemTemplate *)found);
}
