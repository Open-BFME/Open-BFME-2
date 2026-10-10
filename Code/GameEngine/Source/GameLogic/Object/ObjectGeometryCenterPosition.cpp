// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c- /ICode/Libraries/Include
// Retail28C2DD..28C428 (331B), existing neutral Object method pin retained.
// Identity/ABI: WallUpgradeUpdate4AB57E and AI path callers pass Object and
// one canonical Coord3D output. Native flagAC chooses object position38;
// otherwise geometryA8's existing26B get6BD470 copies local centre18 before
// matrix8 transforms it. Original member/helper identifiers remain unresolved.
// Reference: ZH WWMath/matrix3d.h Transform_Vector and Matrix3D*Vector3
// describe the same row-wise affine transform. WB CE6610 independently shows
// local input, separate transform output, alias check, and debug five circles.
// The input/output locals are distinct here. TransformPoint's scalar ctor
// expresses argument evaluation phase; it does not assert original Vector3 ABI.
// Native331 requires the third-row source term order and volatile first-row
// matrix01/02 reads: they prevent cl7.1 from swapping commutative product homes
// while retaining native addition order, all matrix offsets and output stores.
// GlobalCF8 and View slot30 are observed debug marker contract only. Existing
// global owners and neutral bit-copy provider spelling retained; no new pins.
// All receiver/layout views cover observed prefixes, not original full extents.
#include "Lib/Coord3D.h"
struct Rva0087DC00Vec{int x,y,z;};class Rva0087DC00{public:void get(Rva0087DC00Vec*);char pad[4];bool flag04;char pad5[0x18-5];Rva0087DC00Vec center;};
class GlobalData{public:char pad[0xcf8];bool showGeometry;};extern GlobalData *TheWritableGlobalData;
class View{public:virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
 virtual void slot30(const Coord3D*,float,unsigned);};extern View *TheTacticalView;
struct TransformPoint{float x,y,z;TransformPoint(float a,float b,float c):x(a),y(b),z(c){}};
class Object{public:void rva0028C2DD(Coord3D*)const;char pad0[8];float matrix[3][4];Coord3D position;char pad44[0xa8-0x44];Rva0087DC00 geometry;};
void Object::rva0028C2DD(Coord3D *out)const{
 Rva0087DC00 *geom=(Rva0087DC00*)&geometry;
 if(geom->flag04){*out=position;return;}
 Coord3D local;geom->get((Rva0087DC00Vec*)&local);
 TransformPoint p(
  matrix[0][0]*local.x+(*(volatile const float*)&matrix[0][1])*local.y+(*(volatile const float*)&matrix[0][2])*local.z+matrix[0][3],
  matrix[1][0]*local.x+matrix[1][1]*local.y+matrix[1][2]*local.z+matrix[1][3],
  matrix[2][2]*local.z+matrix[2][1]*local.y+matrix[2][0]*local.x+matrix[2][3]);
 out->x=p.x;out->y=p.y;out->z=p.z;
 if(TheWritableGlobalData->showGeometry){TheTacticalView->slot30(out,3.0f,0xff00ff77);TheTacticalView->slot30(out,6.0f,0xff00ff77);TheTacticalView->slot30(out,9.0f,0xff00ff77);TheTacticalView->slot30(out,12.0f,0xff00ff77);TheTacticalView->slot30(out,15.0f,0xff00ff77);}
}
