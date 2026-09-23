// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Target float wrappers around the MSVCR71 double fmod import.
// Called by the snow update; original wrapper names are unknown.
extern "C" double __cdecl fmod(double, double);
float __cdecl Rva000930A5(float lhs, float rhs) { return (float)fmod((double)lhs, (double)rhs); }
float __cdecl Rva000930C0(float lhs, float rhs) { return Rva000930A5(lhs, rhs); }
