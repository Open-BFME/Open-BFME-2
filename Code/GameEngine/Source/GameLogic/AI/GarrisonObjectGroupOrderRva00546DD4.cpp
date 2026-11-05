// cl: /MD
// ?rva00546DD4@GarrisonObjectGroupOrder@@UAEXW4ObjectID@@@Z @0x00546DD4 90B evidence: slot 4 of 0x0086A3C4; calls findObjectByID rowed 0x00049DC5 three times plus AI rva0036EBB8 rowed 0x0036EBB8; uses TheGameLogic; clears +0x18 on null.
// Honest-address slot method via vtable (naming rule).
// Built against the approved TU's class view (GarrisonObjectGroupOrder.cpp):
// the Object's AI at +0x258 is the canonical AIUpdateInterface, whose command
// interface (rowed rva0036EBB8) sits at +0x20.
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

class Drawable;

class Object;

#include "../../../Include/GameLogic/Module/AIUpdate.h"


class Object
{
public:
	Drawable *getDrawable() const;
	ObjectID getID() const { return m_id; }
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_flags438; // +0x438 bit0
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *objectToEnter, CommandSourceType commandSource,
		CanEnterType mode, bool passThrough, bool *outFlag);
};

class ActionManager;

extern ActionManager *TheActionManager;

extern GameLogic *TheGameLogic;

class Xfer;

// Retail vftable 0x00C6A3C4: slot 3 is xfer (0x00546D15) and slot 4 the
// garrison step 0x00546DD4, as in the twin AttackObjectGroupOrder.cpp.
class GarrisonObjectGroupOrder
{
public:
	virtual ~GarrisonObjectGroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual void rva00546DD4(ObjectID id);
	virtual bool rva00546E2E(ObjectID id);
	virtual void slot06();
	virtual void slot07();
	virtual Coord3D *rva00546D7C(int dummy);
	virtual void slot09();
	virtual void slot10();
	virtual bool rva00546DA5(int *outID, void *out);
private:
	char m_pad04[0x18 - 4];
	ObjectID m_targetID; // +0x18
	Coord3D m_pos; // +0x1C
};

void GarrisonObjectGroupOrder::rva00546DD4(ObjectID id)
{
	GameLogic *logic = TheGameLogic;
	Object *first = logic->findObjectByID(id);
	ObjectID mine = m_targetID;
	Object *second = logic->findObjectByID(mine);
	if (second == 0 || first == 0)
		return;
	AIUpdateInterface *ai = first->m_ai;
	if (ai == 0)
		return;
	Object *third = logic->findObjectByID(mine);
	if (third != 0)
		ai->rva0036EBB8(third, CMD_FROM_PLAYER);
	else
		m_targetID = INVALID_OBJECT_ID;
}
