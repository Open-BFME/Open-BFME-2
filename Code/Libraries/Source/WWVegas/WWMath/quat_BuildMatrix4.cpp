// cl: /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?Build_Matrix4@@YA?AVMatrix4@@ABVQuaternion@@@Z, retail 0x00717FA0, 375 bytes.
// Dedicated TU: quat.cpp builds the whole unit at /arch:SSE2 for its 17 matched
// bodies, but this one only matches at /arch:SSE (single-precision SSE keeps the
// double 1.0 constant on x87; SSE2 schedules the FPU tail differently). Source is
// verbatim from the BFME1 ancestor (Code/Libraries/Source/WWVegas/WWMath/quat.cpp,
// Build_Matrix4); Matrix4x4 is a typedef to Matrix4 there, so the spelling is the
// same body quat.cpp already carries unmatched.
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
#include "quat.h"
#include "matrix3d.h"
#include "matrix4.h"
#include "wwmath.h"

Matrix4 Build_Matrix4(const Quaternion & q)
{
	Matrix4 m;

	// initialize the rotation sub-matrix
	m[0][0] = (float)(1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]));
	m[0][1] = (float)(2.0 * (q[0] * q[1] - q[2] * q[3]));
	m[0][2] = (float)(2.0 * (q[2] * q[0] + q[1] * q[3]));

	m[1][0] = (float)(2.0 * (q[0] * q[1] + q[2] * q[3]));
	m[1][1] = (float)(1.0 - 2.0f * (q[2] * q[2] + q[0] * q[0]));
	m[1][2] = (float)(2.0 * (q[1] * q[2] - q[0] * q[3]));

	m[2][0] = (float)(2.0 * (q[2] * q[0] - q[1] * q[3]));
	m[2][1] = (float)(2.0 * (q[1] * q[2] + q[0] * q[3]));
	m[2][2] = (float)(1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]));

	// no translation
	m[0][3] = m[1][3] = m[2][3] = 0.0f;

	// last row
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
	m[3][3] = 1.0f;
	return m;
}
