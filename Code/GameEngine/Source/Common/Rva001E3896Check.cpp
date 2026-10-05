// cl: /O1 /arch:SSE /MD
//
// ?Rva001E3896Check@@YAHM@Z @0x001E3896 (35B).
// Returns fabs(arg) < threshold as int via fabs import plus float compare.
// Evidence: fabs 0x629210 row plus global 0x00BC28F8 plus 2 callers in
// 0x1E7CDF; shape matches Rva00528B37Compare fabs compare precedent.

extern float g_00BC28F8;
extern "C" double __cdecl fabs(double v);

int __cdecl Rva001E3896Check(float x)
{
	if (fabs(x) < g_00BC28F8)
		return 1;
	return 0;
}
