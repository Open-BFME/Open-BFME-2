// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// ?Calculate_Texture_Matrix@RotateTextureMapperClass@@UAEXAAVMatrix4@@@Z 0x00182800 416B
// RotateTextureMapperClass::Calculate_Texture_Matrix retail 0x00182800 416 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D560C class of INI ctor 0x001826D0; gap between Reset 0x001827E0 and Sine ctor 0x001829A0; ZH donor GeneralsMD WW3D2 mapper.cpp Rotate Calculate.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

void RotateTextureMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta =  now - LastUsedSyncTime;
	LastUsedSyncTime=now;

	CurrentAngle+=RadiansPerMilliSec * delta;
	CurrentAngle=fmodf(CurrentAngle,2*WWMATH_PI);
	if (CurrentAngle<0.0f) CurrentAngle+=2*WWMATH_PI;

	// Set up the rotation matrix
	float c,s;
	c=WWMath::Cos(CurrentAngle);
	s=WWMath::Sin(CurrentAngle);
	tex_matrix.Make_Identity();

	// subtract center
	// rotate
	// add center
	// then scale
	tex_matrix[0].Set(Scale.X * c, -Scale.X * s, -Scale.X * (c * Center.U - s * Center.V - Center.U), 0.0f);
	tex_matrix[1].Set(Scale.Y * s, Scale.Y * c, -Scale.Y * (s * Center.U + c * Center.V - Center.V), 0.0f);
}
