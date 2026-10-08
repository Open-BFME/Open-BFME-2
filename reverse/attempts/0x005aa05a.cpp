// ?getPivotPoint@Rva0015334F@@QAE?AUCoord3D@@PAURva005AA55DRecord@@PBU2@1@Z
// partial score=0.75 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
struct Coord3DBase { float x,y,z; };
struct Coord3D : Coord3DBase { Coord3D() {} Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; } };
struct PivotOwner { char pad[0x554]; Coord3D position; };
struct Rva005AA55DRecord { char pad[0x0C]; Coord3D point; char pad18[0x24-0x18]; PivotOwner *owner; };
class Rva0015334F { public: Coord3D getPivotPoint(Rva005AA55DRecord*,const Coord3D*,const Coord3D*); };
Coord3D Rva0015334F::getPivotPoint(Rva005AA55DRecord *record,const Coord3D *from,const Coord3D *to) {
 float dx=record->owner->position.x-record->point.x;
 float dy=record->owner->position.y-record->point.y;
 if (dy*dy+dx*dx >= 160000.0f) return record->owner->position;
 return *to;
}



