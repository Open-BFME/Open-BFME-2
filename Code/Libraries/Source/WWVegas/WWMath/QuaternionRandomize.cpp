// cl: /G7 /arch:SSE2 /DNDEBUG /MD
// BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, quat.cpp Randomize.
// Retail7184E0/217: four rand low-word fractions, then normalize XYZW.
// Donor quat.h names XYZW; target stores and rowed Normalize confirm offsets0/4/8/C.
// The type has no vtable or base and occupies16B in the donor; target accesses agree.
// Rowed Inv_Sqrt4233A/82 uses __fastcall (SI decoration), float stack argument, ret4.
// Keep only the declaration so the donor generic inverse-sqrt is not emitted.
class WWMath { public: static float __fastcall Inv_Sqrt(float); };
class Quaternion {
public:
 float X,Y,Z,W;
 void Normalize();
 void Randomize();
};
#include <stdlib.h>
// Local inline copy of rowed Normalize717460/119; no additional recovery claimed.
// ?Normalize@Quaternion@@QAEXXZ present-unmatched
inline void Quaternion::Normalize()
{
	float len2=X * X + Y * Y + Z * Z + W * W;
	if (0.0f == len2) {
		return;
	} else {
		float inv_mag = WWMath::Inv_Sqrt(len2);

		X *= inv_mag;
		Y *= inv_mag;
		Z *= inv_mag;
		W *= inv_mag;
	}
}

void Quaternion::Randomize(void)
{
	X = ((float) (rand() & 0xFFFF)) / 65536.0f;
	Y = ((float) (rand() & 0xFFFF)) / 65536.0f;
	Z = ((float) (rand() & 0xFFFF)) / 65536.0f;
	W = ((float) (rand() & 0xFFFF)) / 65536.0f;

	Normalize();
}
