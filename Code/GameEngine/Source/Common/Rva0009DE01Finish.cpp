// cl: /DNDEBUG /MD /Oy-
// ?Rva0009DE01Get@@YAMMM@Z @ 0x0009DE01 37B.  log-ratio helper computing
// log10(a)/log10(b) through the rowed msvcr71 log10 import thunk at 0x0062997C.
// The two logs are computed into named locals before the divide; assigning
// straight back into the b argument slot emits the two stack-cleanup pops after
// the fdiv instead of one either side of it.
extern void ji_0062997c();
typedef double (__cdecl *Log10Fn)(double);

float Rva0009DE01Get(float a, float b)
{
	float lb = (float)((Log10Fn)ji_0062997c)((double)b);
	float la = (float)((Log10Fn)ji_0062997c)((double)a);
	return la / lb;
}
