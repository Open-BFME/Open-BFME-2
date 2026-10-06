// ?rva004A7275@Rva004A7275@@QAEHXZ
// partial score=0.93 date=2026-10-07
// ?rva004A7275@Rva004A7275@@QAEHXZ @0x004A7275 182B.
// State update. Owner is machine+0x14. No supply AI or no manager returns
// -2. A positive box count attacks the 0x004F5DFB object; otherwise the
// 0x004F5C84 object. With neither, slot 6 and 0x004F5A67 feed aiHarvest.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;

class AICommandInterface
{
public:
	void rva0026C3AC(Object *target, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *position, CommandSourceType cmdSource);
};

class ResourceGatheringManager
{
public:
	Object *rva004F5DFB(Object *query);
	Object *rva004F5C84(Object *query);
	bool rva004F5A67(Object *query, Coord3D *out);
};

class Player
{
public:
	char m_pad00[0x2e4];
	ResourceGatheringManager *m_rgm;
};

class SupplyTruckAIInterface
{
public:
	virtual int getNumberBoxes() const;
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual bool ferrying() const;
	virtual void s5();
	virtual bool slot6() const;
};

template <int N>
class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <>
class VSlots<0>
{
};

class AIUpdateInterface : public VSlots<95>
{
public:
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();

	char m_pad04[0x20 - 4];
	AICommandInterface m_commands;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	char m_pad00[0x14];
	Object *m_owner;
};

class Rva004A7275
{
public:
	int rva004A7275();

private:
	char m_pad00[0x18];
	StateMachine *m_machine;
};

int Rva004A7275::rva004A7275()
{
	Object *owner = m_machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return -2;

	ResourceGatheringManager *manager = owner->getControllingPlayer()->m_rgm;
	if (!manager)
		return -2;

	SupplyTruckAIInterface *supply = ai->getSupplyTruckAIInterface();
	if (!supply)
		return -2;
	if (!supply->ferrying())
		return -2;

	if (supply->getNumberBoxes() > 0)
	{
		Object *center = manager->rva004F5DFB(owner);
		if (center == 0)
			goto none;
		ai->m_commands.rva0026C3AC(center, CMD_FROM_AI);
	success:
		return -1;
	}

	Object *warehouse = manager->rva004F5C84(owner);
	if (warehouse != 0)
	{
		ai->m_commands.rva0026C3AC(warehouse, CMD_FROM_AI);
		goto success;
	}

	if (supply->slot6() == 0)
		goto none;

	Coord3D pos;
	if (manager->rva004F5A67(owner, &pos) == 0)
		goto none;

	ai->m_commands.aiHarvest(&pos, CMD_FROM_AI);
	goto success;
none:
	return 0;
}
