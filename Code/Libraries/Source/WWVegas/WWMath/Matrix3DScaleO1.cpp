// cl: /O1 /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Matrix3D's three inline Scale overloads, out of line as one /O1 unit
// emitted them.
//
// Retail keeps them packed in header order: Scale(float) at 0x00074643 (its
// row compiles from shattersystem.cpp), Scale(float, float, float) at
// 0x000746C8 and Scale(Vector3 &) at 0x00074754. The three-float overload
// keeps an EBP frame that only /O1 reproduces under /arch:SSE /G7; the Vector3
// one is the same under /O1 and /O2. No retail call reaches the latter two.
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "matrix3d.h"

// The overloads are header inlines; the anchor makes this unit emit its
// copies for the rows. It is not retail code.
#pragma inline_depth(0)
// ?_bfmeMatrix3DScaleAnchor@@YAXAAVMatrix3D@@AAVVector3@@@Z absent-from-retail
void _bfmeMatrix3DScaleAnchor(Matrix3D &m, Vector3 &scale)
{
	m.Scale(1.0f, 1.0f, 1.0f);
	m.Scale(scale);
}
#pragma inline_depth()
