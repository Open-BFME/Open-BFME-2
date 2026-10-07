// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00357475@ScriptEngine@@QAEHABVAsciiString@@PA_N@Z, retail 0x00357475
// (476B). Player-name to player-mask resolution behind the Parameter
// resolver 0x00357B82. Zero Hour's ScriptEngine::getPlayerFromAsciiString
// grown into BFME's mask selectors: "<This Player's Enemies/Allies...>" and
// "<Local Player's ...>" ask the player list for every player in a
// relationship (getPlayersWithRelationship, 0x002A7C70; 4 enemies, 3 allies incl self, 2 allies),
// "<This Player>", "<This Player's Enemy>" (getSkirmishEnemyPlayer, 0x00356F6E, ZH
// getSkirmishEnemyPlayer's slot) and "<Local Player>" give one bit,
// "<All Players>" every bit (rowed 0x002A7D30); anything else is looked up by
// name key and reported when unknown. *matchedSpecialName is cleared only on
// that last path, so callers cache only real player names. BFME 1 names the
// function getPlayerMaskFromAsciiString; the row stays address-derived.

#include "ascii_string.h"

typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	// Matched callers use the target player index at +0x54 directly;
	// avoid an out-of-line getter shared with incompatible layouts.
	int getPlayerMask() const { return 1 << m_playerIndex; }
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
	Player *findPlayerWithNameKey(NameKeyType key);
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships, bool reverse);
	int rva002A7D30();
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	Player *getCurrentPlayer();
	Player *getSkirmishEnemyPlayer();
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);
	int rva00357475(const AsciiString &name, Bool *matchedSpecialName);
};
extern ScriptEngine *TheScriptEngine;

int ScriptEngine::rva00357475(const AsciiString &name, Bool *matchedSpecialName)
{
	if (matchedSpecialName)
		*matchedSpecialName = true;
	if (!TheScriptEngine->getCurrentPlayer())
		return 0;

	int mask = 0;
	int thisIndex = TheScriptEngine->getCurrentPlayer()->m_playerIndex;
	int localIndex = ThePlayerList->m_local->m_playerIndex;
	if (name.compare("<This Player's Enemies>") == 0)
		mask = ThePlayerList->getPlayersWithRelationship(thisIndex, 4, false);
	else if (name.compare("<This Player's Allies incl Self>") == 0)
		mask = ThePlayerList->getPlayersWithRelationship(thisIndex, 3, false);
	else if (name.compare("<This Player's Allies>") == 0)
		mask = ThePlayerList->getPlayersWithRelationship(thisIndex, 2, false);
	else if (name.compare("<This Player>") == 0)
		mask = getCurrentPlayer()->getPlayerMask();
	else if (name.compare("<This Player's Enemy>") == 0)
		mask = getSkirmishEnemyPlayer()->getPlayerMask();
	else if (name.compare("<Local Player>") == 0)
		mask = ThePlayerList->m_local->getPlayerMask();
	else if (name.compare("<Local Player's Enemies>") == 0)
		mask = ThePlayerList->getPlayersWithRelationship(localIndex, 4, false);
	else if (name.compare("<Local Player's Allies incl Self>") == 0)
		mask = ThePlayerList->getPlayersWithRelationship(localIndex, 3, false);
	else if (name.compare("<Local Player's Allies>") == 0)
		mask = ThePlayerList->getPlayersWithRelationship(localIndex, 2, false);
	else if (name.compare("<All Players>") == 0)
		mask = ThePlayerList->rva002A7D30();
	else {
		if (matchedSpecialName)
			*matchedSpecialName = false;
		Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
		if (player)
			mask = player->getPlayerMask();
		else {
			AsciiString msg;
			msg.format("***Invalid Player name: \"%s\"***", name.str());
			AppendDebugMessage(msg, false);
		}
	}
	return mask;
}
