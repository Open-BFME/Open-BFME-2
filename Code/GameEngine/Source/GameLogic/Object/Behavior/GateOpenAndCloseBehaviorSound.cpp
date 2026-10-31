// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
//
// GateOpenAndCloseBehavior's sound and state helpers (BFME 2), from BFME 1's
// GateOpenAndCloseBehavior_playSound.cpp (retail 0x001FC6B0) and the state
// setter in BfmeThreeHundredSeventySix.cpp (BfmeThingYD::bfmeSetYD).
//
// Target facts: both are non-virtual and take the whole gate as `this` (the
// module data at +8 and the object at +0xC of the primary layout, see
// GateOpenAndCloseBehaviorSlots.cpp). 0x004989F5 is called by update and by
// 0x00498AB2; 0x00498AB2 is called with 0 by 0x004991CB and with 2 by
// 0x0049920B. The state at +0x28 runs 0 opening, 1 open, 2 closing, 3 closed
// (see GateOpenAndCloseBehaviorUpdate.cpp); +0x44 is the sound handle and
// +0x48 the played flag. The module data holds four sound references:
// +0x1C and +0x24 are started by the setter for states 0 and 2 and keep
// their handle, +0x20 and +0x28 are started by playSound for states 0..1 and
// 2..3. Events are the shared 0x88-byte prefix built by the owner-ID
// constructor 0x002DA461; TheAudio's slot 25 adds an event and returns its
// handle, slot 27 removes one.
#include <vector>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/Common/BfmeModuleData.h"
#include "../../../Common/Thing/thing.h"

enum NameKeyType { NK_UNKNOWN = 0 };

enum ObjectID;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum UpdateSleepTime;

class GateOpenAndCloseBehaviorModuleData;
struct Rva00498DF3Arg;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_bfmeReserved; // +0x1C
};

// 4-byte polymorphic primary at +0. Inline ctor installs the first vtable
// ahead of the UpdateModule call; the implicit trivial dtor arms nothing
// (the single EH state completes with the UpdateModule construction, whose
// mirror carries the declared-only dtor).
class GatePrimary
{
public:
	GatePrimary() {}
	virtual void gap0() = 0;
	virtual bool rva00498BAF(Object *object) = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual bool slot6() const = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void rva00498806() = 0;
	virtual unsigned char slot10() const = 0;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GateOpenAndCloseBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual UpdateSleepTime update();
	virtual bool rva00498BAF(Object *object);
	virtual void open();
	virtual void close();
	virtual void rva00498806();
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Player *p) const;
	void changeWantOpenCount(int delta);
	bool rva00498980();
	void rva00498DF3(Rva00498DF3Arg *unit, float flt);
	void rva00498F46(Rva00498DF3Arg *unit, int u1, int u2);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void rva004989F5();
	void setOpenCloseState(int state);
	void rva00498FAA();
	void rva0049924B(bool flag);
	void rva004992D5(bool a, bool b);

	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return (const GateOpenAndCloseBehaviorModuleData *)m_moduleData;
	}
	Object *getObject() const { return m_object; }

	ObjectID m_linkedObjectId; // +0x24
	int m_state; // +0x28
	int m_2C; // +0x2C
	bool m_30; // +0x30
	float m_34; // +0x34
	float m_38; // +0x38
	unsigned int m_stateFrame; // +0x3C
	int m_request; // +0x40
	unsigned int m_soundHandle; // +0x44
	bool m_soundPlayed; // +0x48
};

enum ArmorSetType { ARMORSET_NONE = 0 };

enum ObjectID;

// How the rowed setFlag 0x006BF3C0 names its argument, one of the module
// data's geometry-name AsciiStrings.
class BfmeStrF9
{
public:
	unsigned char m_pad[4];
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

// The object's template as this unit reads it: +0xB0 the gate's cylinder
// radius, +0x108 the flag byte the rowed test 0x00498B8B masks with 4.
class ThingTemplate
{
public:
	char m_pad00[0xB0];
	float m_B0; // +0xB0
	char m_padB4[0x108 - 0xB4];
	unsigned char m_flag108; // +0x108
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Player *getControllingPlayer() const;
	int rva0028B511() const;
	void clearArmorSetFlag(ArmorSetType v);
	void setArmorSetFlag(ArmorSetType v);
	void rva0028AB75(bool v);

protected:
	friend class GateOpenAndCloseBehavior;
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x88 - 0x78];
	AsciiString m_name; // +0x88
	Object *m_next; // +0x8C
	unsigned char m_pad090[0xA8 - 0x90];
public:
	BfmeObjF9 m_objA8; // +0xA8
private:
	unsigned char m_pad0A9[0x438 - 0xA9];
	unsigned char m_438; // +0x438
};

class GateRefHolder : public OpaqueRefElement4
{
public:
	GateRefHolder() { referent = 0; }
	~GateRefHolder() { if (referent) referent->Release_Ref(); }
};

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
	GateOpenAndCloseBehaviorModuleData();
	virtual ~GateOpenAndCloseBehaviorModuleData();

	int m_unused04; // +4 untouched padding
	bool m_openByDefault; // +8
	unsigned char m_pad09[3];
	unsigned int m_resetTime; // +0xC ResetTimeInMilliseconds
	unsigned int m_percentOpen; // +0x10 PercentOpen
	AsciiString m_proxy; // +0x14 Proxy, the partner gate's name
	bool m_repel; // +0x18
	unsigned char m_pad19[3];
	GateRefHolder m_openingSound; // +0x1C
	GateRefHolder m_openSound; // +0x20
	GateRefHolder m_closingSound; // +0x24
	GateRefHolder m_closeSound; // +0x28
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_geometryForOpen; // +0x2C
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_geometryForClosed; // +0x38
	int m_snap44; // +0x44
	int m_snap48; // +0x48
};

typedef unsigned int UnsignedInt;

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AudioManager : public VSlots<25>
{
public:
	virtual UnsignedInt addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
	virtual void slot26() = 0;
	virtual void removeAudioEvent(UnsignedInt handle) = 0;
};
extern AudioManager *TheAudio;

// ?rva004989F5@GateOpenAndCloseBehavior@@AAEXXZ @0x004989F5 189B
void GateOpenAndCloseBehavior::rva004989F5()
{
	TheAudio->removeAudioEvent(m_soundHandle);
	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	Object *object = getObject();
	switch (m_state)
	{
	case 0:
	case 1:
		if (data->m_openSound.referent != 0)
		{
			BfmeAudioEventPrefix136 event(data->m_openSound, object->getID());
			TheAudio->addAudioEvent(&event);
		}
		break;
	case 2:
	case 3:
		if (data->m_closeSound.referent != 0)
		{
			BfmeAudioEventPrefix136 event(data->m_closeSound, object->getID());
			TheAudio->addAudioEvent(&event);
		}
		break;
	}
	m_soundPlayed = true;
}

// ?setOpenCloseState@GateOpenAndCloseBehavior@@AAEXH@Z @0x00498AB2 215B
void GateOpenAndCloseBehavior::setOpenCloseState(int state)
{
	if (m_state == state)
		return;

	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	Object *object = getObject();
	switch (state)
	{
	case 0:
		if (data->m_openingSound.referent != 0)
		{
			BfmeAudioEventPrefix136 event(data->m_openingSound, object->getID());
			m_soundHandle = TheAudio->addAudioEvent(&event);
		}
		m_soundPlayed = false;
		break;
	case 2:
		if (data->m_closingSound.referent != 0)
		{
			BfmeAudioEventPrefix136 event(data->m_closingSound, object->getID());
			m_soundHandle = TheAudio->addAudioEvent(&event);
		}
		m_soundPlayed = false;
		break;
	case 1:
	case 3:
		if (!m_soundPlayed)
			rva004989F5();
		break;
	}

	m_state = state;
}
