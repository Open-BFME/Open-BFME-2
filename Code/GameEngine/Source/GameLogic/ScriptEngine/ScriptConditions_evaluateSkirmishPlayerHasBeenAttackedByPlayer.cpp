// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateSkirmishPlayerHasBeenAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E4BFA 125B. ZH donor: GeneralsMD ScriptConditions.cpp
// evaluateSkirmishPlayerHasBeenAttackedByPlayer. Target evidence: the
// evaluateCondition jump table (0x007EC5C0) sends case 97 here, which
// initConditionTemplates names SKIRMISH_PLAYER_HAS_BEEN_ATTACKED_BY_PLAYER.
// BFME2 difference: both player parameters are masks from the pinned
// ScriptEngine helper 0x00357B82, walked with the rowed
// PlayerList::getEachPlayerFromMask 0x002A7BC9 (the attacker mask restarts for
// each player). The attacked-by test is the rowed indexed byte getter
// 0x002AA201 called on the Player with the attacker's index (Player +0x54);
// that row keeps its placeholder class, hence the cast.
#include "ascii_string.h"
class Parameter;
typedef int PlayerMaskType;
class Rva002AA201IndexedByteField
{
public:
    unsigned char get(int index) const;
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
class AsciiString;
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
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/ScriptConditions.h"
bool ScriptConditions::evaluateSkirmishPlayerHasBeenAttackedByPlayer(Parameter *pSkirmishPlayerParm, Parameter *pAttackedByParm)
{
    PlayerMaskType playerMask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
    PlayerMaskType attackerMask = TheScriptEngine->rva00357B82(pAttackedByParm);
    while (playerMask) {
        Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
        if (!player) {
            continue;
        }
        PlayerMaskType mask = attackerMask;
        while (mask) {
            Player *srcPlayer = ThePlayerList->getEachPlayerFromMask(mask);
            if (srcPlayer && ((const Rva002AA201IndexedByteField *)player)->get(srcPlayer->getPlayerIndex())) {
                return true;
            }
        }
    }
    return false;
}
