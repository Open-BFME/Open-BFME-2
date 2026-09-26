// cl: /O1 /MD
//
// ?rva0004550DE@FoundationAIUpdate@@QAEXXZ @0x004550DE, 26 bytes.
// Virtual slot 14 (offset 0x38) of vtable 0x00840608 (primary of
// ??1Rva00455050@@UAE@XZ). Class is FoundationAIUpdate: slot 2 at
// 0x00455070 returns "FoundationAIUpdate", slot 4 at 0x00455167 is the
// FoundationAIUpdate pool key, and the ctor at 0x004551B3 installs this
// vtable. Callee is TheAudio (data 0x009FE6E8, proven by getVolume at
// 0x002E4B2D calling getAudioSettings at +0x134 through it) slot 0x6c
// (removeAudioEvent precedent FlammableUpdate). Body passes m_24 then sets
// it to 1 (AHSV_NoSound). Single caller at 0x00489F01 in unclaimed code.

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
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
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class FoundationAIUpdate : public UpdateModule
{
public:
	void rva0004550DE();

private:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned char m_2C;
};

void FoundationAIUpdate::rva0004550DE()
{
	TheAudio->removeAudioEvent(m_24);
	m_24 = 1;
}
