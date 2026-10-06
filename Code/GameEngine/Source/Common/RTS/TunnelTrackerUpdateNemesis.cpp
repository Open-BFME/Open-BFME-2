// cl: /DNDEBUG /MD
//
// ?updateNemesis@TunnelTracker@@QAEXPBVObject@@@Z @0x004F5935 (74B).
// TunnelTracker nemesis refresh: when no current nemesis and the target
// carries a vehicle/structure/infantry/aircraft kind bit in its template
// dword at +0x108, takes its ID at +0x74 into +0x20; when the current
// nemesis equals the target, refreshes the timestamp at +0x24 from the
// GameLogic frame at +0x40. Rowed getCurNemesis 0x004F5684 twice, rowed
// TheGameLogic. Donors BFME1 TunnelTracker.cpp:130 and ZH variant.

class Object
{
public:
	int getID() const { return m_id; }

private:
	char m_pad00[4];
	void *m_template;
	char m_pad08[0x74 - 8];
	int m_id;
};

struct ObjectTemplate
{
	char m_pad[0x108];
	unsigned int m_kind;
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	char m_pad[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class TunnelTracker
{
public:
	Object *getCurNemesis();
	void updateNemesis(const Object *target);

private:
	char m_pad[0x20];
	int m_curNemesisID;
	unsigned int m_nemesisTimestamp;
};

void TunnelTracker::updateNemesis(const Object *target)
{
	if (getCurNemesis() == 0) {
		if (target != 0) {
			unsigned int kind = ((ObjectTemplate *)*(void *const *)((const char *)target + 4))->m_kind;
			if (((kind >> 8) & 0x13) == 0 && (kind & 0x80) == 0)
				return;
			m_curNemesisID = target->getID();
			m_nemesisTimestamp = TheGameLogic->getFrame();
		}
	} else if (getCurNemesis() == target) {
		m_nemesisTimestamp = TheGameLogic->getFrame();
	}
}
