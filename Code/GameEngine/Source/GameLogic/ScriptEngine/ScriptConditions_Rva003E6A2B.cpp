// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE /G7
// ?rva003E6A2B@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E6A2B 126B
// Chain via 0x0028D2A2; neighbours Rva003E6835 and evaluateTeamOwnedByPlayer.
// Evidence: ScriptConditions 2-Parameter bool via dispatcher 0x003EADEF; getUnitNamed 0x003588E7; flag +0x1C8 bit 8; player mask 0x00357B82 walked by getEachPlayerFromMask 0x002A7BC9; Object gate 0x002943B2 skipping shroud 0x0028D2A2 for Player +0x54 with FOGGED SHROUDED true.
class Parameter;
class Player
{
public:
	char m_pad[0x54];
	int m_54;
};
class Object;
enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
	CELLSHROUD_COUNT
};
class Object
{
public:
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	unsigned char m_pad1C8[0x1C8];
	unsigned char m_1C8;
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *parm);
	int rva00357B82(Parameter *parm);
};
extern ScriptEngine *g_Va009FE16C;
class ScriptConditions
{
protected:
	bool rva003E6A2B(Parameter *pUnitParm, Parameter *pPlayerParm);
};
bool ScriptConditions::rva003E6A2B(Parameter *pUnitParm, Parameter *pPlayerParm)
{
	Object *obj = g_Va009FE16C->getUnitNamed(pUnitParm);
	if (!obj)
		return false;
	if ((obj->m_1C8 & 8) != 0)
		return false;
	int mask = g_Va009FE16C->rva00357B82(pPlayerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!obj->rva002943B2(player)) {
			CellShroudStatus status = obj->getShroudStatusForPlayer(player->m_54);
			if (status == CELLSHROUD_FOGGED || status == CELLSHROUD_SHROUDED)
				return true;
		}
	}
	return false;
}
