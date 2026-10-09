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

// ?Calculate_Texture_Matrix@StepLinearOffsetTextureMapperClass@@UAEXAAVMatrix4@@@Z 0x00182E80 400B
// StepLinearOffsetTextureMapperClass::Calculate_Texture_Matrix retail 0x00182E80 400 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies; flags are neighbour // cl: plus /G7.
// Evidence: vtable slot 9 offset 0x24 of 0x007D56B0 class of INI ctor 0x00182D30; gap between Reset 0x00182E60 and ZigZag ctor 0x00183010; ZH donor GeneralsMD WW3D2 mapper.cpp Step Calculate.

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

// Same donor Vector2 component multiplication, without a competing operator.
static inline Vector2 mapperScaledStep(const Vector2 &step, float scale)
{
    float x = step.X * scale;
    float y = step.Y * scale;
    return Vector2(x, y);
}

void StepLinearOffsetTextureMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta =  now - LastUsedSyncTime;
	LastUsedSyncTime=now;

	Remainder+=delta;
	int num_steps=(int) (StepsPerMilliSec*Remainder);

	if (num_steps!=0)
	{
		CurrentStep+=mapperScaledStep(Step,num_steps);
		Remainder-=num_steps/(float)StepsPerMilliSec;
	}

	// We need to clamp these texture coordinates to a reasonable range so the hardware doesn't
	// choke on them. We do this in one of two ways:
	// If ClampFix is not TRUE we use the fractional part of the offset, restricting it between
	// 0 and 1 with wraparound. This works well for tiled textures.
	// If ClampFix is TRUE we clamp the offsets between -Scale and +Scale with no wraparound.
	// This works well for clamped textures.
	if (!ClampFix) {
		CurrentStep.U -= floorf(CurrentStep.U);
		CurrentStep.V -= floorf(CurrentStep.V);
	} else {
		CurrentStep.U = mapperClamp(CurrentStep.U, -Scale.X, Scale.X);
		CurrentStep.V = mapperClamp(CurrentStep.V, -Scale.Y, Scale.Y);
	}

	// Set up the offset matrix
	tex_matrix.Make_Identity();

	// According to the docs this should work since its 2D
	// otherwise change to translate
	tex_matrix[0].Z = CurrentStep.U;
	tex_matrix[0].X = Scale.X;
	tex_matrix[1].Z = CurrentStep.V;
	tex_matrix[1].Y = Scale.Y;
}
