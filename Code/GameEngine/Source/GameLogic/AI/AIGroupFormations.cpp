// AI group formation construction and placement.
// Retail 0x005494A0..0x00549C6D; WorldBuilder 0x013B96A0.
// Scalar float overloads of fabs preserve the retail x87/SSE scheduling.
// stlport
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?rva005490AE@Rva005490D2@@QBEHXZ, RVA 0x005490AE, 36B
// ?rva005490D2@Rva005490D2@@QBEHXZ, RVA 0x005490D2, 31B
// Max and summing loops over the array at +4 with count at +0 via double
// indirection; retail places them back to back. The max takes the dword at
// +0x564 with cmovg (callers 0x00549403 and 0x0054945F), which MSVC 7.1
// emits only under /arch:SSE; the sum adds the dword at +0x568 (single
// caller at 0x005493CC). xor-first and dec/jne point to /O1; neighbours are
// Disp getters and a clamped setter.
struct Leaf005490D2 {
	char pad[0x564];
	int field564;
	int field568;
};
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct FormationKind {char pad[0x78];int kind;};
struct FormationAIUpdate {int unused;FormationKind*data;};
struct FormationUnitGate {char pad[0x1f0];FormationAIUpdate*update;};
struct Mid005490D2 {
	int unk0;
	Leaf005490D2 *leaf;
 char pad8[0x30];float positionX,positionY,positionZ;char pad44[0x214];FormationUnitGate*gate;char pad25C[0x1b4];int formationId;Coord2D formationOffset;
};
struct Rva005490D2 {
	
	int count;
	Mid005490D2 *array[6];
	int rva005490AE() const;
	int rva005490D2() const;
 void rva005490F1(const Coord2D*origin,int formationId);
};
int Rva005490D2::rva005490AE() const
{
	int best = 0;
	for (int unitIndex = 0; unitIndex < count; ++unitIndex) {
		int unitWidth = array[unitIndex]->leaf->field564;
		if (unitWidth > best)
			best = unitWidth;
	}
	return best;
}
int Rva005490D2::rva005490D2() const
{
	int total = 0;
	int remainingUnits = count;
	if (remainingUnits > 0) {
		Mid005490D2 **unitIter = (Mid005490D2 **)array;
		do {
			total += (*unitIter)->leaf->field568;
			++unitIter;
		} while (--remainingUnits);
	}
	return total;
}



#include <deque>
// Formation rows are 0x1C: count plus six unit pointers. Width clamp
// 0x549237 and row stride in the formation builder independently prove this.
// TheAI/data offsets are target facts; the original spacing names are unknown.
struct FormationSpacingView {char pad[0xa0];float spacingA0,spacingA4,spacingA8;char padAC[8];int widthB4;};
class AI {public:char pad[0x18];FormationSpacingView*data;};
extern AI*TheAI;
// cl: /DNDEBUG /MD
// ?rva00549252@Rva00549252@@QAEXXZ, RVA 0x00549252, 243B
// Zero slot counts at +8 stride 0x1c then nested loops over +0x120 array
// with 0x258/0x1f0/0x78 gate plus leaf 0x568 accumulate and bfmePush.
// Evidence: prev same flags, callee rowed bfmePush 0x00548FC0, caller
// 0x00549434, offsets 0x120/0x124/0x1B4/0x1B8 and count>=10 plus k<13 gate.
class Gen_0015A260 {
public:
	void bfmePush(int value) throw();
	int m_count;
	int m_items[6];
};

void Gen_0015A260::bfmePush(int value) throw() {
 int count=m_count;
 if(count<6){m_items[count]=value;++m_count;}
}

struct Leaf00549252 {
	char m_pad[0x568];
	int m_0568;
};

struct Gate00549252 {
	char m_pad[0x78];
	int m_0078;
};

struct Inner200549252 {
	int m_00;
	Gate00549252 *m_04;
};

struct Inner100549252 {
	char m_pad[0x1F0];
	Inner200549252 *m_01F0;
};

struct Mid00549252 {
	int m_00;
	Leaf00549252 *m_04;
	char m_pad08[0x250];
	Inner100549252 *m_0258;
};

class Rva00549252 {
public:
	int m_00;
	int m_04;
	Gen_0015A260 m_slots08[10];
	int m_0120;
	Mid00549252 *m_array124[1];
	char m_pad128[0x1B4 - 0x128];
	int m_01B4;
	unsigned char m_01B8;
	void rva00549252();
};

void Rva00549252::rva00549252()
{
	int rowDepth = 0;
	int rowIndex = 0;
	m_01B4 = 0;
	if (m_00 > 0) {
		Gen_0015A260 *slot = m_slots08;
		do {
			slot->m_count = 0;
			++rowIndex;
			slot++;
		} while (rowIndex < m_00);
	}
	m_00 = 0;
	int formationKind = 0;
	if (m_00 >= 10)
		return;
	while (formationKind < 13) {
		if (m_00 >= 10)
			break;
		int unitIndex = 0;
		if (m_0120 > 0) {
			Mid00549252 **unitIter = m_array124;
			do {
				Mid00549252 *unit = *unitIter;
				Inner100549252 *s1 = unit->m_0258;
				if (s1 != 0) {
					Inner200549252 *s2 = s1->m_01F0;
					if (s2 != 0) {
						Gate00549252 *kindData = s2->m_04;
						if (kindData->m_0078 == formationKind) {
							rowDepth += unit->m_04->m_0568;
							if (rowDepth > m_04) {
								++m_00;
								if (m_00 >= 10)
									break;
								rowDepth = unit->m_04->m_0568;
							}
							m_slots08[m_00].bfmePush((int)unit);
							if (m_01B4 < rowDepth)
								m_01B4 = rowDepth;
						}
					}
				}
				++unitIndex;
				++unitIter;
			} while (unitIndex < m_0120);
		}
		if (formationKind == 3 || formationKind == 6 || formationKind == 0 || formationKind == 9 || formationKind == 12) {
			if (rowDepth > 0)
				++m_00;
			rowDepth = 0;
		}
		++formationKind;
	}
	m_01B8 = 1;
}

class Rva0015A390Inner {public:int dword_0,dword_4,dword_8,dword_c,dword_10,dword_14;};
class Rva0015A390Bucket {public:Rva0015A390Bucket();int dword_0;Rva0015A390Inner inner_4;};
struct FormationDimensions:Coord2D {FormationDimensions(float a,float b){x=a;y=b;} ~FormationDimensions(){}};
class FormationSquad {
public:
 FormationSquad();
 FormationDimensions rva00549425();
 void rva00549345(const Coord2D*origin,int formationId);
 void SetSquadWidth(int width);
 void AddUnit(Mid005490D2 *unit);

 int rows,width;
 Rva0015A390Bucket rowStorage[10];
 int unitCount;
 Mid005490D2*units[36];
 int totalHeight;
 bool ready;
};
// Target549425..549489 (100B). The served123B boundary includes two
// independent count getters at549489 and549493. The target loop repeatedly
// reads row[0], with no row-pointer advance; preserve that observable behavior.
// WB identifies the family, but its ApplyUnitPositions pairing is broader
// than this body, so the member's original name remains unknown.
FormationDimensions FormationSquad::rva00549425(){
 if(!ready)reinterpret_cast<Rva00549252*>(this)->rva00549252();
 FormationSpacingView*data=TheAI->data;
 float height=totalHeight*data->spacingA0;
 int widthTotal=0;
 for(int rowIndex=0;rowIndex<rows;++rowIndex)widthTotal+=reinterpret_cast<Rva005490D2*>(rowStorage)[0].rva005490AE();
 return FormationDimensions(widthTotal*data->spacingA4,height);
}

// Retail's independent getters subtract two16B deque iterators over8B
// elements. This is a typed ABI view of the existing concrete owner; it
// does not establish the original element type or container field names.
struct BfmeE8 {int a,b;};
template<> int _STL::_Deque_iterator_base<BfmeE8>::_M_subtract(const _STL::_Deque_iterator_base<BfmeE8>&)const;
struct FormationDequeView {
 _STL::_Deque_iterator_base<BfmeE8>start,finish;
 int size()const{return finish._M_subtract(start);}
};
class Rva00549489 {public:int get()const;FormationDequeView view;};
int Rva00549489::get()const{return view.size();}
class Rva00549493 {public:int get()const;char pad[0x14];FormationDequeView view;};
int Rva00549493::get()const{return view.size();}

// Native5491E4..549237 83B; WB caller array stride1BC establishes
// this as the FormationSquad constructor. Row default lifetimes initialize
// ten count/six-pointer records before resetting the remaining unit list.
// Existing neutral Bucket constructor clears precisely these seven words;
// its 28B storage view preserves the provider declaration and original name
// uncertainty. Width default is the target AI data field+B4 doubled.
FormationSquad::FormationSquad():rows(0),width(TheAI->data->widthB4*2),unitCount(0),totalHeight(0),ready(false){
 for(int unitIndex=0;unitIndex<36;++unitIndex)units[unitIndex]=0;
}

// Native5490F1..5491E4 complete243B. Target unit+410 ID and+414
// local offset plus gate258/1F0/kind78 are independently visible here.
// A scalar float copy preserves the native SSE loads and both spill homes;
// the canonical aggregate assignment stores the resulting eight bytes.
struct FormationPosition:Coord2D {FormationPosition(const Coord2D&rhs){x=rhs.x;y=rhs.y;}};
void Rva005490D2::rva005490F1(const Coord2D*origin,int formationId){
 int depth=0;
 for(int unitIndex=0;unitIndex<count;++unitIndex){
  int height=array[unitIndex]->leaf->field568;
  FormationSpacingView*data=TheAI->data;
  FormationPosition position(*origin);position.y+=(depth+height*0.5f)*data->spacingA0;position.x-=array[unitIndex]->leaf->field564*data->spacingA4*0.5f;
  array[unitIndex]->formationId=formationId;
  Mid005490D2*unit=array[unitIndex];
  if(unit->gate&&unit->gate->update&&unit->gate->update->data->kind==0){position.x*=0.5f;position.y*=0.5f;}
  unit->formationOffset=position;
  depth+=height;
 }
}

// Native549345..54941E complete219B. Scalar origin copying keeps
// both floats live through the visible integer-only row sum; starting
// columns before the row clamp preserves native initialization order.
void FormationSquad::rva00549345(const Coord2D*origin,int formationId){
 float halfColumn=TheAI->data->spacingA4*0.5f;
 float height=totalHeight*TheAI->data->spacingA0;
 int columns=0;
 if(rows>10)rows=10;
 for(int rowIndex=0;rowIndex<rows;++rowIndex){
  FormationSpacingView*data=TheAI->data;
  Rva005490D2*row=reinterpret_cast<Rva005490D2*>(&rowStorage[rowIndex]);
  FormationPosition position(*origin);
  position.x-=columns*data->spacingA4;
  position.x+=halfColumn;
  position.y+=(height-row->rva005490D2()*data->spacingA0)*0.5f;
  row->rva005490F1(&position,formationId);
  columns+=row->rva005490AE();
 }
}

// AIGroup::createFormation native5494A0..549C6D. Full WB13B96A0 gives
// grouping and six-attempt swap algorithm; offsets below are retail facts.
// Original argument types are not recovered: RET8 discards two unused words.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>
inline float Coord3D::length() const {return (float)sqrt(x*x+y*y+z*z);}
inline void Coord3D::normalize() {
 float len=length();
 if(len!=0.0f){float scale=1.0f/len;x*=scale;y*=scale;z*=scale;}
}
template<class T> inline volatile T &__vref(T &value){return *(volatile T *)&value;}
class Object;
struct Rva0028AC4EEntry;
class Object { public: const Rva0028AC4EEntry *rva0028AC4E() const; };
#include "../../Common/RTS/XYDistanceCallView.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)

// FormationSquad::AddUnit @ 0x00548FD4 (45B)
// WorldBuilder lead: FormationSquad::AddUnit
// Capped 36-item list leaf thiscall: clears the item's formationId word,
// appends the item while fewer than 36 are stored, then marks the squad dirty.
// Retail emits `and [esi+0x410],0` (not a folded mov) plus `lea eax,[ecx+0x120]`
// for the count access under /O1.
void FormationSquad::AddUnit(Mid005490D2 *unit)
{
	unit->formationId &= 0;

	if (unitCount < 36)
	{
		units[unitCount] = unit;
		++unitCount;
	}

	ready = false;
}

// Visible leaf from the verified549237 provider: the parent relies on ECX
// surviving this integer-only setter before advancing its squad pointer.
// FormationSquad::SetSquadWidth @ 0x00549237 (27B)
// WorldBuilder lead: FormationSquad::SetSquadWidth
// Clamps width to [2, 6] at +4.
//
//
void FormationSquad::SetSquadWidth(int squadWidth) {
 if(squadWidth<2)squadWidth=2;
 else if(squadWidth>6)squadWidth=6;
 width=squadWidth;
}
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
class GameClient {
 friend class AIGroup;
protected: DrawableID allocDrawableID();
};
enum IterOrderType { ITER_FASTEST=0, ITER_SORTED_NEAR_TO_FAR=1 };
class SimpleObjectIterator {
public:
 SimpleObjectIterator();
 virtual ~SimpleObjectIterator();
 virtual int first();
 virtual int next();
 void insert(int object, float distance);
 void sort(IterOrderType);
 char cursor[0x10];
 FormationDequeView items;
 char tail[8];
};
struct FormationMemberNode {
 FormationMemberNode *next,*previous;
 Mid005490D2 *object;
};
class AIGroup {
public:
 void createFormation(int unused0,int unused1);
 int unknown0;
 FormationMemberNode *members;
 char unknown8[0x10];
 Coord3D start,end;
};

// Rotation helper at 0x00549033, compiled through its real caller below.
// Both points and the offset use a private register ABI in retail.
static void RotateFormationOffset(const Coord3D *from,const Coord3D *to,Coord2D *offset)
{
 Coord3D direction;
 direction.x=to->x; direction.y=to->y; direction.z=to->z;
 direction.x-=from->x; direction.y-=from->y; direction.z-=from->z;
 direction.z=0.0f;
 direction.normalize();
 direction.y=0.0f-direction.y;
 Coord3D perpendicular;
 perpendicular.x=0.0f-direction.y; __vref(perpendicular.y)=direction.x; perpendicular.z=0.0f;
 float x=offset->x;
 direction.x*=x; direction.y*=x;
 float y=offset->y;
 perpendicular.x*=y; perpendicular.y*=y;
 direction.x+=perpendicular.x; direction.y+=perpendicular.y;
 offset->x=direction.x; offset->y=direction.y;
}

struct FormationVector:Coord3D {
 FormationVector(const FormationVector& formationVector){x=formationVector.x;y=formationVector.y;z=formationVector.z;}
 FormationVector(const Coord3D& coord){x=coord.x;y=coord.y;z=coord.z;}
 ~FormationVector(){}
 FormationVector& sub(const Coord3D& other){x-=other.x;y-=other.y;z-=other.z;return *this;}
 FormationVector& add(const Coord3D& other){x+=other.x;y+=other.y;z+=other.z;return *this;}
 FormationVector& scale(const float& factor){x*=factor;y*=factor;z*=factor;return *this;}
 FormationVector& scaleValue(float factor){x*=factor;y*=factor;z*=factor;return *this;}
};

void AIGroup::createFormation(int unused0,int unused1)
{
 int formationId=(int)((GameClient *)TheAI)->allocDrawableID();
 SimpleObjectIterator *ordered=new SimpleObjectIterator;
 SimpleObjectIterator *candidates=new SimpleObjectIterator;
 int squadWidth=TheAI->data->widthB4*2;
 bool forceTwoSquads=false;
 int squadCapacity=squadWidth*6;
 FormationSquad squads[12];
 for(int i=0;i<12;++i)squads[i].SetSquadWidth(squadWidth);
 int area=0;
 int specialCount=0;
 for(FormationMemberNode *node=members->next;node!=members;node=node->next) {
  Mid005490D2 *unit=node->object;
  ordered->insert((int)unit,((Rva000CBA20 *)unit)->distSq((const Rva000CBA20Point *)&end));
  candidates->insert((int)unit,((Rva000CBA20 *)unit)->distSq((const Rva000CBA20Point *)&end));
  unit->formationId=0;
  int unitArea=unit->leaf->field564*unit->leaf->field568;
  if(unitArea<1)unitArea=1;
  area+=unitArea;
  FormationAIUpdate *ai=(FormationAIUpdate *)((Object *)unit)->rva0028AC4E();
  int kind=ai->data->kind;
  if(kind>=4 && kind<=6)++specialCount;
 }
 if(ordered->items.size()==0) { ::delete ordered;::delete candidates;return; }
 ordered->sort(ITER_SORTED_NEAR_TO_FAR);
 candidates->sort(ITER_SORTED_NEAR_TO_FAR);
 int squadCount=(area+squadCapacity-1)/squadCapacity;
 // WB has a specialCount adjustment guarded by a constant-false flag;
 // retail removes it, retaining the reads above.
 if(squadCount==1 && squadWidth<=specialCount && forceTwoSquads)squadCount=2;
 if(squadCount>12)squadCount=12;
 int squadIndex=0;
 for(int kind=0;kind<13;++kind) {
  for(Mid005490D2 *unit=(Mid005490D2 *)ordered->first();unit;unit=(Mid005490D2 *)ordered->next()) {
   if(unit->gate && unit->gate->update && unit->gate->update->data->kind==kind) {
    squads[squadIndex].AddUnit(unit);
    if(++squadIndex>=squadCount)squadIndex=0;
   }
  }
 }
 float left=0.0f,right=0.0f;
 for(int i=0;i<squadCount;++i) {
  FormationDimensions dimensions=squads[i].rva00549425();
  Coord2D origin;
  if(i&1) {
   origin.x=right;
   origin.y=TheAI->data->spacingA8*0.5f;
   right+=dimensions.x+TheAI->data->spacingA8;
  } else {
   origin.x=left;
   origin.y=0.0f-dimensions.y-TheAI->data->spacingA8*0.5f;
   left+=dimensions.x;left+=TheAI->data->spacingA8;
  }
  if(squadCount==1)origin.y=dimensions.y*-0.5f;
  squads[i].rva00549345(&origin,formationId);
 }
 if(!ordered->first()) {::delete ordered;::delete candidates;return;}
 FormationVector firstPosition(*(const Coord3D *)&((Mid005490D2 *)ordered->first())->positionX);
 FormationVector anchor(start);
 FormationVector direction(end);
 direction.sub(start);direction.z=0.0f;
 direction.normalize();
 FormationVector halfStep(direction);
 halfStep.scaleValue(TheAI->data->spacingA4*0.5f);
 direction.scale((firstPosition.y-start.y)*direction.y+(firstPosition.x-start.x)*direction.x);
 direction.add(halfStep);
 anchor.add(direction);
 for(Mid005490D2 *unit=(Mid005490D2 *)ordered->first();unit;unit=(Mid005490D2 *)ordered->next()) {
  int attempts=6;
  bool swapped;
  do {
   swapped=false;
   FormationUnitGate *gate=unit->gate;
   if(!gate || !gate->update)break;
   --attempts;
   Coord2D slot=unit->formationOffset;
   Coord2D position;position.x=unit->positionX-anchor.x;position.y=unit->positionY-anchor.y;
   RotateFormationOffset(&start,&end,&position);
   float oldY=fabs(slot.y-position.y);
   float oldX=fabs(slot.x-position.x);
   bool pastCurrent=false;
   for(Mid005490D2 *other=(Mid005490D2 *)candidates->first();other;other=(Mid005490D2 *)candidates->next()) {
    if(other==unit) {pastCurrent=true;continue;}
    if(!pastCurrent || !other->gate || !other->gate->update)continue;
    if(gate->update->data->kind!=other->gate->update->data->kind)continue;
    Coord2D otherSlot=other->formationOffset;
    Coord2D otherPosition;otherPosition.x=other->positionX-anchor.x;otherPosition.y=other->positionY-anchor.y;
    RotateFormationOffset(&start,&end,&otherPosition);
    float otherY=fabs(otherSlot.y-otherPosition.y);
    float otherX=fabs(otherSlot.x-otherPosition.x);
    float swappedY=fabs(otherSlot.y-position.y);
    float swappedX=fabs(otherSlot.x-position.x);
    float otherSwappedY=fabs(slot.y-otherPosition.y);
    float otherSwappedX=fabs(slot.x-otherPosition.x);
    float oldCost=oldY+otherY+oldY+otherY+oldX+otherX+fabs(oldX-otherX)*0.25f;
    float newCost=swappedY+otherSwappedY+swappedY+otherSwappedY+swappedX+otherSwappedX+fabs(swappedX-otherSwappedX)*0.25f;
    float gain=(oldY+oldX)-(swappedY+swappedX);
    if(gain<0.0f)continue;
    if(newCost<gain*0.3f+oldCost) {
     Coord2D temporary=unit->formationOffset;
     unit->formationOffset=other->formationOffset;
     other->formationOffset=temporary;
     swapped=true;
     break;
    }
   }
  } while(swapped && attempts>0);
 }
 Mid005490D2 *front=0;
 float nearestY=1.0e9f,farthestX=-1.0e9f;
 for(Mid005490D2 *unit=(Mid005490D2 *)ordered->first();unit;unit=(Mid005490D2 *)ordered->next()) {
  Coord2D offset=unit->formationOffset;
  if(offset.y<0.0f)continue;
  if(offset.x<farthestX)continue;
  if(offset.x==farthestX && offset.y>nearestY)continue;
  nearestY=offset.y;farthestX=offset.x;front=unit;
 }
 float shiftY=0.0f,shiftX=0.0f;
 if(front) {
  if(front->leaf->field568>1) {
   Coord2D offset=front->formationOffset;
   shiftY=TheAI->data->spacingA0*0.25f-offset.y;
   if(offset.y==0.0f)shiftY=0.0f;
   shiftX=0.0f-offset.x-TheAI->data->spacingA4*0.25f;
  } else {Coord2D offset=front->formationOffset;shiftY=0.0f-offset.y;}
 }
 for(Mid005490D2 *unit=(Mid005490D2 *)ordered->first();unit;unit=(Mid005490D2 *)ordered->next()) {
  Coord2D offset=unit->formationOffset;
  offset.y+=shiftY;offset.x+=shiftX;
  unit->formationOffset=offset;
 }
 ::delete ordered;
 ::delete candidates;
}
