// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// ?Calculate_Texture_Matrix@EdgeMapperClass@@UAEXAAVMatrix4@@@Z 0x00183540 214B
// EdgeMapperClass::Calculate_Texture_Matrix retail 0x00183540 214 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D5738 class of INI ctor 0x00183410; gap between Reset 0x00183520 and WSEnv ctor 0x00183620; ZH donor GeneralsMD WW3D2 mapper.cpp Edge Calculate with Init expanded to direct stores.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

void EdgeMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int now=WW3D::Get_Sync_Time();

	float delta=(now-LastUsedSyncTime)*0.001f;
	LastUsedSyncTime=now;

	VOffset+=delta*VSpeed;
	VOffset-=WWMath::Floor(VOffset);
	float vo = VOffset;

	// takes the Z component and
	// uses it to index the texture
	tex_matrix[0].X = 0.0f;
	tex_matrix[0].Y = 0.0f;
	tex_matrix[0].Z = 0.5f;
	tex_matrix[0].W = 0.5f;
	tex_matrix[1].W = vo;
	tex_matrix[1].X = 0.0f;
	tex_matrix[1].Y = 0.0f;
	tex_matrix[1].Z = 0.0f;
	tex_matrix[2].X = 0.0f;
	tex_matrix[2].Y = 0.0f;
	tex_matrix[2].Z = 1.0f;
	tex_matrix[2].W = 0.0f;
	tex_matrix[3].X = 0.0f;
	tex_matrix[3].Y = 0.0f;
	tex_matrix[3].Z = 0.0f;
	tex_matrix[3].W = 1.0f;
}
