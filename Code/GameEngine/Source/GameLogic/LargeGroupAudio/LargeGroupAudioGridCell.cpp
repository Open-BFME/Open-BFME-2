// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include
// Target identity: WorldBuilder 0x01569090 names this method at
// LargeGroupAudioGridCell.cpp lines 487..488. Native 0x005C8876..0x005C8A98
// supplies the 546-byte boundary and every accessed field: cell coordinates
// +0/+4; eight neighbor pointers +0x0C; neighbor weight WORD +0x44. Existing
// rowed addToWeight/setOverlappedLocking independently use the same offsets.
// WB's weighted-neighbor sums guide the algorithm. The grid and returned
// position type names are unresolved, so their views keep address names.
// Native RET8 returns three reals through a hidden result pointer; scalar
// copy construction reproduces that ABI without altering canonical Coord3D.
// TheTerrainLogic is the existing DFEC50 owner and its height slot is +0x18,
// also established by PolygonTriggerCenter and the ZH TerrainLogic header.
// No BFME1/ZH clean donor for this BFME-specific grid method was found.
#include "Lib/Coord3D.h"
class TerrainLogic {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual float getGroundHeight(float,float,Coord3D *) const;
};
extern TerrainLogic *TheTerrainLogic;
struct Rva005C8876Grid { char unknown00[0x10]; float cellWidth; float speed; };
struct Rva005C8876Position { float x,y,z; Rva005C8876Position() {} Rva005C8876Position(const Rva005C8876Position &p):x(p.x),y(p.y),z(p.z) {} };
class LargeGroupAudioGridCell {
public:
 Rva005C8876Position getPreferredAudioPosition(Rva005C8876Grid *grid);
 float x,y;
 void *loop;
 LargeGroupAudioGridCell *neighbors[8];
 char unknown2C[0x18];
 unsigned short weight;
 unsigned char steps,locks;
};
Rva005C8876Position LargeGroupAudioGridCell::getPreferredAudioPosition(Rva005C8876Grid *grid)
{
 Rva005C8876Position result;
 result.x=x; result.y=y;
 float distance=grid->cellWidth/3.0f;
 float totalX=0,plusX=0,totalY=0,plusY=0;
 if(neighbors[0]) { totalX+=neighbors[0]->weight; plusX+=neighbors[0]->weight; }
 if(neighbors[1]) { totalX+=neighbors[1]->weight; plusX-=neighbors[1]->weight; }
 if(neighbors[2]) { totalY+=neighbors[2]->weight; plusY+=neighbors[2]->weight; }
 if(neighbors[3]) { totalY+=neighbors[3]->weight; plusY-=neighbors[3]->weight; }
 if(neighbors[4]) { float w=neighbors[4]->weight*0.7071067811865476; totalX+=w; plusX+=w; totalY+=w; plusY+=w; }
 if(neighbors[5]) { float w=neighbors[5]->weight*0.7071067811865476; totalX+=w; plusX+=w; totalY+=w; plusY-=w; }
 if(neighbors[6]) { float w=neighbors[6]->weight*0.7071067811865476; totalX+=w; plusX-=w; totalY+=w; plusY+=w; }
 if(neighbors[7]) { float w=neighbors[7]->weight*0.7071067811865476; totalX+=w; plusX-=w; totalY+=w; plusY-=w; }
 if(totalX!=0) result.x+=(plusX/totalX)*distance;
 if(totalY!=0) result.y+=(plusY/totalY)*distance;
 result.z=TheTerrainLogic->getGroundHeight(result.x,result.y,0);
 return result;
}
