// ?wrapAngle@@YAMM@Z at retail 0x006E03F0 (67 bytes).
//
// BFME1 angle wrapper transferred from the reference reconstruction
// (reference/open-bfme-1/Code/GameEngine/Source/Common/SmallGaps/wrapAngle.cpp):
// the same fmod-then-fold shape, but BFME2 halves every constant — the fmod
// divisor is (double)PI instead of (double)TwoPi, the upper fold fires at
// +HalfPi subtracting PI, and the lower fold is guarded by a strict
// HalfPi test with a >-PI early return instead of the plain -PI test.
//
// Shape, all retail-measured: fld/fld/call into the msvcr71 __CIfmod import
// thunk at 0x00629A36 (intrinsic fmod, x87-stack args — no pushes), fcom
// against +HalfPi with test-ah,1/jne over the fsub PI, fcom against
// -HalfPi with test-ah,5/jp out (the strict < is what selects the 0x05
// mask; <= emits 0x41), then fcom against -PI with test-ah,0x41/je out
// (the > early return is what selects je; <= with an else emits jp).
// The pooled literals ride compiler DIR32 relocs: float PI plus its
// (double)PI conversion, and +HalfPi/-HalfPi/-PI.

#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")

float wrapAngle(float angle)
{
	angle = (float)fmod(angle, 3.14159274f);
	if (angle >= 1.57079637f)
		angle -= 3.14159274f;
	if (angle < -1.57079637f) {
		if (angle > -3.14159274f)
			return angle;
		angle += 3.14159274f;
	} else
		return angle;
	return angle;
}
