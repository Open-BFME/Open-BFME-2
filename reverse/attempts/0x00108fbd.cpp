// ?projectRangesRva00108FBD@@YAXABVVector3@@0MMMMAAVVector2@@1@Z
// partial score=0.5 date=2026-10-07
// BFME2 native 0x108FBD..0x109129 (364B), Ghidra FUN_00508fbd.
// BFME1 donor 1399ad37 compiled /O1 /arch:SSE /G7 emits 359B.
// Native private ABI ECX/EAX axes EDX/ESI outputs plus four stack floats.
// /G6 /G5 /O2 variants and scoped storage/copy-shape trials did not match.
// Native retains pair-return temporaries with integer copies; this reference
// collapses them into direct SSE stores and differs in scheduling/frame.
// Neighboring axes323 and extrema71 are already rowed in the scoped helper TU.
// cl: -O1 -arch:SSE -G7 -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// File-static helpers of BFME's W3DProjectedShadow.cpp TU (retail
// 0x007AF710 / 0x007AF940), the eventual home of the projected-shadow
// family (callers 0x007B23F0 and 0x007B4FE0). MSVC 7.1 gives a file-static
// function whose address is not taken a private register convention when its
// caller is in the same TU: 0x007AF710 takes four stack floats and returns a
// Vector2 through a hidden pointer in ECX; 0x007AF940 takes axisA in ECX,
// axisB in EAX, xr in EDI, yr in ESI plus four stack floats, and its caller
// pops the stack. Both conventions come out of the compiler by themselves
// here (docs/shape_levers.md, "Compiler-private ABI").
// Types: the callers pass two adjacent 12-byte vectors (Vector3, frame of
// six 12-byte objects at 0x48) and zero two adjacent 8-byte outputs (Vector2).
// The names keep the address: no caller, string or Zero Hour twin names them.
#include "vector2.h"
#include "vector3.h"
#include "matrix3d.h"

// Retail 0x007AF7E0 (EXACT here; claimed by another lane, not landed): Zero Hour queueDecal's decal axes from the object
// transform (x axis flattened and normalised, v = u rotated by -90 degrees;
// falls back to the y axis, then to (0,-1,0)).
static void decalAxesRva00108E7A(const Matrix3D &objXform, Vector3 &uVector, Vector3 &vVector)
{
	uVector = objXform.Get_X_Vector();
	uVector.Z = 0.0f;
	float vecLength = uVector.Length();
	if (vecLength != 0.0f) {
		uVector *= 1.0f / vecLength;
		vVector.Set(uVector.Y, -uVector.X, 0.0f);
	} else {
		vVector = objXform.Get_Y_Vector();
		vVector.Z = 0.0f;
		vecLength = vVector.Length();
		if (vecLength != 0.0f)
			vVector *= 1.0f / vecLength;
		else
			vVector.Set(0.0f, -1.0f, 0.0f);
		uVector.Set(-vVector.Y, vVector.X, 0.0f);
	}
}

static Vector2 minMax4Rva00108E33(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Vector2(lo, hi);
}

static void projectRangesRva00108FBD(const Vector3 &axisA, const Vector3 &axisB, float sizeA, float sizeB,
	float offA, float offB, Vector2 &xr, Vector2 &yr)
{
	Vector3 a0 = -((offA + 0.5f) * sizeA) * axisA;
	Vector3 a1 = (0.5f - offA) * sizeA * axisA;
	Vector3 b0 = -((offB + 0.5f) * sizeB) * axisB;
	Vector3 b1 = (0.5f - offB) * sizeB * axisB;
	Vector3 c0 = b0 + a0;
	Vector3 c1 = b0 + a1;
	Vector3 c2 = b1 + a1;
	Vector3 c3 = b1 + a0;
	xr = minMax4Rva00108E33(c0.X, c1.X, c2.X, c3.X);
	yr = minMax4Rva00108E33(c0.Y, c1.Y, c2.Y, c3.Y);
}

// ?Rva00108FBDTrialCaller absent-from-retail
void Rva00108FBDTrialCaller(const Vector3 &a, const Vector3 &b, float s0, float s1, float s2, float s3,
	Vector2 *out)
{
	Matrix3D m(true);
	Vector3 u, v;
	decalAxesRva00108E7A(m, u, v);
	Vector2 xr(0, 0), yr(0, 0);
	projectRangesRva00108FBD(u, v, s0, s1, s2, s3, xr, yr);
	projectRangesRva00108FBD(b, a, s1, s0, s3, s2, out[0], out[1]);
	out[2] = xr;
	out[3] = yr;
}
