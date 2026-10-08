// ?newMap@VictorySystemNewMapView@@QAEXXZ
// partial score=0.99581 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// WB1075B20 names VictorySystem::newMap and the native boundary is404DE5..405094.
// Reference VictorySystem reset/CellGrid construction provide subsystem leads;
// this body is reconstructed from target WB/native evidence, not a byte lift.
// Named TheTerrainLogic and ThePlayerList providers replace the old global wall.
// The nonthrowing parameter finder404D70 walks records and calls the rowed
// read-only string comparator6A00. Native EH also excludes the Default temporary.
// Remaining mismatch: the second argument-cleanup POP precedes FMUL0.5 here;
// retail places that POP after FMUL. Full emitted size687 and EH data agree.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);
struct Region3D {Coord3D lo,hi;float width()const{return hi.x-lo.x;}float height()const{return hi.y-lo.y;}};
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
class NewMapTerrainView {public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
 virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();virtual void slot08();
 virtual void getExtent(Region3D *);
};
class Player {public:char unknown00[0x58];AsciiString faction;};
class PlayerList {public:Player *getNthPlayer(int);char unknown00[0x14];unsigned count;};
extern PlayerList *ThePlayerList;
class CellGrid {public:CellGrid(int,int,float,float);private:int width,height;unsigned count;float size,offset;void *cells,*values;};
class Rva00404B03 {public:void rva00404B03();};
class Rva00404D70 {public:int rva00404D70(const AsciiString &) throw();};
class VictorySystemNewMapView {public:void newMap();private:
 char unknown00[0x10];float cellSize;unsigned playerCount;float scale,subtract,radius,bonus;
 unsigned playerParameterIndex[20];char unknown78[0x12c-0x78];CellGrid *grids[2];bool initialized;
};
void VictorySystemNewMapView::newMap()
{
 reinterpret_cast<Rva00404B03 *>(this)->rva00404B03();
 if(cellSize>0.0f){
  Region3D extent;
  cellSize=100.0f>cellSize?100.0f:cellSize;
  reinterpret_cast<NewMapTerrainView *>(TheTerrainLogic)->getExtent(&extent);
  if(extent.width()>0.0f && extent.height()>0.0f){
   cellSize=cellSize>(extent.height()>extent.width()?extent.width():extent.height())?
    (extent.height()>extent.width()?extent.width():extent.height()):cellSize;
   int width=(int)ceil(fabs(extent.width())/cellSize);
   int height=(int)ceil(fabs(extent.height())/cellSize);
   grids[0]=new CellGrid(width,height,cellSize,0.0f);
   ++width;++height;
   grids[1]=new CellGrid(width,height,cellSize,-(cellSize/2.0f));
  }
  bonus=bonus>1.0f?bonus:1.0f;
  radius=(cellSize*bonus/2.0f)*sqrt(2.0f);
  playerCount=ThePlayerList->count;
  for(unsigned i=0;i<playerCount;++i){
   bool neutral=false;
   Player *player=ThePlayerList->getNthPlayer(i);
   AsciiString faction=player->faction;
   int index=reinterpret_cast<Rva00404D70 *>(this)->rva00404D70(faction);
   if(faction.isEmpty() || faction.compareNoCase("Observer")==0 || faction.compareNoCase("Civilian")==0)
    neutral=true;
   if(index==0x7fffffff)
    index=reinterpret_cast<Rva00404D70 *>(this)->rva00404D70(AsciiString("Default"));
   if(index!=0x7fffffff)
    playerParameterIndex[i]=index | (neutral?0x80000000:0);
   else playerParameterIndex[i]=0;
  }
  initialized=true;
 }
}
