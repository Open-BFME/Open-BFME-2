// ?fixEndpoints@Rva00311B70@@QAEXXZ
// partial score=0.868936 date=2026-10-09
// cl: /O1 /Oy- /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
struct Coord3DBase {float x,y,z;};
class Coord3D:public Coord3DBase {public:
 __forceinline Coord3D() {}
 __forceinline Coord3D(const Coord3DBase &p) {x=p.x;y=p.y;z=p.z;}
 __forceinline Coord3D &operator=(const Coord3DBase &p) {x=p.x;y=p.y;z=p.z;return *this;}
 __forceinline void sub(const Coord3DBase *p) {x-=p->x;y-=p->y;z-=p->z;}
 __forceinline void scale(float f) {x*=f;y*=f;z*=f;}
 float length() const;void normalize();
};
struct EndpointRecord {char head[0xa4];Coord3DBase point;char tail[8];};
class Rva00311B70 {public:void fixEndpoints();char head[0x2c]; _STL::vector<EndpointRecord> records;};
void Rva00311B70::fixEndpoints() {
 Coord3D point(records[1].point),delta;
 Coord3D second(records[2].point);
 delta.x=point.x-second.x;delta.y=point.y-second.y;delta.z=point.z-second.z;
 float length=delta.length();
 Coord3D first(records[0].point);delta=point;delta.sub(&first);delta.normalize();delta.scale(length);
 point.sub(&delta);*(Coord3D*)&records[0].point=point;
 int n=records.size();
 point=records[n-2].point;delta=point;Coord3D beforeLast(records[n-3].point);delta.sub(&beforeLast);
 length=delta.length();delta=point;Coord3D last(records[n-1].point);delta.sub(&last);delta.normalize();delta.scale(length);
 point.sub(&delta);*(Coord3D*)&records[n-1].point=point;
}
