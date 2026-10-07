// cl: /ICode/Libraries/Include /O1 /arch:SSE /G7 /DNDEBUG /MD
// Target 0x002FFFCA-0x0030000C, 66B, complete RET28 boundary.
// Compare the second coordinate with Object's established +0x38 position
// using the byte-verified exact-equality body 0x00003702. If they differ,
// add bit 0x100 to the fourth argument and forward all seven arguments to
// the native 0x002FF07B worker (2146B, RET28). Native callers 0x004DB989,
// 0x00543614 and 0x00543768 use EAX as a nullable pointer and the last
// dereferences its +4 field, so the pointer return is a target fact.
// The receiver, worker/result identities and opaque trailing-word meanings
// are unresolved. Equality's TU view reuses the canonical 12B coordinate.
#include "Lib/Coord3D.h"
class Object;
class Rva00003702CoordEqualityView { public: bool equals(const Coord3D&) const; };
class Rva002FFFCA {
public:
    void* rva002FFFCA(Object*,const Coord3D*,float,unsigned int,int,int,int);
    void* rva002FF07B(Object*,const Coord3D*,float,unsigned int,int,int,int);
};
void* Rva002FFFCA::rva002FFFCA(Object* object,const Coord3D* targetPosition,float radius,unsigned int flags,int a,int b,int c) {
    const Coord3D* position=(const Coord3D*)((const char*)object+0x38);
    if(!((const Rva00003702CoordEqualityView*)targetPosition)->equals(*position)) flags|=0x100;
    return rva002FF07B(object,targetPosition,radius,flags,a,b,c);
}
