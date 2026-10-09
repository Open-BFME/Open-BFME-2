// ?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z
// partial score=0.72 date=2026-10-09
// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// Target [142170,14232B) is a spatial tree rectangle query. The node stride
// (28), quadrant subdivision, list offsets and pool are native evidence.
// Original function names are unknown; no donor name is asserted.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
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
struct SceneCollectRect { float xmin,ymin,xmax,ymax; };
class BfmeSceneVector {
public:
 void rva00142170(Gen_00943CF0_Node **out,SceneCollectCell *node,unsigned n,int xmin,int ymin,int xmax,int ymax,int ox,int oy,int extent);
 void rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin);
 float bounds[6]; SceneCollectCell *vector; int vector_max; float scale; unsigned level_mask;
};
void BfmeSceneVector::rva00142170(Gen_00943CF0_Node **out,SceneCollectCell *node,unsigned n,int xmin,int ymin,int xmax,int ymax,int ox,int oy,int extent)
{
 if(!node->objects.Is_Empty()) {
  MultiListIterator<RenderObjClass> it(&node->objects);
  for(; !it.Is_Done(); it.Next()) {
   RenderObjClass *object=it.Peek_Obj();
   Gen_00943CF0_Node *item;
  retry:
   if(g_Rva0006EFC8Pool00DB424C.m_head) goto pop_end;
   if(g_Rva0006EFC8Pool00DB424C.rva0006EFC8(0,g_Rva0006EFC8Pool00DB424C.m_00*8+4)) goto retry;
   item=0;
   goto prepend;
  pop_end:
   item=(Gen_00943CF0_Node*)g_Rva0006EFC8Pool00DB424C.m_head;
   g_Rva0006EFC8Pool00DB424C.m_head=item->m_next;
  prepend:
   void **valuePtr=(void**)((char*)item+4);
   if(valuePtr) *valuePtr=object;
   item->m_next=0;
   item->m_next=*out; *out=item;
  }
 }
 if(node->count) {
  int half=extent/2;
  int my=oy+half;
  ++node;
  if(ymin<my) {
   int mx=ox+half;
   if(xmin<mx) rva00142170(out,node,n>>2,xmin,ymin,xmax,ymax,ox,oy,half);
   if(xmax>=mx) rva00142170(out,node+n,n>>2,xmin,ymin,xmax,ymax,mx,oy,half);
  }
  if(ymax>=my) {
   int mx=ox+half;
   if(xmin<mx) rva00142170(out,node+2*n,n>>2,xmin,ymin,xmax,ymax,ox,my,half);
   if(xmax>=mx) rva00142170(out,node+3*n,n>>2,xmin,ymin,xmax,ymax,mx,my,half);
  }
 }
}
void BfmeSceneVector::rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin)
{
 int x0=((Gen_009431F0*)this)->map_x(rect.xmin-(margin ? margin[0] : 0.0f));
 int x1=((Gen_009431F0*)this)->map_x(rect.xmax+(margin ? margin[0] : 0.0f));
 int y0=((Gen_009431F0*)this)->map_y(rect.ymin-(margin ? margin[1] : 0.0f));
 int y1=((Gen_009431F0*)this)->map_y(rect.ymax+(margin ? margin[1] : 0.0f));
 rva00142170(out,vector,(unsigned)vector_max>>2,x0,y0,x1,y1,0,0,level_mask);
}
