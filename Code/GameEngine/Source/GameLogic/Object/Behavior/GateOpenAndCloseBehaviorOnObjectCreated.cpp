// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
//
// GateOpenAndCloseBehavior::onObjectCreated (BFME 2), from BFME 1's
// GateOpenAndCloseBehavior_onObjectCreated.cpp (retail 0x001FD780).
//
// Target facts: the body is slot 1 of the module vftable 0x00C50144 that the
// rowed ctor 0x0049889C installs at +4, so `this` is the module subobject and
// members of the whole gate are reached at this-4 (see
// GateOpenAndCloseBehaviorSlots.cpp for the four vptrs). BFME 2 changes the
// dead-owner path: instead of BFME 1's state update it runs the rowed
// 0x004992D5 with both flags set and drops the gate from the global gate list
// ([0x00DFEEF8]+0x940, the list the ctor appends to and the dtor removes
// from) through the rowed 0x004E908C. The gate name is the module data's
// AsciiString at +0x14 and the linked object ID is at +0x24, as in BFME 1;
// the partner's module is found by the "GateProxyBehavior" name key.
#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ModuleData
{
};

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
	unsigned char m_pad00[0x14];
	AsciiString m_gateName; // +0x14
};

class Module
{
public:
	virtual ~Module();
	virtual void onObjectCreated();
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const AsciiString &getName() const { return m_name; }
	Object *getNextObject() const { return m_next; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }

protected:
	friend class GateOpenAndCloseBehavior;
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad000[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x88 - 0x78];
	AsciiString m_name; // +0x88
	Object *m_next; // +0x8C
	unsigned char m_pad090[0x438 - 0x90];
	unsigned char m_438; // +0x438
};

class GameLogic
{
public:
	Object *getFirstObject();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GateOpenBehaviorList
{
public:
	void rva004E908C(void *item);
};

class Rva002A8F24
{
public:
	unsigned char m_pad[0x940];
	GateOpenBehaviorList *m_gateList; // +0x940
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern Rva002A8F24 *g_00DFEEF8;

class GatePrimary
{
public:
	virtual void gap0() = 0;
};

class BehaviorModule : public Module
{
protected:
	virtual void loadPostProcess();

	const ModuleData *m_moduleData;
	Object *m_object;
};
struct BehaviorModuleInterface { virtual void f0C() {} };
struct UpdateModuleInterface { virtual void f10() {} };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	virtual void onObjectCreated();

private:
	void rva004992D5(bool a, bool b);

	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return static_cast<const GateOpenAndCloseBehaviorModuleData *>(m_moduleData);
	}

	Object *getObject() const { return m_object; }

	ObjectID m_linkedObjectId; // +0x24
};

// ?onObjectCreated@GateOpenAndCloseBehavior@@UAEXXZ @0x0049936A 267B
void GateOpenAndCloseBehavior::onObjectCreated()
{
	BehaviorModule::loadPostProcess();

	if (m_object == 0)
		return;

	if (m_object->isEffectivelyDead())
	{
		rva004992D5(true, true);
		g_00DFEEF8->m_gateList->rva004E908C(this);
	}

	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	if (((const StringBase<char> *)&data->m_gateName)->isEmpty())
		return;

	Object *candidate = TheGameLogic->getFirstObject();
	AsciiString candidateName;
	while (candidate != 0)
	{
		candidateName = candidate->getName();
		if (candidateName.compare(data->m_gateName) == 0)
		{
			static NameKeyType gateKey =
				TheNameKeyGenerator->nameToKey("GateProxyBehavior");
			GateOpenAndCloseBehavior *other =
				static_cast<GateOpenAndCloseBehavior *>(candidate->findModule(gateKey));
			if (other != 0)
			{
				other->m_linkedObjectId = getObject()->getID();
				m_linkedObjectId = candidate->getID();
			}
			break;
		}
		candidate = candidate->getNextObject();
	}
}
