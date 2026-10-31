// cl: /Ireference/shims/bfme2_part_emt /DNDEBUG /MD /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/shims /Ireference/shims/bfmeparticlequat /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeparticlehandle
// ?Update_On_Visibilty@ParticleEmitterClass@@MAEXXZ @ 0x001A2260 (91B).
//
// BFME1 donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp
// (ParticleEmitterClass::Update_On_Visibilty via Is_Not_Hidden plus Start and Stop).
// Evidence: vtable slot 132 offset 0x210 of 0x007D69F8 for ctor 0x001A1070 class;
// retail calls virtual plus 0x184 twice and tail-jmps to Start 0x001A1B20;
// Active at plus 0x110 and IsInScene at plus 0x129 and IsInvisible at plus 0x130
// match 0xC4 base layout already proved by Set_Name at 0x001A2220;
// Stop and Is_Stopped are inlined as store plus compares with no direct calls.
#include "../../../../../reference/shims/bfme2renderobj/rendobj.h"
#include "part_emt.h"

void ParticleEmitterClass::Update_On_Visibilty(void)
{
	if (Is_Not_Hidden_At_All() && !IsInvisible && !Active && IsInScene) {
		Start();
	} else if ((!Is_Not_Hidden_At_All() || IsInvisible) && Active) {
		Active = false;
	}
	return;
}
