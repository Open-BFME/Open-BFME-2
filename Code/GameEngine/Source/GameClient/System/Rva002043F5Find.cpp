// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva002043F5Get@@YG... @0x002043F5 72B: wrapper building a local AsciiString
// from a const char* then returning TheParticleSystemManager->findTemplate.
// Evidence: calls StringBase ctor PBD 0x00037BA0, global TheParticleSystemManager
// 0x00DFDD04, findTemplate 0x001F90DA, releaseBuffer 0x00036410; ret 4 with
// EH scope for the local; vtable 0x007E39F4 slot 6 reference.

#include "ascii_string.h"

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
    ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};

extern ParticleSystemManager *TheParticleSystemManager;

ParticleSystemTemplate *__stdcall Rva002043F5Get(const char *name)
{
    AsciiString tmp(name);
    return TheParticleSystemManager->findTemplate(tmp);
}
