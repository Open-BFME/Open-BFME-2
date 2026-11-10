// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /I.
//
// ?cellCallback@Rva002F5925Info@@QAEHPAVPathfindCell@@0HH@Z, retail 0x002f5925, 853 bytes. Banked partial (score 0.997991) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native2F5925..2F5C7A full853 RET16; published2F6B22 walk names
// the callback receiver. BF1 pinned575 ExamineCellsStructCellCallback and
// ZH examineCellsCallback provide purpose; native proves each target delta.
#include <math.h>
#include "Coord3D.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

struct In002E6BA1
{
	Int m_00;
	Int m_04;
};

class Rva002E6BA1;
#include "../../Include/Common/MixFileInfoBuffer.h"

extern int TheMixFileInfoPool;
void Rva0052DBCDInit(void);
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in);

class Rva002E6AF3
{
public:
	int get() const;
};

class Rva002E6B06
{
public:
	int rva002E6B06();
};

#include "../../Include/GameLogic/PathfindCell.h"

class Rva002F5925CellView
{
public:
	Bool getOpen() const { return (unsigned char)reinterpret_cast<const Rva002E6AF3 *>(this)->get() != 0; }
	Bool getClosed() { return (unsigned char)reinterpret_cast<Rva002E6B06 *>(this)->rva002E6B06() != 0; }
	Int getType() const {return (Int)(m_flags&15);}
 Bool getPinched()const{return ((m_flags>>16)&1)!=0;}
 Bool getBit23()const{return ((m_flags>>23)&1)!=0;}
 Int getLayer() const { return (m_flags >> 4) & 0x3F; }
	Bool getBit21() const { return ((m_flags >> 21) & 1) != 0; }
	int getCostSoFar() const { return m_info->field12; }
	void setCostSoFar(unsigned short cost) { m_info->field12 = cost; }
	void setTotalCost(unsigned short cost) { m_info->field10 = cost; }
	__forceinline void allocateInfo(In002E6BA1 *coord)
	{
		if (!m_info)
		{
			if (TheMixFileInfoPool == 0)
				Rva0052DBCDInit();
			m_info = Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (int)this, coord);
		}
		else
		{
			m_info->m_0C = 0;
		}
	}
	void setBlockedByAlly() { m_info->m_flags &= ~1u; }

	MixFileInfoBuffer *m_info;
	char m_pad04[0x0C - 4];
	unsigned int m_flags;
};

struct Rva002F4491FireCell
{
	char m_pad00[6];
	unsigned short m_count;
	char m_pad08[0x14 - 8];
};

class Rva002872BA
{
public:
	static __forceinline Int realToIntFloor(Real realValue)
	{
		Real floored = (Real)floor(realValue);
		long i;
		__asm {
			fld [floored]
			fistp [i]
		}
		return i;
	}
	__forceinline Bool isBurning(const Coord3D &pos) const
	{
		Int x = realToIntFloor((pos.x + 0.5f) * 0.1f);
		Int y = realToIntFloor((pos.y + 0.5f) * 0.1f);
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
			return m_cells[x][y].m_count > 0;
		return false;
	}

private:
	char m_pad00[0x70];
	Rva002F4491FireCell **m_cells;
	char m_pad74[4];
	Int m_width;
	Int m_height;
};
extern Rva002872BA *TheTriggerManager;
static __forceinline Rva002F5925CellView *cellView(PathfindCell *cell) { return (Rva002F5925CellView *)cell; }


#include "../../../Libraries/Include/Lib/ICoord2D.h"
enum PathfindLayerEnum {OBSERVED_LAYER_1=1};
struct CallbackTemplate {char pad[0x108];unsigned kind[8];unsigned kindOf(unsigned n)const{return kind[n>>5]&(1U<<(n&31));}};
class Object {public:void *vptr;CallbackTemplate *definition;char pad8[0x250-8];void *observed250;};
struct TCheckMovementInfo {ICoord2D cell;PathfindLayerEnum layer;int radius;bool centerInCell,field11;char pad12[2];unsigned options;int ignoreID;char pad1C[16];int field2C;bool field30,field31,field32;char pad33;int blockers;};
#include "../../Include/Common/Rva002E6FDF.h"
#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
// Original spelling is unknown. Native9FF0CC is the four-byte BSS counter
// cleared by the search entry points and incremented against the limit at121C.
// All users share this owner; its unsigned view preserves the native comparison.
unsigned int PathfinderSearchCellsVisited;
int isGroundOrBridgeLayer(int);
#include "../../Include/GameLogic/PathfindZoneManager.h"
#include "../../Include/Common/Rva002E6DC4.h"
#include "../../Include/Common/Rva002EBC7FPair.h"
class Pathfinder {
public:
 bool rva002EA658(Object*,TCheckMovementInfo&,const ICoord2D*);
 int CalcExtraCosts(Object*,PathfindCell*,Rva002EBC7FPair*,int,int,bool);
 int rva002F0A72(PathfindCell*,PathfindCell*);
 void AddToOpenList(PathfindCell*);
 char pad0[0x24];int loX,loY,hiX,hiY;char pad34[4];bool tunneling;
 char pad39[0x460-0x39];PathfindZoneManager zones;
};
struct Rva002F5925Info
{
public:
	int cellCallback(PathfindCell*,PathfindCell*,int,int);
	Pathfinder *pathfinder; // +0x00
	char data4[16]; // +0x04
	bool center; // +0x14
	bool human; // +0x15
	char m_pad16[0x2];
	int radius; // +0x18
	Object *object; // +0x1C
	PathfindCell *goal; // +0x20
	int ignoreID; // +0x24
	ICoord2D previous; // +0x28
	int range; // +0x30
};
int Rva002F5925Info::cellCallback(PathfindCell *from,PathfindCell *to,int x,int y)
{
 if(PathfinderSearchCellsVisited>TheWritableGlobalData->m_maxCellsToExamineTowardsGoal)return 1;
 ++PathfinderSearchCellsVisited;
 if(range>0){int dx=x-cellView(goal)->m_info->field00;int dy=y-cellView(goal)->m_info->field04;if((dx*dx+dy*dy)*100<range*range)return 1;}
 Coord3D point;point.x=(float)(x*10);point.y=(float)(y*10);
 if(TheTriggerManager->isBurning(point))return 1;
 Pathfinder *localPathfinder=pathfinder;
 if(localPathfinder->tunneling)return 1;
 if(from){
  if(cellView(to)->getOpen() || cellView(to)->getClosed())return 1;
  if(!((Rva002E6DC4*)localPathfinder)->rva002E6DC4(data4,to))return 1;
  if((unsigned char)isGroundOrBridgeLayer(cellView(to)->getLayer()) && !localPathfinder->zones.IsPassable(x,y))return 1;
  if(cellView(from)->getLayer()!=cellView(to)->getLayer())return 1;
  if(cellView(to)->getPinched())return 1;
  if(cellView(to)->getBit23()){
   if(cellView(goal)->getType()!=0 || !object->observed250 || !object->definition->kindOf(0xBF))return 1;
  }
  if(cellView(to)->getType()==2)return 1;
  if(human){if(x<pathfinder->loX || y<pathfinder->loY || x>pathfinder->hiX || y>pathfinder->hiY)return 1;}
  TCheckMovementInfo info;((Rva002E6FDF*)&info)->rva002E6FDF();
  info.cell.y=y;info.layer=(PathfindLayerEnum)cellView(from)->getLayer();info.centerInCell=center;info.radius=radius;
  info.options=(object->definition->kindOf(0x5A)?1:16)|2;info.ignoreID=ignoreID;
  info.cell.x=x;
  info.field11=false;
  if(!pathfinder->rva002EA658(object,info,&previous) || info.blockers)return 1;
  In002E6BA1 coord;coord.m_00=x;coord.m_04=y;
  unsigned newCost=cellView(from)->getCostSoFar()+(cellView(to)->getBit21()?2.5f:5.0f);
  newCost+=pathfinder->CalcExtraCosts(object,from,(Rva002EBC7FPair*)&coord,info.radius,info.radius+(info.centerInCell?1:0),true);
  cellView(to)->allocateInfo(&coord);cellView(to)->setBlockedByAlly();
  int remaining=pathfinder->rva002F0A72(to,goal);
  cellView(to)->setCostSoFar((unsigned short)newCost);to->SetParentCell((int*)from);
  cellView(to)->setTotalCost((unsigned short)(cellView(to)->getCostSoFar()+remaining));pathfinder->AddToOpenList(to);
 }
 previous.x=x;previous.y=y;return 0;
}
