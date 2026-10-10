// cl: /DNDEBUG /MD /EHsc
//
// ??1AudioLoopUpgrade@@MAE@XZ, retail 0x004B7B20, 97 bytes.
// AudioLoopUpgrade behavior dtor: restores the five vptrs (+0x00 0xC58CC4,
// +0x0C 0xC496F8, +0x10 0xC58CB8, +0x20 0xC58C70, +0x28 0xC58C68, DIR32),
// stops the loop sound through TheAudio (data 0x009FE6E8) at AudioManager
// slot 0x6c (removeAudioEvent) with the +0x2c handle when present (state 0),
// then calls the primary base dtor (rowed ??1UpdateModule@@UAE@XZ at
// 0x0024A797, state -1). Layout from the rowed ctor 0x004B7CBC (size 0x30
// via factory, m_x2c/audio handle at +0x2c) and the UpdateModule/STL pad
// shape of the ALU donor TU. Caller is the slot-0 ??_G at 0x004B7D37.
// Shape follows ArmorUpgradeDtor/PoisonedBehaviorDtor (multi-vptr restore
// plus UpgradeModule-family base call) plus FoundationAIUpdateSlot14
// (TheAudio slot-0x6c remove).
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

class UpdateModule
{
public:
	virtual ~UpdateModule();

private:
	unsigned char m_pad[0xc - 4];
};

class AudioLoopBase0C
{
public:
	virtual void base0CAnchor();
};

class AudioLoopBase10
{
public:
	virtual void base10Anchor();

private:
	unsigned char m_pad[0x20 - 0x14];
};

class AudioLoopBase20
{
public:
	virtual void base20Anchor();

private:
	unsigned char m_pad[0x28 - 0x24];
};

class AudioLoopBase28
{
public:
	virtual void base28Anchor();
};

class AudioLoopUpgrade : public UpdateModule,
	public AudioLoopBase0C,
	public AudioLoopBase10,
	public AudioLoopBase20,
	public AudioLoopBase28
{
protected:
	virtual ~AudioLoopUpgrade();

private:
	unsigned int m_handle2C; // +0x2c
};

AudioLoopUpgrade::~AudioLoopUpgrade()
{
	if (TheAudio != 0)
		TheAudio->removeAudioEvent(m_handle2C);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?base28Anchor@AudioLoopBase28@@UAEXXZ=?rva004B7E3C@AudioLoopUpgrade@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?base20Anchor@AudioLoopBase20@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?base10Anchor@AudioLoopBase10@@UAEXXZ=?rva004B7B87@AudioLoopUpgrade@@QAEHXZ")
#pragma comment(linker, "/alternatename:?base0CAnchor@AudioLoopBase0C@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
