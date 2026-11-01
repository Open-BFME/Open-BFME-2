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
	void *rva0031D5F8(const AsciiString *key); // 0x0031D5F8, findCommandSet
};

typedef bool Bool;
typedef unsigned int UnsignedInt;
class ThingTemplate;
class UpgradeTemplate;
enum GUICommandType
{
	GUI_COMMAND_DOZER_CONSTRUCT = 1,
	GUI_COMMAND_UNIT_BUILD = 3,
	GUI_COMMAND_46 = 46,
	GUI_COMMAND_53 = 53
};
struct UpgradeTemplateList
{
	const UpgradeTemplate **m_begin;
	const UpgradeTemplate **m_end;
	const UpgradeTemplate **m_capacity;
	UnsignedInt size() const { return (UnsignedInt)(m_end - m_begin); }
	const UpgradeTemplate *operator[](UnsignedInt i) const { return m_begin[i]; }
};
class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	UnsignedInt getOptions() const { return m_options; }
	const ThingTemplate *rva0035B570() const;		// the button's thing template
	const UpgradeTemplateList &getNeededUpgrades() const { return m_neededUpgrades; }
	Bool isAnyUpgradeEnough() const { return m_anyUpgrade; }

private:
	unsigned char m_pad00[0x14];
	GUICommandType m_command;		// +0x14
	unsigned char m_pad18[0x1C - 0x18];
	UnsignedInt m_options;			// +0x1C
	unsigned char m_pad20[0x28 - 0x20];
	UpgradeTemplateList m_neededUpgrades;	// +0x28
	Bool m_anyUpgrade;			// +0x34
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const; // 0x00409EE8
};

class Rva00391994
{
public:
	bool rva00391994();
};

bool Rva00391994::rva00391994(void)
{
	if ((*(BfmeWorldRV **)&TheControlBar)) {
		const AsciiString *name = ((const Object *)this)->rva00290E67();
		const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
		if (cmdSet) {
			for (int i = 0; i < 0x20; ++i) {
				const CommandButton *btn = cmdSet->getCommandButton(i);
				if (btn && btn->getCommandType() == 0x16)
					return true;
			}
		}
	}
	return false;
}
