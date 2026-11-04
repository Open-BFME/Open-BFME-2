// cl: /MD /Oy-
// ?angleDifference@@YAMMM@Z, retail 0x0010416E, 39 bytes.
// Evidence: unlock lane, callers at 0x0010451F/0x00104548 in 0x00104359, float 6.2831853 at 0x007C746C (2pi TwoPi).

float __cdecl angleDifference(float a, float b)
{
	if (b > a)
		a += 6.2831853f;
	return a - b;
}
