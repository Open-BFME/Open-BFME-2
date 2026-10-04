// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE /G7
// ?rva003E6AA9@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E6AA9 174B
// Team twin of 0x003E6A2B; neighbours Rva003E6A2B and evaluateTeamOwnedByPlayer.
// Evidence: ScriptConditions 2-Parameter bool via dispatcher 0x003EAE15; getTeamNamed 0x003584E9; flag +0x1C8 bit 8; player mask 0x00357B82 walked by getEachPlayerFromMask 0x002A7BC9; Object gate 0x002943B2 skipping shroud 0x0028D2A2 for Player +0x54 with FOGGED SHROUDED true.
#include "ascii_string.h"
class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
};
class Player
{
public:
	char m_pad[0x54];
	int m_54;
};
class Object;
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
class Object
{
public:
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	unsigned char m_pad1C8[0x1C8];
	unsigned char m_1C8;
};
class PlayerList { public: Player *getEachPlayerFromMask(int &mask); };
extern PlayerList *ThePlayerList;
class Team;
template<class OBJCLASS> class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	unsigned char m_rest[20];
};
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
	int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *g_Va009FE16C;
class ScriptConditions
{
protected:
	bool rva003E6AA9(Parameter *pTeamParm, Parameter *pPlayerParm);
};
bool ScriptConditions::rva003E6AA9(Parameter *pTeamParm, Parameter *pPlayerParm)
{
	Team *team = g_Va009FE16C->getTeamNamed(pTeamParm->getString(), false);
	if (!team)
		return false;
	int mask = g_Va009FE16C->rva00357B82(pPlayerParm);
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	while (!iter.done()) {
		Object *obj = iter.cur();
		if ((obj->m_1C8 & 8) == 0) {
			int m = mask;
			while (m) {
				Player *player = ThePlayerList->getEachPlayerFromMask(m);
				if (!obj->rva002943B2(player)) {
					CellShroudStatus status = obj->getShroudStatusForPlayer(player->m_54);
					if (status == CELLSHROUD_FOGGED || status == CELLSHROUD_SHROUDED)
						return true;
				}
			}
		}
		iter.advance();
	}
	return false;
}
