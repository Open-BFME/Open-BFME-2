// cl: /MD /O1 /arch:SSE /G7
// Address-named float-to-double wrappers at 0x000032B8 and 0x000032C9.
// Their call sites are inside unclaimed FUN_00526433; the target calls fabs and sqrt.
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);

double __cdecl Rva000032B8(float value)
{
	return fabs(value);
}

double __cdecl Rva000032C9(float value)
{
	return sqrt(value);
}
