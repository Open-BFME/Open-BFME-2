// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (sixteenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered unless named, so each keeps an
// address-derived name and a view of only the members it touches. Callees use
// the ledger's existing spellings.

class Object;
struct Coord3D;

// --- 0x005F8E7D..0x005F8ECA: StrategicHUD::BattlePromptMovieClip::Impl's Apt
// command callbacks. Its constructor 0x005FA3B1 binds them, in this order, to
// "<level>.<name>_OnOpen", "_OnClosed", "_OnAutoResolveButtonClicked",
// "_OnRealTimeButtonClicked" and "_OnRetreatButtonClicked"
// (StrategicHUDBattlePromptMovieClipConstructor.cpp). A state word (+0x18)
// gates the +0x00 listener's virtual slots (0 -> 1 with slot 1; 2 -> 3 with
// slot 0; state 1 with slots 2, 3 and 4); the command argument is unused.
class Rva005F8E7DListener
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
};

namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::BattlePromptMovieClip::Impl
{
public:
	void OnOpen(const char *unused);
	void OnClosed(const char *unused);
	void OnAutoResolveButtonClicked(const char *unused);
	void OnRealTimeButtonClicked(const char *unused);
	void OnRetreatButtonClicked(const char *unused);
private:
	Rva005F8E7DListener *m_listener;
	char m_pad04[0x18 - 4];
	int m_state;											// +0x18
};

void StrategicHUD::BattlePromptMovieClip::Impl::OnOpen(const char *)
{
	if (m_state == 0)
	{
		m_state = 1;
		m_listener->s1();
	}
}

void StrategicHUD::BattlePromptMovieClip::Impl::OnClosed(const char *)
{
	if (m_state == 2)
	{
		m_state = 3;
		m_listener->s0();
	}
}

void StrategicHUD::BattlePromptMovieClip::Impl::OnAutoResolveButtonClicked(const char *)
{
	if (m_state == 1)
		m_listener->s2();
}

void StrategicHUD::BattlePromptMovieClip::Impl::OnRealTimeButtonClicked(const char *)
{
	if (m_state == 1)
		m_listener->s3();
}

void StrategicHUD::BattlePromptMovieClip::Impl::OnRetreatButtonClicked(const char *)
{
	if (m_state == 1)
		m_listener->s4();
}

// --- 0x004A9774 (43B) / 0x004A979F (52B): AIUpdateInterface dock and
// harvest overrides that remember, for a player-free command (source 0), the
// dock's +0x74 id (+0x4A4) or the harvest point (+0x4A8, flagged at +0x4B4).
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

struct Rva004A9774Point
{
	float x;
	float y;
	float z;
};

class AIUpdateInterface
{
protected:
	virtual void privateDock(Object *obj, CommandSourceType cmdSource);			// 0x0026481B
	virtual void privateHarvest(const Coord3D *pos, CommandSourceType cmdSource);	// 0x00264853
};

class Rva004A9774AI : public AIUpdateInterface
{
protected:
	virtual void privateDock(Object *obj, CommandSourceType cmdSource);
	virtual void privateHarvest(const Coord3D *pos, CommandSourceType cmdSource);
private:
	char m_pad[0x4A4 - 4];
	int m_dockID;											// +0x4A4
	Rva004A9774Point m_harvestPos;							// +0x4A8
	bool m_hasHarvestPos;									// +0x4B4
};

void Rva004A9774AI::privateDock(Object *obj, CommandSourceType cmdSource)
{
	AIUpdateInterface::privateDock(obj, cmdSource);
	if (cmdSource == CMD_FROM_PLAYER && obj)
		m_dockID = *(const int *)((const char *)obj + 0x74);
}

void Rva004A9774AI::privateHarvest(const Coord3D *pos, CommandSourceType cmdSource)
{
	AIUpdateInterface::privateHarvest(pos, cmdSource);
	if (cmdSource == CMD_FROM_PLAYER && pos)
	{
		m_harvestPos = *(const Rva004A9774Point *)pos;
		m_hasHarvestPos = true;
	}
}

// --- 0x004E07A9 (26B) / 0x004E07C3 (33B): a by-value 16-byte block and one
// or two words.
struct Rva004E07A9Block
{
	int m_data[4];
};

struct Rva004E07A9
{
	Rva004E07A9(Rva004E07A9Block block, int a);
	Rva004E07A9Block m_block;
	int m_10;
};

struct Rva004E07C3
{
	Rva004E07C3(Rva004E07A9Block block, int a, int b);
	Rva004E07A9Block m_block;
	int m_10;
	int m_14;
};
