// ?rva00041403@@YAXPAEH@Z
// partial score=0.85 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
extern "C" __declspec(dllimport) int __cdecl _isnan(double);
static __forceinline void replaceNan(float &value, const float &replacement)
{
 if (_isnan(value)) *(unsigned *)&value = *(const unsigned *)&replacement;
}
static __declspec(noinline) void rva00041403(unsigned char *base, int offset)
{
 float *first = (float *)(base + offset);
 float *second = (float *)(base + offset + 0x48);
 float *third = (float *)(base + offset + 0x90);
 if (_isnan(*first)) *first = 0.0f;
 replaceNan(*second, *first);
 replaceNan(*third, *first);
}
// ?rva00041403Caller absent-from-retail
void rva00041403Caller(unsigned char *base, int offset)
{
 rva00041403(base, offset);
}
