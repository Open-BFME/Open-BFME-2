// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
//
// ?upgradeImplementation@AudioLoopUpgrade@@MAEXXZ, retail 0x004B7D53, 141 bytes.
// Slot 10 of AudioLoopUpgrade's UpgradeMux vftable 0x00858C70 (slot 11 is the
// rowed getUpgradeActivationMasks, 12 performUpgradeFX), the slot BFME 1 names
// upgradeImplementation (reference/open-bfme-1/game/GameEngine/Source/GameLogic/
// Object/Upgrade/AudioLoopUpgradeUpgradeImplementation.cpp, its 0x002D33E0).
// `this` is the UpgradeMux at AudioLoopUpgrade +0x20, so the UpdateModule base
// is this-0x20. The body stops the loop already playing (handle at +0x2C, 1
// when none, as the ctor stores), starts the module data's sound (+0x08) as an
// event owned by the object's ID (Object +0x74) through TheAudio slots 0x6C and
// 0x64, and when the kill-after delay (+0x0C, unsigned compare) is set wakes the
// update after it. The event is the 0x88-byte BfmeAudioEventPrefix136
// (ObjectID owner ctor 0x002DA461, dtor 0x002D9A43).

#include "Common/BfmeAudioEventPrefix136.h"

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_pad000[0x74];
	ObjectID m_id; // +0x74
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

typedef int AudioHandle;

enum
{
	AHSV_NoSound = 1
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03) AUDIO_SLOT(04)
	AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07) AUDIO_SLOT(08) AUDIO_SLOT(09)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24)
#undef AUDIO_SLOT
	virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd);
	virtual void slot26();
	virtual void removeAudioEvent(AudioHandle audioEvent);
};
extern AudioManager *TheAudio;

class ModuleData;

class AudioLoopUpgradeModuleData
{
public:
	unsigned char m_pad000[0x08];
	OpaqueRefElement4 m_soundToPlay; // +0x08
	unsigned int m_killAfterMS; // +0x0C
	bool m_killOnDeath; // +0x10
};

class UpdateModule
{
public:
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

template <int N> class UpgradeMuxSlots : public UpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class UpgradeMuxSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class UpgradeMux : public UpgradeMuxSlots<10>
{
protected:
	virtual void upgradeImplementation() = 0;

private:
	bool m_upgradeExecuted;
};

class AudioLoopUpgradeInterface
{
public:
	virtual void slot();
};

class AudioLoopUpgrade : public UpdateModule, public UpgradeMux, public AudioLoopUpgradeInterface
{
protected:
	virtual void upgradeImplementation();

private:
	const AudioLoopUpgradeModuleData *getAudioLoopUpgradeModuleData() const
	{
		return (const AudioLoopUpgradeModuleData *)getModuleData();
	}

	AudioHandle m_soundHandle; // +0x2C
};

// ?upgradeImplementation@AudioLoopUpgrade@@MAEXXZ
void AudioLoopUpgrade::upgradeImplementation()
{
	const AudioLoopUpgradeModuleData *d = getAudioLoopUpgradeModuleData();
	if (TheAudio)
	{
		if (m_soundHandle != AHSV_NoSound)
			TheAudio->removeAudioEvent(m_soundHandle);
		BfmeAudioEventPrefix136 soundToPlay(d->m_soundToPlay, getObject()->getID());
		m_soundHandle = TheAudio->addAudioEvent(&soundToPlay);
	}
	if (d->m_killAfterMS > 0)
		setWakeFrame(getObject(), (UpdateSleepTime)d->m_killAfterMS);
}
