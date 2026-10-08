// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?rva00409EB3@CreateAHeroHero@@QAEPBVCommandButton@@I@Z, retail 0x00409EB3 53B.
// Indexed CommandButton via ControlBar lookup with count guard. Evidence:
// leaf lane, caller 0x005B4686, callees InitButtonList rva00409EA0
// findCommandButton rowed, TheControlBar global, prev/next same block.

#include "ascii_string.h"

class CommandButton;
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;
class CreateAHeroHero
{
public:
	void InitButtonList();
	int rva00409EA0();
	const CommandButton *rva00409EB3(unsigned index);

private:
	char m_pad00[0x3C];
	AsciiString *m_begin;
	AsciiString *m_end;
};
const CommandButton *CreateAHeroHero::rva00409EB3(unsigned index)
{
	InitButtonList();
	const CommandButton *result = 0;
	int count = rva00409EA0();
	if (index < (unsigned)count)
	{
		AsciiString *base = m_begin;
		result = TheControlBar->findCommandButton(base[index]);
	}
	return result;
}
