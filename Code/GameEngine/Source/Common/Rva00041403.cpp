// cl: /O1 /arch:SSE /G7 /MD
// Native00041403..00041457, RET0: ECX base and EAX byte offset.
// Checks three float words spaced72 bytes apart. A NaN in the first
// becomes zero; later NaNs receive the first word without float conversion.
// Method identity and the enclosing object remain address derived.
extern "C" __declspec(dllimport) int __cdecl _isnan(double);
static __forceinline void replaceNan(unsigned &value, const unsigned &replacement)
{
 if (_isnan(*(const float *)&value)) value = replacement;
}
static __declspec(noinline) void rva00041403(unsigned char *base, int offset)
{
 float *first = (float *)(base + offset);
 float *second = (float *)(base + offset + 0x48);

 if (_isnan(*first)) *first = 0.0f;
 replaceNan(*(unsigned *)second, *(unsigned *)first);
 unsigned &third = *(unsigned *)((unsigned char *)first + 0x90);
 replaceNan(third, *(unsigned *)first);
}
// ?rva00041403Caller absent-from-retail
void rva00041403Caller(unsigned char *base, int offset)
{
 rva00041403(base, offset);
}
