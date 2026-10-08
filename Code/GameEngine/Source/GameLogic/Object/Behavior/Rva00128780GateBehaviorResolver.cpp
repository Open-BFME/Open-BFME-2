// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/Object/Behavior/Rva00128780GateBehaviorResolver.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?resolveGateBehavior@Rva00128780GateBehaviorOwner@@QAE_NXZ 0x00256996 (134B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

enum NameKeyType { };
// Zero Hour's GameCommon.h spells the id an enum; retail's 0x00049DC5 row takes it.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual void moduleSlot();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void updateSlot();
};
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GateOpenAndCloseBehavior : public UpdateModule, public Module { };

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00128780GateBehaviorOwner
{
public:
	bool resolveGateBehavior();

private:
	char m_pad0[0x24];
	ObjectID m_objectID;
	char m_pad28[0x24];
	GateOpenAndCloseBehavior *m_gateBehavior;
};

bool Rva00128780GateBehaviorOwner::resolveGateBehavior()
{
	if (m_objectID == 0)
		return false;

	Object *object = TheGameLogic->findObjectByID(m_objectID);
	if (object == 0)
		return false;

	static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	m_gateBehavior = static_cast<GateOpenAndCloseBehavior *>(object->findModule(gateKey));
	if (m_gateBehavior != 0)
		return true;

	return false;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?bfmeAskBJA@BfmeThingBJA@@QAE_NXZ=?resolveGateBehavior@Rva00128780GateBehaviorOwner@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskDSK@BfmeThingDSK@@QAE_NXZ=?resolveGateBehavior@Rva00128780GateBehaviorOwner@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskBJB@BfmeThingBJB@@QAE_NXZ=?resolveGateBehavior@Rva00128780GateBehaviorOwner@@QAE_NXZ")
