// cl: /DNDEBUG /MD
//
// ?rva004B7E3C@AudioLoopUpgrade@@UAEXH@Z, retail 0x004B7E3C, 57 bytes.
// Sits between the Disp8 getter at 0x004B7E23 and the rowed
// ?xfer@AudioLoopUpgrade@@MAEXPAVXfer@@@Z at 0x004B7E75: checks the
// AudioLoopUpgradeModuleData kill-on-death flag at +0x10 via the module
// data at primary+0x04, stops the loop sound through TheAudio (data
// 0x009FE6E8) at AudioManager slot 0x6c (removeAudioEvent) with the +0x2C
// handle when present, marks it 1, then setWakeFrame via rowed 0x44DF71
// to UPDATE_SLEEP_FOREVER. The secondary this at +0x28 gives primary via
// -0x28, module data via -0x24, object via -0x20 and handle via +0x04
// (primary+0x2C). Shape follows the rowed rva004B7DE0 secondary helper
// plus the FoundationAIUpdateSlot14 TheAudio remove. Honest address name:
// method identity unproven.

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

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
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class Object;
class AudioLoopUpgrade;

class UpdateModule
{
protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
	friend class AudioLoopUpgrade;
};

struct AudioLoopUpgradeModuleData004B7E3C
{
	char m_pad00[0x10];
	unsigned char m_killOnDeath;
};

class AudioLoopUpgrade
{
public:
	virtual void rva004B7E3C(int unused);

private:
	AudioHandle m_handle04;
};

void AudioLoopUpgrade::rva004B7E3C(int unused)
{
	AudioLoopUpgradeModuleData004B7E3C *data = *(AudioLoopUpgradeModuleData004B7E3C **)((char *)this - 0x24);
	if (data->m_killOnDeath == 0)
		return;
	if (TheAudio != 0) {
		TheAudio->removeAudioEvent(m_handle04);
		m_handle04 = 1;
	}
	UpdateModule *upd = (UpdateModule *)((char *)this - 0x28);
	Object *obj = *(Object **)((char *)this - 0x20);
	upd->setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
	(void)unused;
}
