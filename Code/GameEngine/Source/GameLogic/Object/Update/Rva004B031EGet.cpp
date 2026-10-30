// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004B031E@SpecialDisguiseUpdate@@QAEPAXXZ, retail 0x004B031E, 21 bytes.
// Honest-address thiscall with no stack args returning void*: loads
// AsciiString at [this+4]+0xD0 and looks it up through global g_009FF000
// slot rva002D06CA. Evidence: rowed callee 0x002D06CA, extern name in use
// g_009FF000 (?g_009FF000@@3PAVRva002D06CA@@A), callers 0x004B052E/0x004B0570
// test eax (non-void return), neighbours ModuleUpdateDtors / SpecialDisguise.
#include "ascii_string.h"

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};

extern ThingFactory *TheThingFactory;

class ModuleData;

class SpecialDisguiseUpdateModuleData
{
public:
	unsigned char m_pad00[0xD0];
	AsciiString m_disguiseAsTemplate; // +0xD0
};

class SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
protected:
	const ModuleData *m_moduleData; // +0x04
};

class SpecialDisguiseUpdate : public SpecialAbilityUpdate
{
public:
	void *rva004B031E();
};

void *SpecialDisguiseUpdate::rva004B031E()
{
	const SpecialDisguiseUpdateModuleData *data = (const SpecialDisguiseUpdateModuleData *)m_moduleData;
	return (void *)TheThingFactory->findTemplate(data->m_disguiseAsTemplate);
}
