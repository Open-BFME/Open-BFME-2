// cl: /Ireference/shims/bfmerendobj /O2 /G7 /MD /arch:SSE2 /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME1 donor 4367fc698990427e26cc1c399989d074d8ee9bbe:
// game/Libraries/Source/WWVegas/WWMath/quat.cpp and wwmath.h.
// Target Fast_Slerp at RVA 0x007187B0 is 1080B, ending at ret 0x00718BE7
// before eight int3 bytes. Target establishes three 16B quaternion views and
// spherical interpolation; the original spelling remains unproven.
// Fallback REL32 goes through RVA 0x0075B4C6 / IAT VA 0x00BBAA28, whose PE import
// is d3dx9_27.dll!D3DXQuaternionSlerp (stdcall, four arguments, pointer return).
// VA 0x00E1D058 is initially zero-fill; byte writes at RVA 0x000BE5E0 (1)
// and 0x000BE716 (0) establish a mutable switch. Its original name is unknown.
// Acos/Sin tables use the existing WWMathInit.cpp definitions, independently
// established by retail Init stores at VA 0x00E19020 and 0x00E1C020.
// O1 header context preserves retail Fabs (19B) and VCI (34B) copies.
// Local floor/table helpers preserve the donor formulas without emitting
// incompatible shared WWMath COMDAT copies.
#pragma optimize("gsy", on)
// Use the native quaternion siblings' CRT inline-adapter visibility.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include "quat.h"
#include "wwmath.h"
#include <math.h>
// ?bfmeFastSlerpFloor absent-from-retail
static __forceinline int bfmeFastSlerpFloor (const float& f)
{
	int a			= *reinterpret_cast<const int*>(&f);			// take bit pattern of float into a register
	int sign		= (a>>31);												// sign = 0xFFFFFFFF if original value is negative, 0 if positive
	a&=0x7fffffff;															// we don't need the sign any more

	int exponent	= (a>>23)-127;										// extract the exponent
	int expsign	= ~(exponent>>31);									// 0xFFFFFFFF if exponent is positive, 0 otherwise
	int imask		= ( (1<<(31-(exponent))))-1;					// mask for true integer values
	int mantissa	= (a&((1<<23)-1));								// extract mantissa (without the hidden bit)
	int r			= ((unsigned int)(mantissa|(1<<23))<<8)>>(31-exponent);	// ((1<<exponent)*(mantissa|hidden bit))>>24 -- (we know that mantissa > (1<<24))

	r = ((r & expsign) ^ (sign)) + ((!((mantissa<<8)&imask)&(expsign^((a-1)>>31)))&sign);	// if (fabs(value)<1.0) value = 0; copy sign; if (value < 0 && value==(int)(value)) value++;
	return r;
}
#pragma optimize("", on)

bool Rva00E1D058FastSlerpInline;
extern "C" Quaternion * __stdcall rva0075B4C6D3DXQuaternionSlerp(Quaternion *, const Quaternion *, const Quaternion *, float);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?bfmeFastSlerpAcos absent-from-retail
static __forceinline float bfmeFastSlerpAcos(float val)
{
	// Near -1 and +1, the table becomes too inaccurate
	if (WWMath::Fabs(val) > 0.975f) {
		return (float)::acos(val);
	}

	val*=float(ARC_TABLE_SIZE/2);

	int idx0=bfmeFastSlerpFloor(val);
	int idx1=idx0+1;
	float frac=val-(float)idx0;

	idx0+=ARC_TABLE_SIZE/2;
	idx1+=ARC_TABLE_SIZE/2;

	// we dont even get close to the edge of the table...
	assert((idx0 >= 0) && (idx0 < ARC_TABLE_SIZE));
	assert((idx1 >= 0) && (idx1 < ARC_TABLE_SIZE));

	// compute and return the interpolated value
	return (1.0f - frac) * _FastAcosTable[idx0] + frac * _FastAcosTable[idx1];
}

// ?bfmeFastSlerpSin absent-from-retail
static __forceinline float bfmeFastSlerpSin(float val)
{
	val*=float(SIN_TABLE_SIZE) / (2.0f * WWMATH_PI);

	int idx0=bfmeFastSlerpFloor(val);
	int idx1=idx0+1;
	float frac=val-(float)idx0;

	idx0 = ((unsigned)idx0) & (SIN_TABLE_SIZE-1);
	idx1 = ((unsigned)idx1) & (SIN_TABLE_SIZE-1);

	return (1.0f - frac) * _FastSinTable[idx0] + frac * _FastSinTable[idx1];
}

void __cdecl Fast_Slerp(Quaternion& res, const Quaternion & p,const Quaternion & q,float alpha)
{
	float beta;			// complementary interploation parameter
	float theta;		// angle between p and q
	float cos_t; 		// sine, cosine of theta
	float oo_sin_t;
	int qflip;			// use flip of q?

	if (!Rva00E1D058FastSlerpInline) {
		rva0075B4C6D3DXQuaternionSlerp(&res, &p, &q, alpha);
		_ReadWriteBarrier();
	} else {

	// cos theta = dot product of p and q
	cos_t = p.X * q.X + p.Y * q.Y + p.Z * q.Z + p.W * q.W;

	// if q is on opposite hemisphere from A, use -B instead
	if (cos_t < 0.0f) {
		cos_t = -cos_t;
		qflip = true;
	} else {
		qflip = false;
	}

	if (1.0f - cos_t < WWMATH_EPSILON * WWMATH_EPSILON) {

		// if q is very close to p, just linearly interpolate
		// between the two.
		beta = 1.0f - alpha;

	} else {

		theta = bfmeFastSlerpAcos(cos_t);
		float sin_t = bfmeFastSlerpSin(theta);
		oo_sin_t = 1.0f / sin_t;
		beta = bfmeFastSlerpSin(theta - alpha*theta) * oo_sin_t;
		alpha = bfmeFastSlerpSin(alpha*theta) * oo_sin_t;
	}

	if (qflip) {
		alpha = -alpha;
	}

	res.X = beta*p.X + alpha*q.X;
	res.Y = beta*p.Y + alpha*q.Y;
	res.Z = beta*p.Z + alpha*q.Z;
	res.W = beta*p.W + alpha*q.W;
	}
}
