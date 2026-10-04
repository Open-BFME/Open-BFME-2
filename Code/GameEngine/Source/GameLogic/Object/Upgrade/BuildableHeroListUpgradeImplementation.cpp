// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BuildableHeroListUpgrade::upgradeImplementation, retail 0x004B837F (83
// bytes): slot 10 of the +0x10 UpgradeMux vtable 0x00C58F70 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). For every name in the
// list the controlling Player's +0x34 object keeps at +0x198, the template
// TheThingFactory finds for it (the pinned ThingFactory::findTemplate) goes to
// the Player's +0x738 member 0x0037F32F (pinned by address) with the Player;
// then TheControlBar is flagged (+0x28) to rebuild and the UpgradeModule
// condition apply 0x004CE4A0 runs (tail call).
#include "ascii_string.h"
#include <vector>
typedef bool Bool;
class ModuleData;
class ThingTemplate;
class Player;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;
class Rva0037F32F
{
public:
	void rva0037F32F(const ThingTemplate *tmpl, Player *player);
};
struct Rva004B837FList
{
	unsigned char m_pad000[0x198];
	_STL::vector<AsciiString> m_names;	// +0x198
};
class Player
{
public:
	unsigned char m_pad000[0x34];
	Rva004B837FList *m_34;			// +0x34
	unsigned char m_pad038[0x738 - 0x38];
	Rva0037F32F m_738;			// +0x738
};
class Object
{
public:
	Player *getControllingPlayer() const;
};
class ControlBar
{
public:
	unsigned char m_pad00[0x28];
	Bool m_28;				// +0x28
};
extern ControlBar *TheControlBar;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
class UpgradeMuxIface
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual void m02() = 0;
	virtual void m03() = 0;
	virtual void m04() = 0;
	virtual void m05() = 0;
	virtual void m06() = 0;
	virtual void m07() = 0;
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
public:
	void rva004CE4A0();
};
class BuildableHeroListUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeImplementation();
};
void BuildableHeroListUpgrade::upgradeImplementation()
{
	Player *player = getObject()->getControllingPlayer();
	_STL::vector<AsciiString> &names = player->m_34->m_names;
	for (_STL::vector<AsciiString>::iterator it = names.begin(); it != names.end(); ++it)
	{
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(*it);
		player->m_738.rva0037F32F(tmpl, player);
	}
	TheControlBar->m_28 = true;
	rva004CE4A0();
}
