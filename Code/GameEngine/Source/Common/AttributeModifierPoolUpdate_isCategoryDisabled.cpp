// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// AttributeModifierPoolUpdate::isCategoryDisabled (WorldBuilder name, AttributeModifier.cpp line 806: the +0x30 per-category table test).
// was ?rva004031DD@Rva004031DD@@QAEEH@Z retail 0x004031DD 22B
// Unsigned frame-vs-slot check: return TheGameLogic+0x40 < this[index] at +0x30.
// Evidence: mov eax [TheGameLogic] mov eax [eax+0x40] mov edx esp+4 cmp setb ret 4;
// neighbours AttributeModifierPoolUpdateRva / Rva004031F3 share flags; owner
// unproven so honest Rva name; caller 0x0050876D in FUN_00908684.
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

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

__declspec(noinline) inline unsigned char AttributeModifierPoolUpdate::isCategoryDisabled(int index)
{
	return TheGameLogic->getFrame() < m_categoryFrames[index].frame;
}
// Select-any: addModifierToPool (0x00403E72) expands the same test inline; the anchor keeps this copy emitted.
// ?bfmeAnchorIsCategoryDisabled absent-from-retail
unsigned char bfmeAnchorIsCategoryDisabled(AttributeModifierPoolUpdate *attributeModifierPoolUpdate, int index) { return attributeModifierPoolUpdate->isCategoryDisabled(index); }
