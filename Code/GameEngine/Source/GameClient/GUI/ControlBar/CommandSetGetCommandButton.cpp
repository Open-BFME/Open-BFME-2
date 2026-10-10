// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// CommandSet::getCommandButton, retail 0x00409EE8 (51 bytes), after Zero
// Hour's GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference): Zero Hour
// returns m_command[i]. BFME 2 (target evidence) first asks TheGameLogic for
// an override of slot i of the set named at CommandSet +0x10 through
// 0x00246F8E (a GameLogic map lookup keyed by name and slot that writes the
// button and returns true when found; its name is not established), and
// otherwise returns the button array at +0x14.
typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
class ThingTemplate { public: void GetAssetList(int,int); };
class CommandButton { public: const ThingTemplate *rva0035B570() const; };

class GameLogic
{
public:
	Bool rva00246F8E(const AsciiString &setName, Int slot, const CommandButton **button);
};
extern GameLogic *TheGameLogic;

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;
 void rva00409F1B(int,int);
private:
	unsigned char m_pad00[0x10];
	AsciiString m_name; // +0x10
	const CommandButton *m_command[32]; // +0x14: native asset walker proves32 slots
};

//-------------------------------------------------------------------------------------------------
const CommandButton *CommandSet::getCommandButton(Int i) const
{
	const CommandButton *button;
	if (TheGameLogic && TheGameLogic->rva00246F8E(m_name, i, &button))
		return button;
	return m_command[i];
}

// Native104B409F1B/WBc28F60 walks all32 slots, honoring each GameLogic
// override before loading the fallback. Kinds1/3 forward non-null template
// assets through existing notify33CF34 (a proven GetAssetList ABI view).
// Positive lookup-success branch preserves native fallback/success block order.
void CommandSet::rva00409F1B(int a, int b)
{
	for (int i = 0; i < 32; ++i)
	{
		const CommandButton *button;
		const CommandButton *cur;
		if (TheGameLogic && TheGameLogic->rva00246F8E(m_name,i,&button))
            cur=button;
        else {
            button=m_command[i];cur=button;
        }
		if (cur == 0)
			continue;
		int kind = *(const int *)((const char *)cur + 0x14);
		switch (kind)
		{
		case 1:
		case 3:
			break;
		default:
			continue;
		}
		const ThingTemplate *tmpl = cur->rva0035B570();
		if (tmpl == 0)
			continue;
		const_cast<ThingTemplate *>(tmpl)->GetAssetList(a, b);
	}
}
