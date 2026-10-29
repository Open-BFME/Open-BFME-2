// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?doMergeTeamIntoTeam@ScriptActions@@IAEXABVAsciiString@@0@Z, retail
// 0x003C01E2 (294 bytes, EH, RET 8). Zero Hour's doMergeTeamIntoTeam flow:
// walk the source team's member list (the next object is read before advance,
// since setTeam breaks the iterator), move every member to the destination
// team and update it (0x003BA83F). BFME 2 additions: the destination is found
// exact, a source under another player is first handed to the destination's
// player, members whose container has the 0x20 template flag are skipped and the
// pass repeats up to three times until the source is empty (then it is deleted).
// Name from the Zero Hour donor flow (iterate, nextObj, setTeam, deleteTeam);
// the WorldBuilder name is not proven by a string.
#include "ascii_string.h"

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Player;
class Team;

struct Rva003C01E2ContainerTemplate
{
	char m_pad[0x115];
	unsigned char m_f115;
};

struct Rva003C01E2Container
{
	char m_pad[4];
	Rva003C01E2ContainerTemplate *m_template;
};

class Object
{
public:
	void setTeam(Team *team);	// 0x00298AE4
	char m_pad00[0x274];
	Rva003C01E2Container *m_container;	// +0x274
};

class Team
{
public:
	Player *getControllingPlayer() const;	// 0x0039D7CF
	void setControllingPlayer(Player *player);	// 0x0039D97E
	Object *rva0039E8EB();
	void deleteTeam(bool flag);	// 0x003A10FE
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
	char m_pad[0x5D];
	unsigned char m_active;	// +0x5D
	unsigned char m_justCreated;	// +0x5E
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

int __cdecl rva003BA83F(void *obj, int value);

class ScriptActions
{
protected:
	void doMergeTeamIntoTeam(const AsciiString &teamSrcName, const AsciiString &teamDestName);
};

void ScriptActions::doMergeTeamIntoTeam(const AsciiString &teamSrcName, const AsciiString &teamDestName)
{
	Team *teamSrc = TheScriptEngine->getTeamNamed(teamSrcName, false);
	Team *teamDest = TheScriptEngine->getTeamNamed(teamDestName, true);
	if (!teamSrc || !teamDest || teamSrc == teamDest)
		return;

	if (teamSrc->getControllingPlayer() != teamDest->getControllingPlayer())
		teamSrc->setControllingPlayer(teamDest->getControllingPlayer());

	int tries = 3;
	do {
		DLINK_ITERATOR<Object> iter = teamSrc->iterate_TeamMemberList();
		Object *nextObj = iter.cur();
		while (!iter.done()) {
			Object *obj = nextObj;
			if (!obj)
				break;
			nextObj = iter.cur();
			iter.advance();
			Rva003C01E2Container *container = obj->m_container;
			if (!container || !(container->m_template->m_f115 & 0x20)) {
				obj->setTeam(teamDest);
				rva003BA83F(obj, 0);
			}
		}
		if (nextObj) {
			nextObj->setTeam(teamDest);
			rva003BA83F(nextObj, 0);
		}
		if (!teamSrc->rva0039E8EB()) {
			teamSrc->deleteTeam(false);
			break;
		}
	} while (--tries > 0);

	if (!teamDest->m_active) {
		teamDest->m_justCreated = 1;
		teamDest->m_active = 1;
	}
}
