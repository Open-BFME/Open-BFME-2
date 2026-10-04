// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// TooltipUpgrade::upgradeRemovalImplementation, retail 0x004B7ADB (69
// bytes): slot 8 of the +0x10 UpgradeMux vtable 0x00C58BC0 (slot 10 is the
// rowed 0x004B7A9D; the recipe of RemoveUpgradeUpgradeRemovalImplementation.cpp).
// Only when the upgrade is in effect (mux slot 0): the Object's Drawable, if
// any, drops the two tooltip strings it carries at +0x348 and +0x34C and
// TheControlBar is flagged (+0x28) to rebuild; then the executed flag is
// cleared (mux slot 9).
#include "ascii_string.h"
typedef bool Bool;
class ModuleData;
class Drawable
{
public:
	unsigned char m_pad000[0x348];
	AsciiString m_348;		// +0x348
	AsciiString m_34C;		// +0x34C
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Object : public Thing
{
};
class ControlBar
{
public:
	unsigned char m_pad00[0x28];
	Bool m_28;			// +0x28
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
};
class TooltipUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
};
void TooltipUpgrade::upgradeRemovalImplementation()
{
	if (isAlreadyUpgraded())
	{
		Drawable *draw = getObject()->getDrawable();
		if (draw)
		{
			draw->m_348.clear();
			draw->m_34C.clear();
			TheControlBar->m_28 = true;
		}
		setUpgradeExecuted(false);
	}
}
