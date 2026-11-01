// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
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
// (primary+0x2C). Shape follows the rowed upgradeRemovalImplementation secondary helper
// plus the FoundationAIUpdateSlot14 TheAudio remove. Honest address name:
// method identity unproven.

#include "GameLogic/Module/UpdateModule.h"
#include "Common/Snapshot.h"
#include "Common/ObjectModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };
enum NameKeyType;
class BfmeFixedStorage002CF0F0;
class MultiIniFieldParse;
typedef unsigned int AudioHandle;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct SoundHolder
{
	SoundHolder() : m_ptr(0) {}
	~SoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class DieMuxData
{
public:
	DieMuxData *init();

private:
	unsigned char m_pad[0x30];
};

class AudioLoopUpgradeModuleData : public Snapshot
{
	friend class AudioLoopUpgrade;
public:
	AudioLoopUpgradeModuleData();
	virtual ~AudioLoopUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	unsigned int m_unused04;
	SoundHolder m_soundToPlay; // +0x08
	int m_killAfterMS; // +0x0C
	bool m_killOnDeath; // +0x10
	unsigned char m_pad11[3];
	Rva0025342CMember m_member14; // +0x14
	DieMuxData m_die124; // +0x124
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

class UpgradeMux
{
public:
	UpgradeMux();
	// Rowed: slot 0 of retail's UpgradeMux table 0x00C5FF10 and of this class's 0x00C58C70.
	virtual bool isAlreadyUpgraded() const;

private:
	bool m_upgradeExecuted;
};

class ALU_Iface4 { public: virtual void rva004B7E3C(int) = 0; };

class AudioLoopUpgrade : public UpdateModule,
	public UpgradeMux,
	public ALU_Iface4
{
public:
	AudioLoopUpgrade(Thing *, const ModuleData *);
	virtual NameKeyType getModuleNameKey() const;
	BfmeFixedStorage002CF0F0 *getDisabledTypesToProcess(BfmeFixedStorage002CF0F0 *out);
	// Rowed in AudioLoopUpgradeRva004B7E3C.cpp: slot 0 of retail table 0x00C58C68.
	virtual void rva004B7E3C(int);

protected:
	virtual ~AudioLoopUpgrade();

private:
	unsigned int m_soundHandle; // +0x2C
};

void AudioLoopUpgrade::rva004B7E3C(int unused)
{
	const AudioLoopUpgradeModuleData *data = (const AudioLoopUpgradeModuleData *)getModuleData();
	if (!data->m_killOnDeath)
		return;
	if (TheAudio != 0) {
		TheAudio->removeAudioEvent(m_soundHandle);
		m_soundHandle = 1;
	}
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	(void)unused;
}
