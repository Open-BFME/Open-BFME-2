// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?getCommandOption@BattlePlanUpdate@@UBE?AW4CommandOption@@XZ, retail 0x0049771E (33B).
// Ported from Open-BFME-1 BattlePlanUpdate.cpp (BFME1 0x00285550): donor switch
// on the desired plan at +0x08 with OPTION_ONE/TWO/THREE returns. The method is
// virtual (UBE mangling), so the TU-local holder carries a vtable pointer at
// +0x00 with the desired plan at +0x08.

enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0,
	PLANSTATUS_BOMBARDMENT,
	PLANSTATUS_HOLDTHELINE,
	PLANSTATUS_SEARCHANDDESTROY
};

enum CommandOption
{
	OPTION_ONE = 0x00002000,
	OPTION_TWO = 0x00004000,
	OPTION_THREE = 0x00008000
};

class BattlePlanUpdate
{
public:
	virtual CommandOption getCommandOption() const;

private:
	void *m_vtable;	// +0x00
	int m_desiredPlan;	// retail reads this at +0x08 (the full module class
			// carries a second leading slot ahead of it)
};

// ?getCommandOption@BattlePlanUpdate@@UBE?AW4CommandOption@@XZ
CommandOption BattlePlanUpdate::getCommandOption() const
{
	switch (m_desiredPlan)
	{
		case PLANSTATUS_BOMBARDMENT:
			return OPTION_ONE;
		case PLANSTATUS_HOLDTHELINE:
			return OPTION_TWO;
		case PLANSTATUS_SEARCHANDDESTROY:
			return OPTION_THREE;
	}
	return (CommandOption)0;
}
