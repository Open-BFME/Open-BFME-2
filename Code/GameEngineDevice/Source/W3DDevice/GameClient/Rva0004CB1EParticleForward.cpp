// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?Rva0004CB1E@@YAXH@Z, retail 0x0004CB1E (20 bytes): forwards its argument to
// ParticleSystemManager's doParticles slot 16 (+0x40) when the manager exists.
// ParticleSys.h establishes the RenderInfoClass-reference slot contract; this
// row retains its existing integer argument ABI at the forwarding boundary.
#include "../../../../GameEngine/Include/GameClient/ParticleSys.h"

void Rva0004CB1E(int value)
{
	if (TheParticleSystemManager)
		TheParticleSystemManager->doParticles(*reinterpret_cast<RenderInfoClass *>(value));
}
