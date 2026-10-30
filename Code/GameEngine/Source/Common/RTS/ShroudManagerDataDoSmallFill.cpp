// cl: /O2 /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /EHsc /MD
// ShroudManager::Data::DoSmallFill, native 0x0073AAE0..0x0073AD8D (685B, RET 0xC).
// Identity: WB 0x17E0670 names the body and its exact warning text; native
// UpdateCellsTouched 0x0073AD90 calls it for small geometry.
// Semantic guide: BFME 1 575ba2b PartitionData_doSmallFill.cpp (COI list
// model, addCoverage link order, WWMath fld/fistp float-to-int idiom); BFME 2
// replaces the circular fill with this rectangular one (target-only facts:
// half-cell radius clamp, floor of the four cell edges, row ranges from the
// grid's rowed 0x0073A2A0 and the 0xA8 cell / 0x10 COI strides).
// The row walk returns its end iterator into the row's first-cell slot, which
// is written back only when the row was non-empty.
#include <math.h>
#include <new>
#include "ascii_string.h"

class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual Debug &slot20(float value);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug &slot6c(int first, int second, int third);
};

extern Debug *theDebug;

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

// WWMath::Float_To_Long idiom.
__forceinline int smallFillInteger(float value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

struct SmallFillCOI;

class BfmeCellFD
{
public:
	SmallFillCOI *first;
	char opaque04[0xA8 - 4];
};

struct SmallFillCOI
{
	BfmeCellFD *cell;
	void *owner;
	SmallFillCOI **previous;
	SmallFillCOI *next;
};

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
    void rva0073CE90(int,int,int,int,int,int);
	char opaque00[4];
	float originX, originY;
	char opaque0C[0x1C - 0xC];
	float cellSize, scale;
};

class SmallFillNamedObject
{
public:
	virtual AsciiString name();
};

class UpdateOwner;
class ShroudManager
{
public:
	class Data
	{
	public:
		bool DoSmallFill(float x, float y, float radius);
        void UpdateCellsTouched();
		Gen_008F7CD0 *grid;
		SmallFillNamedObject *object;
		SmallFillNamedObject *ghost;
        char opaque0C[0x1C - 0xC];
		SmallFillCOI *coi;
        int coiCount;
        int shroudedness[20];
        int otherStates[20];
        unsigned char playerFlags[20];
        int cellX,cellY;
        int revealRadii[3];
        unsigned revealMask;
        float rotation;
        int changeRadii[3];
        unsigned changeMasks[3],changeAmounts[3];
        bool forceUpdate;
	};
};

// Link each cell of [first, last) to the next free COI; returns the end iterator.
__forceinline BfmeCellFD *smallFillRow(SmallFillCOI *&out, BfmeCellFD *first, BfmeCellFD *const &last)
{
	while (first != last)
	{
		BfmeCellFD *cell = first;
		SmallFillCOI *current = out++;
		++first;
		current->cell = cell;
		SmallFillCOI *next = cell->first;
		current->next = next;
		if (next)
			next->previous = &current->next;
		current->previous = (SmallFillCOI **)cell;
		cell->first = current;
	}
	return first;
}

__forceinline Debug &smallFillName(Debug &stream, const AsciiString &name)
{
	stream.slot38(name.str());
	return stream;
}

bool ShroudManager::Data::DoSmallFill(float x, float y, float radius)
{
	float cellSize = grid->cellSize;
	if (radius > cellSize * 0.5f)
	{
		bfmeRva000387C0() && (_bfme_debugRecordCallsite(1), theDebug->slot60(),
			(smallFillName(theDebug->slot6c(0, 0, 0).slot38("Object "),
				object ? object->name() : AsciiString("*unknown*"))
				.slot38(" is too large for 'small' geometry.\nRadius given is ").slot20(radius).slot38(" but maximum radius for small geometry is ")
				.slot20(grid->cellSize * 0.5f).slot38("; truncating.\n\nIn order to fix this problem either set the geometry of the given object\nto non-small or reduce the geometry major radius.\n")).slot4c(2), true);
		radius = grid->cellSize * 0.5f;
	}
	SmallFillCOI *out = coi;
	int firstX = smallFillInteger((float)floor((double)((x - radius - grid->originX) * grid->scale)));
	int lastX = smallFillInteger((float)floor((double)((x + radius - grid->originX) * grid->scale)));
	int firstY = smallFillInteger((float)floor((double)((y - radius - grid->originY) * grid->scale)));
	int lastY = smallFillInteger((float)floor((double)((y + radius - grid->originY) * grid->scale)));
	while (firstY <= lastY)
	{
		BfmeCellFD *first, *last;
		grid->rva0073A2A0(&first, &last, firstX, lastX, firstY);
		++firstY;
		if (first != last)
			first = smallFillRow(out, first, last);
	}
	return true;
}

// ShroudManager::Data::UpdateCellsTouched, native 0x0073AD90..0x0073B216,
// complete 1158B instance entry. WB 0x017E0C10 independently names the
// method and m_ghostObj+8 assertion. The native call graph, geometry query,
// COI fill dispatch and three-radius reveal/change operations agree.
// Semantic/structural guide: Open-BFME-1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/GameEngine/Source/GameLogic/Object/PartitionData_updateCellsTouched.cpp.
// Target evidence supplies 20 player slots, three reveal radii at+E0,
// mask+EC, rotation+F0, three change radii/masks/amounts at+F4/+100/+10C,
// cached cell coordinates+D8/+DC and rotation invalidation flag+118.
// The donor's PartitionData spelling is not claimed for this target.
// The owner views below retain neutral names: native proves their virtual
// base conversion and slots, but does not establish their original types.
// GeometryShape is 36B with the existing GeometryInfo query and AsciiString
// lifetime; the extra byte at+21 is initialized to one, purpose unknown.
// Existing CDEArraySlot destructor pin proves the empty element callback.
// Existing address-derived DoShroudReveal declaration is the independently
// proven thiscall(x,y,radii[3],rotation,mask) contract from the rowed739A30
// caller. No callee implementation or original method name is inferred here.
// Native x87 rounding uses the existing FISTP conversion helper.
// The TU-local distance utility takes grid before distance so MSVC evaluates
// the float argument before loading the receiver, as in the donor guide.
// It has internal linkage; no public grid method or target name is added.
#include "Lib/Coord3D.h"
struct UpdateOffset { UpdateOffset():x(0),y(0),z(0){} float x,y,z; };
struct GeometryShape {
 __declspec(dllimport) __forceinline GeometryShape():type(0),height(1),major(1),minor(1),enabled(true),unmodelled21(true){}
 int type;float height,major,minor;UpdateOffset offset;AsciiString name;
 bool enabled,unmodelled21;
};
class GeometryInfo {public:void rva006BD9C0(GeometryShape&)const;void*vt;bool small;};
class UpdateThing {
public:virtual const GeometryInfo* geometry()const;
 virtual const Coord3D*position()const;virtual float angle()const;
};
class UpdateOwner:public virtual UpdateThing {
public:virtual void slot00();virtual void cellChanged();virtual void slot08();
 virtual void reveal(unsigned*,float*,float*,float*);
 virtual float change(int,unsigned*,unsigned*);
};
struct CDEArraySlot {~CDEArraySlot();char storage[16];};
class BfmeThingCDE {public:void d_008f7ec0();void initializeArray(int);
 bool DoRectFill(float,float,float,float,float);
private:friend class ShroudManager::Data;bool rva0073A9B0(float,float,float);};
class BfmeShapeEU;
class BfmeHostEU {public:int bfmeStepsEU(const BfmeShapeEU*);};
class ShroudManagerImpl {public:
 void QueueUndoShroudReveal(int,int,int*,float,unsigned);
private:friend class ShroudManager::Data;
 void DoShroudReveal(int,int,void*,float,int);
};

// Calls retain the existing provider owner spellings; no alias or new pin.
__forceinline int updateFloor(float gridCoordinate){return smallFillInteger((float)floor((double)gridCoordinate));}
__forceinline int updateCeil(float cellDistance){return smallFillInteger((float)ceil((double)cellDistance));}
static __forceinline int updateDistance(Gen_008F7CD0 *grid,float distance){return updateCeil(distance*grid->scale);}
void ShroudManager::Data::UpdateCellsTouched()
{
 if(!object && !ghost)return;
 SmallFillNamedObject*chosen=object?object:ghost;
 UpdateOwner*obj=(UpdateOwner*)chosen;
 UpdateThing*thing=obj;
 const GeometryInfo*geom=thing->geometry();
 const Coord3D*pos=thing->position();
 ((BfmeThingCDE*)this)->d_008f7ec0();
 GeometryShape shape;
 geom->rva006BD9C0(shape);
 if(!geom->small){
  int count=((BfmeHostEU*)grid)->bfmeStepsEU((const BfmeShapeEU*)&shape);
  if(count!=coiCount){delete[](CDEArraySlot*)coi;coi=0;((BfmeThingCDE*)this)->initializeArray(count);}
 }
 if(geom->small)DoSmallFill(pos->x,pos->y,shape.major);
 else switch(shape.type){
 case 0:case 1:((BfmeThingCDE*)this)->rva0073A9B0(pos->x,pos->y,shape.major);break;
 case 2:{float minor=shape.minor;float major=shape.major;
  ((BfmeThingCDE*)this)->DoRectFill(pos->x,pos->y,major,minor,thing->angle());break;}
 }
 if(object){
  int x=updateFloor((pos->x-grid->originX)*grid->scale);
  int y=updateFloor((pos->y-grid->originY)*grid->scale);
  if(x==cellX && y==cellY && revealRadii[0]>=0 &&
    (revealRadii[0]!=revealRadii[1] || revealRadii[0]!=revealRadii[2]) &&
    ((UpdateOwner*)object)->angle()!=rotation)forceUpdate=true;
  if(x!=cellX || y!=cellY || forceUpdate){
   if(revealRadii[0]>=0)((ShroudManagerImpl*)grid)->QueueUndoShroudReveal(cellX,cellY,revealRadii,rotation,revealMask);
   int i;
   for(i=0;i<3;++i)if(changeRadii[i]>=0 && changeAmounts[i]>0)
    grid->rva0073CE90(cellX,cellY,changeRadii[i],i,-(int)changeAmounts[i],changeMasks[i]);
   float ranges[3];
   ((UpdateOwner*)object)->reveal(&revealMask,&ranges[0],&ranges[1],&ranges[2]);
   rotation=((UpdateOwner*)object)->angle();
   for(i=0;i<3;++i)revealRadii[i]=ranges[i]<0?-1:updateDistance(grid,ranges[i]);
   if(revealRadii[0]>=0)((ShroudManagerImpl*)grid)->DoShroudReveal(x,y,revealRadii,rotation,revealMask);
   for(i=0;i<3;++i){
    float range=((UpdateOwner*)object)->change(i,&changeAmounts[i],&changeMasks[i]);
    changeRadii[i]=range<0?-1:updateDistance(grid,range);
    if(changeRadii[i]>=0 && changeAmounts[i]>0){
     if(changeMasks[i]==0)changeMasks[i]=revealMask;
     grid->rva0073CE90(x,y,changeRadii[i],i,changeAmounts[i],changeMasks[i]);
    }
   }
   cellX=x;cellY=y;((UpdateOwner*)object)->cellChanged();
  }
 }
 for(int playerIndex=0;playerIndex<20;++playerIndex)shroudedness[playerIndex]=0;
}
