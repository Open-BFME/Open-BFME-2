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

// ?Calculate_Texture_Matrix@LinearOffsetTextureMapperClass@@UAEXAAVMatrix4@@@Z 0x001822E0 337B
// LinearOffsetTextureMapperClass::Calculate_Texture_Matrix retail 0x001822E0 337 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D577C class of INI ctor 0x00184170 and 0x007D581C BumpEnv; ZH donor GeneralsMD WW3D2 mapper.cpp Linear Calculate.

#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
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

// Native BFME1 donor 9cb clamp semantics; keep this inline operation local.
static inline float mapperClamp(float value, float low, float high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

void LinearOffsetTextureMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
	float del = (float)delta;
	float offset_u = CurrentUVOffset.X + UVOffsetDeltaPerMS.X * del;
	float offset_v = CurrentUVOffset.Y + UVOffsetDeltaPerMS.Y * del;

	// We need to clamp these texture coordinates to a reasonable range so the hardware doesn't
	// choke on them. We do this in one of two ways:
	// If ClampFix is not TRUE we use the fractional part of the offset, restricting it between
	// 0 and 1 with wraparound. This works well for tiled textures.
	// If ClampFix is TRUE we clamp the offsets between -Scale and +Scale with no wraparound.
	// This works well for clamped textures.
	if (!ClampFix) {
		offset_u = offset_u - floorf(offset_u);
		offset_v = offset_v - floorf(offset_v);
	} else {
		offset_u = mapperClamp(offset_u, -Scale.X, Scale.X);
		offset_v = mapperClamp(offset_v, -Scale.Y, Scale.Y);
	}

	// Set up the offset matrix
	tex_matrix.Make_Identity();

	// According to the docs this should work since its 2D
	// otherwise change to translate
	tex_matrix[0].Z=offset_u;
	tex_matrix[0].X=Scale.X;
	tex_matrix[1].Z=offset_v;
	tex_matrix[1].Y=Scale.Y;

	// Update state
	CurrentUVOffset.X = offset_u;
	CurrentUVOffset.Y = offset_v;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}
