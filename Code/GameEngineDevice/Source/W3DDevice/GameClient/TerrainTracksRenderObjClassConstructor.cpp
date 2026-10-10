// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native840F1..84206 RET0 boundary277B. Existing Rva0084096 destructor
// and its BC743C primary vtable establish this owner; do not rename it.
// ZH TerrainTracksRenderObjClass constructor/header and WB8BACD0 supply
// semantic/field leads. Retail fixes RefCountClass8, two12B records at8,
// texture2C and hundred48B edge records3C followed by anchor12FC and tail.
// All offsets and callback identities are native facts; exact class/member
// identities outside the already-owned edgeInfo remain donor inferences.
// Inline counted texture default/cleanup supplies native unwind state1;
// per-iteration edge pointer selects native Z cursor at+44. Canonical
// coordinate PODs preserve storage; shared empty12B ctor is a real provider.
#include "refcount.h"
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
struct Rva000840F1Point : Coord3D { Rva000840F1Point(); };
class TerrainTracksRenderObjClass { public:
    struct edgeInfo {
        Coord3D endPointPos[2];
        Coord2D endPointUV[2];
        int timeAdded; float alpha;
        edgeInfo();
    };
};
class TextureClass {public: void Release_Ref();};
struct Rva000840F1Texture {TextureClass *ptr;Rva000840F1Texture():ptr(0){}~Rva000840F1Texture(){if(ptr)ptr->Release_Ref();}};
class Rva0084096 : public RefCountClass {
public: Rva0084096(); virtual ~Rva0084096();
private:
    Rva000840F1Point bounds[2];
    Coord3D unknown20;
    Rva000840F1Texture texture;
    int activeCount,totalAdded;void *owner;
    TerrainTracksRenderObjClass::edgeInfo edges[100];
    Coord3D lastAnchor;
    int bottomIndex,topIndex;
    bool haveAnchor,bound;
    float width,length;
    bool airborne,haveCap;
    void *next,*prev;
};
Rva0084096::Rva0084096()
{
    Coord3D *anchor=&lastAnchor;anchor->x=0;anchor->y=1;anchor->z=2.25f;
    haveAnchor=false;haveCap=true;
    topIndex=0;bottomIndex=0;activeCount=0;totalAdded=0;bound=false;owner=0;
    for(int i=0;i<100;++i) {
        TerrainTracksRenderObjClass::edgeInfo *edge=&edges[i];
        edge->endPointPos[0].x=0;edge->endPointPos[0].y=0;edge->endPointPos[0].z=0;
        edge->endPointPos[1].x=0;edge->endPointPos[1].y=0;edge->endPointPos[1].z=0;
        edge->endPointUV[0].x=0;edge->endPointUV[0].y=0;
        edge->endPointUV[1].x=0;edge->endPointUV[1].y=0;
        edge->timeAdded=0;edge->alpha=0;
    }
    airborne=false;next=0;prev=0;width=0;length=0;
}
