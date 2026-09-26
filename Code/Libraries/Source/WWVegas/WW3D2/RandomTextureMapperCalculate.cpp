// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// ?Calculate_Texture_Matrix@RandomTextureMapperClass@@UAEXAAVMatrix4@@@Z 0x001838B0 393B
// RandomTextureMapperClass::Calculate_Texture_Matrix retail 0x001838B0 393 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D57F4 class of INI ctor 0x001867A0; gap between Reset 0x00183890 and D3DXMATRIX ctor 0x00183A40; ZH donor GeneralsMD WW3D2 mapper.cpp Random Calculate with randomize inlined.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

extern Random4Class rand4;

void RandomTextureMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta=now-LastUsedSyncTime;
	LastUsedSyncTime=now;
	Remainder+=delta;

	if (FPMS!=0.0f) {

		int num_frames=(int) (Remainder*FPMS);

		if (num_frames!=0) {
			CurrentAngle=2*WWMATH_PI*rand4.Get_Float();
			Center.U=rand4.Get_Float();
			Center.V=rand4.Get_Float();
			Remainder-=num_frames/FPMS;
		}
	}

	// Set up the random matrix - start with a rotation matrix of 'CurrentAngle' about the Z-axis.
	// We apply the scale matrix to the right of the unscaled rotate/offset matrix, because we
	// don't want the scaling to affect the offset. So we get:
	// [  c -s  uoff ]     [ Sx  0   0 ]     [ cSx -sSy uoff ]
	// [  s  c  voff ]  *  [ 0   Sy  0 ]  =  [ sSx  cSy voff ]
	// [  0  0   1   ]     [ 0   0   1 ]     [  0    0    1  ]
	float c = cosf(CurrentAngle);
	float s = sinf(CurrentAngle);
	tex_matrix.Make_Identity();
	tex_matrix[0][0] = c * Scale.X;
	tex_matrix[0][1] = -s * Scale.Y;
	tex_matrix[1][0] = s * Scale.X;
	tex_matrix[1][1] = c * Scale.Y;

	// Offset matrix
	float uoff = Center.U + Remainder * Speed.U;
	float voff = Center.V + Remainder * Speed.V;
	uoff = fmodf(uoff, 1.0f);
	voff = fmodf(voff, 1.0f);
	tex_matrix[0].Z = uoff;
	tex_matrix[1].Z = voff;
}
