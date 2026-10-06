// cl: /DNDEBUG /MD
//
// ?getCurNemesis@TunnelTracker@@QAEPAVObject@@XZ @0x004F5684 (97B).
// TunnelTracker nemesis guard: returns 0 when no nemesis, when the nemesis
// timestamp plus LOGICFRAMES_PER_SECOND*4 has passed the GameLogic frame at
// +0x40, when findObjectByID misses, when the stealth query says hidden, or
// when the Object dead byte at +0x438 is set; otherwise returns the target.
// Adapted from BFME1 TunnelTrackerGetCurNemesis (ZH 4*LOGICFRAMES generalized
// to g_Va00DBA4E4*4). Pinned name, rowed findObjectByID 0x00049DC5 and rowed
// Object stealth query 0x002943B2. Callers at 0x004F5938 plus AITNGuard.

class Player;

class Object
{
public:
	bool rva002943B2(const Player *viewer);
	bool isEffectivelyDead() const { return (m_deadFlag & 1) != 0; }

private:
	unsigned char m_pad[0x438];
	unsigned char m_deadFlag;
};

enum ObjectID
{
	INVALID_ID = 0
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id);

private:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

class TunnelTracker
{
public:
	Object *getCurNemesis();

private:
	unsigned char m_pad[0x20];
	int m_curNemesisID;
	unsigned int m_nemesisTimestamp;
};

Object *TunnelTracker::getCurNemesis()
{
	if (m_curNemesisID == 0)
		return 0;
	if (m_nemesisTimestamp + (unsigned int)g_Va00DBA4E4 * 4 < TheGameLogic->getFrame()) {
		m_curNemesisID = 0;
		return 0;
	}
	Object *target = TheGameLogic->findObjectByID((ObjectID)m_curNemesisID);
	if (target != 0 && target->rva002943B2(0))
		target = 0;
	if (target != 0 && target->isEffectivelyDead())
		target = 0;
	if (target == 0)
		m_curNemesisID = 0;
	return target;
}
