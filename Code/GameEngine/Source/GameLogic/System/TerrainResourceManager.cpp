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

struct Rva003598A5Obj { virtual void f(int,int); };
class TerrainResourceManager {
public:
    void rva003598A5(int,int,int,void *);
    void rva0035997F(int,int,int,void *);
    float rva00359A0C(float,float,float,bool,int);
private:
    char pad00[0x1c];
    float originX1C, originY20;
    char pad24[0x18];
    float cell3C;
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
