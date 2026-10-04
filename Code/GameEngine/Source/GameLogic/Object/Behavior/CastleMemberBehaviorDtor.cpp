// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1CastleMemberBehavior@@MAE@XZ, retail 0x00395759, 103 bytes.
// CastleMemberBehavior dtor: restores the three MI vptrs (+0 0xC1A22C
// plus +0x0C 0xC1A170 plus +0x10 0xC1A160, DIR32), stops the audio loop
// through TheAudio (data 0x009FE6E8) at AudioManager slot 0x6c
// (removeAudioEvent) with the +0x20 handle when present then stores 1,
// restores the intermediate primary 0xBEEA7C plus +0x0C 0xBEE9C0 by hand
// and calls the opaque fold-point base at 0x0049B47C via the Rva0049B47C
// pin. Layout follows the rowed ctor 0x395B66 (UpdateModule base size 0x14
// with three ints at +0x14/+0x18/+0x1C plus derived +0x20/+0x24/+0x25).
// Shape follows LaserUpdateDtor (audio plus hand-placed intermediate
// restore plus Rva0049B47C base call) over PoisonedBehaviorDtor MI.

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

class Thing;
class ModuleData;

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

// Shared intermediate: Rva0049B47C (padded to 0xC) plus MiBase1 at +0xC.
// Empty dtor inlines into the derived so the derived restores PrimaryP's
// +0/+0xC vptrs itself then calls the pinned fold base (see
// Rva0024A797DeletingDtor.cpp PrimaryP24A797).
class PrimaryP : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP() {}
};

class CastleB2
{
public:
	virtual void f2();
};

class CastleMemberBehavior : public PrimaryP, public CastleB2
{
protected:
	virtual ~CastleMemberBehavior();
private:
	unsigned m_14;
	unsigned m_18;
	unsigned m_1C;
	unsigned m_20;
	unsigned char m_24;
	unsigned char m_25;
};

// ??1CastleMemberBehavior@@MAE@XZ @0x00395759
CastleMemberBehavior::~CastleMemberBehavior()
{
	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_20);
		m_20 = 1;
	}
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@CastleB2@@UAEXXZ=?rva0039922D@CastleBehavior@@QAEXPAURva00398E4AArg@@@Z")
#pragma comment(linker, "/alternatename:?f1@MiBase1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
