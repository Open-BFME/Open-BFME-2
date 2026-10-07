// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// BFME 1 W3DProjectedShadowDecalHelpers.cpp, donor revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20, compiled with BFME 2 flags above.
// These file-static algorithms come from ZH queueDecal: flatten/normalise the
// transform axes, and find the extrema of four projected corner coordinates.
// Their original private names are unknown, so names retain target addresses.
// Native axes body 0x108E7A..0x108FBD (323B), Ghidra FUN_00508e7a. Calls at
// 0x10ACAB / 0x10ACBF / 0x10CB9C pass Matrix3D in ESI and two Vector3 outputs
// in ECX/EDX. X/Y basis elements are +0/+0x10 and +4/+0x14; output Z is zero.
// Native extrema body 0x108E33..0x108E7A (71B), immediately after the thunk
// at 0x108E28. Inputs use XMM1/2/3 and one stack float; hidden Vector2 output
// is EAX. The projected-range body at 0x108FBD inlines the same extrema logic.
// A compiler-visible caller preserves both private conventions, as MSVC 7.1
// derives them from same-unit calls. It is an emission pattern, not a retail
// caller recovery. All body bytes and compiler float literals are verified.
#include "wwmath.h"

// Scoped storage views use the evidenced 12B vector, 8B pair, and 3x4 matrix
// representations without defining copies of the public math-library methods.
class Rva00108E7AVector
{
public:
    float X, Y, Z;
    WWINLINE Rva00108E7AVector() {}
    WWINLINE Rva00108E7AVector(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE Rva00108E7AVector &operator=(const Rva00108E7AVector &v)
    { X=v.X; Y=v.Y; Z=v.Z; return *this; }
    WWINLINE Rva00108E7AVector &operator*=(float k)
    { X=X*k; Y=Y*k; Z=Z*k; return *this; }
    WWINLINE void Set(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE float Length() const { return WWMath::Sqrt(X*X+Y*Y+Z*Z); }
};
class Rva00108E33Pair
{
public:
    float X, Y;
    WWINLINE Rva00108E33Pair(float x, float y) { X=x; Y=y; }
    WWINLINE Rva00108E33Pair &operator=(const Rva00108E33Pair &v)
    { X=v.X; Y=v.Y; return *this; }
};
class Rva00108E7AMatrix
{
public:
    float Row[3][4];
    WWINLINE Rva00108E7AVector Get_X_Vector() const
    { return Rva00108E7AVector(Row[0][0],Row[1][0],Row[2][0]); }
    WWINLINE Rva00108E7AVector Get_Y_Vector() const
    { return Rva00108E7AVector(Row[0][1],Row[1][1],Row[2][1]); }
};

static void decalAxesRva00108E7A(const Rva00108E7AMatrix &objXform, Rva00108E7AVector &uVector, Rva00108E7AVector &vVector)
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

static Rva00108E33Pair minMax4Rva00108E33(float a, float b, float c, float d)
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
	return Rva00108E33Pair(lo, hi);
}

// ?Rva00108E33EmissionPattern absent-from-retail
void Rva00108E33EmissionPattern(const Rva00108E7AMatrix &m, Rva00108E7AVector &u, Rva00108E7AVector &v,
    float a, float b, float c, float d, Rva00108E33Pair *out)
{
    decalAxesRva00108E7A(m, u, v);
    out[0] = minMax4Rva00108E33(a, b, c, d);
    out[1] = minMax4Rva00108E33(b, c, d, a);
}
