// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// AttributeModifierUpgrade::upgradeImplementation, retail 0x004B678D (32
// bytes), and upgradeRemovalImplementation, retail 0x004B67AD (47 bytes):
// slots 10 and 8 of the +0x10 UpgradeMux vtable 0x00C587A0 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). Applying runs the
// UpgradeModule condition apply 0x004CE4A0 and hands the module data's +0x118
// name to the rowed Object::rva0028EA91 with -1; removal, only when the
// upgrade is in effect (mux slot 0), runs the condition removal 0x004CE4A8,
// hands the same name to Object 0x0028EB42 (pinned by address on this call
// site) and clears the executed flag (mux slot 9).
#include "ascii_string.h"
typedef bool Bool;
class ModuleData;
class Object
{
public:
	bool rva0028EA91(const AsciiString &name, int value);
	void rva0028EB42(const AsciiString &name);
};
struct AttributeModifierUpgradeModuleData
{
	unsigned char m_pad00[0x118];
	AsciiString m_name; // +0x118
};
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
// UpgradeMux interface at +0x10: slot 0 isAlreadyUpgraded, slot 8
// upgradeRemovalImplementation, slot 9 setUpgradeExecuted, slot 10
// upgradeImplementation.
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
	void rva004CE4A8();
};
class AttributeModifierUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
	const AttributeModifierUpgradeModuleData *getData() const
	{
		return (const AttributeModifierUpgradeModuleData *)m_moduleData;
	}
};
void AttributeModifierUpgrade::upgradeImplementation()
{
	rva004CE4A0();
	getObject()->rva0028EA91(getData()->m_name, -1);
}
void AttributeModifierUpgrade::upgradeRemovalImplementation()
{
	if (isAlreadyUpgraded())
	{
		rva004CE4A8();
		getObject()->rva0028EB42(getData()->m_name);
		setUpgradeExecuted(false);
	}
}
