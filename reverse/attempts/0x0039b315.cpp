// ?rva0039B315@ExperienceTracker@@QAEXM_N000@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva0039B315@ExperienceTracker@@QAEXM_N000@Z retail 0x0039B315, 188 B.
// Zero Hour's ExperienceTracker::addExperiencePoints shape: forward to the
// experience sink's tracker (scaled, flags true/false; cl turns the tail
// recursion into retail's loop), else scale by the multiplayer XP multiplier
// (building or unit by the parent template's KindOf bit 0x108&0x80) and hand
// everything to 0x0039B16F (unrowed; would need a pin).
class Object;
class ExperienceTracker;

class GameLogic
{
public:
	Object *findObjectByID(unsigned int id);	// 0x00049DC5
	char rva0023C6FD();				// 0x0023C6FD
};
extern GameLogic *TheGameLogic;

class PlayerList
{
public:
	int rva002A7C0B(bool b);			// 0x002A7C0B
};
extern PlayerList *ThePlayerList;

class MultiPlayMults
{
public:
	float getBuildingXPMult(int player) const;	// 0x002359A6
	float getUnitXPMult(int player) const;		// 0x0023598B
};

class GlobalData
{
public:
	unsigned char m_pad[0xEC4];
	MultiPlayMults m_multiPlayMults;		// +0xEC4
};
extern GlobalData *TheWritableGlobalData;

class ThingTemplate
{
public:
	bool isStructure() const { return (m_kindOf[0x108 - 0x100] & 0x80) != 0; }
private:
	unsigned char m_pad[0x100];
	unsigned char m_kindOf[0x10];			// +0x100
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x264 - 8];
	ExperienceTracker *m_experienceTracker;		// +0x264
};

class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);
	void rva0039B16F(float amount, bool a, bool b, bool c, bool d, float mult);	// 0x0039B16F

private:
	unsigned char m_pad00[0x1C];
	float m_experienceScalar;			// +0x1C
	unsigned char m_pad20[0x34 - 0x20];
	Object *m_parent;				// +0x34
	unsigned int m_experienceSink;			// +0x38
};

void ExperienceTracker::rva0039B315(float amount, bool a, bool b, bool c, bool d)
{
	GameLogic *gameLogic = TheGameLogic;
	if (m_experienceSink)
	{
		Object *sink = gameLogic->findObjectByID(m_experienceSink);
		if (sink)
		{
			sink->getExperienceTracker()->rva0039B315(amount * m_experienceScalar, a, b, true, false);
			return;
		}
	}

	float mult = 1.0f;
	if (gameLogic->rva0023C6FD())
	{
		int player = ThePlayerList->rva002A7C0B(false);
		if (m_parent->getTemplate()->isStructure())
			mult = TheWritableGlobalData->m_multiPlayMults.getBuildingXPMult(player);
		else
			mult = TheWritableGlobalData->m_multiPlayMults.getUnitXPMult(player);
	}
	rva0039B16F(amount, a, b, c, d, mult);
}
