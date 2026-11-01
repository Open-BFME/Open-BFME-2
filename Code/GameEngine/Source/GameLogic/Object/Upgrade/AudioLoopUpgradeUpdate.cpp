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

#include "../../../../Include/Common/GameAudio.h"

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
