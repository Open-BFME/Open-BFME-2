// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// Target [142330,142407) maps a floating rectangle to spatial cells and
// calls the recursive tree query at142170. Its node stride is 28 bytes.
// Original function names are unknown; no donor name is asserted.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
struct Gen_00943CF0_Node { Gen_00943CF0_Node *m_next; void *m_value; };
struct SceneCollectCell { unsigned count; MultiListClass<RenderObjClass> objects; };
typedef char SceneCollectCellSize[(sizeof(SceneCollectCell)==28)?1:-1];
class Gen_009431F0 { public: int map_x(float); int map_y(float); };
struct SceneCollectPair { float X,Y; };
struct SceneCollectRect {
 SceneCollectPair min,max;

};
class BfmeSceneVector {
public:
 void rva00142170(Gen_00943CF0_Node **out,SceneCollectCell *node,unsigned n,int xmin,int ymin,int xmax,int ymax,int ox,int oy,int extent);
 void rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin);
 float bounds[6]; SceneCollectCell *vector; int vector_max; float scale; unsigned level_mask;
};
typedef char SceneCollectIndexMatches[(sizeof(BfmeSceneVector)==sizeof(BFME2SceneSpatialIndex))?1:-1];
typedef char SceneCollectCellMatches[(sizeof(SceneCollectCell)==sizeof(BFME2SceneSpatialNode))?1:-1];

void BfmeSceneVector::rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin)
{
 int x0=((Gen_009431F0*)this)->map_x(rect.min.X-(margin ? margin[0] : 0.0f));
 int x1=((Gen_009431F0*)this)->map_x(rect.max.X+(margin ? margin[0] : 0.0f));
 int y0=((Gen_009431F0*)this)->map_y(rect.min.Y-(margin ? margin[1] : 0.0f));
 int y1=((Gen_009431F0*)this)->map_y(rect.max.Y+(margin ? margin[1] : 0.0f));
 rva00142170(out,vector,(unsigned)vector_max>>2,x0,y0,x1,y1,0,0,level_mask);
}

