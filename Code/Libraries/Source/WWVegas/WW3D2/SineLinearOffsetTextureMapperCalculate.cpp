// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// ?Calculate_Texture_Matrix@SineLinearOffsetTextureMapperClass@@UAEXAAVMatrix4@@@Z 0x00182BA0 226B
// SineLinearOffsetTextureMapperClass::Calculate_Texture_Matrix retail 0x00182BA0 226 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D5658 class of INI ctor 0x00182A30; gap between Reset 0x00182B80 and Step ctor 0x00182C90; Apply slot 5 calls [eax+0x24]; ZH donor GeneralsMD WW3D2 mapper.cpp Sine Calculate.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

void SineLinearOffsetTextureMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta =  now - LastUsedSyncTime;
	LastUsedSyncTime=now;

	const float ms_to_radians=2*WWMATH_PI/1000.0f;

	CurrentAngle+=delta*ms_to_radians;

	float offset_u=UAFP.X*sin(UAFP.Y*CurrentAngle+UAFP.Z*WWMATH_PI);
	float offset_v=VAFP.X*sin(VAFP.Y*CurrentAngle+VAFP.Z*WWMATH_PI);

	// Set up the offset matrix
	tex_matrix.Make_Identity();

	// According to the docs this should work since its 2D
	// otherwise change to translate
	tex_matrix[0].Z = offset_u;
	tex_matrix[0].X = Scale.X;
	tex_matrix[1].Z = offset_v;
	tex_matrix[1].Y = Scale.Y;
}
