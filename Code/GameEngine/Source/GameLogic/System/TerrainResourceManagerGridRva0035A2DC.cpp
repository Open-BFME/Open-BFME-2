// ?rva0035A2DC@Rva0035A2DC@@QAEXPAURegion3D@@M@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <math.h>
#include <vector>
#include <list>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"
struct BfmePod8
{
public:
	int a[2]; // +0x00
};
struct BfmeE8
{
public:
	int a; // +0x00
	int b; // +0x04
};
namespace _STL {template<> void vector<BfmeE8,allocator<BfmeE8> >::reserve(unsigned int);}
class Rva0035A18D {
public: Rva0035A18D();~Rva0035A18D();
 _STL::vector<BfmePod8> values; int state;
};
class PlayerList {public:int rva002A7C0B(bool);};
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
struct Rva0035A238Argument;
class Rva000CBA20;
struct BfmePod12;
class Rva0035A238
{
public:
	void rva0035A238(Rva0035A238Argument *argument, float value, bool flag, bool front);
	void rva00359E93(Rva0035A238Argument *argument, float value, bool front, bool extra);
	void rva00359D99(Rva000CBA20 *center, float radius);
	void rva0035A14F(Rva0035A238Argument *argument);
private:
	char unknown00[0x14];
	_STL::list<BfmePod12> records;
};
struct Entry00359D42;
class Cb00359D42;
struct ResourceCell;
class TerrainResourceManager {
public:
	void enumerateRegisteredClaimants(int mask, Cb00359D42 *cb);
	void rva003598A5(int,int,int,void *);
public:
	void rva0035997F(int,int,int,void *);
public:
	float rva00359A0C(float,float,float,bool,int);
public:
	unsigned int getCellClaimant(int,int,int);
public:
	void updateMapConstantCells();
public:
	float getCellSize() const { return cell3C; }
private:
	char pad00[0x14];
	Entry00359D42 *m_list;
	char pad18[4];
private:
	float originX1C, originY20;
private:
	char pad24[0x10];
private:
	int width34,height38;
private:
	float cell3C;
private:
	ResourceCell *cells40;
public:
	void tryToClaimCell(int,int,int,ObjectID,bool,int*,int*);
public:
	bool isCellClaimable(int, int, int, int, bool, int);
public:
	void rva0035A61F(unsigned int *color, int x, int y, int claimant);
private:
	__forceinline bool isClaimable(int cx, int cy, int claimant)
	{
		return isCellClaimable(cx, cy, 0, 0, false, claimant);
	}
};
class Rva00359E04Owner;
class Rva00359E04Listener;
class Rva00359E04Listener {
public:virtual void slot00();virtual void slot01();virtual void notify00(Rva00359E04Owner*);
};
class Rva00359E04Listener;
class Rva00359E04Owner;
struct Rva00359AECCall;
class Rva00359BE8List
{
public:
	void forEach(void (Rva00359E04Listener::*notify)(Rva00359E04Owner *), Rva00359E04Owner *owner);
	void apply(const Rva00359AECCall &call);
private:
	Rva00359E04Listener **m_begin;
	Rva00359E04Listener **m_end;
	Rva00359E04Listener **m_capacity;
	unsigned int m_index;
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
