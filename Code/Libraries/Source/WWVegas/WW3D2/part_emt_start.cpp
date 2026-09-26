// cl: /G7 /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Start@ParticleEmitterClass@@QAEXXZ @0x001A1B20 176B via BFME1 donor part_emt.cpp Start between Reset and Stop
// evidence: gap between ?Reset (0x001A1A80) and ?Stop (0x001A1BD0) in same TU; BFME1 donor order Reset/Start/Stop matches; callers at 0x001A228D and 0x001A2660
#include "rendobj.h"
#include "part_emt.h"
#include "wwdebug.h"
#include "ww3d.h"
#include "assetmgr.h"
#include "part_ldr.h"
#include "w3derr.h"
#include "scene.h"
#include "texture.h"
#include "wwprofile.h"

void ParticleEmitterClass::Start(void)
{
	// Note:  This flag needs to be set first thing, otherwise
	// getting the transform will result in an 'update_x' call
	// which in turn results in a 'Set_Animation_Hidden' call, which
	// in turn will cause the Update_Visibilty function to call
	// this method.  And then... Stack Overflow!  ;)
	Active = true;

	// Initialize previous transform:
	PrevQ = Build_Quaternion(Get_Transform());
	PrevOrig = Get_Transform().Get_Translation();

	// Reset the number of particles to emit (if necessary)
	if (IsComplete == true) {
		ParticlesLeft = MaxParticles;
		IsComplete = false;
	}

	// This is to keep track of particles so that
	// the line segments can start and stop properly
	GroupID++;
	Buffer->Set_Current_GroupID(GroupID);
}
