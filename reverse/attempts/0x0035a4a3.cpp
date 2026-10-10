// ?isCellClaimable@TerrainResourceManager@@QAE_NHHHH_NH@Z
// partial score=0.94 date=2026-10-10
// ?isCellClaimable@TerrainResourceManager@@QAE_NHHHH_NH@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "../../Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
class Object {public: CellShroudStatus getShroudStatusForPlayer(int) const;};
extern GameLogic *TheGameLogic;
extern PartitionManager *TheShroudManager;
struct BfmePod8 {int a[2];};
namespace _STL {
template<> BfmePod8 *vector<BfmePod8,allocator<BfmePod8> >::erase(BfmePod8*,BfmePod8*);
}
struct ResourceCell { _STL::vector<BfmePod8> values; int state; };
class TerrainResourceManager {
public: bool isCellClaimable(int,int,int,int,bool,int);
private: char pad00[0x1c];float originX1C,originY20;char pad24[0x10];int width34,height38;float cell3C;ResourceCell *cells40;
};
bool TerrainResourceManager::isCellClaimable(int x,int y,int id,int ownId,bool force,int player)
{
 if(!cells40 || x<0 || x>=width34 || y<0 || y>=height38) return false;
 int shroud=0;
 if(!force && player>=0) {
    Coord3D point;
    point.x=(x+0.5f)*cell3C+originX1C;
    point.y=(y+0.5f)*cell3C+originY20;
    point.z=0;
    shroud=(int)TheShroudManager->getShroudStatusForPlayer(player,&point);
    if(shroud==2) return false;
 }
 ResourceCell& cell=cells40[y*width34+x];
 switch(cell.state) {
 case 0:return true;
 case 1:return false;
 case 2:
    if(force || player==-1 || shroud!=0) return true;
    for(BfmePod8 *i=cell.values.begin();i!=cell.values.end();++i)
       if(i->a[0]==player) return false;
    return true;
 case 3: {
    if(!force && shroud!=0) return true;
    BfmePod8 *first=cell.values.begin();
    BfmePod8 *last=cell.values.end();
    if((unsigned int)(last-first)>=1) {
       BfmePod8& claimant=*first;
       if(player>=0) {
          Object *object=TheGameLogic->findObjectByID((ObjectID)claimant.a[1]);
          if(!object) {
             cell.values.erase(first,last);
             cell.state=0;
             return true;
          }
          int status=(int)object->getShroudStatusForPlayer(player);
          if(status==3 || status==4) return true;
       }
       if(!force) return false;
       if(claimant.a[0]!=player && id!=0x7FFFF43 && id!=claimant.a[1] && ownId!=claimant.a[1]) return false;
    }
    else cell.state=0;
    return true;
 }
 default:return false;
 }
}
