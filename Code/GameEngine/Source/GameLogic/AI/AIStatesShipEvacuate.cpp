// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// AIStates.cpp's evacuation helper 0x003532BF (WorldBuilder 0x00DFA1A0 names it ShipEvacuate::Evacuate), with
// visible copies of the three command helpers retail's unit defines in front of it (/EHs keeps their state store).

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

enum AICommandType
{
	AICMD_DUMMY_17 = 17
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

#include "../../../Include/Common/RvaCoords.h"

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	void *m_obj;
	void *m_otherObj;
	const void *m_team;
	RvaCoords m_coords;
	const void *m_waypoint;
	const void *m_polygon;
	Int m_intValue;
	char m_rest[0xC0 - 0x38];
};

class Rva00352F9D
{
public:
	virtual void rvaVirtual(AICommandParms *parms);
	void rva0035300B(const void *obj, const Coord3D &pos, CommandSourceType src);
	void rva003530F3(const void *obj, const Coord3D &pos, CommandSourceType src);
	void rva003531DB(const void *obj, const Coord3D &pos, CommandSourceType src);
};

// Byte copies of the rows in Rva00352F9DAICommand.cpp; the caller sees that none keeps the position.
__declspec(noinline) inline void Rva00352F9D::rva0035300B(const void *obj, const Coord3D &pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x4B, src);
	parms.m_pos = pos;
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}

__declspec(noinline) inline void Rva00352F9D::rva003530F3(const void *obj, const Coord3D &pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x4A, src);
	parms.m_pos = pos;
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}

__declspec(noinline) inline void Rva00352F9D::rva003531DB(const void *obj, const Coord3D &pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x54, src);
	parms.m_pos = pos;
	parms.m_obj = (void *)obj;
	parms.m_intValue = 0x7fffffff;
	rvaVirtual(&parms);
}

class Object;
class StateMachine;

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};

class AIUpdateInterface : public VirtualSlots<143>
{
public:
	virtual CommandSourceType getLastCommandSource() const = 0; // slot 143
	void ignoreObstacle(const Object *obj);
	unsigned char m_pad04[0x20 - 0x04];
	Rva00352F9D m_commands; // +0x20
};

// The contained objects come back by value: a context word and the list (header node, next first).
struct ContainedNode
{
	ContainedNode *next;
	ContainedNode *prev;
	Object *object;
};
struct ContainedList
{
	ContainedNode *header;
};
struct ContainedObjects
{
	void *context;
	ContainedList *list;
};

class ContainModuleInterface : public VirtualSlots<69>
{
public:
	virtual Int getContainCount(Int extra) = 0; // slot 69
	virtual ContainedObjects getContainedObjects() = 0; // slot 70
};

#include "../../../Include/Common/ThingTemplate.h"

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Real get31C() const { return m_31c; }
	Real get320() const { return m_320; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x250 - 0x44];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x31C - 0x25C];
	Real m_31c; // +0x31C
	Real m_320; // +0x320
};

// Once land is in reach, sends every contained object to the owner's point at +0x31C/+0x320; kind 0x6D
// passengers get command 0x54 (attack move) or 0x4A, the others 0x4B.
void rva003532BF(Object *owner, StateMachine *machine, Bool attackMove)
{
	ContainModuleInterface *contain = owner->getContain();
	if (contain && contain->getContainCount(0))
	{
		Coord3D land;
		const Coord3D *position = owner->getPosition();
		if (TheAI->pathfinder()->getClosestPointOnLand(position, owner, &land))
		{
			ContainedObjects objects = contain->getContainedObjects();
			for (ContainedNode *node = objects.list->header->next; node != objects.list->header; node = node->next)
			{
				Object *passenger = node->object;
				passenger->getAI()->ignoreObstacle(owner);
				Coord3D dest;
				dest.x = owner->get31C();
				dest.y = owner->get320();
				dest.z = position->z;
				if (((passenger->getTemplate()->m_kindof[3] & (1U << 13)) != 0))
				{
					if (attackMove)
						passenger->getAI()->m_commands.rva003531DB(owner, dest, owner->getAI()->getLastCommandSource());
					else
						passenger->getAI()->m_commands.rva003530F3(owner, dest, owner->getAI()->getLastCommandSource());
				}
				else
					passenger->getAI()->m_commands.rva0035300B(owner, dest, owner->getAI()->getLastCommandSource());
			}
		}
	}
}
