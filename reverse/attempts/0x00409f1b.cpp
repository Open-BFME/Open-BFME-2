// ?rva00409F1B@CommandSet@@QAEXHH@Z
// partial score=0.96 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?rva00409F1B@CommandSet@@QAEXHH@Z @0x00409F1B 104B: loop 32 command slots resolving override via GameLogic map then notifying ThingTemplate for button kinds 1 and 3. Evidence: neighbours CommandSetGetCommandButton same +0x10/+0x14 layout, callees pinned GameLogic 0x246F8E CommandButton 0x35B570 notify 0x33CF34, callers unclaimed.
#include "ascii_string.h"

class CommandButton;
class ThingTemplate;
class Rva0020AA00Target;

class GameLogic
{
public:
	bool rva00246F8E(const AsciiString &setName, int slot, const CommandButton **button);
};
extern GameLogic *TheGameLogic;

class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;
private:
	char m_pad00[0x14];
	int m_commandType;
};

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

class CommandSet
{
public:
	void rva00409F1B(int a, int b);
private:
	char m_pad00[0x10];
	AsciiString m_name;
	const CommandButton *m_slots[32];
};

// ?rva00409F1B@CommandSet@@QAEXHH@Z present-unmatched
void CommandSet::rva00409F1B(int a, int b)
{
	for (int i = 0; i < 32; ++i)
	{
		const CommandButton *button;
		const CommandButton *cur;
		if (!TheGameLogic || !TheGameLogic->rva00246F8E(m_name, i, &button))
		{
			cur = m_slots[i];
			button = cur;
		}
		else
			cur = button;
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
		reinterpret_cast<Rva0020AA00Target *>(const_cast<ThingTemplate *>(tmpl))->notify(a, b);
	}
}
