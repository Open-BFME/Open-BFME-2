// ?rva00086812@Rva00086761CameraMove@@QAEXH@Z
// partial score=0.8945 date=2026-10-05
// ?rva00086812@Rva00086761CameraMove@@QAEXH@Z
// partial score=0.95 date=2026-10-03
// cl: /O1 /G7 /arch:SSE /MD /EHs-c- /DNDEBUG
class Rva00086761CameraMove { public: void rva00086812(int); };
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern double g_00BBCC70;
extern double g_00BC26F8;
// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing (x87 blocker).
__forceinline long fast_float2long_round(float f)
{
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}
// ?rva00086812@Rva00086761CameraMove@@QAEXH@Z present-unmatched
void Rva00086761CameraMove::rva00086812(int value)
{
 register Rva00086761CameraMove *me = this;
 if (*(unsigned char *)((char *)me + 0x228))
  *(int *)((char *)me + 0x21C) = value;
 if (*(unsigned char *)((char *)me + 0x254))
  *(int *)((char *)me + 0x248) = value;
 if (*(unsigned char *)((char *)me + 0x204))
  *(int *)((char *)me + 0x1F8) = value;
 if (*(unsigned char *)((char *)me + 0x27C))
  *(int *)((char *)me + 0x270) = value;
 if (*(unsigned char *)((char *)me + 0x1DC))
  *(int *)((char *)me + 0x1B8) = value;
 if (*(int *)((char *)me + 0x2354) == 1) {
  float sum = 0.0f;
  if (*(volatile int *)((char *)me + 0x22F0) <= 0) return;
  int i = 0;
  float fvalue = (float)value;
  int *dst = (int *)((char *)me + 0x1EF8);
  for (i = 0; i < *(volatile int *)((char *)me + 0x22F0); i++, dst++) {
   sum += *(float *)((char *)dst - 0x414);
   float avg = sum / *(float *)((char *)me + 0x1EE8);
   int old = *dst;
   double d = (g_00BBCC70 - avg) * old + avg * fvalue + g_00BC26F8;
   float f = (float)floor(d);
   *dst = fast_float2long_round(f);
  }
  return;
 }
 *(int *)((char *)me + 0x23D4) = value;
}
