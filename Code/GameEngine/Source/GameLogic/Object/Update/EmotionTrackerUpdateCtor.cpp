// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0EmotionTrackerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004B21B9, 420 bytes. Donor: BFME 1's EmotionTrackerUpdateCtor.cpp
// (member roles and the entry loop are carried from it). Target evidence:
// the body runs the rowed UpdateModule ctor 0x00253390 and the implicit ctor
// of the one-slot interface at +0x20 (vtable 0x0081C780, slot 0 _purecall),
// then stores the four vtables the rowed dtor 0x004B1322 restores
// (0x0085667C primary, slot 3 the rowed xfer 0x004B1ECB). It builds the
// +0x90 emotion vector (STLport's ICF-folded vector base ctor 0x00211E58;
// element spelling Rva004DD489 as in the rowed xfer, whose elements go
// through the pinned xfer 0x004DD489) and the +0xA4 ObjectID set (25-byte
// set ctor 0x000D3A71; the dtor's opaque Rva002EE9B7 spelling), sets +0xB0
// and +0xC4 to -1 and zeroes the rest; BFME 2 has twelve slots in the three
// parallel arrays and leaves +0xC0 false. As in BFME 1 the distribution
// index is the object's ID modulo the module data's +0x0C count plus one
// (else 1), and every entry of the data's +0x34 vector becomes an emotion
// through the rowed EmotionSystem::createEmotion 0x0042632F, appended with
// the ICF-folded pointer-vector push_back 0x004DFCB0. New in BFME 2: an
// entry without its +0x18D flag is first resolved by name through the
// pinned EmotionSystem::findNugget 0x004264F4 (the name copied by the
// ICF-shared AsciiString-at-+0 getter rowed as getTooltipName 0x002E4336).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

class ModuleData;
class Object;
class Emotion;
class EmotionNugget;
class BfmeEmotionName;
class Rva004DD489;

class Thing
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual Object *asObject();
private:
	unsigned char m_pad04[0x70];
public:
	ObjectID m_id; // +0x74
};

// The ICF-shared copy of an AsciiString at +0, rowed under this name.
class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName() const;
};

class EmotionTrackerUpdateEntry
{
public:
	Bool isCreateDirectly() const { return m_createDirectly; }
	unsigned char m_pad00[0x18D];
	Bool m_createDirectly; // +0x18D
};

class EmotionSystem
{
public:
	Emotion *createEmotion(EmotionTrackerUpdateEntry *entry, Object *object);
	EmotionNugget *findNugget(const BfmeEmotionName &name);
};

extern EmotionSystem *TheEmotionSystem;

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_pad00[0x0C];
	UnsignedInt m_distributionCount; // +0x0C
	unsigned char m_pad10[0x34 - 0x10];
	_STL::vector<EmotionTrackerUpdateEntry *> m_entries; // +0x34
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Thing *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot() = 0;
};

// The ObjectID set at +0xA4; its ctor is the 25-byte STLport set ctor
// 0x000D3A71, its dtor the one the rowed dtor runs.
class Rva002EE9B7
{
public:
	Rva002EE9B7();
	~Rva002EE9B7();
private:
	void *m_header;
	Int m_count;
	Int m_compare;
};

class EmotionTrackerUpdate : public UpdateModule, public EmotionTrackerUpdateSecondaryBase
{
public:
	EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~EmotionTrackerUpdate();
	virtual void slot();
private:
	enum { SLOT_COUNT = 12 };
	Bool m_active[SLOT_COUNT]; // +0x24
	UnsignedInt m_startFrame[SLOT_COUNT]; // +0x30
	UnsignedInt m_endFrame[SLOT_COUNT]; // +0x60
	_STL::vector<Rva004DD489 *> m_emotions; // +0x90
	Rva004DD489 *m_current; // +0x9C
	UnsignedInt m_distributionIndex; // +0xA0
	Rva002EE9B7 m_emotionTargets; // +0xA4
	Int m_B0; // +0xB0
	Int m_B4; // +0xB4
	ObjectID m_B8; // +0xB8
	UnsignedInt m_BC; // +0xBC
	Bool m_enabled; // +0xC0
	Int m_C4; // +0xC4
};

EmotionTrackerUpdate::EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_current(0),
	  m_B0(-1),
	  m_C4(-1)
{
	const EmotionTrackerUpdateModuleData *data = (const EmotionTrackerUpdateModuleData *)m_moduleData;

	m_B4 = 0;
	m_B8 = 0;
	m_BC = 0;
	m_enabled = false;

	for (Int i = 0; i < SLOT_COUNT; ++i)
	{
		m_active[i] = false;
		m_startFrame[i] = 0;
		m_endFrame[i] = 0;
	}

	if (data->m_distributionCount > 0)
		m_distributionIndex = m_object->m_id % data->m_distributionCount + 1;
	else
		m_distributionIndex = 1;

	for (UnsignedInt i = 0; i < data->m_entries.size(); ++i)
	{
		EmotionTrackerUpdateEntry *entry = data->m_entries[i];
		if (entry != 0)
		{
			Rva004DD489 *emotion = 0;
			if (entry->isCreateDirectly())
			{
				emotion = (Rva004DD489 *)TheEmotionSystem->createEmotion(data->m_entries[i], thing != 0 ? thing->asObject() : 0);
			}
			else
			{
				EmotionNugget *nugget = TheEmotionSystem->findNugget((const BfmeEmotionName &)((const MultiplayerColorDefinition *)entry)->getTooltipName());
				if (nugget != 0)
					emotion = (Rva004DD489 *)TheEmotionSystem->createEmotion((EmotionTrackerUpdateEntry *)nugget, thing != 0 ? thing->asObject() : 0);
			}
			if (emotion != 0)
				m_emotions.push_back(emotion);
		}
	}
}
