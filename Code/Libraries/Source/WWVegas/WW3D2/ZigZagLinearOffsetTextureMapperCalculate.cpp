// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// ?Calculate_Texture_Matrix@ZigZagLinearOffsetTextureMapperClass@@UAEXAAVMatrix4@@@Z 0x00183240 361B
// ZigZagLinearOffsetTextureMapperClass::Calculate_Texture_Matrix retail 0x00183240 361 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D56F8 class of INI ctor 0x001830D0; gap between Reset 0x00183220 and Edge ctor 0x001833B0; ZH donor GeneralsMD WW3D2 mapper.cpp ZigZag Calculate.

#include "../../../../../reference/shims/bfme_matrix3d_link/vector4.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

void ZigZagLinearOffsetTextureMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta =  now - LastUsedSyncTime;
	LastUsedSyncTime=now;
	Remainder+=delta;

	float offset_u=0.0f;
	float offset_v=0.0f;

	if (Period>0.0f)
	{
		// figure out the fractional number of periods
		int num_periods=(int) (Remainder/Period);
		Remainder-=num_periods*Period;

		float time=0.0f;
		if (Remainder>Half_Period) {
			time=Period-Remainder;
		} else {
			time=Remainder;
		}
		offset_u=Speed.U * time;
		offset_v=Speed.V * time;
	}

	// Set up the offset matrix
	tex_matrix.Make_Identity();

	// According to the docs this should work since its 2D
	// otherwise change to translate
	tex_matrix[0].Z = offset_u;
	tex_matrix[0].X = Scale.X;
	tex_matrix[1].Z = offset_v;
	tex_matrix[1].Y = Scale.Y;
}
