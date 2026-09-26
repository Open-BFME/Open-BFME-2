// cl: /Ireference/shims/bfmeparticlequat /G7 /Ireference/shims/bfme2renderobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// ?Update_Cached_Bounding_Volumes@ParticleEmitterClass@@EBEXXZ @0x001A1D70 97B via BFME1 donor part_emt.cpp Update_Cached_Bounding_Volumes
// evidence: vslot 127 of ParticleEmitterClass vtable 0x007D69F8; sphere4C box5C bits20000 match donor Init Center Extent Validate; callees Get_Position rowed
#include "rendobj.h"
#include "quat.h"
#include "part_emt.h"
#include "wwdebug.h"
#include "ww3d.h"
#include "assetmgr.h"
#include "part_ldr.h"
#include "w3derr.h"
#include "scene.h"
#include "texture.h"
#include "wwprofile.h"

void ParticleEmitterClass::Update_Cached_Bounding_Volumes(void) const
{
	CachedBoundingSphere.Init(Get_Position(),0.0);
	CachedBoundingBox.Center = Get_Position();
	CachedBoundingBox.Extent.Set(0,0,0);
	Validate_Cached_Bounding_Volumes();
}
