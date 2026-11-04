// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// stlport
//
// HordeMeleeFormation::findMeleeAttackPosition, retail 0x005852DF..0x005858F3 (1556B), thiscall ret 0x1C.
//
// Picks a melee attack position for a formation member around its target.
// Same ring search as HordeMeleeSwarm::findMeleeAttackPosition (0x00583D54),
// plus a centre cell on the first ring: the member's own cell offset 14 units
// back along the target direction (distance 0). An overlap accepted by the
// attack-range test scores dist + 1 here instead of the swarm's dist - 5.
//
// Evidence (target): WorldBuilder twin 0x01475120 is
// HordeMeleeFormation::findMeleeAttackPosition (HordeMeleeFormation.cpp
// assert at line 511, DEBUG logs "Allowed backwards due to overlap" and
// "Moving too far away from group."; the centre cell is Normalize then
// scale(14) then the negated x/y). Callees are rowed or pinned under the
// spellings used here.
// Codegen notes: as in the swarm unit, the ObjectID lookup chain is visible
// and both ring searches share one i/j pair. Coord3D::GetLength 0x00005A26
// and Coord3D::Normalize 0x00005A70 are defined here as noinline COMDAT
// copies (byte-identical to their rows): seeing that they keep no pointer to
// the delta lets cl drop the dead x/y stores after scale(14) and gives
// retail's delta/offset frame slots.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Common/GameLogicObjectLookupView.h"
#include "../../../../Common/RTS/XYDistanceCallView.h"
#include <math.h>
#include <vector>
#include <deque>

typedef int Int;
typedef bool Bool;
typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_WALL = 0x10
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

#include "../../../../../Include/GameLogic/Weapon.h"

enum ObjectStatusTypes { FORMATION_STATUS_1C=0x1c, FORMATION_STATUS_44=0x44 };
enum CommandSourceType { FORMATION_COMMAND=2 };
template<int N> class FormationSlots : public FormationSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class FormationSlots<0> {};
class FormationRangeQuery : public FormationSlots<18> { public: virtual Object *query(int,const Coord3D *,float,int,int)=0; };
class FormationContainer : public FormationSlots<31> { public: virtual FormationRangeQuery *rangeQuery()=0; };


class FormationAI : public FormationSlots<110> { public: virtual bool idleBlocked()=0; virtual bool specialState()=0;
 virtual void slot112()=0;
 virtual void slot113()=0;
 virtual void slot114()=0;
 virtual void slot115()=0;
 virtual void slot116()=0;
 virtual void slot117()=0;
 virtual void slot118()=0;
 virtual void slot119()=0;
 virtual void slot120()=0;
 virtual void slot121()=0;
 virtual void slot122()=0;
 virtual void slot123()=0;
 virtual void slot124()=0;
 virtual void slot125()=0;
 virtual void slot126()=0;
 virtual void slot127()=0;
 virtual void slot128()=0;
 virtual void slot129()=0;
 virtual void slot130()=0;
 virtual void slot131()=0;
 virtual void slot132()=0;
 virtual void slot133()=0;
 virtual void slot134()=0;
 virtual void slot135()=0;
 virtual void resetAttack()=0; };
class AICommandInterface { public: void rva0026C2D9(Object *,int,CommandSourceType); void aiIdle(CommandSourceType); };
class AIUpdateInterface
{
public:
	void *getLocomotorSet() const { return m_1dc; }
private:
	unsigned char m_pad000[0x1DC];
	void *m_1dc;					// +0x1DC
};

class Object
{
public:
	Int rva0028B511() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return (AIUpdateInterface *)m_ai; }
	Int getTeamValue() const { return m_274; }
	Object *rva002931F5(bool);
	bool testStatus(ObjectStatusTypes) const;
	void rva0028ACEE(int,int);
	void rva00295F05(bool);
	unsigned char pad0[4];
	void *m_template;				// +0x04
	unsigned char pad8[0x38 - 8];
	Coord3D m_position;				// +0x38
	unsigned char pad44[0x74 - 0x44];
	int m_id;					// +0x74
	unsigned char pad78[0x250 - 0x78];
	FormationContainer *m_container;		// +0x250
	unsigned char pad254[4];
	FormationAI *m_ai;				// +0x258
	unsigned char pad25C[0x274 - 0x25C];
	Int m_274;					// +0x274
	unsigned char pad278[0x438 - 0x278];
	unsigned char flags;				// +0x438
};

#include "../../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

struct FormationLookupNode { FormationLookupNode *next; ObjectID key; Object *object; };
struct FormationLookupBuckets {
 FormationLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 FormationLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct FormationLookupMap { unsigned char hashEqual[4]; FormationLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 FormationLookupMap *map=(FormationLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 FormationLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}
extern int BfmeLogicFramesPerSecond;	// LOGICFRAMES_PER_SECOND

int Rva002EDE5B(void *obj, Coord3D *pos);
int Rva002E9B31Get(void *obj);

struct FormationNode { FormationNode *next,*prev; Object *object; };
struct FormationList { FormationNode *head; };
struct FormationRange {
 void *owner; FormationList *list;
 unsigned int size() const { unsigned int memberCount=0; for(FormationNode *formationNode=list->head->next;formationNode!=list->head;formationNode=formationNode->next) ++memberCount; return memberCount; }
};
class FormationListProvider : public FormationSlots<70> { public: virtual void fill(FormationRange *)=0; };
class FormationLeaderProvider : public FormationSlots<38> { public: virtual void setLeader(Object *)=0; };
struct FormationMember { unsigned char pad[0x18]; int follows; };
struct FormationHeld { unsigned char pad0[8]; Object *leader; unsigned char padC[0x120-0xc]; bool active;
 unsigned char pad121[0x188-0x121]; FormationMember *members; };
struct FormationData { void *unknown; bool follow; char pad5[3]; float firstDistance,nextDistance; };
struct BfmeE8 { int a,b; };
struct BfmeE12 { float x,y,z; };
#include "../../../../../../Libraries/Source/WWVegas/WWLib/Gen00595870Payload.h"
namespace _STL {
 template<> void deque<BfmeE8>::clear();
 template<> void deque<Gen_t_00595870_p12cd>::push_back(const Gen_t_00595870_p12cd &);
 // pop_front calls the rowed retail body 0x00585063; max<int> is always inlined here.
 template<> void deque<BfmeE12>::_M_pop_front_aux();
 template<> __declspec(dllimport) __forceinline const int &max<int>(const int &__a, const int &__b) { return __a < __b ? __b : __a; }
}
class Rva00585257Iter : public _STL::_Deque_iterator_base<BfmeE12> { public: void *rva00585257(); };

class Rva0046ACF6 { public: int rva0046ACF6(int); };
class Rva005D6FE5 { public: unsigned char rva005D6FE5(); };
struct FormationAttackEntry { int state; Coord3D position,previousPosition; bool needsPosition; unsigned char pad1D[3];
 unsigned int nextFrame,lastFrame; _STL::deque<BfmeE12> path; ObjectID lastTarget; };
class HordeMeleeFormation {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void startMeleeAttack(Object *);
 virtual void slot4(); virtual void updateMeleeAttack(Object *);
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual bool rva00585017(int,Coord3D *);
 bool findMeleeAttackPosition(Object *,Coord3D *,Object *,const Coord3D *,bool,int *,bool);
 FormationHeld *held;
 _STL::vector<FormationAttackEntry> attacks;
 bool force; FormationData *data;
};

__declspec(noinline) inline float Coord3D::GetLength() const
{
	float x_value = x;
	float y_value = y;
	float z_value = z;
	return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}

__declspec(noinline) inline float Coord3D::Normalize()
{
	float len = GetLength();
	float scale = 1.0f / len;
	x *= scale;
	y *= scale;
	z *= scale;
	return len;
}

inline void Coord3D::scale(float s)
{
	x *= s;
	y *= s;
	z *= s;
}

static __forceinline void copyCoord(Coord3D &destination, const Coord3D *source)
{
	destination.x = source->x;
	destination.y = source->y;
	destination.z = source->z;
}

static __forceinline void subCoord(Coord3D &coordinate, const Coord3D *subtrahend)
{
	coordinate.x -= subtrahend->x;
	coordinate.y -= subtrahend->y;
	coordinate.z -= subtrahend->z;
}

Bool HordeMeleeFormation::findMeleeAttackPosition(Object *obj, Coord3D *result, Object *victim, const Coord3D *victimPos,
	Bool unused, Int *frames, Bool allowOverlap)
{
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	AIUpdateInterface *ai = obj->getAI();
	*frames = 0;
	if (!ai)
		return false;

	void *locomotorSet = ai->getLocomotorSet();
	const Real goodAngle = 0.7071f;
	const Real closeRatio = 0.5f;
	const Weapon *weapon = obj->getCurrentWeapon(0);
	Object *leader = held->leader;

	Coord3D pos;
	copyCoord(pos, obj->getPosition());
	Rva002EDE5B(obj, &pos);

	Real dist;
	{
		Coord3D dir;
		copyCoord(dir, victimPos);
		subCoord(dir, &pos);
		dir.z = 0.0f;
		dist = dir.Normalize();
	}

	Coord3D best;
	copyCoord(best, &pos);
	Bool found = false;
	Real bestOffset = 0.0f;
	Real bestGain = 0.0f;
	Int rings = Rva002E9B31Get(obj) * 2;
	Bool isFar = dist > (Real)(rings * 20);
	Real bestDist = dist + 100.0f;

	Int overlapIds[16];
	Bool overlapping = TheAI->pathfinder()->GetOverlapGoalUnits(obj, obj->getPosition(), overlapIds) > 0;
	Bool blocked = !TheAI->pathfinder()->IsHordeMeleeLinePassable(obj, locomotorSet, layer, &pos, &pos);

	Coord3D lastGood;
	Int xStep, j;
	copyCoord(lastGood, &pos);
	if (blocked)
	{
		for (Int r = 1; r <= 2 && blocked; r++)
		{
			for (xStep = -r; xStep <= r && blocked; xStep++)
			{
				for (j = -r; j <= r && blocked; j++)
				{
					if (xStep == r || j == r || xStep == -r || j == -r)
					{
						Coord3D cand;
						copyCoord(cand, &pos);
						cand.x += (Real)xStep * 10.0f;
						cand.y += (Real)j * 10.0f;
						if (TheAI->pathfinder()->IsHordeMeleeLinePassable(obj, locomotorSet, layer, &cand, &cand))
						{
							lastGood = cand;
							blocked = false;
						}
					}
				}
			}
		}
	}

	PathfindLayerEnum objLayer = (PathfindLayerEnum)obj->rva0028B511();
	for (Int r = 1; r <= rings; r++)
	{
		for (xStep = -r; xStep <= r; xStep++)
		{
			for (j = -r; j <= r; j++)
			{
				if ((xStep == 0 && j == 0 && r <= 1) || xStep == r || j == r || xStep == -r || j == -r)
				{
					Real xOffset = (Real)xStep * 10.0f;
					Real yOffset = (Real)j * 10.0f;
					Coord3D delta;
					delta.x = pos.x + xOffset;
					delta.y = pos.y + yOffset;
					delta.z = 0.0f;
					subCoord(delta, victimPos);
					delta.z = 0.0f;
					Real candDist;
					if (xStep == 0 && j == 0)
					{
						candDist = 0.0f;
						delta.Normalize();
						delta.scale(14.0f);
						xOffset = -delta.x;
						yOffset = -delta.y;
					}
					else
					{
						candDist = delta.GetLength();
						if (candDist > dist && !overlapping)
							continue;
					}

					Coord3D cand;
					copyCoord(cand, &pos);
					cand.x += xOffset;
					cand.y += yOffset;
					leader->rva002C97E8(leader->getPosition(), &cand);

					PathfindLayerEnum candLayer = TheTerrainLogic->getLayerForDestination(obj, &cand);
					if (candLayer != objLayer)
					{
						if (candLayer != LAYER_WALL && objLayer != LAYER_WALL)
							continue;
						cand.z = TheTerrainLogic->getLayerHeight(cand.x, cand.y, candLayer, 0, true);
						if (fabs(cand.z - pos.z) > 40.0f)
							continue;
					}

					Bool canUseCandidate = false;
					Bool clear = TheAI->pathfinder()->rva002EDFF9(obj, &cand);
					if (!clear && allowOverlap && weapon)
					{
						Int ids[16];
						if (TheAI->pathfinder()->GetOverlapGoalUnits(obj, &cand, ids) == 2 && weapon)
						{
							Object *object = TheGameLogic->findObjectByID((ObjectID)ids[0]);
							Object *secondOverlapUnit = TheGameLogic->findObjectByID((ObjectID)ids[1]);
							if (object && secondOverlapUnit && object->getTeamValue() == secondOverlapUnit->getTeamValue() && obj->getTeamValue() == object->getTeamValue())
							{
								if (const_cast<Weapon *>(weapon)->isWithinAttackRange(obj, &cand, victim, victimPos, 0.0f, true))
								{
									clear = true;
									candDist = dist + 1.0f;
								}
							}
						}
					}
					if (clear)
					{
						if (blocked)
							canUseCandidate = true;
						else
							canUseCandidate = TheAI->pathfinder()->IsHordeMeleeLinePassable(obj, locomotorSet, layer, &lastGood, &cand);
					}
					if (canUseCandidate && candDist < bestDist)
					{
						best = cand;
						bestDist = candDist;
						bestOffset = (Real)sqrt(yOffset * yOffset + xOffset * xOffset);
						bestGain = dist - candDist;
						found = true;
					}
				}
			}
		}
		if (!isFar && found && bestGain / bestOffset > goodAngle)
			break;
	}

	if (found)
	{
		*result = best;
		if (bestGain / bestOffset < closeRatio)
			*frames = BfmeLogicFramesPerSecond * 2;
	}
	else
	{
		*frames = BfmeLogicFramesPerSecond * 4;
	}
	return found;
}

inline __declspec(noinline) float Coord3D::GetLengthEstimate2D() const
{
    if (fabs(x) > fabs(y)) {
        return (float)(fabs(x) + 0.25f * fabs(y));
    }
    return (float)(fabs(y) + 0.25f * fabs(x));
}

// ?updateMeleeAttack@HordeMeleeFormation@@UAEXPAVObject@@@Z, retail
// 0x005863E5..0x00586A2C (1607 bytes, ret 4): slot 5 of the vtable at
// 0x0086FD90; WB 0x01473460 names HordeMeleeFormation::updateMeleeAttack
// (HordeMeleeFormation.cpp). Two passes over the formation list: record each
// member's previous position, then for each attack entry extend its 0x0C
// path deque, follow the leader's path back to the follow distance, or run
// the shared position search. The follower block copies the leader index
// into its own local: with the long-lived follows cl derives follows*0x54
// as a CSE temp and makes it the address base; retail has begin as base.
void HordeMeleeFormation::updateMeleeAttack(Object *victim)
{
 if(!victim) return;
 if(((Rva005D6FE5 *)this)->rva005D6FE5()) startMeleeAttack(victim);
 FormationRange range;
 ((FormationListProvider *)((char *)held+0x20))->fill(&range);
 FormationHeld *owner=held;
 Object *leader=owner->leader;
 if(!leader->testStatus(FORMATION_STATUS_44))
  ((FormationLeaderProvider *)((char *)owner+0x11c))->setLeader(leader);
 Object *container=victim->rva002931F5(false);
 if(container) victim=container;
 unsigned int now=TheGameLogic->getFrame();
 int count=range.size()/2;
 count=_STL::max(count,2);
 FormationNode *node;
 for(node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index>=0 && index<attacks.size()) attacks[index].previousPosition=unit->m_position;
 }
 for(node=range.list->head->next;node!=range.list->head;node=node->next) {
  Object *unit=node->object;
  if(!unit) continue;
  FormationAI *ai=unit->m_ai;
  if(ai && *(int *)((char *)ai+0x1fc)==4 && *(int *)((char *)ai+0x140)) continue;
  int index=((Rva0046ACF6 *)held)->rva0046ACF6(unit->m_id);
  if(index<0 || index>=attacks.size()) continue;
  FormationAttackEntry &entry=attacks[index];
  bool savePosition=false;
  if(entry.path.empty()) savePosition=true;
  else {
   const BfmeE12 &last=entry.path.back();
   Coord3D delta;
   delta.x=last.x; delta.y=last.y; delta.z=last.z;
   const Coord3D *p=&unit->m_position;
   delta.x-=p->x; delta.y-=p->y; delta.z-=p->z;
   if(delta.GetLengthEstimate2D()>=10.0f) savePosition=true;
  }
  if(savePosition) {
   if(entry.path.size()>10) entry.path.pop_front();
   ((_STL::deque<Gen_t_00595870_p12cd> *)&entry.path)->push_back(*(const Gen_t_00595870_p12cd *)&unit->m_position);
  }
  if(unit->testStatus(FORMATION_STATUS_1C) || ai->specialState()) {
   entry.needsPosition=true; entry.lastFrame=now;
   unit->rva0028ACEE((int)&unit->m_position,unit->rva0028B511());
   continue;
  }
  bool inRange=false;
  if(entry.state==3) inRange=((*(unsigned int *)((char *)victim->m_template+0x110)) & (1u<<29))!=0;
  if(*(unsigned char *)((char *)victim->m_template+0x108)&0x80) {
   int ids[16];
   Pathfinder *pathfinder=TheAI->pathfinder();
   int overlap=pathfinder->GetOverlapGoalUnits(unit,&unit->m_position,ids);
   if(overlap==0 || overlap==2) inRange=true;
  }
  if(inRange && unit->getCurrentWeapon(0) && unit->getCurrentWeapon(0)->isWithinAttackRange((const Object *)unit,victim,0.0f,1) && unit->m_ai) {
   ((AICommandInterface *)((char *)unit->m_ai+0x20))->rva0026C2D9(victim,0x7fffffff,FORMATION_COMMAND);
   unit->rva0028ACEE((int)&unit->m_position,unit->rva0028B511());
   continue;
  }
  FormationMember *members=held->members;
  int follows=members[index].follows;
  if(follows>=0) {
   if(!data->follow || (entry.state!=3 && entry.state!=0)) continue;
   int leader=follows;
   float distance=members[leader].follows>=0?data->nextDistance:data->firstDistance;
   _STL::deque<BfmeE12>::reverse_iterator it=attacks[leader].path.rbegin();
   for(;it!=attacks[leader].path.rend();++it) {
    BfmeE12 *point=(BfmeE12 *)((Rva00585257Iter *)&it)->rva00585257();
    Coord3D delta;
    delta.x=point->x; delta.y=point->y; delta.z=point->z;
    const Coord3D *previous=&attacks[leader].previousPosition;
    delta.x-=previous->x; delta.y-=previous->y; delta.z-=previous->z;
    if(delta.GetLengthEstimate2D()>=distance) break;
   }
   if(it!=attacks[leader].path.rend()) {
    entry.position=*(Coord3D *)((Rva00585257Iter *)&it)->rva00585257();
    held->active=true; entry.state=1; entry.nextFrame=0;
    unit->rva0028ACEE((int)&entry.position,unit->rva0028B511());
   } else {entry.state=0; entry.nextFrame=now+BfmeLogicFramesPerSecond;}
   entry.needsPosition=false;
   continue;
  }
  if(entry.nextFrame>now && !force) continue;
  if(entry.state==1 || entry.state==2) { held->active=true; continue; }
  if(entry.state==3) { unit->rva00295F05(false); if(unit->testStatus(FORMATION_STATUS_1C)) continue; }
  if(entry.state==0 && count>0) entry.needsPosition=true;
  if(!entry.needsPosition && entry.state!=3) continue;
  entry.position=unit->m_position;
  Coord3D position;
  position.x=victim->m_position.x; position.y=victim->m_position.y; position.z=victim->m_position.z;
  Object *other=victim->rva002931F5(false);
  FormationContainer *attached;
  if(other && (attached=other->m_container)!=0 && attached->rangeQuery()) {
   Object *nearest=other->m_container->rangeQuery()->query(0,&entry.position,0.0f,0,0);
   if(nearest) {
    Object *last=TheGameLogic->findObjectByID(entry.lastTarget);
    if(last && !(last->flags&1)) {
     float oldDistance=((Rva000CBA20 *)last)->distSq((const Rva000CBA20Point *)&unit->m_position);
     if(((Rva000CBA20 *)nearest)->distSq((const Rva000CBA20Point *)&unit->m_position)+400.0f>oldDistance) nearest=last;
    }
    position=nearest->m_position;
   }
  }
  bool recent=entry.lastFrame+BfmeLogicFramesPerSecond>now;
  int frames=0;
  bool found=findMeleeAttackPosition(unit,&entry.position,victim,&position,recent,&frames,true);
  if(frames) entry.nextFrame=now+frames; else entry.nextFrame=0;
  if(found) { held->active=true; entry.state=1; --count; }
  else { if(entry.nextFrame) unit->rva00295F05(false); entry.state=0; entry.needsPosition=false; }
  unit->rva0028ACEE((int)&entry.position,unit->rva0028B511());
  entry.needsPosition=false;
  if(count<1) break;
 }
 force=false;
}
