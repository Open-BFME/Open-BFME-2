// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// ?Calculate_Texture_Matrix@ClassicEnvironmentMapperClass@@UAEXAAVMatrix4@@@Z 0x00183340 105B
// ClassicEnvironmentMapperClass::Calculate_Texture_Matrix retail 0x00183340 105 bytes.
// Dedicated TU; flags are mapper neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D3170 Classic and 0x007D31C0 Environment; gap between ZigZag Calculate 0x00183240+248 and Edge ctor 0x001833B0; ZH donor GeneralsMD WW3D2 mapper.cpp Classic Calculate Init expanded to direct stores.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

void ClassicEnvironmentMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	tex_matrix[0].X = 0.5f;
	tex_matrix[0].Y = 0.0f;
	tex_matrix[0].Z = 0.0f;
	tex_matrix[0].W = 0.5f;
	tex_matrix[1].X = 0.0f;
	tex_matrix[1].Y = 0.5f;
	tex_matrix[1].Z = 0.0f;
	tex_matrix[1].W = 0.5f;
	tex_matrix[2].X = 0.0f;
	tex_matrix[2].Y = 0.0f;
	tex_matrix[2].Z = 1.0f;
	tex_matrix[2].W = 0.0f;
	tex_matrix[3].X = 0.0f;
	tex_matrix[3].Y = 0.0f;
	tex_matrix[3].Z = 0.0f;
	tex_matrix[3].W = 1.0f;
}
