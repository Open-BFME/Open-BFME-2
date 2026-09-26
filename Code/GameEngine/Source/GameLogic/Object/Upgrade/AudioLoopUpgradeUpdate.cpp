// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva004B7B87@AudioLoopUpgrade@@QAEHXZ, retail 0x004B7B87, 35 bytes.
// ?rva004B7DE0@AudioLoopUpgrade@@QAEXXZ, retail 0x004B7DE0, 46 bytes.
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

class UpdateModule
{
public:
	void setWakeFrame(Object *obj, unsigned int frame);
};

class AudioLoopUpgrade
{
public:
	int rva004B7B87();
	void rva004B7DE0();

private:
	unsigned char m_pad0C[0xc];
	unsigned int m_handle0C; // +0x0c
	unsigned char m_pad1C[0xc];
	unsigned int m_handle1C; // +0x1c
};

int AudioLoopUpgrade::rva004B7B87()
{
	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_handle1C);
		m_handle1C = 1;
	}
	return UPDATE_SLEEP_FOREVER;
}

void AudioLoopUpgrade::rva004B7DE0()
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
