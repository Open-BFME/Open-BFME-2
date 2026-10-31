// cl: /Ireference/shims/bfme2_ascii
// ?evaluateCanBuildObjectTypeAtBase@ScriptConditions@@IAE_NPAVParameter@@00@Z
// retail 0x003E5017 157B leaf free stdcall bool of 3x Parameter ret 0xc. Evidence:
// rowed ThingFactory::rva002D06CA via g_009FF000 with (Parameter+0x10 AsciiString)
// plus rowed ScriptEngine::getUnitNamed via g_Va009FE16C plus rowed rva00357B82
// plus rowed PlayerList::getPlayerFromMask via ThePlayerList plus rowed
// Object::getControllingPlayer twice plus static CastleBehavior::rva0003955DA
// plus rowed Object::findModule plus rowed Rva003971BF::rva003971BF;
// Parameter +0x08 int +0x10 AsciiString like sibling 0x003E6ED0;
// globals g_009FF000 g_Va009FE16C ThePlayerList; siblings 0x003E4F79 /O1.
#include "ascii_string.h"

class ScriptConditions;
class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};

class Energy
{
public:
	float getEnergySupplyRatio() const;
};
template <int N> class BitFlags;
typedef BitFlags<116> KindOfMaskType;
enum ScienceType
{
    SCIENCE_INVALID = -1
};
class UnitRevivalTracker;
class Object;
class Rva004DF17F;
struct PlayerTeamNode;
class Player
{
public:
	UnitRevivalTracker *getUnitRevivalTracker() { return (UnitRevivalTracker *)m_unitRevivalTracker; }
	int getArmyID() const { return m_armyID; }
	Object *rva002AC629();
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;
	bool hasAnyObjects(bool flag) const;
	bool rva002AB3FA() const;
	int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
	bool rva002A9CB8();
	Rva004DF17F *getEnergy() { return (Rva004DF17F *)&m_energy; }
	int countBuildings();
	__declspec(dllimport) __forceinline int getPlayerIndex() const { return m_playerIndex; }
	bool isCapableOfPurchasingScience(ScienceType science) const;
	int getSciencePurchasePoints() const { return m_sciencePurchasePoints; }
	int getMpStartIndex() const { return m_mpStartIndex; }
	bool rva002A9CA4(int value);
	int rva002ABD1D(int kind, int limit);
	PlayerTeamNode *getPlayerTeams() const { return m_playerTeamPrototypes; }
	int getSupplyBoxValue(); // 0x002A9DAC
	char m_pad00[0x1C];
	int m_1c; // +0x1C
	char m_pad20[0x4];
	int m_sciencePurchasePoints; // +0x24
	char m_pad28[0x2C];
	int m_playerIndex; // +0x54
	AsciiString m_side; // +0x58
	char m_pad5C[0x34];
	int m_90; // +0x90
	int m_94; // +0x94
	char m_pad98[0x124];
	Energy m_energy; // +0x1BC
	char m_pad1BD[0x3];
	int m_val1C0; // +0x1C0
	int m_val1C4; // +0x1C4
	char m_pad1C8[0x118];
	int m_mpStartIndex; // +0x2E0
	char m_pad2E4[0x48];
private:
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
	char m_pad330[0x7C];
	int m_armyID; // +0x3AC
	char m_pad3B0[0x388];
	unsigned char m_unitRevivalTracker[4]; // +0x738
	char m_pad73C[0x14];
public:
	int m_750; // +0x750
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
	Player *getEachPlayerFromMask(int &mask);
	int rva002A7C0B(bool flag);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
	char m_pad00[0x18];
private:
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;


#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};
extern class ThingFactory *TheThingFactory;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/Module.h"

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

struct Arg3971BF
{
};

class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *arg);
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
struct Coord3D;
class Rva00261C89;
class ContainModuleInterface;
class PolygonTrigger;
class BodyModuleInterface;
class AIUpdateInterface;
class ExperienceTracker;
class Object
{
private:
	friend bool __stdcall Rva003E4B83Get(Parameter *);
public:
	friend class ScriptConditions;
	const Coord3D *getPosition() const { return &m_pos; }
	Rva00261C89 *getField04() const { return (Rva00261C89 *)m_template; }
	bool testStatus(ObjectStatusTypes status) const;
	float getVisionRange() const;
	bool hasSpecialPower(SpecialPowerType type) const;
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned int getID() const { return m_id; }
	const AsciiString *rva00290E67() const;
	bool didEnter(PolygonTrigger *trigger); // 0x0028D718
	bool didExit(PolygonTrigger *trigger); // 0x0028D757
	BodyModuleInterface *getBodyModule() const { return m_body; }
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	void *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38
	char m_pad44[0x30];
	unsigned int m_id; // +0x74
	char m_pad78[0x150];
	unsigned char m_disabledMask[4]; // +0x1C8
	char m_pad1CC[0x84];
	ContainModuleInterface *m_contain; // +0x250
private:
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258 (retail-proven by the kept ScriptActions_doTeamFaceWaypoint row)
	char m_pad25C[0x8];
public:
	ExperienceTracker *m_experienceTracker; // +0x264
	char m_pad268[0xC];
private:
	void *m_containedBy; // +0x274
	char m_pad278[0x1D4];
public:
	int m_44c; // +0x44C
};

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateCanBuildObjectTypeAtBase(Parameter *parameter, Parameter *b, Parameter *c)
{
	void *payload = (void *)TheThingFactory->findTemplate(c->m_string);
	if (!payload)
		return false;
	Object *obj = TheScriptEngine->getUnitNamed(b);
	if (!obj)
		return false;
	int mask = TheScriptEngine->rva00357B82(parameter);
	if (!mask)
		return false;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player != 0) {
		Player *ctrl1 = obj->getControllingPlayer();
		if (ctrl1 == player) {
			Player *ctrl2 = obj->getControllingPlayer();
			if (player == ctrl2) {
				Module *mod = obj->findModule(CastleBehavior::rva0003955DA());
				if (mod != 0) {
					if (((Rva003971BF *)mod)->rva003971BF((Arg3971BF *)payload) != false)
						return true;
				}
			}
		}
	}
	return false;
}
