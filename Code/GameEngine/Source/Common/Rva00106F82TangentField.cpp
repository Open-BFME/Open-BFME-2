// cl: /O1 /DNDEBUG /MD
// Clean BFME1 Rva007AE410TinyBodies.cpp at 1281192 supplies the full donor
// file. /O1 places only this new35-byte body, the remaining tiny leaves fold.
// Native106F82 has a Ghidra35-byte boundary and a direct caller1083F3.
// Source/target agree on a float argument, multiplication by float bits
// 0x42652EE0 (57.2957763671875), conversion to double for tan, and a float
// store at receiver+0x88. Native62993A is independently a JMP through the
// msvcr71.dll import tan at VA BBA574. The existing _tan pin binds that import.
// Original owner/method names and angle units remain unknown. This view only
// describes the observed field prefix, not the full target class or its size.
// Use the original MSVC math.h float overload and intrinsic setting; a
// declaration-only trial differed in POP/FSTP ordering. No CRT shim is needed.
// MSVC /O1 emits copies of tanf and tan(float). Keep these header wrappers
// private: their global copies differ from the census keepers. Their bodies
// and the external double-tan declaration are the original math.h definitions.
#define inline static inline
#include <math.h>
#undef inline
#pragma intrinsic(tan)
class Rva00106F82Field {
public:
 void setScaledTangent(float argument);
private:
 char opaque00[0x88];
 float value88;
};
void Rva00106F82Field::setScaledTangent(float argument) {
 value88=(float)tan(argument*57.295776f);
}





