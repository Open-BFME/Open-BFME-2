// cl: /O1 /G7 /arch:SSE /MD
// TerrainResourceManager's grid traversal. WB names the neighboring
// updateMapConstantCells359C31 / enumerateRegisteredClaimants359D42 and
// DoXfer35ABE0 in this logical file. The original traversal names are unknown.
// Native359A0C converts world coordinates/radius to cells and calls35997F;
// both native and WB E60FF0 retain ECX=this on each span call at3598A5.
// The span body does not read this, but its callers prove the member ABI.
// Replace the former standalone stdcall view; preserve all38 bytes and the
// same visitor slot0. No additional name is pinned onto the existing body.
#include <math.h>
#include "TerrainResourceVisitorView.h"
// The existing ratio provider reads the complete visitor's counters10/14.
class Rva00359835 { public: float rva00359835() const; };
// A plain cast emits _ftol2 (211B query); retail uses this established
// WWMath x87 rounding shape. Only this compiler blocker requires asm.
__forceinline int cellInteger(float value)
{
 int result;
 __asm fld value
 __asm fistp result
 return result;
}

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Pathfinder {public: void GetCellType(int,void*,void*,void*,int);};
class AI {public: char pad00[0x10]; Pathfinder *pathfinder10;};
class TerrainLogic;
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
class Rva00359C06Listener {
public: virtual void slot00(); virtual void notify(void*,int,int);
};
class Rva00359C06List {
public: void forEach(void (Rva00359C06Listener::*)(void*,int,int),void*,int,int);
};

struct CellClaimant { int player; unsigned int object; };
struct ResourceCell { CellClaimant *first,*last,*capacity; int state; };
struct Rva003598A5Obj { virtual void f(int,int); };
class TerrainResourceManager {
public:
    void rva003598A5(int,int,int,void *);
    void rva0035997F(int,int,int,void *);
    float rva00359A0C(float,float,float,bool,int);
    unsigned int getCellClaimant(int,int,int);
    void updateMapConstantCells();
    // ?TerrainResourceManager::getCellSize present-unmatched
    float getCellSize() const { return cell3C; }
private:
    char pad00[0x1c];
    float originX1C, originY20;
    char pad24[0x10];
    int width34,height38;
    float cell3C;
    ResourceCell *cells40;
};
void TerrainResourceManager::rva003598A5(int low,int high,int y,void *visitor)
{
    Rva003598A5Obj *o=static_cast<Rva003598A5Obj *>(visitor);
    for(int x=low;x<=high;++x) o->f(x,y);
}

// Native35997F..359A0C and WB E60FF0: midpoint-circle span traversal.
// WB names the surrounding TerrainResourceManager methods; original name unknown.
void TerrainResourceManager::rva0035997F(int centerX,int centerY,int radius,void *visitor)
{
    int x=0;
    int y=radius;
    int error=2*(1-radius);
    for(;;) {
        if(error+y>0) {
            if(y==0 && radius==1) ++x;
            rva003598A5(centerX-x,centerX+x,centerY+y,visitor);
            if(y==0) break;
            rva003598A5(centerX-x,centerX+x,centerY-y,visitor);
            --y;
            error-=2*y-1;
        }
        if(x>error) {
            ++x;
            error+=2*x+1;
        }
    }
}

// Native359A0C..359AEC RET20; WB E60670 converts world-space coordinates
// to cells, visits the enclosing grid circle, and returns successes/attempts.
// Origin1C/20 and cell3C are target accesses; the original method name is unknown.
float TerrainResourceManager::rva00359A0C(float x,float y,float radius,bool flag,int player)
{
 x-=originX1C;
 y-=originY20;
 int cellX=cellInteger((float)floor((x/cell3C)+0.5f));
 int cellY=cellInteger((float)floor((y/cell3C)+0.5f));
 int cellRadius=cellInteger((float)ceil(radius/cell3C));
 Rva0035986C visitor((int)this,flag,player,false);
 rva0035997F(cellX,cellY,cellRadius,&visitor);
 return reinterpret_cast<const Rva00359835*>(&visitor)->rva00359835();
}

// Native359902..35997F: range/initialized guards and state2 player search,
// state3 first claimant with empty-cell reset. WB E608E0 names getCellClaimant
// and has the same cell states and record roles. Return representation is inferred.
unsigned int TerrainResourceManager::getCellClaimant(int x,int y,int player)
{
 if(x<0 || x>=width34 || y<0 || y>=height38 || !cells40) return 0;
 ResourceCell& cell=cells40[y*width34+x];
 switch(cell.state) {
 case 0: case 1: return 0;
 case 2:
   if(player==-1) return 0;
   for(CellClaimant *i=cell.first;i!=cell.last;++i)
      if(i->player==player) return i->object;
   return 0;
 case 3:
   if((unsigned int)(cell.last-cell.first)<1) {cell.state=0;return 0;}
   return cell.first->object;
 default:return 0;
 }
}

// WB E60440 names updateMapConstantCells; native359C31..359D42 RET.
// Native centers cells without the world origin and writes constant state1
// for unavailable or eligible pathfinder types, then broadcasts list+4 slot1.
// Inline cell-size accessor preserves the retail SSE multiplication order.
void TerrainResourceManager::updateMapConstantCells()
{
 if(!cells40 || !TheTerrainLogic) return;
 for(int y=0;y<height38;++y) {
   for(int x=0;x<width34;++x) {
     Coord3D point;
     point.x=(x+0.5f)*getCellSize();
     point.y=(y+0.5f)*getCellSize();
     point.z=0;
     bool found=false,other=false;
     int type=2;
     TheAI->pathfinder10->GetCellType((int)&point,&found,&other,&type,1);
     if(!found || type==1 || type==7 || type==2 || type==5) {
       ResourceCell& cell=cells40[y*width34+x];
       if(cell.state!=1) {
         cell.state=1;
         reinterpret_cast<Rva00359C06List*>((char*)this+4)->forEach(&Rva00359C06Listener::notify,this,x,y);
       }
     }
   }
 }
}
