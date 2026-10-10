// ?rva0035A2DC@Rva0035A2DC@@QAEXPAURegion3D@@M@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <math.h>
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

struct Region3D {
 Coord3D lo,hi;
 Region3D(const Region3D&);
 float width() const {return hi.x-lo.x;}
 float height() const {return hi.y-lo.y;}
};
struct BfmePod8 {int a[2];};
struct BfmeE8 {int a,b;};
namespace _STL {template<> void vector<BfmeE8,allocator<BfmeE8> >::reserve(unsigned int);}
class Rva0035A18D {
public: Rva0035A18D();~Rva0035A18D();
 _STL::vector<BfmePod8> values; int state;
};
class PlayerList {public:int rva002A7C0B(bool);};
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
struct Rva0035A238Argument;
class Rva0035A238 {public:void rva00359E93(Rva0035A238Argument*,float,bool,bool);};
class TerrainResourceManager {public:void updateMapConstantCells();};
class Rva00359E04Owner;
class Rva00359E04Listener {
public:virtual void slot00();virtual void slot01();virtual void notify00(Rva00359E04Owner*);
};
class Rva00359BE8List {
public:void forEach(void (Rva00359E04Listener::*)(Rva00359E04Owner*),Rva00359E04Owner*);
};
struct StoredClaim {StoredClaim *next,*prev;ObjectID id;float radius;bool flag,extra;char pad[2];};
class Rva0035A2DC {
public:void rva0035A2DC(Region3D*,float);
private:
 char pad00[0x14]; StoredClaim *head14;float maxRadius18;Region3D extent1C;int width34,height38;float cell3C;Rva0035A18D *cells40;
};
// Native uses FISTP with the current rounding mode; an ordinary cast emits
// a different conversion sequence (441B caller versus the native455B).
__forceinline int cellInteger(float value)
{
 int result;
 __asm fld value
 __asm fistp result
 return result;
}

void Rva0035A2DC::rva0035A2DC(Region3D *bounds,float cellSize)
{
 Region3D region(*bounds);
 if(1.0f>region.width()) region.hi.x=region.lo.x+1.0f;
 if(1.0f>region.height()) region.hi.y=region.lo.y+1.0f;
 float inverse=1.0f/cellSize;
 int width=cellInteger((float)ceil(region.width()*inverse));
 if(width<1) width=1;
 int height=cellInteger((float)ceil(region.height()*inverse));
 if(height<1) height=1;
 delete[] cells40;
 int count=width*height;
 cells40=new Rva0035A18D[count];
 for(int i=0;i<count;++i) {
    reinterpret_cast<_STL::vector<BfmeE8>*>(&cells40[i].values)->reserve(ThePlayerList->rva002A7C0B(false));
    (this ? cells40 : cells40)[i].state=0;
 }
 extent1C=region;
 width34=width;height38=height;cell3C=cellSize;
 reinterpret_cast<Rva00359BE8List*>((char*)this+4)->forEach(&Rva00359E04Listener::notify00,reinterpret_cast<Rva00359E04Owner*>(this));
 reinterpret_cast<TerrainResourceManager*>(this)->updateMapConstantCells();
 for(StoredClaim *i=head14->next;i!=head14;i=i->next) {
    Object *object=TheGameLogic->findObjectByID(i->id);
    if(object) reinterpret_cast<Rva0035A238*>(this)->rva00359E93(reinterpret_cast<Rva0035A238Argument*>(object),i->radius,false,i->extra);
 }
}
