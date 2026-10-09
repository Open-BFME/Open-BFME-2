// cl: /O1 /G7 /arch:SSE /MD
// TerrainResourceManager's grid traversal. WB names the neighboring
// updateMapConstantCells359C31 / enumerateRegisteredClaimants359D42 and
// DoXfer35ABE0 in this logical file. The original traversal names are unknown.
// Native359A0C converts world coordinates/radius to cells and calls35997F;
// both native and WB E60FF0 retain ECX=this on each span call at3598A5.
// The span body does not read this, but its callers prove the member ABI.
// Replace the former standalone stdcall view; preserve all38 bytes and the
// same visitor slot0. No additional name is pinned onto the existing body.
struct Rva003598A5Obj { virtual void f(int,int); };
class TerrainResourceManager {
public:
    void rva003598A5(int,int,int,void *);
    void rva0035997F(int,int,int,void *);
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
