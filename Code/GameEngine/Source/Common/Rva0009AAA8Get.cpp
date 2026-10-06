// cl: /MD
//
// ?Rva0009AAA8Get@@YAMM@Z @0x0009AAA8 (39B).
// Free float helper calling sqrt; callers 0x9B510 0x9BAA4 pass a float and
// store a float result. Shape is a=x*x returning a+x*(sqrt(x)-a).

#include <math.h>

float __cdecl Rva0009AAA8Get(float x)
{
	float a = x * x;
	return a + x * ((float)sqrt(x) - a);
}
