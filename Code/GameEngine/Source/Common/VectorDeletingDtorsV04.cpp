// cl: /O1 /DNDEBUG /MD /EHsc
// Existing byte-exact wrappers with complete destructor providers.
// Unresolved owners remain in VectorDeletingDtorsV04_Unresolved.cpp.
// Class declarations, sizes, compiler flags and callee names are retained.
// Each native 75-byte body calls its complete destructor both directly and
// through the array cleanup callback, frees through the appropriate delete,
// and returns the receiver. No new class identity or layout is inferred.
//
//   ??_E        dtor        size  vtable#slot
//   0x003A9951  0x003A9F8A  0x18  0x00C1C188#0
//   0x003A9B97  0x003A9A8B  0x40  0x00C1C1B8#0
//   0x003A9DDE  0x003A9D43  0x14  0x00C1C1E8#0
//   0x003AA02D  0x003A9F8A  0x1C  0x00C1C218#0
//   0x003AA704  0x003AA6BD  0x48  0x00C1C270#0

#include <new>

#include "../../Include/GameClient/LifeEventModuleInfo.h"
namespace FXParticleSystem
{
}

namespace FXParticleSystem
{
class RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleInfo();
	virtual ~RenderObjectDrawModuleInfo();
private:
	char m_unmodelled_04[0x40 - 0x04];
};
}

namespace FXParticleSystem
{
class GpuDrawModuleInfo
{
public:
	GpuDrawModuleInfo();
	virtual ~GpuDrawModuleInfo();
private:
	char m_unmodelled_04[0x14 - 0x04];
};
}

namespace FXParticleSystem
{
class TerrainCollisionModuleInfo
{
public:
	TerrainCollisionModuleInfo();
	virtual ~TerrainCollisionModuleInfo();
private:
	char m_unmodelled_04[0x1C - 0x04];
};
}

class Rva003AA6BD
{
public:
	virtual ~Rva003AA6BD();
private:
	char m_unmodelled_04[0x48 - 0x04];
};

// ?<bfmeVectorDeleteAnchorV04> absent-from-retail
void bfmeVectorDeleteAnchorV04()
{
	new FXParticleSystem::LifeEventModuleInfo[2];
	new FXParticleSystem::RenderObjectDrawModuleInfo[2];
	new FXParticleSystem::GpuDrawModuleInfo[2];
	new FXParticleSystem::TerrainCollisionModuleInfo[2];
	new Rva003AA6BD[2];
}
