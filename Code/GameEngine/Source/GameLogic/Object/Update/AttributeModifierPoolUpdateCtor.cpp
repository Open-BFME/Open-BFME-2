// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
//
// ??0AttributeModifierPoolUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00403BEF, 157 bytes. Behavior-side ctor over the rowed
// UpdateModule base 0x253390. Factory 0x24C6B1 news 0xA8 and calls here;
// vtable 0xC3856C slot0 is the deleting dtor at 0x403C8C and slots carry
// the pool-name getters at 0x403A5B/0x403A61, proving the class.
//
// Layout: UpdateModule base (0x20) + modifier vector at +0x20 (12B,
// 16B elements through the folded Vector_base at 0x211E58, cleared
// through the rowed EraseRange at 0x2983DA) + max frame at +0x2C
// (UPDATE_SLEEP_FOREVER) + 15 pool names at +0x30 (AsciiString array
// built through vector_constructor_iterator 0x1423) + 15 tallies at
// +0x6C. Total 0xA8, matching the factory news.
#include <vector>

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

struct BfmeE16
{
	float x, y, z, w;
};

class AsciiString
{
public:
	AsciiString();
	void clear() { m_data = 0; }
private:
	void *m_data;
};

class Rva00297360Element
{
public:
	~Rva00297360Element();
private:
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
};

namespace _STL {
// The modifier vector is 16B elements. Its base builds through the
// ICF-folded ctor at 0x211E58 (same 29B as the matched BfmeE16 row;
// twin-pinned Rva spelling, BannerCarrier precedent) and its dtor is
// the rowed Rva vector dtor at 0x403960. Declared without bodies so
// the calls stay outlined with EH.
template<> _Vector_base<Rva00297360Element, allocator<Rva00297360Element> >::_Vector_base(const allocator<Rva00297360Element> &);
}

class Rva002983DAVector
{
public:
	Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);
	Rva00297360Element *m_start;
	Rva00297360Element *m_finish;
	Rva00297360Element *m_end;
};

class BehaviorModuleBase
{
	virtual void unused();
	int m_a;
	int m_b;
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
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
	AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AttributeModifierPoolUpdate();
private:
	_STL::vector<Rva00297360Element> m_modifiers;
	unsigned int m_maxFrame;
	AsciiString m_poolNames[15];
	unsigned int m_poolCounts[15];
};

// ??0AttributeModifierPoolUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00403BEF
AttributeModifierPoolUpdate::AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	Rva002983DAVector *modifierView = reinterpret_cast<Rva002983DAVector *>(&m_modifiers);
	modifierView->EraseRange(modifierView->m_start, modifierView->m_finish);
	m_maxFrame = UPDATE_SLEEP_FOREVER;
	for (int i = 0; i < 15; ++i) {
		m_poolNames[i].clear();
		m_poolCounts[i] = 0;
	}
	setWakeFrame(*(Object **)((char *)this + 8), UPDATE_SLEEP_FOREVER);
}

// ??1AttributeModifierPoolUpdate@@UAE@XZ @0x00403A12
AttributeModifierPoolUpdate::~AttributeModifierPoolUpdate()
{
}
