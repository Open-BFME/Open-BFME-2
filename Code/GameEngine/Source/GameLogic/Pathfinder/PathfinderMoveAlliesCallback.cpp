// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Semantic guides: BF1 f98983a7d PathfindMoveAlliesCellCallbackEc070.cpp
// and ZH AIPathfind.cpp moveAlliesDestinationCallback/MADStruct.
// Target facts: complete 0x002F3F7D..0x002F40E7 RET16 and WB 0x00D70120
// establish the callback convention and occupant scan. Target cell info head
// +0x20, node object +8 and payload Object/ignoreID/coordinate at 0/4/8 are
// read independently from native accesses. Original callback/class names remain
// unresolved; use the existing address-derived callback signature.
// Target adds a contain-slot31/slot6 exclusion, moving-state predicate and a
// squared-distance threshold using owner float +0xB8. Its radius interpretation
// is structural inference; the three ABI views claim only measured offsets.
// Read the ID through the node: cl retains the native later null check then,
// while reading through the local Object pointer removes those four bytes.
#include "Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
template <int N> class Slots : public Slots<N - 1>
{
  public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Slots<0>
{
};
class Object;
class Rva002F3F7DHordeView : public Slots<6>
{
  public:
	virtual bool contains(Object *) = 0;
};
class ContainModuleInterface : public Slots<31>
{
  public:
	virtual Rva002F3F7DHordeView *getHordeContain() = 0;
};
class ThingTemplate
{
  public:
	bool testFlag115() const
	{
		return (flag115 & 0x20) != 0;
	}

  private:
	unsigned char pad[0x115];
	unsigned char flag115;
};
class AICommandInterface
{
  public:
	void rva0026C411(Object *, const Coord3D *, CommandSourceType);
};
class StateMachine
{
  public:
	const Coord3D *getGoalPosition() const
	{
		return &goal;
	}

  private:
	unsigned char pad[0x24];
	Coord3D goal;
};
class AIUpdateInterface
{
  public:
	bool isMoving() const;
	bool rva00262DD3(const Object *) const;
	const Coord3D *getGoalPosition() const
	{
		return machine->getGoalPosition();
	}

  private:
	unsigned char pad[0x30];
	StateMachine *machine;
};
class Object
{
  public:
	Relationship getRelationship(const Object *) const;
	bool rva002931BA();
	const ThingTemplate *getTemplate() const
	{
		return templ;
	}
	int getID() const
	{
		return id;
	}
	float getRadius() const
	{
		return radius;
	}
	ContainModuleInterface *getContain() const
	{
		return contain;
	}
	AIUpdateInterface *getAI() const
	{
		return ai;
	}
	Object *getContainedBy() const
	{
		return containedBy;
	}

  private:
	unsigned char pad0[4];
	const ThingTemplate *templ;
	unsigned char pad8[0x74 - 8];
	int id;
	unsigned char pad78[0xB8 - 0x78];
	float radius;
	unsigned char padBC[0x250 - 0xBC];
	ContainModuleInterface *contain;
	unsigned char pad254[4];
	AIUpdateInterface *ai;
	unsigned char pad25C[0x274 - 0x25C];
	Object *containedBy;
};
extern GameLogic *TheGameLogic;
struct OccupantNode
{
	OccupantNode *next, *previous;
	Object *object;
};
struct CellInfo
{
	unsigned char pad[0x20];
	OccupantNode *occupants;
};
class PathfindCell
{
  public:
	CellInfo *info;
	OccupantNode *getOccupants() const
	{
		return info ? info->occupants : 0;
	}
};
class Rva002F3F7DInfo
{
  public:
	int cellCallback(PathfindCell *, PathfindCell *, int, int);
	Object *m_obj;
	int m_ignoreID;
	Coord3D m_destination;
};
int Rva002F3F7DInfo::cellCallback(PathfindCell *previous, PathfindCell *current, int x, int y)
{
	for (OccupantNode *node = current->getOccupants(); node; node = node->next)
	{
		Object *other = node->object;
		if (other == m_obj || node->object->getID() == m_ignoreID || m_obj->getRelationship(other) != ALLIES)
			continue;
		Object *ignore = TheGameLogic->findObjectByID((ObjectID)m_ignoreID);
		if (ignore && ignore->getTemplate()->testFlag115() && ignore->getContain())
		{
			Rva002F3F7DHordeView *horde = ignore->getContain()->getHordeContain();
			if (horde && horde->contains(other))
				continue;
		}
		if (other)
		{
			if (other->rva002931BA())
			{
				Object *parent = other->getContainedBy();
				if (parent)
					other = parent;
			}
		}
		AIUpdateInterface *ai = other ? other->getAI() : 0;
		if (other && ai)
		{
			bool moving = ai->isMoving();
			if (moving)
			{
				if (!ai->rva00262DD3(m_obj))
				{
					const Coord3D *goal = ai->getGoalPosition();
					float dx = goal->x - m_destination.x;
					float dy = goal->y - m_destination.y;
					float dz = goal->z - m_destination.z;
					float radius = m_obj->getRadius();
					if (dz * dz + dy * dy + dx * dx < radius * radius)
						moving = false;
				}
			}
			if (!moving)
			{
				((AICommandInterface *)((char *)ai + 0x20))->rva0026C411(m_obj, &m_destination, CMD_FROM_AI);
				break;
			}
		}
	}
	return 0;
}
