// ?evaluatePlayerIsInPlanningMode@ScriptConditions@@IAE_NPAVParameter@@@Z
// retail 0x003E54B4, 67 bytes.
// Evidence: leaf via pin-only ScriptEngine::rva00357B82 plus rowed PlayerList::getEachPlayerFromMask; ThePlayerList 0x009FEEE8 plus g_Va009FE16C ScriptEngine global; Player +0x750 == 2.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

class Parameter
{
};

class ScriptEngine
{
public:
	int rva00357B82(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

class Player
{
public:
	char m_pad[0x750];
	int m_750;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	bool evaluatePlayerIsInPlanningMode(Parameter *param);
};

bool ScriptConditions::evaluatePlayerIsInPlanningMode(Parameter *param)
{
	if (!param)
		return false;

	int mask = TheScriptEngine->rva00357B82(param);
	Player *player = ThePlayerList->getEachPlayerFromMask(mask);
	if (!player)
		return false;

	return player->m_750 == 2;
}
