// ?rva00142410@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAVCameraClass@@PBM@Z
// partial score=0.85 date=2026-10-09
// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// Target [142170,14232B) is a spatial tree rectangle query. The node stride
// (28), quadrant subdivision, list offsets and pool are native evidence.
// Original function names are unknown; no donor name is asserted.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
#include "camera.h"
#include "plane.h"
struct Gen_00943CF0_Node { Gen_00943CF0_Node *m_next; void *m_value; };
class Rva0006EFC8 {
public:
 bool rva0006EFC8(int arena,int size);
 int m_00; void *m_04; void *m_head;
 void *(__cdecl *m_alloc)(int,int);
 void (__cdecl *m_free)(void*,int); int m_14;
};
extern Rva0006EFC8 g_Rva0006EFC8Pool00DB424C;
struct SceneCollectCell { unsigned count; MultiListClass<RenderObjClass> objects; };
typedef char SceneCollectCellSize[(sizeof(SceneCollectCell)==28)?1:-1];
class Gen_009431F0 { public: int map_x(float); int map_y(float); };
struct SceneCollectPair { float X,Y; };
struct SceneCollectRect {
 SceneCollectPair min,max;
 // ?SceneCollectRect::Add_Point present-unmatched
 __forceinline void Add_Point(const Vector2 &p) {
  if(p.X<min.X) min.X=p.X; else if(p.X>max.X) max.X=p.X;
  if(p.Y<min.Y) min.Y=p.Y; else if(p.Y>max.Y) max.Y=p.Y;
 }
};
class BfmeSceneVector {
public:
 void rva00142170(Gen_00943CF0_Node **out,SceneCollectCell *node,unsigned n,int xmin,int ymin,int xmax,int ymax,int ox,int oy,int extent);
 void rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin);
 void rva00142410(Gen_00943CF0_Node **out,CameraClass *camera,const float *margin);
 float bounds[6]; SceneCollectCell *vector; int vector_max; float scale; unsigned level_mask;
};
void BfmeSceneVector::rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin)
{
 int x0=((Gen_009431F0*)this)->map_x(rect.min.X-(margin ? margin[0] : 0.0f));
 int x1=((Gen_009431F0*)this)->map_x(rect.max.X+(margin ? margin[0] : 0.0f));
 int y0=((Gen_009431F0*)this)->map_y(rect.min.Y-(margin ? margin[1] : 0.0f));
 int y1=((Gen_009431F0*)this)->map_y(rect.max.Y+(margin ? margin[1] : 0.0f));
 rva00142170(out,vector,(unsigned)vector_max>>2,x0,y0,x1,y1,0,0,level_mask);
}

// Target [142410,1426A6),662B: unrolled near corners then four ray-plane
// intersections. Frustum corner and transform accesses agree with CameraClass.
// Native +40 is the transform Z-axis Z component; 800 and 1 are retail literals.
void BfmeSceneVector::rva00142410(Gen_00943CF0_Node **out,CameraClass *camera,const float *margin)
{
 const Vector3 *corners=camera->Get_Frustum_Corners();
 SceneCollectRect rect;
 rect.max.X=corners[0].X;
 rect.max.Y=corners[0].Y;
 rect.min=rect.max;
 rect.Add_Point(*(const Vector2*)&corners[1]);
 rect.Add_Point(*(const Vector2*)&corners[2]);
 rect.Add_Point(*(const Vector2*)&corners[3]);
 PlaneClass plane;
 if(camera->Get_Transform()[2][2]<0.0f) plane.D=800.0f;
 for(int i=0;i<4;++i) {
  float t;
  if(!plane.Compute_Intersection(corners[i],corners[i+4],&t)) t=1.0f;
  Vector3 point=corners[i]+(corners[i+4]-corners[i])*t;
  rect.Add_Point(Vector2(point.X,point.Y));
 }
 rva00142330(out,rect,margin);
}
