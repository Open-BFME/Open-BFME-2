// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
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
#include <math.h>
#include "Lib/Coord3D.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
struct Rva005C8876Grid { char unknown00[0x10]; float cellWidth; float speed; };
struct Rva005C8876Position { float x,y,z; Rva005C8876Position() {} Rva005C8876Position(const Rva005C8876Position &p):x(p.x),y(p.y),z(p.z) {} };

#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../Include/GameLogic/Module/Rva002D9508.h"
class AudioManager { public:
virtual void rvaSlot0();
virtual void rvaSlot1();
virtual void rvaSlot2();
virtual void rvaSlot3();
virtual void rvaSlot4();
virtual void rvaSlot5();
virtual void rvaSlot6();
virtual void rvaSlot7();
virtual void rvaSlot8();
virtual void rvaSlot9();
virtual void rvaSlot10();
virtual void rvaSlot11();
virtual void rvaSlot12();
virtual void rvaSlot13();
virtual void rvaSlot14();
virtual void rvaSlot15();
virtual void rvaSlot16();
virtual void rvaSlot17();
virtual void rvaSlot18();
virtual void rvaSlot19();
virtual void rvaSlot20();
virtual void rvaSlot21();
virtual void rvaSlot22();
virtual void rvaSlot23();
virtual void rvaSlot24();
virtual void rvaSlot25();
virtual void rvaSlot26();
virtual void rvaSlot27();
virtual void rvaSlot28();
virtual void rvaSlot29();
virtual void rvaSlot30();
virtual void rvaSlot31();
virtual void rvaSlot32();
virtual void rvaSlot33();
virtual void rvaSlot34();
virtual void rvaSlot35();
virtual void rvaSlot36();
virtual void rvaSlot37();
virtual void rvaSlot38();
virtual void rvaSlot39();
virtual void rvaSlot40();
virtual void rvaSlot41();
virtual void rvaSlot42();
virtual void rvaSlot43();
virtual void rvaSlot44();
virtual void rvaSlot45();
virtual void rvaSlot46();
virtual void rvaSlot47();
virtual void rvaSlot48();
virtual void rvaSlot49();
virtual void rvaSlot50();
virtual void rvaSlot51();
virtual void rvaSlot52();
virtual void rvaSlot53(unsigned int,const void *);
};
extern AudioManager *TheAudio;

class LargeGroupAudioGridCell {
public:
 Rva005C8876Position getPreferredAudioPosition(Rva005C8876Grid *grid);
 void update(Rva005C8876Grid *grid);
 float x,y;
 BfmeAudioEventPrefix136 *loop;
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

// Native 0x005C8A98..0x005C8C37, 415 bytes, RET4: WB names this method update
// (LargeGroupAudioGridCell.cpp, reverse/wb_name_leads.csv). The looping event
// glides toward getPreferredAudioPosition: a countdown (steps) lerps by 1/steps,
// otherwise the move is clamped to grid->speed per call, then the event position
// is set (0x002D9508) and pushed through audio slot 53.
// Codegen finding: retail keeps the clamped delta as three volatile-style reads
// that land in xmm0..2 before the scale factor is stored (fstp to a stack home)
// and multiplies each by the memory-resident factor (mulss reg,[factor]); reading
// delta through a volatile view while the factor stays an ordinary float
// reproduces it, whereas a volatile factor flips the operand roles.
void LargeGroupAudioGridCell::update(Rva005C8876Grid *grid)
{
 if(loop) {
  Rva005C8876Position preferred=getPreferredAudioPosition(grid);
  bool valid;
  BfmeEventPositionView current=loop->rva002DA1CC(valid);
  float maxSpeed=grid->speed;
  if(!valid) current=*reinterpret_cast<BfmeEventPositionView *>(&preferred);
  BfmeEventPositionView next;
  if(steps>0) {
   float factor=1.0f/steps;
   next.x=current.x+(preferred.x-current.x)*factor;
   next.y=current.y+(preferred.y-current.y)*factor;
   next.z=current.z+(preferred.z-current.z)*factor;
   --steps;
  } else {
   Coord3D delta;
   delta.x=preferred.x-current.x;
   delta.y=preferred.y-current.y;
   delta.z=preferred.z-current.z;
   float lengthSq=delta.z*delta.z+delta.y*delta.y+delta.x*delta.x;
   if(lengthSq<=maxSpeed*maxSpeed) {
    next=*reinterpret_cast<BfmeEventPositionView *>(&preferred);
   } else {
    float factor=maxSpeed/(float)sqrt((double)lengthSq);
    volatile Coord3D &vd=delta; float dx=vd.x, dy=vd.y, dz=vd.z;
    dx*=factor; dy*=factor; dz*=factor;
    next=current;
    next.x+=dx; next.y+=dy; next.z+=dz;
   }
  }
  reinterpret_cast<Rva002D9508 *>(loop)->rva002D9508(&next);
  TheAudio->rvaSlot53(loop->m_int0C,&next);
 }
}
