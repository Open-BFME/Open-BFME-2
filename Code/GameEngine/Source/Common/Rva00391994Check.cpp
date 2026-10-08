// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00391994@Rva00391994@@QAE_NXZ @ 0x00391994 (69B) unlock: command-button 0x16 scan over 32 slots via rowed Object name plus rowed Rva0031D5F8 lookup plus pinned getCommandButton. Evidence: global g_bfmeWorldRV null check then name then lookup then 0x20 loop with +0x14 compare to 0x16; caller 0x00394231.
#include "ascii_string.h"

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class Object
{
public:
	const AsciiString *rva00290E67(void) const;
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *);
};

class CommandButton
{
public:
	int m_pad[5];
	int m_14;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int) const;
};

class Rva00391994
{
public:
	bool rva00391994(void);
};

bool Rva00391994::rva00391994(void)
{
	if ((*(BfmeWorldRV **)&TheControlBar)) {
		const AsciiString *name = ((const Object *)this)->rva00290E67();
		const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
		if (cmdSet) {
			for (int i = 0; i < 0x20; ++i) {
				const CommandButton *btn = cmdSet->getCommandButton(i);
				if (btn && btn->m_14 == 0x16)
					return true;
			}
		}
	}
	return false;
}
