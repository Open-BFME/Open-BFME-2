// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0CastleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x003983D4,
// 329 bytes. Target evidence: the body runs the rowed FoundationAIUpdate
// ctor 0x004551B3 and the implicit ctor of the all-_purecall interface at
// +0x30 (vtable 0x0084EF80), then stores the five vtables the rowed dtor
// 0x0039857D restores (0x0081A780 primary, slot 0 the rowed
// ??_GCastleBehavior 0x00399354). Its members follow the dtor's teardown:
// five vectors at +0x50..+0x80 (the ICF-folded empty vector base ctor
// 0x00211E58; the dtor only frees them), the set at +0x8C (set ctor
// 0x000D3A71, the dtor's Rva002EE9B7 spelling), the AsciiString at +0x98
// and the map at +0xA0 (map ctor 0x0033C432, the dtor's Rva00395CEB). The
// +0x80 vector holds the pointers the rowed clear 0x00397E50 unlinks and
// deletes (the rowed search 0x00396023 indexes it). The first three vectors
// are cleared through the ICF-folded 4-byte erase 0x00532803, spelled
// vector<ObjectID> because that spelling's base ctor and erase are the
// folded bodies (the element type itself is not established). The body then
// resets the set (rowed 0x002EE9B7) and the +0x80 vector (0x00397E50), marks
// +0x3C when the module data's +0x10 name is set and wakes next frame.
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
private:
	Object *m_object; // +0x08
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
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class FoundationAIUpdateInterface
{
public:
	virtual void slot0();
};

class FoundationAIUpdate : public UpdateModule, public FoundationAIUpdateInterface
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FoundationAIUpdate();
private:
	UnsignedInt m_24; // +0x24
	UnsignedInt m_28; // +0x28
	Bool m_2C; // +0x2C
};

class CastleBehaviorInterface
{
public:
	virtual void slot0() = 0;
};

class CastleBehaviorModuleData
{
public:
	unsigned char m_pad00[0x10];
	StringBase<char> m_10; // +0x10 (an AsciiString)
};

// The +0x8C set (set ctor 0x000D3A71; rowed reset 0x002EE9B7).
class Rva002EE9B7
{
public:
	Rva002EE9B7();
	~Rva002EE9B7();
	void rva002EE9B7();
private:
	void *m_header;
	Int m_count;
	Int m_compare;
};

// The +0xA0 map (map ctor 0x0033C432).
class Rva00395CEB
{
public:
	Rva00395CEB();
	~Rva00395CEB();
private:
	void *m_header;
	Int m_count;
	Int m_compare;
};

// The rowed clear of the +0x80 vector.
class Rva00397E50
{
public:
	void rva00397E50();
};

struct Rva002E36D5Node;
struct Rva003983D4Element74;

class CastleBehavior : public FoundationAIUpdate, public CastleBehaviorInterface
{
public:
	CastleBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~CastleBehavior();
	virtual void slot0();
private:
	Int m_34; // +0x34
	Int m_38; // +0x38
	Bool m_3C; // +0x3C
	Bool m_3D; // +0x3D
	Real m_40; // +0x40
	Bool m_44; // +0x44
	Int m_48; // +0x48
	Real m_4C; // +0x4C
	_STL::vector<ObjectID> m_50; // +0x50
	_STL::vector<ObjectID> m_5C; // +0x5C
	_STL::vector<ObjectID> m_68; // +0x68
	_STL::vector<Rva003983D4Element74 *> m_74; // +0x74
	_STL::vector<Rva002E36D5Node *> m_80; // +0x80
	Rva002EE9B7 m_8C; // +0x8C
	AsciiString m_98; // +0x98
	Int m_9C; // +0x9C
	Rva00395CEB m_A0; // +0xA0
};

CastleBehavior::CastleBehavior(Thing *thing, const ModuleData *moduleData)
	: FoundationAIUpdate(thing, moduleData),
	  m_34(0),
	  m_38(0),
	  m_3C(false),
	  m_3D(true),
	  m_40(0.0f),
	  m_44(false),
	  m_48(-1),
	  m_4C(0.0f),
	  m_9C(0)
{
	m_50.clear();
	m_5C.clear();
	m_68.clear();
	m_8C.rva002EE9B7();
	((Rva00397E50 *)this)->rva00397E50();

	if (!((const CastleBehaviorModuleData *)m_moduleData)->m_10.isEmpty())
		m_3C = true;

	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
