// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva002922D9@Object@@QAE_NPBVCommandButton@@@Z @0x002922D9 87B
// Evidence: pin Object::rva002922D9; 5 matched callers pass a CommandButton;
// +0x44 slot via rowed Object::getSpecialPowerModule 0x0028BB9E; name via rowed
// Object::rva00290E67 0x00290E67; set lookup via g_bfmeWorldRV and rowed
// Rva0031D5F8::rva0031D5F8 0x0031D5F8; 0x20 slots via rowed
// CommandSet::getCommandButton 0x00409EE8.
#include "ascii_string.h"

struct BfmeWorldRV;
extern struct BfmeWorldRV *g_bfmeWorldRV;

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};

class CommandButton
{
public:
	char m_pad00[0x44];
	void *m_special44;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	const AsciiString *rva00290E67() const;
	bool rva002922D9(const CommandButton *btn);
};

bool Object::rva002922D9(const CommandButton *btn)
{
	void *special = btn->m_special44;
	if (special) {
		if (this->getSpecialPowerModule(reinterpret_cast<const SpecialPowerTemplate *>(special)) == 0)
			return false;
	}
	const AsciiString *name = rva00290E67();
	const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)g_bfmeWorldRV)->rva0031D5F8(name);
	if (cmdSet == 0)
		return false;
	for (int i = 0; i < 0x20; ++i) {
		if (cmdSet->getCommandButton(i) == btn)
			return true;
	}
	return false;
}
