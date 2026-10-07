// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc
//
// ObjectDefectionHelper (Zero Hour GameLogic/Object/Helper/ObjectDefectionHelper.cpp).
//   0x004DF547 478B update (UpdateModuleInterface entry, this at +0x10)
//
// Target evidence: the helper layout is the rowed 0x30-byte class of
// ObjectDefectionHelperCtor.cpp, whose detection window start/end, flash phase
// and FX flag (+0x20/+0x24/+0x28/+0x2C) the rowed startDefectionTimer
// 0x004DF725 seeds. update reads the owner's drawable through the rowed
// Thing::getDrawable 0x005508E2 and its undetected-defector bit (Object +0x438
// bit 1, cleared through the rowed setter 0x0028AC34). When the window ends it
// flashes the drawable (0x00278C7C) with white and plays the misc-audio event at
// +0x24; a dead owner with an AI (bit 0 of the same byte, AI at +0x258) or one
// with status 13 drops the bit. Otherwise the flash phase advances by
// 0.5 * (1 - timeLeft / (10 * frame rate)) and each falling edge flashes again
// with the misc-audio event at +0x20. The events go through the rowed audio
// event ctor 0x002D97D6, setObjectID 0x002D9531 (Object +0x74), TheAudio's
// addAudioEvent (slot 25) and the rowed destructor 0x002D9A43.
// Donor-carried: the names and the ZH body.

#include "Common/BfmeAudioEventPrefix136.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_FIRING_WEAPON = 13
};

// Logic frame rate, read where Zero Hour uses LOGICFRAMES_PER_SECOND.
extern int g_Va00DBA4E4;
#define DEFECTION_DETECTION_TIME_MAX (10 * g_Va00DBA4E4)

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class Drawable
{
public:
	// Drawable::flashAsSelected; the rowed callee takes the colour as a word.
	void rva00278C7C(int color);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class AIUpdateInterface;

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void rva0028AC34(Bool undetectedDefector);

	Int getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool getIsUndetectedDefector() const { return (m_privateStatus & 2) != 0; }
	void friend_setUndetectedDefector(Bool status) { rva0028AC34(status); }

private:
	unsigned char m_unmodelled00[0x74];
	Int m_id;																																	///< 0x74
	unsigned char m_unmodelled78[0x258 - 0x78];
	AIUpdateInterface *m_ai;																									///< 0x258
	unsigned char m_unmodelled25C[0x438 - 0x25C];
	unsigned char m_privateStatus;																						///< 0x438
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unmodelled00[0x40];
	UnsignedInt m_frame;																											///< 0x40
};

extern GameLogic *TheGameLogic;

struct MiscAudio
{
	unsigned char m_unmodelled00[0x20];
	OpaqueRefElement4 m_defectorTimerTickSound;																///< 0x20
	OpaqueRefElement4 m_defectorTimerDingSound;																///< 0x24
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0) AUDIO_SLOT(1) AUDIO_SLOT(2) AUDIO_SLOT(3) AUDIO_SLOT(4)
	AUDIO_SLOT(5) AUDIO_SLOT(6) AUDIO_SLOT(7) AUDIO_SLOT(8) AUDIO_SLOT(9)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24)
	virtual UnsignedInt addAudioEvent(const BfmeAudioEventPrefix136 *event);
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34)
	AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44)
	AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54)
	AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64)
	AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74)
	AUDIO_SLOT(75) AUDIO_SLOT(76) AUDIO_SLOT(77)
	virtual const MiscAudio *getMiscAudio();
#undef AUDIO_SLOT
};

extern AudioManager *TheAudio;

// AudioEventRTS::setObjectID (honest address name).
class Rva002D9531
{
public:
	void rva002D9531(int value);
};

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

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	Object *getObject() const { return m_object; }

private:
	const void *m_moduleData;
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
};

class ObjectDefectionHelper : public ObjectHelper
{
public:
	virtual UpdateSleepTime update();

private:
	UnsignedInt m_defectionDetectionStart;																		///< 0x20
	UnsignedInt m_defectionDetectionEnd;																			///< 0x24
	Real m_defectionDetectionFlashPhase;																			///< 0x28
	Bool m_doDefectorFX;																											///< 0x2C
};

//-------------------------------------------------------------------------------------------------
UpdateSleepTime ObjectDefectionHelper::update()
{
	Object *obj = getObject();
	Drawable *draw = obj->getDrawable();

	// if we are here, we should be an undetected defector, but
	// just in case someone has changed us behind our backs...
	if (!obj->getIsUndetectedDefector())
		return UPDATE_SLEEP_FOREVER;

	UnsignedInt now = TheGameLogic->getFrame();
	UnsignedInt detectionEnd = m_defectionDetectionEnd;
	if (now >= detectionEnd)
	{
		obj->friend_setUndetectedDefector(false);

		// timer has reached zero, so we flash white once
		if (draw && m_doDefectorFX)
		{
			RGBColor white = { 1, 1, 1 };
			draw->rva00278C7C((int)&white);

			BfmeAudioEventPrefix136 defectorVulnerableSound(TheAudio->getMiscAudio()->m_defectorTimerDingSound, 0);
			reinterpret_cast<Rva002D9531 *>(&defectorVulnerableSound)->rva002D9531(obj->getID());
			TheAudio->addAudioEvent(&defectorVulnerableSound);
		}
		return UPDATE_SLEEP_FOREVER;
	}

	// dead or attacking... our cover is blown.
	if ((obj->getAI() != 0 && obj->isEffectivelyDead()) || obj->testStatus(OBJECT_STATUS_IS_FIRING_WEAPON))
	{
		obj->friend_setUndetectedDefector(false);
		return UPDATE_SLEEP_FOREVER;
	}

	if (draw && m_doDefectorFX) // skip fx if merely 'invulnerable'
	{
		Bool lastPhase = (((Int)m_defectionDetectionFlashPhase) & 1); // were we in a flashy phase last frame?
		UnsignedInt timeLeft = detectionEnd - now;
		m_defectionDetectionFlashPhase += 0.5f * (1.0f - ((Real)timeLeft / DEFECTION_DETECTION_TIME_MAX));
		Bool thisPhase = (((Int)m_defectionDetectionFlashPhase) & 1); // are we in a flashy phase this frame?

		if (lastPhase && !thisPhase)
		{
			draw->rva00278C7C(0);

			BfmeAudioEventPrefix136 defectorTimerSound(TheAudio->getMiscAudio()->m_defectorTimerTickSound, 0);
			reinterpret_cast<Rva002D9531 *>(&defectorTimerSound)->rva002D9531(obj->getID());
			TheAudio->addAudioEvent(&defectorTimerSound);
		}
	}

	return UPDATE_SLEEP_NONE;
}
