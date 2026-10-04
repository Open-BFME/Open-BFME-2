// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG
// AITacticDefensive.cpp -- named by retail's __FILE__ literal at 0x00C76860,
// pushed with line 43 into GetGameLogicRandomValueReal below.
//
// ?v3@Rva005DCB27@@UAE_NPAXH@Z @0x005DCB32 121B
// Slot 3 of the tactic whose destructor is 0x005DCB27 (table at VA
// 0x00C76834): after the AITactic slot 3 (0x004ECE61, pinned as
// Rva004ECECD::v3) accepts the unit, look up the owner's (+0x24)
// TheSkirmishAIManager record (0x002A8AB1), and with the chance table at
// record+0x160 indexed by the tactic slot (+0x20 -> +0x2C) set the unit's
// +0x2D0 to 2 unless a [0, 1] game-logic random value reaches that chance;
// always set +0x21C to 0x28 and answer true. Retail tests random >= chance
// and acts when it fails (fxch, fcompi, jae), so a NaN chance also takes
// the branch; `random < chance` compiles to the reverse operand order.
// fcompi needs /arch:SSE. Names are address-derived.
#define AITACTICDEFENSIVE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\AITacticDefensive.cpp"

float GetGameLogicRandomValueReal(float low, float high, char *file, int line);

struct Rva005DCB32Chances
{
	char m_pad00[0x7C];
	float m_chance[1];		// +0x7C, indexed by the tactic's slot
};
struct Rva002A8AB1Record
{
	char m_pad000[0x160];
	Rva005DCB32Chances *m_chances;	// +0x160
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

struct Rva005DCB32Slot
{
	char m_pad00[0x2C];
	int m_index;			// +0x2C
};
struct Rva005DCB32Unit
{
	char m_pad000[0x21C];
	int m_21C;			// +0x21C
	char m_pad220[0x2D0 - 0x220];
	int m_2D0;			// +0x2D0
};

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual bool v3(void *unit, int count);
};

class Rva005DCB27 : public Rva004ECECD
{
public:
	virtual bool v3(void *unit, int count);
	char m_pad04[0x20 - 4];
	Rva005DCB32Slot *m_slot;	// +0x20
	void *m_owner;			// +0x24
};

bool Rva005DCB27::v3(void *unit, int count)
{
	if (Rva004ECECD::v3(unit, count)) {
		Rva005DCB32Unit *target = (Rva005DCB32Unit *)unit;
		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
		Rva005DCB32Chances *chances = record->m_chances;
		int index = m_slot->m_index;
		if (!(GetGameLogicRandomValueReal(0.0f, 1.0f, AITACTICDEFENSIVE_FILE, 43) >= chances->m_chance[index]))
			target->m_2D0 = 2;
		target->m_21C = 0x28;
		return true;
	}
	return false;
}
