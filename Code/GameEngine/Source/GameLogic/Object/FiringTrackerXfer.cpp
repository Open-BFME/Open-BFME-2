// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// FiringTracker (Zero Hour GameLogic/Object/FiringTracker.cpp) in BFME 2:
//   0x004DEBC1 199B xfer
//   0x004DEC88 179B coolDown(Bool forceReset)
//   0x004DED3B 151B update (UpdateModuleInterface entry, this at +0x10):
//     banked in reverse/attempts, exact apart from the register choice for
//     the object/last-shot-position operands of the moved test
//   0x004DEDD2 249B speedUp
//   0x004DEECB 662B shotFired(weapon, victimID, victimPosition, forceReset)
//   0x004DEAB0  27B calcTimeToSleep
// Target evidence: update is the only FiringTracker body reached through
// the UpdateModuleInterface (+0x10) table; it calls 0x004DEC88 with 1 when
// the object has moved off the last shot position and with 0 when the
// cooldown frame passes, and tail-calls 0x004DEAB0. Object::fireCurrentWeapon
// calls 0x004DEECB on the tracker as shotFired; it
// calls 0x004DEC88 and 0x004DEDD2 by the continuous-fire bonus bits (2 mean,
// 3 fast, Object +0x380) and ends with setWakeFrame(calcTimeToSleep()).
// 0x004DEAB0 tests the three wake frames (+0x3C/+0x40/+0x54) and returns
// UPDATE_SLEEP_FOREVER or UPDATE_SLEEP_NONE.
// Donor-carried: the names, the Zero Hour bodies and BFME 1's extensions
// (FiringTrackerCooldown, FiringTrackerBFMESpeedUp, FiringTrackerUpdate,
// FiringTrackerShotFired001B3510 at Open-BFME-1 6d943426). BFME 2 renumbers
// the continuous-fire model conditions (slow 115, mean 116, fast 117, in a
// 19-word flag set), reads the logic frame rate from a global, and builds the
// fire sound from the template's event reference. The flag set is an STLport
// bitset as in BFME 1's donor: its two locals take retail's stack slots only
// with the bitset base, and its sets are inlined unchecked.
//
// ?xfer@FiringTracker@@MAEXPAVXfer@@@Z retail 0x004DEBC1 199 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00861530 (class of rowed dtor
// ??1FiringTracker@@UAE@XZ in FiringTrackerDtor.cpp, same primary as rowed
// deleting dtor 0x004DEBA5 and pool key 0x004DEACB with FiringTracker string).
// Base UpdateModule xfer via rowed 0x0044DF9F then IsLightCRC early-out via
// Xfer slot 0x10 then Version(1,2) via Xfer slot 0x28 then int at +0x20 via
// Xfer slot 0x7C plus ObjectIDs at +0x24/+0x38 via rowed XferObjectID
// 0x003060B2 plus uints at +0x3C/+0x40/+0x44 via Xfer slot 0x78 plus Coord at
// +0x48 via Xfer slot 0x60 plus bool at +0x34 via Xfer slot 0x90 plus Coord
// at +0x28 via Xfer slot 0x60 plus version-gated uint at +0x54 via Xfer slot
// 0x78 plus TheAudio (data 0x00DFE6E8) xferAudioHandle at AudioManager slot
// 0x160 for +0x58. Layout is donor BFME1 FiringTrackerBFMEXfer (UpdateModule
// base 0x20 plus consecutiveShots plus victimID plus victimPosition plus
// victimIsPosition plus auxID plus three frames plus lastShotPosition plus
// stopLoopingSound plus audioHandle). Recipe follows FlammableUpdateXfer
// (Version plus audio-handle shape) plus GateOpenAndCloseBehaviorXfer.

#include <bitset>
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
#include "Common/BfmeAudioEventPrefix136.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" void *__cdecl memset(void *dest, int value, unsigned int count);

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *event) = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual Bool isCurrentlyPlaying(AudioHandle handle) = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	virtual void _pad78() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0;
};

extern AudioManager *TheAudio;

#include "../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#define UPDATE_SLEEP(x) ((UpdateSleepTime)(x))

enum
{
	AHSV_NoSound = 1
};

// Logic frame rate (5), read where Zero Hour uses LOGICFRAMES_PER_SECOND.
extern int BfmeLogicFramesPerSecond;

// Coord3D: canonical value and base compatibility headers.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

inline void Coord3D::zero() { x = 0.0f; y = 0.0f; z = 0.0f; }

// Coord3D::equals (rowed 0x00003702 here), out of line but visible:
// update's operand order (the Object loaded into ECX before the frame
// read, add ecx,0x38 after pushing &m_lastShotPosition) needs cl to see it.
inline __declspec(noinline) bool Coord3D::equals(const Coord3DBase &that) const
{
	return x == that.x && y == that.y && z == that.z;
}


enum ModelConditionFlagType
{
	MODELCONDITION_CONTINUOUS_FIRE_SLOW = 115,
	MODELCONDITION_CONTINUOUS_FIRE_MEAN = 116,
	MODELCONDITION_CONTINUOUS_FIRE_FAST = 117
};

class ModelConditionFlags
{
public:
	__declspec(dllimport) __forceinline ModelConditionFlags() {}
	void set(ModelConditionFlagType bit) { m_bits._Unchecked_set(bit); }

private:
	_STL::bitset<608> m_bits;
};

enum WeaponBonusConditionType
{
	WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN = 2,
	WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST = 3
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_0x26 = 0x26
};

class Drawable;

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_position; }
	Drawable *getDrawable() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Object *rva002931F5(Bool lookUpProducer);
	void reloadAllAmmo(Bool forceReload);
	// clearAndSetModelConditionFlags(clr, set)
	void rva0028CFB2(const int *clr, const int *set);
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clr, const ModelConditionFlags &set)
	{
		rva0028CFB2((const int *)&clr, (const int *)&set);
	}

	__declspec(dllimport) __forceinline Bool testWeaponBonusCondition(WeaponBonusConditionType wst) const { return ((m_weaponBonusCondition >> wst) & 1) != 0; }
	void setWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition |= (1 << wst); }
	void clearWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition &= ~(1 << wst); }

private:
	unsigned char m_unmodelled00[0x38];
	Coord3D m_position;																												///< 0x38
	unsigned char m_unmodelled44[0x74 - 0x44];
	ObjectID m_id;																														///< 0x74
	unsigned char m_unmodelled78[0x380 - 0x78];
	UnsignedInt m_weaponBonusCondition;																				///< 0x380
};


extern GameLogic *TheGameLogic;

// Retail inlines the dllimport getters everywhere and has no out-of-line
// copy; other units' private views emit them with other layouts
// (FiringTracker.cpp's ZH port is first in link order), so dllimport keeps
// this unit's copies inline-only.
class WeaponTemplate
{
public:
	__declspec(dllimport) Int getContinuousFireOneShotsNeeded() const { return m_continuousFireOneShotsNeeded; }
	__declspec(dllimport) Int getContinuousFireTwoShotsNeeded() const { return m_continuousFireTwoShotsNeeded; }
	__declspec(dllimport) UnsignedInt getContinuousFireCoastFrames() const { return m_continuousFireCoastFrames; }
	__declspec(dllimport) UnsignedInt getAutoReloadWhenIdleFrames() const { return m_autoReloadWhenIdleFrames; }
	__declspec(dllimport) UnsignedInt getFireSoundLoopTime() const { return m_fireSoundLoopTime; }
	const OpaqueRefElement4 &getFireSound() const { return m_fireSound; }

private:
	unsigned char m_unmodelled00[0xC8];
	OpaqueRefElement4 m_fireSound;																						///< 0xC8
	UnsignedInt m_fireSoundLoopTime;																					///< 0xCC
	unsigned char m_unmodelledD0[0xF8 - 0xD0];
	Int m_continuousFireOneShotsNeeded;																				///< 0xF8
	Int m_continuousFireTwoShotsNeeded;																				///< 0xFC
	UnsignedInt m_continuousFireCoastFrames;																	///< 0x100
	UnsignedInt m_autoReloadWhenIdleFrames;																		///< 0x104
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	UnsignedInt getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }

	__declspec(dllimport) Int getContinuousFireOneShotsNeeded() const { return m_template->getContinuousFireOneShotsNeeded(); }
	__declspec(dllimport) Int getContinuousFireTwoShotsNeeded() const { return m_template->getContinuousFireTwoShotsNeeded(); }
	__declspec(dllimport) UnsignedInt getContinuousFireCoastFrames() const { return m_template->getContinuousFireCoastFrames(); }
	__declspec(dllimport) UnsignedInt getAutoReloadWhenIdleFrames() const { return m_template->getAutoReloadWhenIdleFrames(); }
	__declspec(dllimport) UnsignedInt getFireSoundLoopTime() const { return m_template->getFireSoundLoopTime(); }
	const OpaqueRefElement4 &getFireSound() const { return m_template->getFireSound(); }

private:
	void *m_vtbl;
	const WeaponTemplate *m_template;																					///< 0x04
	unsigned char m_unmodelled08[0x18 - 0x08];
	UnsignedInt m_whenWeCanFireAgain;																					///< 0x18
};

// AudioEventRTS::setObjectID (honest address name).
class Rva002D9531
{
public:
	void rva002D9531(int value);
};

// pickAndPlayUnitVoiceResponse's parameter type. The list a caller hands it
// is a plain list<Drawable *>: retail destroys it with the base destructor
// 0x00239AF4 on the normal path and with the list<Drawable *> destructor
// thunk 0x00239BAB in the unwind funclet.
class DrawableList : public _STL::list<Drawable *>
{
};

class PickAndPlayInfo;

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DC = 0x7DC
	};
};

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

#include "../../../Include/Common/ObjectModule.h"

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class FiringTracker : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void shotFired(const Weapon *weaponFired, ObjectID victimID, const Coord3D *victimPosition, Bool forceReset);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void coolDown(Bool forceReset);
	void speedUp();
	UpdateSleepTime calcTimeToSleep();

	int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3D m_victimPosition;
	bool m_victimIsPosition;
	unsigned char m_pad35[3];
	ObjectID m_auxiliaryObjectID;
	unsigned int m_frameToStartCooldown;
	unsigned int m_frameToForceReload;
	unsigned int m_lastShotFrame;
	Coord3D m_lastShotPosition;
	unsigned int m_frameToStopLoopingSound;
	AudioHandle m_audioHandle;
};

void FiringTracker::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_consecutiveShots;
	XferObjectID(xfer, &m_victimID);
	XferObjectID(xfer, &m_auxiliaryObjectID);
	*xfer == m_frameToStartCooldown;
	*xfer == m_frameToForceReload;
	*xfer == m_lastShotFrame;
	*xfer == asBase(m_lastShotPosition);
	*xfer == m_victimIsPosition;
	*xfer == asBase(m_victimPosition);
	if (version.m_minimum >= 2) {
		*xfer == m_frameToStopLoopingSound;
	}
	if (TheAudio != 0) {
		TheAudio->xferAudioHandle(xfer, &m_audioHandle);
	}
}

//-------------------------------------------------------------------------------------------------
void FiringTracker::shotFired(const Weapon *weaponFired, ObjectID victimID, const Coord3D *victimPosition, Bool forceReset)
{
	Object *victim = TheGameLogic->findObjectByID(victimID);
	if (victim && victim->testStatus(OBJECT_STATUS_0x26))
	{
		m_auxiliaryObjectID = victim->rva002931F5(false) ? victim->rva002931F5(false)->getID() : INVALID_OBJECT_ID;
	}

	UnsignedInt now = TheGameLogic->getFrame();
	m_lastShotFrame = now;
	m_lastShotPosition = *getObject()->getPosition();

	if (forceReset)
	{
		m_consecutiveShots = 1;
		coolDown(true);
		return;
	}

	if (victimID != INVALID_OBJECT_ID || victimPosition == NULL)
	{
		if (m_victimIsPosition)
		{
			m_consecutiveShots = 1;
			m_victimPosition.zero();
		}
		else if (victimID == m_victimID)
		{
			++m_consecutiveShots;
		}
		else if (now < m_frameToStartCooldown)
		{
			++m_consecutiveShots;
		}
		else
		{
			m_consecutiveShots = 1;
		}
		m_victimID = victimID;
		m_victimIsPosition = false;
	}
	else
	{
		if (!m_victimIsPosition)
		{
			m_consecutiveShots = 1;
			m_victimPosition = *victimPosition;
			m_victimID = INVALID_OBJECT_ID;
		}
		else if (m_victimPosition.equals(asBase(*victimPosition)))
		{
			++m_consecutiveShots;
		}
		else if (now < m_frameToStartCooldown)
		{
			++m_consecutiveShots;
			m_victimPosition = *victimPosition;
		}
		else
		{
			m_consecutiveShots = 1;
			m_victimPosition = *victimPosition;
		}
		m_victimIsPosition = true;
	}

	UnsignedInt autoReloadDelay = weaponFired->getAutoReloadWhenIdleFrames();
	if (autoReloadDelay > 0)
		m_frameToForceReload = now + autoReloadDelay;

	UnsignedInt coast = weaponFired->getContinuousFireCoastFrames();
	if (coast)
		m_frameToStartCooldown = weaponFired->getPossibleNextShotFrame() + coast;
	else
		m_frameToStartCooldown = 0;

	Int shotsNeededOne = weaponFired->getContinuousFireOneShotsNeeded();
	Int shotsNeededTwo = weaponFired->getContinuousFireTwoShotsNeeded();

	if (getObject()->testWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN))
	{
		if (m_consecutiveShots < shotsNeededOne)
			coolDown(false);
		else if (m_consecutiveShots > shotsNeededTwo)
			speedUp();
	}
	else if (getObject()->testWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST))
	{
		if (m_consecutiveShots < shotsNeededTwo)
			coolDown(false);
	}
	else
	{
		if (m_consecutiveShots > shotsNeededOne)
			speedUp();
	}

	UnsignedInt fireSoundLoopTime = weaponFired->getFireSoundLoopTime();
	if (fireSoundLoopTime != 0)
	{
		if (m_frameToStopLoopingSound == 0 || !TheAudio->isCurrentlyPlaying(m_audioHandle))
		{
			BfmeAudioEventPrefix136 audio(weaponFired->getFireSound(), 0);
			reinterpret_cast<Rva002D9531 *>(&audio)->rva002D9531(getObject()->getID());
			m_audioHandle = TheAudio->addAudioEvent(&audio);
		}
		m_frameToStopLoopingSound = now + fireSoundLoopTime;
	}
	else
	{
		BfmeAudioEventPrefix136 fireAndForgetSound(weaponFired->getFireSound(), 0);
		reinterpret_cast<Rva002D9531 *>(&fireAndForgetSound)->rva002D9531(getObject()->getID());
		TheAudio->addAudioEvent(&fireAndForgetSound);
		m_frameToStopLoopingSound = 0;
	}

	setWakeFrame(getObject(), calcTimeToSleep());
}

//-------------------------------------------------------------------------------------------------
UpdateSleepTime FiringTracker::update()
{
	UnsignedInt now = TheGameLogic->getFrame();

	if (!getObject()->getPosition()->equals(asBase(m_lastShotPosition)))
		coolDown(true);

	if (m_frameToForceReload != 0 && now >= m_frameToForceReload)
	{
		getObject()->reloadAllAmmo(false);
		m_frameToForceReload = 0;
	}

	if (m_frameToStopLoopingSound != 0 && now >= m_frameToStopLoopingSound)
	{
		TheAudio->removeAudioEvent(m_audioHandle);
		m_frameToStopLoopingSound = 0;
		m_audioHandle = AHSV_NoSound;
	}

	if (m_frameToStartCooldown != 0 && now > m_frameToStartCooldown)
	{
		m_frameToStartCooldown = now + BfmeLogicFramesPerSecond;
		coolDown(false);
		return UPDATE_SLEEP(BfmeLogicFramesPerSecond);
	}

	return calcTimeToSleep();
}

//-------------------------------------------------------------------------------------------------
UpdateSleepTime FiringTracker::calcTimeToSleep()
{
	if (m_frameToStopLoopingSound == 0 && m_frameToStartCooldown == 0 && m_frameToForceReload == 0)
		return UPDATE_SLEEP_FOREVER;
	return UPDATE_SLEEP_NONE;
}

//-------------------------------------------------------------------------------------------------
void FiringTracker::speedUp()
{
	ModelConditionFlags clr, set;
	Object *self = getObject();

	if (self->testWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST))
	{
		// Already at full speed.
	}
	else if (self->testWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN))
	{
		_STL::list<Drawable *> list;
		list.push_back(self->getDrawable());
		pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_BFME2_0x7DC, NULL);

		self->setWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST);
		set.set(MODELCONDITION_CONTINUOUS_FIRE_FAST);

		self->clearWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_MEAN);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_SLOW);
	}
	else
	{
		self->setWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN);
		set.set(MODELCONDITION_CONTINUOUS_FIRE_MEAN);

		self->clearWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_FAST);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_SLOW);
	}

	self->clearAndSetModelConditionFlags(clr, set);
}

//-------------------------------------------------------------------------------------------------
void FiringTracker::coolDown(Bool forceReset)
{
	ModelConditionFlags clr, set;

	if (!forceReset
		&& (getObject()->testWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST)
			|| getObject()->testWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN)))
	{
		// Straight to zero from wherever it is
		set.set(MODELCONDITION_CONTINUOUS_FIRE_SLOW);
		getObject()->clearWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST);
		getObject()->clearWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_FAST);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_MEAN);
	}
	else
	{
		getObject()->clearWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_FAST);
		getObject()->clearWeaponBonusCondition(WEAPONBONUSCONDITION_CONTINUOUS_FIRE_MEAN);
		m_frameToStartCooldown = 0;
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_FAST);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_MEAN);
		clr.set(MODELCONDITION_CONTINUOUS_FIRE_SLOW);
		m_lastShotPosition.zero();
	}

	getObject()->clearAndSetModelConditionFlags(clr, set);
	m_consecutiveShots = 0;
	m_victimID = INVALID_OBJECT_ID;
}
