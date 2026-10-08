// cl: /MD /EHsc /DNDEBUG
// ?rva00094D44@@YGMMMM@Z @0x00094D44 100B: free function returning a float
// from three float args. Defaults to the 999999.0f compiler literal (retail
// .rdata 0xBC7484); when the .data pointer global is set, overrides with the
// dot of its +0x84 16-byte record against (a, b, c) plus the record tail, in
// retail evaluation order (z*c + y*b + x*a + w). Honest address-derived name;
// boundary verified (push ebp at 0x94D44, fld + leave + ret 0xC at end).
struct RvaVec4B { float x; float y; float z; float w; };
struct RvaDE4880Owner { unsigned char m_pad[0x84]; RvaVec4B m_84; };
static RvaDE4880Owner *g_00DE4880;
float __stdcall rva00094D44(float a, float b, float c)
{
	RvaDE4880Owner *g = g_00DE4880;
	float r = 999999.0f;
	if (g) {
		RvaVec4B v = g->m_84;
		r = v.z * c;
		r += v.y * b;
		r += v.x * a;
		r += v.w;
	}
	return r;
}

// BFME1 34f59164 Rva006E1CA0VectorLength.cpp supplies the clean expression.
// Target evidence independently establishes native94DE5..94E2C (71B RET0),
// one __cdecl pointer argument, float loads0/4/8, sqrt thunk62921C and ST0
// result. The owner/type name is unknown; retain an address-qualified view.
#include <math.h>

class Rva00094DE5Vector
{
public:
 static float length(const Rva00094DE5Vector *vector);
private:
 float x;
 float y;
 float z;
};

float Rva00094DE5Vector::length(const Rva00094DE5Vector *vector)
{
 return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}
