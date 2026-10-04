// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/Palantir
//
// BFME2 literal fix: retail's two statics name "NonCommand_MultiplayerOptions"
// (VA 0x00C02D90, the observer-active arm) and "NonCommand_Options" (VA
// 0x00C02D7C, the inactive arm); the donor carried BFME1's "NonCommand_Objectives"
// and "NonCommand_PlayerStatus". Only the literals differ; the body is byte-equal.
//
// Open-BFME5: the observer-dependent command dispatch at retail 0x0058EDB0,
// 228 bytes.  Same two-static shape as 0x0058ECA0, but the selector is a live
// observer plus a predicate call rather than a flag bit.

class AsciiStringYU
{
public:
	AsciiStringYU(const char *text);

	~AsciiStringYU(void);
};

class BfmeObserverYU
{
public:
	bool bfmeActiveYU(void);
};

class BfmeRegistryYU
{
public:
	void *bfmeFindYU(const AsciiStringYU &name);

	void bfmeUseYU(int mode, void *entry);
};

// The global at 0x012F33F8 is the ControlBar singleton; only the accessor
// spellings the method pins carry are needed here, so it stays incomplete.
class ControlBar;
class GameLogic;
extern GameLogic *TheGameLogic;				// retail 0x012F0898
extern ControlBar *TheControlBar;			// retail 0x012F33F8

// ?bfmeApplyYU@@YGXH@Z
void __stdcall bfmeApplyYU(int unused)
{
	AsciiStringYU *name;

	if (TheGameLogic != 0 && ((BfmeObserverYU *)TheGameLogic)->bfmeActiveYU())
	{
		static AsciiStringYU s_bfmeObjectivesYU("NonCommand_MultiplayerOptions");

		name = &s_bfmeObjectivesYU;
	}
	else
	{
		static AsciiStringYU s_bfmeOtherYU("NonCommand_Options");

		name = &s_bfmeOtherYU;
	}

	void *entry = reinterpret_cast<BfmeRegistryYU *>(TheControlBar)->bfmeFindYU(*name);

	if (entry != 0)
		reinterpret_cast<BfmeRegistryYU *>(TheControlBar)->bfmeUseYU(0, entry);
}
