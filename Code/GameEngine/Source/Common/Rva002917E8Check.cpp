// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002917E8@Rva002917E8@@QAE_NXZ @ 0x002917E8 (79B) unlock: Object 6-bit plus command-button 0x10 flag scan over 32 slots via rowed Object name plus rowed Rva0031D5F8 lookup plus pinned getCommandButton. Evidence: rva0028ADF7 row plus g_bfmeWorldRV plus 0x20 loop with +0x1c test 0x10; caller 0x0030F019.
#include "ascii_string.h"

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class Object
{
public:
	int rva0028ADF7(int slot) const;
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
	char m_pad[0x1C];
	unsigned char m_flag1C;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int) const;
};

class Rva002917E8
{
public:
	bool rva002917E8(void);
};

bool Rva002917E8::rva002917E8(void)
{
	unsigned char first = (unsigned char)((const Object *)this)->rva0028ADF7(6);
	if (first)
		return true;
	const AsciiString *name = ((const Object *)this)->rva00290E67();
	const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
	if (cmdSet) {
		for (int i = 0; i < 0x20; ++i) {
			const CommandButton *btn = cmdSet->getCommandButton(i);
			if (btn && (btn->m_flag1C & 0x10))
				return true;
		}
	}
	return false;
}
