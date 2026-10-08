// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference semantic lead: GeneralsMD W3DTerrainTracks.cpp computeTrackSpacing
// at BFME1 checkout dae380faa5f6fa536eec8d6ebbe877321d4cb51d.
// Retail 0x84B18..0x84C05 supplies the boundary and target-specific ABI:
// EDI renderer, ESI two endpoint vectors, two stack bone names, XMM0 result.
// Slot C8 resolves a bone; slot CC takes a 48-byte output and bone index,
// returning a matrix reference. The slot identities are structural inferences
// from the reference; their arguments and matrix translation offsets are retail facts.
// Keeping the caller in this TU lets MSVC derive its private convention.
// WWMath::Sqrt is the existing donor x87 implementation, matching retail FSQRT.
// The renderer and track classes are partial ABI views, not recovered names.
#include "wwmath.h"
struct TrackVector { float x,y,z;
 TrackVector(){} TrackVector(float a,float b,float c):x(a),y(b),z(c){}
 TrackVector(const TrackVector&a):x(a.x),y(a.y),z(a.z){}
 TrackVector& operator=(const TrackVector&a){x=a.x;y=a.y;z=a.z;return *this;}
};
struct TrackMatrix { float m[3][4]; };
class Rva00084B18RenderObj {
public:
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual int boneIndex(const char*);
 virtual const TrackMatrix &boneTransform(TrackMatrix &,int);
};
class Rva00084206Track {
public:
 char pad0[8]; TrackVector endpoints[2]; char pad20[0x12f1];
 bool bound; char pad1312[0xe]; Rva00084206Track *next,*prev;
 void init(float,float,const char*);
};
static __declspec(noinline) float computeTrackSpacing(Rva00084B18RenderObj *obj,TrackVector *ends,const char *left,const char *right) {
 float spacing=14.0f;
 int a=obj->boneIndex(left); int b=obj->boneIndex(right);
 if(a && b) {
  TrackMatrix temp; const TrackMatrix &m=obj->boneTransform(temp,a);
  ends[0]=TrackVector(m.m[0][3],m.m[1][3],m.m[2][3]);
  const TrackMatrix &n=obj->boneTransform(temp,b);
  ends[1]=TrackVector(n.m[0][3],n.m[1][3],n.m[2][3]);
  float x=ends[1].x-ends[0].x,y=ends[1].y-ends[0].y,z=ends[1].z-ends[0].z;
  float sum=z*z+y*y+x*x; spacing=WWMath::Sqrt(sum)+4.0f;
 }
 return spacing;
}
class Rva00084C05System {
public:
 char pad[0x10]; Rva00084206Track *used,*free;
 Rva00084206Track *bind(Rva00084B18RenderObj*,float,const char*,const char*,const char*);
};
Rva00084206Track *Rva00084C05System::bind(Rva00084B18RenderObj *obj,float length,const char *texture,const char *left,const char *right) {
 Rva00084206Track *mod=free;
 if(mod) {
  if(mod->next) mod->next->prev=mod->prev;
  if(mod->prev) mod->prev->next=mod->next; else free=mod->next;
  mod->prev=0; mod->next=used;
  if(used) used->prev=mod;
  used=mod;
  mod->init(computeTrackSpacing(obj,mod->endpoints,left,right),length,texture);
  mod->bound=true;
 }
 return mod;
}
