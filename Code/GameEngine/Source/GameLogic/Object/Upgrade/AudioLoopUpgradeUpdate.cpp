// cl: /DNDEBUG /MD /EHsc
//
// ?update@AudioLoopUpgrade@@QAEHXZ, retail 0x004B7B87, 35 bytes.
// ?upgradeRemovalImplementation@AudioLoopUpgrade@@QAEXXZ, retail 0x004B7DE0, 46 bytes.
// Virtual slot 18 (offset 0x48) of vtable 0x00858C70 (class of the rowed
// AudioLoopUpgrade ctor; prev ModuleNameGetters 0x004B7B81 plus next pool key
// 0x004B7BBB). Body stops the loop sound through TheAudio (data 0x009FE6E8)
// at AudioManager slot 0x6c (removeAudioEvent) with the +0x1c handle when
// present, marks it 1, and returns UPDATE_SLEEP_FOREVER (0x3FFFFFFF).
// Shape follows FoundationAIUpdateSlot14 (TheAudio slot-0x6c remove plus
// handle set to 1) plus FlammableUpdate::stopBurningSound (null-checked
// TheAudio remove). Semantic slot name unproven so this rides an
// address-derived AudioLoopUpgrade-scoped name.
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

typedef unsigned int AudioHandle;

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

class Object;
class AudioLoopUpgrade;

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
	friend class AudioLoopUpgrade;
};

class AudioLoopUpgrade
{
public:
	int update();
	void upgradeRemovalImplementation();

private:
	unsigned char m_pad0C[0xc];
	unsigned int m_handle0C; // +0x0c
	unsigned char m_pad1C[0xc];
	unsigned int m_handle1C; // +0x1c
};

int AudioLoopUpgrade::update()
{
	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_handle1C);
		m_handle1C = 1;
	}
	return UPDATE_SLEEP_FOREVER;
}

void AudioLoopUpgrade::upgradeRemovalImplementation()
{
	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_handle0C);
		m_handle0C = 1;
	}
	UpdateModule *upd = (UpdateModule *)((char *)this - 0x20);
	Object *obj = *(Object **)((char *)this - 0x18);
	upd->setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
}
