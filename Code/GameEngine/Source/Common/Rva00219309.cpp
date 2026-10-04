// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva00219309@Rva00219309@@QAEHXZ @0x00219309 53B
// Honest-address count of leading non-null CommandButtons for the CommandSet
// looked up by the AsciiString at this+0x1dc via g_bfmeWorldRV.
// Evidence: retail add ecx,0x1dc plus rowed Rva0031D5F8 lookup 0x0031D5F8
// plus pin-only CommandSet::getCommandButton 0x00409EE8 looped over 0x20;
// callers at 0x00219341 0x005B27A1 0x005B2BF3 0x005B332A 0x005B36A4.
#include "ascii_string.h"

struct BfmeWorldRV;
extern struct BfmeWorldRV *g_bfmeWorldRV;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};

class CommandButton;
class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class Rva00219309
{
public:
	int rva00219309();
	char m_pad[0x1dc];
	AsciiString m_name;
};

int Rva00219309::rva00219309()
{
	void *p = ((Rva0031D5F8 *)g_bfmeWorldRV)->rva0031D5F8(&m_name);
	if (p == 0)
		return 0;
	CommandSet *cmdSet = (CommandSet *)p;
	unsigned int i = 0;
	for (; i < 0x20; ++i)
	{
		if (cmdSet->getCommandButton((int)i) == 0)
			break;
	}
	return (int)i;
}
