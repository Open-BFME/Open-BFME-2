// cl: /Ireference/shims/bfme2_part_emt /DNDEBUG /MD /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/shims /Ireference/shims/bfmeparticlequat /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeparticlehandle

// BFME's ParticleEmitterClass visibility wrappers. Retail's RenderObjClass
// interface has an extra Set_Visible scene token relative to the later public
// header. BFME2 RenderObjClass has one fewer slot before Set_Visible vs BFME1
// (retail calls [edx+0x210] slot 132, donor [edx+0x214] slot 133).

#include "../../../../../reference/shims/bfme2renderobj/rendobj.h"
#include "part_emt.h"

// ?Set_Visible@ParticleEmitterClass@@UAEXHH@Z
void ParticleEmitterClass::Set_Visible(int onoff, int sceneToken)
{
	RenderObjClass::Set_Visible(onoff, sceneToken);
	Update_On_Visibilty();
}

// ?Set_Hidden@ParticleEmitterClass@@UAEXH@Z
void ParticleEmitterClass::Set_Hidden(int onoff)
{
	if (onoff) {
		Bits &= ~IS_NOT_HIDDEN;
	} else {
		Bits |= IS_NOT_HIDDEN;
	}
	Update_On_Visibilty();
}

// ?Set_Animation_Hidden@ParticleEmitterClass@@UAEXH@Z
void ParticleEmitterClass::Set_Animation_Hidden(int onoff)
{
	if (onoff) {
		Bits &= ~IS_NOT_ANIMATION_HIDDEN;
	} else {
		Bits |= IS_NOT_ANIMATION_HIDDEN;
	}
	Update_On_Visibilty();
}

// Set_Force_Visible is a header inline in retail: other units emit select-any
// copies, so a strong definition here was a duplicate in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is not
// retail code. Qualified call so the virtual dispatch does not hide the copy.
#pragma inline_depth(0)
// ?bfmeEmitParticleEmitterVisibilityWrappers@@YAXPAVParticleEmitterClass@@@Z present-unmatched
void bfmeEmitParticleEmitterVisibilityWrappers(ParticleEmitterClass *particleEmitter)
{
	particleEmitter->ParticleEmitterClass::Set_Force_Visible(0);
}
#pragma inline_depth()
