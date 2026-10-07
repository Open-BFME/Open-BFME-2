// cl: /ICode/Libraries/Include /O1 /arch:SSE /G7 /DNDEBUG /MD
// Target 0x002F3BB3-0x002F3C09, 86B, full Ghidra RET20 boundary.
// Rowed bounded-cell helper 0x002EBC34 determines the position's cell; a
// negative x fails immediately. Otherwise the rowed 0x20-byte callback
// initializer 0x002ED7B6 receives this/owner/three opaque words/position,
// and the 467B native helper 0x002F379E receives that record, the cell and
// TheWritableGlobalData's +0x11F8 word. Provider source and their call sites
// establish Pathfinder ownership; original method/word meanings are unresolved.
// The configuration global reuses GlobalData.cpp's canonical symbol spelling.
#include "Lib/Coord3D.h"
struct ICoord2D { int x,y; };
class Rva002EBC34 { public: ICoord2D* rva002EBC34(ICoord2D*,void*,const Coord3D*); };
class Rva002ED7B6 {
public:
    Rva002ED7B6* rva002ED7B6(int,void*,int,int,int,int);
    char m_bytes[0x20];
};
class GlobalData;
extern GlobalData* TheWritableGlobalData;
struct Rva002F3BB3GlobalData { char m_lead[0x11f8]; int m_limit; };
class Pathfinder {
public:
    bool rva002F3BB3(void*,int,int,int,const Coord3D*);
    bool rva002F379E(const ICoord2D*,int,Rva002ED7B6*);
};
bool Pathfinder::rva002F3BB3(void* object,int a,int b,int c,const Coord3D* position) {
    ICoord2D cell;
    ((Rva002EBC34*)this)->rva002EBC34(&cell,object,position);
    if(cell.x<0) return false;
    Rva002ED7B6 info;
    return rva002F379E(&cell,((Rva002F3BB3GlobalData*)TheWritableGlobalData)->m_limit,
        info.rva002ED7B6((int)this,object,a,b,c,(int)position));
}
