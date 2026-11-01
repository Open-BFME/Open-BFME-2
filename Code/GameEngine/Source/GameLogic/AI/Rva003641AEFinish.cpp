// cl: /DNDEBUG /MD
//
// ?rva003641AE@Path@@QAEHMM@Z @0x003641AE (68B).
// Clamp a scaled product into [1,128]: the product of the two float factors
// and the two globals is rounded to nearest via an x87 fld/fistp helper, then
// clamped.  Evidence: callers 0x00364FBA and 0x0036596A; globals 0x00BC9D14
// and 0x00C17274 are the float factors; IAT ceil at 0x00BBA578.
// The double accumulator keeps retail's x87 operand order (fld b first,
// fmul g1, fmul a, fmul g2); a plain float chain is reassociated by the
// compiler.  The fistp helper is required because a plain (int) cast emits
// _ftol2 under /O1.

#include <math.h>

// Native factors at VA BC9D14 and C17274; original identifiers unknown.
float BfmePathArcFactor0 = 0.03333333507180214f;
float g_00C17274 = 5.092957973480225f;

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// Retail caller 0x00364FAD and WB F24175 both set ECX to Path this.
#include "../../../Include/GameLogic/PathfindPath.h"

int Path::rva003641AE(float a, float b)
{
	double d = b;
	b = (float)ceil((a * (d * BfmePathArcFactor0)) * g_00C17274);
	int i = fast_float2long_round(b);
	if (i < 1)
		i = 1;
	if (i > 128)
		i = 128;
	return i;
}
