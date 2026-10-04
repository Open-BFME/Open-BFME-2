// cl: /O1 /DNDEBUG /MD
//
// DynamicPortalBehaviour::upgradeRemovalImplementation, retail 0x00460C7D
// (61 bytes): slot 8 of the +0x10 UpgradeMux vtable 0x00C427C0 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). Clears the executed flag
// (mux slot 9) first, runs the portal cleanup the class dtor runs too (the
// pinned ?bfmeCallEBC@BfmeOwnerEBC, reached the way DynamicPortalBehaviourDtor.cpp
// reaches it) and the UpgradeModule condition removal 0x004CE4A8; then, for
// an Object with an AI, slot 2 of the rowed Object::rva0028BCF4 result runs
// with 0.
typedef bool Bool;
class ModuleData;
class Rva0028BCF4Result
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void rvaSlot2(int value) = 0;
};
class AIUpdateInterface;
class Object
{
public:
	void *rva0028BCF4() const;
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;	// +0x258
};
class BfmeOwnerEBC
{
public:
	void bfmeCallEBC();
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
class DynamicPortalBehaviour : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
};
void DynamicPortalBehaviour::upgradeRemovalImplementation()
{
	setUpgradeExecuted(false);
	((BfmeOwnerEBC *)this)->bfmeCallEBC();
	rva004CE4A8();
	Object *obj = m_object;
	if (obj->getAI())
	{
		Rva0028BCF4Result *result = (Rva0028BCF4Result *)obj->rva0028BCF4();
		if (result)
			result->rvaSlot2(0);
	}
}
