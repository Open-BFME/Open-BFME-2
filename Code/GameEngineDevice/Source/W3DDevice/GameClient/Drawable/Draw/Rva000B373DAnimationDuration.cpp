// cl: /O1 /DNDEBUG /MD
// Whole one-body BFME1 donor W3DModelDraw_setAnimationLoopDuration.cpp at
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies this transfer. Its /O1
// placement is unique at native0x000B373D/60; no other viable bodies emitted.
// Native facts: RET4 unsigned argument conversion adds float2^32 when needed,
// multiplies by exact float200.0 (43480000 at RVA0x009BA4F0), calls msvcr71.dll
// ceil through IAT0x00BBA578, then forwards float result and this-12 to the
// independently rowed131-byte body0x000B2F38. Three native vtables reference
// this entry at RVAs0x007CBBDC,0x007CBF5C,0x007CC5EC. The donor's W3DModelDraw
// owner and setAnimationLoopDuration spelling remain donor evidence, not
// independently proven target identities; address-qualified views preserve
// that uncertainty and describe neither full class size nor layout.
// Rva000B2F38 is a declaration only, binding the existing verified/linking
// provider. The math.h wrappers retain their original definitions with
// private linkage, as in the successful tangent transfer, to avoid duplicate
// public COMDAT providers. Float constants are verified by the normal gate.
#define inline static inline
#include <math.h>
#undef inline
#pragma intrinsic(ceil)
class Rva000B2F38 { public: bool rva000B2F38(float); };
class Rva000B373D { public: void setDuration(unsigned int); };
void Rva000B373D::setDuration(unsigned int amount) {
 float result=(float)ceil((float)amount * 200.0f);
 Rva000B2F38 *primary=(Rva000B2F38*)((char*)this-12);
 float *resultPtr=&result;
 primary->rva000B2F38(*resultPtr);
}
