// cl: /O1 /DNDEBUG /MD /EHsc
// Target evidence: Ghidra bounds 0x0023C8DA at 40 bytes. Retail calls the
// pinned 0x00210DC9 query through the 0x00DFE1C8 singleton, then conditionally
// calls 0x0040F87E on this+0x184. Matched GameLogic::LivingWorldTacticalBattleComplete
// confirms GameLogic's +0x184 member is ArmySummarySystem; this method and the
// nested operation's purpose remain address-derived.

class Rva00DFE1C8Host
{
public:
	bool rva00210DC9();
};

extern Rva00DFE1C8Host *g_00DFE1C8;

class ArmySummarySystem
{
public:
	bool rva0040F87E();
};

class GameLogic
{
public:
	bool rva0023C8DA(unsigned char value);

private:
	unsigned char m_pad00[0x184];
	ArmySummarySystem m_armySummarySystem;
};

// ?rva0023C8DA@GameLogic@@QAE_NE@Z
bool GameLogic::rva0023C8DA(unsigned char value)
{
	bool result = g_00DFE1C8->rva00210DC9();
	if (result && value == 0)
		result = m_armySummarySystem.rva0040F87E();
	return result;
}
