// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluatePlayerHasPower and
// evaluatePlayerHasNOrFewerBuildings. Target evidence: the evaluateCondition
// jump table (0x007EC5C0) sends cases 33 and 47 (PLAYER_HAS_POWER, and
// PLAYER_HAS_NO_POWER through the dispatcher) to 0x003E417D and case 32 to
// 0x003E4132, which initConditionTemplates names PLAYER_HAS_N_OR_FEWER_BUILDINGS.
// BFME2 difference: the player parameter is a mask from the pinned ScriptEngine
// helper 0x00357B82, walked with the rowed PlayerList::getEachPlayerFromMask
// 0x002A7BC9 on ThePlayerList (0x00DFEEE8); power asks the rowed 0x004DF17F on
// the energy block embedded at Player +0x1BC (ZH hasSufficientPower), and the
// building count sums Player::countBuildings 0x002AB10F over the mask.
// Structural inference: the count result is an if/return pair, which keeps
// retail's setge into al without a zeroed eax.
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
typedef int PlayerMaskType;
class Rva004DF17F
{
public:
    bool rva004DF17F() const;
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
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/ScriptConditions.h"
bool ScriptConditions::evaluatePlayerHasNOrFewerBuildings(Parameter *pBuildingCountParm, Parameter *pPlayerParm)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    int count = 0;
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (pPlayer) {
            count += pPlayer->countBuildings();
        }
    }
    // Native code reads this view's +0x08 word directly. Other Parameter
    // views give getInt a different layout, so do not emit that shared name.
    if (pBuildingCountParm->m_int >= count) {
        return true;
    }
    return false;
}
bool ScriptConditions::evaluatePlayerHasPower(Parameter *pPlayerParm)
{
    PlayerMaskType mask = TheScriptEngine->rva00357B82(pPlayerParm);
    while (mask) {
        Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
        if (!pPlayer) {
            continue;
        }
        Rva004DF17F *pPlayersEnergy = pPlayer->getEnergy();
        if (!pPlayersEnergy) {
            continue;
        }
        if (pPlayersEnergy->rva004DF17F()) {
            return true;
        }
    }
    return false;
}
