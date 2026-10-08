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

// Native 000416EC..0004171A, RET0. The target and its debug counterpart
// establish three float values spaced72 bytes apart, copied from one
// offset to another after the existing NaN sanitizer and squared.
// The static helper plus source-only caller lets MSVC reproduce the
// native private ABI: base in EDI, destination in ESI, source and the
// unused name on the stack. No assembler or manually named register is used.
static __declspec(noinline) void rva000416EC(unsigned char *base, int source,
 int destination, const char *name)
{
 rva00041403(base, source);
 for (int i = 0; i < 3; ++i)
 {
  float value = *(float *)(base + i * 0x48 + source);
  *(float *)(base + i * 0x48 + destination) = value * value;
 }
}

// ?rva000416ECCaller absent-from-retail
void rva000416ECCaller(unsigned char *base, int source, int destination,
 const char *name)
{
 rva000416EC(base, source, destination, name);
}
