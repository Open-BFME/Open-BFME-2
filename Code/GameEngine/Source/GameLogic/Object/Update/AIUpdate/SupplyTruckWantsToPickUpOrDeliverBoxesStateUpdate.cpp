// cl: /O1 /DNDEBUG /MD
// ?update@SupplyTruckWantsToPickUpOrDeliverBoxesState@@UAE?AW4StateReturnType@@XZ,
// retail 0x004A7275 (182 bytes).
// Donor (Zero Hour SupplyTruckAIUpdate.cpp
// SupplyTruckWantsToPickUpOrDeliverBoxesState::update): with boxes, dock at
// the player's best supply center; without, at the best warehouse.
// Target evidence: WorldBuilder lead names 0x004A7275
// SupplyTruckWantsToPickUpOrDeliverBoxesState::update. Retail reads the
// machine owner (State+0x18 -> StateMachine+0x14), its AI (Object+0x258),
// the controlling player's ResourceGatheringManager (Player+0x2E4), the AI's
// supply-truck interface (AI vslot 95), and docks through the matched
// AICommandInterface 0x0026C3AC (aiDock's argument order) with CMD_FROM_AI.
// The manager calls 0x004F5DFB / 0x004F5C84 sit in the boxes / no-boxes
// arms exactly where the donor calls findBestSupplyCenter /
// findBestSupplyWarehouse, and are pinned from this body.
// BFME 2 deltas (target): a null manager also fails; with no warehouse, an
// interface flag (vslot 6) asks the manager (0x004F5A67, unnamed) for a
// harvest position and orders the matched aiHarvest there; and the
// fall-through returns STATE_CONTINUE instead of STATE_FAILURE.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;

class AICommandInterface
{
public:
	void rva0026C3AC(Object *obj, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
};

class SupplyTruckAIInterface
{
public:
	virtual int getNumberBoxes() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual bool isAvailableForSupplying() const = 0;
	virtual void slot5() = 0;
	virtual bool slot6() const = 0;
};

class AIUpdateInterface
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94)
#undef V
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;

	char m_pad04[0x20 - 0x04];
	AICommandInterface m_commands; // +0x20
};

class ResourceGatheringManager
{
public:
	Object *findBestSupplyWarehouse(Object *queryObject);
	Object *findBestSupplyCenter(Object *queryObject);
	bool rva004F5A67(Object *queryObject, Coord3D *pos);
};

class Player
{
public:
	ResourceGatheringManager *getResourceGatheringManager() const { return m_resourceGatheringManager; }

private:
	char m_pad[0x2E4];
	ResourceGatheringManager *m_resourceGatheringManager; // +0x2E4
};

class Object
{
public:
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }

private:
	char m_pad[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	Object *getMachineOwner() const { return m_machine->getOwner(); }

private:
	char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class SupplyTruckWantsToPickUpOrDeliverBoxesState : public State
{
public:
	virtual StateReturnType update();
};

StateReturnType SupplyTruckWantsToPickUpOrDeliverBoxesState::update()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ownerAI = owner->getAIUpdateInterface();
	if (!ownerAI)
		return STATE_FAILURE;

	Player *ownerPlayer = owner->getControllingPlayer();
	ResourceGatheringManager *manager = ownerPlayer->getResourceGatheringManager();
	if (!manager)
		return STATE_FAILURE;

	SupplyTruckAIInterface *update = ownerAI->getSupplyTruckAIInterface();
	if (!update)
		return STATE_FAILURE;

	if (!update->isAvailableForSupplying())
		return STATE_FAILURE;

	int numBoxes = update->getNumberBoxes();
	if (numBoxes > 0)
	{
		Object *bestCenter = manager->findBestSupplyCenter(owner);
		if (bestCenter)
		{
			ownerAI->m_commands.rva0026C3AC(bestCenter, CMD_FROM_AI);
			return STATE_SUCCESS;
		}
	}
	else
	{
		Object *bestWarehouse = manager->findBestSupplyWarehouse(owner);
		if (bestWarehouse)
		{
			ownerAI->m_commands.rva0026C3AC(bestWarehouse, CMD_FROM_AI);
			return STATE_SUCCESS;
		}
		if (update->slot6())
		{
			Coord3D pos;
			if (manager->rva004F5A67(owner, &pos))
			{
				ownerAI->m_commands.aiHarvest(&pos, CMD_FROM_AI);
				return STATE_SUCCESS;
			}
		}
	}
	return STATE_CONTINUE;
}
