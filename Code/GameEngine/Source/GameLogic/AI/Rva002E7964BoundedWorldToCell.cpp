// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Target evidence: native 002E7964..002E79A8; calls the rowed world-to-cell
// converter then checks four signed cell bounds at this+14..20. The name and
// class remain address-neutral; a Pathfinder ownership is not established.
// The center argument is the existing pinned one-byte ABI carrier. Preserve
// that carrier across the bool callee ABI rather than normalizing it here.
struct ICoord2D {int x,y;};
#include "Coord3D.h"
struct IRegion2D {ICoord2D lo,hi;};
ICoord2D *Rva002E7875WorldToCell(ICoord2D*,bool,const Coord3D*);
class Rva002E7964 {
public:
 void rva002E7964(ICoord2D*,unsigned char,const Coord3D*);
 char pad[0x14];IRegion2D extent;
};
void Rva002E7964::rva002E7964(ICoord2D *out,unsigned char center,const Coord3D *pos){
 ICoord2D tmp;
 typedef ICoord2D *(__cdecl *CellCall)(ICoord2D*,unsigned char,const Coord3D*);
 reinterpret_cast<CellCall>(Rva002E7875WorldToCell)(&tmp,center,pos);
 if(tmp.x<extent.lo.x || tmp.y<extent.lo.y || tmp.x>extent.hi.x || tmp.y>extent.hi.y)tmp.x=-1;
 *(out?out:out)=tmp;
}
