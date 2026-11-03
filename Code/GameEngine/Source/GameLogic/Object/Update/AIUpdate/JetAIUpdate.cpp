// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// BFME 2 has no JetAIUpdate: game.dat holds no such module name and no row is one of its
// methods. One shared inline rests in this file until its address gets an approved unit,
// Matrix3D(bool) (0x0004C91A).
#include "matrix3d.h"

// A constructor has no address to take, so a call from a function nothing runs makes this
// unit emit the body.
static void constructMatrix()
{
	Matrix3D matrix(true);
}

extern const void *const g_matrixConstructorAnchor = (const void *)&constructMatrix;
