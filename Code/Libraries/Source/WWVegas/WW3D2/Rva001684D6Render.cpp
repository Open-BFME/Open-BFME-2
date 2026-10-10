// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmestreak /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Semantic guide BFME1 simplestreak.cpp Bitmap2DObjClass::Render575ba2b04;
// WB A1B020 identifies SimpleStreakLineClass::Render in simplestreak.cpp.
// Native table BD41C8 slot12 points168157. Keep existing RVA class owner.
// WB A1E840 names the actual REL32 callee126433 RenderStreak; six stack
// arguments and receiverE4 establish this scoped declaration. This first
// in-image pin does not claim recovery of the large callee body.
#include "rendobj.h"
#include "rinfo.h"
#include "ww3d.h"
struct PointStorage {void*vt;Vector3*Vector;int Capacity,Count;};
struct WidthStorage {void*vt;float*Vector;int Capacity,Count;};
class Rva00126314 {public:void rva00126433(RenderInfoClass&,const Matrix3D&,unsigned,Vector3*,float*,const SphereClass&);ShaderClass Get_Shader()const{return shader;}private:void*texture;ShaderClass shader;char rest[28];};
class Rva001684D6:public RenderObjClass {public:virtual void Render(RenderInfoClass&);private:PointStorage points;WidthStorage widths;Rva00126314 renderer;};
void Rva001684D6::Render(RenderInfoClass&rinfo){
if(!Is_Not_Hidden_At_All())return;
unsigned level=0;if(!WW3D::Is_Sorting_Enabled())level=renderer.Get_Shader().Guess_Sort_Level();
if(WW3D::Are_Static_Sort_Lists_Enabled()&&level!=0){WW3D::Add_To_Static_Sort_List(this,level);return;}
if(points.Count<2)return;if(points.Count!=widths.Count)return;
SphereClass sphere;Get_Obj_Space_Bounding_Sphere(sphere);
renderer.rva00126433(rinfo,Transform,points.Count,points.Vector,widths.Vector,sphere);}
