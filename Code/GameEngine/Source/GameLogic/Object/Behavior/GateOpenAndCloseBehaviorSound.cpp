// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
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
#include "Common/BfmeAudioEventPrefix136.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class ModuleData
{
};

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
	unsigned char m_pad00[0x1C];
	OpaqueRefElement4 m_openingSound; // +0x1C
	OpaqueRefElement4 m_openSound; // +0x20
	OpaqueRefElement4 m_closingSound; // +0x24
	OpaqueRefElement4 m_closeSound; // +0x28
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_pad000[0x74];
	ObjectID m_id; // +0x74
};

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

class GatePrimary
{
public:
	virtual void gap0() = 0;
};

class Module
{
public:
	virtual ~Module();
};

class BehaviorModule : public Module
{
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
struct BehaviorModuleInterface { virtual void f0C() {} };
struct UpdateModuleInterface { virtual void f10() {} };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	UnsignedInt m_14;
	Int m_18;
	Int m_1C;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
private:
	void rva004989F5();
	void setOpenCloseState(Int state);

	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return static_cast<const GateOpenAndCloseBehaviorModuleData *>(m_moduleData);
	}
	Object *getObject() const { return m_object; }

	Int m_linkedObjectId; // +0x24
	Int m_state; // +0x28
	Int m_2C;
	Bool m_30;
	float m_34;
	float m_38;
	UnsignedInt m_stateFrame; // +0x3C
	Int m_request; // +0x40
	UnsignedInt m_soundHandle; // +0x44
	Bool m_soundPlayed; // +0x48
};

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
void GateOpenAndCloseBehavior::setOpenCloseState(Int state)
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
