// ?rva002C986B@Object@@QBEPAUCoord3D@@PAU2@PBU2@@Z
// partial score=0.6721008403361344 date=2026-10-09
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD
// Target evidence: 00265514..00265596/130 and002C986B..002C98E2/119 RET8.
// Native planar workers2654FC/26382B and canonical length3571 are owned.
// Object radiusB8 and boundary shrink factor (distance-radii)/distance are native.
// WB BB5F00 unnamed130; BB6180 Object::Get2DBorderVectorTo119.
// WB return-construction flags establish by-value coordinate return. The explicit
// out pointer below is an ABI view of its hidden return buffer, not a claim about
// the original C++ prototype. Canonical trivial Coord3D return instead copies via
// MOVSD; member copy and scalar results still have different SSE register order.
// Shared432 scalar-order trials plus O2/O1/Op variants:130 best.877162837;
// corresponding119.672100840. No Code edit, no pins, no recovery asserted.
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Object {
public:
 Coord3D *getPlanarDirectionTo(Coord3D*,const Object*)const;
 void Get2DCenterVectorTo(Coord3D*,const Coord3D*)const;
 Coord3D *rva00265514(Coord3D*,const Object*)const;
 Coord3D *rva002C986B(Coord3D*,const Coord3D*)const;
 char pad[0xb8];float radius;
};
Coord3D *Object::rva00265514(Coord3D *out,const Object *that)const {
 Coord3D dir;getPlanarDirectionTo(&dir,that);
 float dist=dir.length();float radiusSum=that->radius+radius;
 float x,y,z;
 if(radiusSum>=dist){x=0.0f;y=0.0f;z=0.0f;}
 else {float scale=(dist-radiusSum)/dist;y=dir.y*scale;z=dir.z*scale;x=dir.x*scale;}
 out->x=x;out->y=y;out->z=z;
 return out;
}
Coord3D *Object::rva002C986B(Coord3D *out,const Coord3D *pos)const {
 Coord3D dir;Get2DCenterVectorTo(&dir,pos);
 float dist=dir.length();
 float x,y,z;
 if(radius>=dist){x=0.0f;y=0.0f;z=0.0f;}
 else {float scale=(dist-radius)/dist;y=dir.y*scale;z=dir.z*scale;x=dir.x*scale;}
 out->x=x;out->y=y;out->z=z;
 return out;
}
