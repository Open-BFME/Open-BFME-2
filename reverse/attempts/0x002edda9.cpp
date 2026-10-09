// ?AdjustToNearestValidCell@Pathfinder@@QAE_NPAUCoord3D@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /ICode/Libraries/Include/Lib
// Native2EDDA9..2EDE5B RET4 and WB D465D0 establish identity and ABI.
// Only the target-proven +1208 search-budget access is represented;
// the prefix of GlobalData and the three terrain slot flags remain unnamed.
// Short search-local lifetimes reproduce the native cell/float scratch reuse.
#include "Coord3D.h"
typedef bool Bool;
typedef int Int;
struct ICoord2D { Int x,y; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class TerrainLogic {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual float getGroundHeight(float,float,Coord3D *);
 virtual float slot1C(float,float,int,int,int);
};
extern TerrainLogic *TheTerrainLogic;
class Rva002E7964 { public: void rva002E7964(ICoord2D *,unsigned char,const Coord3D *); };
class Pathfinder {
public:
 Bool AdjustToNearestValidCell(Coord3D *);
 Bool rva002EB11B(const ICoord2D *,Int,ICoord2D *,void *);
};
// WB D465D0 and native 2EDDA9..2EDE5B RET4 establish identity and ABI.
Bool Pathfinder::AdjustToNearestValidCell(Coord3D *position)
{
    ICoord2D found;
    {
        ICoord2D cell;
        ((Rva002E7964 *)this)->rva002E7964(&cell,1,position);
        if (cell.x < 0) return false;
        found.x=0; found.y=0;
        Pathfinder *context=this;
        if (!rva002EB11B(&cell,*(Int *)((char *)TheWritableGlobalData+0x1208),&found,&context)) return false;
    }
    position->x=found.x*10+1.0f;
    position->y=found.y*10+1.0f;
    position->z=TheTerrainLogic->slot1C(position->x,position->y,1,0,1);
    return true;
}

