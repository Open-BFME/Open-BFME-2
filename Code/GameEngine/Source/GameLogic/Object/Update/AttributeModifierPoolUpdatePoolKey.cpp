// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?getModuleNameKey@AttributeModifierPoolUpdate@@UBE?AW4NameKeyType@@XZ @0x403A61
// (69B): cached pool-name key for AttributeModifierPoolUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AttributeModifierPoolUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. Globals are
// TU-local externs (DIR32 slots patch from retail, no pins; nameToKey resolves
// via its matched row).

#include <vector>
#include "ascii_string.h"
class Thing;
class ModuleData;
class Object;
class Xfer;
enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum NameKeyType { NAMEKEY_INVALID=-1 };

class Rva00297360Element
{
public:
	Rva00297360Element(const Rva00297360Element &that);
	~Rva00297360Element();
	int index;
	AsciiString name;
	unsigned expiration;
	unsigned upgrade;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BehaviorModuleBase
{
	virtual void unused();
public:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual void update();
	void xfer(Xfer *xfer);
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

// One entry of the +0x30 table: retail builds the table through the non-EH vector constructor
// iterator 0x00001423 and the folded null constructor 0x00326BE6, and never destroys it.
struct AttributeModifierCategoryFrame
{
	AttributeModifierCategoryFrame() : frame(0) {}
	unsigned int frame;
};

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
	AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AttributeModifierPoolUpdate();
	virtual NameKeyType getModuleNameKey() const;
	int rva004031C9(int index);
	unsigned char isCategoryDisabled(int index);
	bool rva00403170(unsigned frame, const void *entry, int includeCategories);
	bool rva00403382(int attribute, float *bonus, int name);
	void rva00403415(int *mask, int value);
	bool rva00403448(int attribute, float *multiplier, int name, int includeCategories);
	void rva00403744(const AsciiString &name);
	bool addModifierToPool(const AsciiString &name, int duration);
protected:
	virtual void xfer(Xfer *xfer);
private:
	_STL::vector<Rva00297360Element> m_modifiers;
	unsigned int m_maxFrame;
	AttributeModifierCategoryFrame m_categoryFrames[15];
	unsigned int m_poolCounts[15];
};

// ?getModuleNameKey@AttributeModifierPoolUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AttributeModifierPoolUpdate::getModuleNameKey() const
{
	static NameKeyType TheAttributeModifierPoolUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return TheAttributeModifierPoolUpdatePoolKey;
}
