// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluatePlayerHasCredits@ScriptConditions@@IAE_NPAVParameter@@00@Z @0x003E3F59 165B: player-mask sum of Player+0x94 vs threshold with 0..5 op switch
// Evidence: neighbours ScriptConditions_evaluateNamedUnit and evaluateRva003E3FFE same flags; rowed getEachPlayerFromMask 0x002A7BC9 plus pin rva00357B82 plus globals g_Va009FE16C ThePlayerList plus caller 0x003EAD99
#include "ascii_string.h"
class AsciiString;
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

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

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

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluatePlayerHasCredits(Parameter *pValue, Parameter *pOp, Parameter *pPlayerParm)
{
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	int total = 0;
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			if (&player->m_90) {
				total += player->m_94;
			}
		}
	}
	int op = pOp->m_int;
	bool result = false;
	switch (op) {
	case 0:
		result = pValue->m_int < total;
		break;
	case 1:
		result = pValue->m_int <= total;
		break;
	case 2:
		result = pValue->m_int == total;
		break;
	case 3:
		result = pValue->m_int >= total;
		break;
	case 4:
		result = pValue->m_int > total;
		break;
	case 5:
		result = pValue->m_int != total;
		break;
	default:
		break;
	}
	return result;
}
