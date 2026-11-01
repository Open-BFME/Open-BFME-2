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

typedef unsigned int AudioHandle;

enum
{
	AHSV_NoSound = 1
};

struct BfmeAudioEventPrefix136;
class Xfer;

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
	virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
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
	virtual void _pad52() = 0;
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

class ModuleData;

class AudioLoopUpgradeModuleData
{
public:
	unsigned char m_pad000[0x08];
	OpaqueRefElement4 m_soundToPlay; // +0x08
	unsigned int m_killAfterMS; // +0x0C
	bool m_killOnDeath; // +0x10
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

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
	const AudioLoopUpgradeModuleData *audioLoopUpgradeModuleData = getAudioLoopUpgradeModuleData();
	if (TheAudio)
	{
		if (m_soundHandle != AHSV_NoSound)
			TheAudio->removeAudioEvent(m_soundHandle);
		BfmeAudioEventPrefix136 soundToPlay(audioLoopUpgradeModuleData->m_soundToPlay, getObject()->getID());
		m_soundHandle = TheAudio->addAudioEvent(&soundToPlay);
	}
	if (audioLoopUpgradeModuleData->m_killAfterMS > 0)
		setWakeFrame(getObject(), (UpdateSleepTime)audioLoopUpgradeModuleData->m_killAfterMS);
}
