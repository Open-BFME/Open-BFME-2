// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ScriptConditions::evaluateHasDelayedCarryoverUnitOfType, retail 0x003EA87C
// (307B), from WorldBuilder's ScriptConditions.cpp (name, statement order,
// ArmySummary::HasDelayedCarryoverUnitOfTypes): the condition side of
// ScriptActions' delayed-carryover actions (ScriptActions_delayedCarryover.cpp
// carries the same views). With a linear campaign running, the campaign
// manager answers (0x001EB0FB); otherwise any army of the players the
// parameter selects must hold a delayed carryover unit of the types.

#include "ascii_string.h"
#include <vector>

enum ObjectID { INVALID_ID = 0 };

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Player
{
public:
	class UnitRevivalTracker *getUnitRevivalTracker() { return (UnitRevivalTracker *)m_unitRevivalTracker; }
	int getArmyID() const { return m_armyID; }

private:
	unsigned char m_pad00[0x3AC];
	int m_armyID;
	unsigned char m_pad3B0[0x738 - 0x3B0];
	unsigned char m_unitRevivalTracker[4];
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	int getListSize() const { return m_objectTypes.size(); }
	void addObjectType(const AsciiString &objectType);

private:
	AsciiString m_listName;
	_STL::vector<AsciiString> m_objectTypes;
};

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	int rva00357B82(class Parameter *param);
	class Team *getTeamNamed(AsciiString name, bool);
	bool didUnitExist(const AsciiString &name);
	void rva00357960(const AsciiString &name, class Object *obj);
	void addObjectToCache(class Object *obj, const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class UnitRevivalTracker;

class LinearCampaignManager
{
public:
	void *getCampaign() const { return m_campaign; }
	bool hasCampaign() const { return m_campaign != 0; }
	bool rva001EC9AC(ObjectTypes *types, UnitRevivalTracker *tracker, Player *player);
	ObjectID rva001EC99B(ObjectTypes *types, Player *player);
	bool rva001EB0FB(class Rva00376A62 &types);

private:
	unsigned char m_pad00[0x10];
	void *m_campaign;
};
extern LinearCampaignManager *TheLinearCampaignManager;

// WorldBuilder names this class ArmySummary. The local vector's base ctor is
// the shared fold at 0x00211E58, which already has a real name, so the element
// class keeps an address-derived spelling (the address of the spawn method).
class Rva0040D701ArmySummary
{
public:
	bool SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes *types);
	ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes *types);
	bool HasDelayedCarryoverUnitOfTypes(ObjectTypes *types);
};

class Rva002BA8F1Logic
{
public:
	void rva002B323C(_STL::vector<Rva0040D701ArmySummary *> *armies, int armyID);
};
class Rva002BA8F1Logic; extern class LivingWorldLogic *TheLivingWorldLogic;

class ScriptConditions
{
protected:
	bool evaluateHasDelayedCarryoverUnitOfType(const AsciiString &objectTypeName,
		class Parameter *playerParam);
};

bool ScriptConditions::evaluateHasDelayedCarryoverUnitOfType(const AsciiString &objectTypeName,
	Parameter *playerParam)
{
	ObjectTypes tempTypes;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectTypeName);
	if (!types || types->getListSize() == 0) {
		tempTypes.addObjectType(objectTypeName);
		types = &tempTypes;
	}
	if (TheLinearCampaignManager->hasCampaign())
		return TheLinearCampaignManager->rva001EB0FB(*(Rva00376A62 *)types);
	if (!((Rva002BA8F1Logic *)TheLivingWorldLogic))
		return false;
	int mask = TheScriptEngine->rva00357B82(playerParam);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		int armyID = player->getArmyID();
		if (armyID == -1)
			continue;
		_STL::vector<Rva0040D701ArmySummary *> armies;
		((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B323C(&armies, armyID);
		_STL::vector<Rva0040D701ArmySummary *>::iterator it = armies.begin();
		_STL::vector<Rva0040D701ArmySummary *>::iterator end = armies.end();
		for (; it != end; ++it) {
			if ((*it)->HasDelayedCarryoverUnitOfTypes(types))
				return true;
		}
	}
	return false;
}
