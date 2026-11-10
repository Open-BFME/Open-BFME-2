// cl: /Ob1 /MD /D_CRTIMP=
// Native fp8.obj public identity and complete retail 18-byte body.
// The original direct call reaches msvcr71!_controlfp through its existing
// six-byte retail import thunk. No CRT implementation source was read.
// Mask 0x30000 selects x87 precision; value 0x10000 requests 53 bits.
#include <float.h>
extern "C" void __cdecl _setdefaultprecision() {
 _controlfp(0x10000,0x30000);
}
