// cl: /DNDEBUG /MD /EHsc
// ??1BattlePlanUpdate@@UAE@XZ retail 0x004978A3 114B (was rowed as the opaque ??1Rva004978A3)
// Identity: ??0BattlePlanUpdate 0x00497ED0 installs 0x0084FBAC/+0xC 0x0084D640/+0x10 0x0084FBA0/+0x20 0x0084FB7C,
// the set this destructor restores; 0x0084FBAC is the only vtable holding its deleting dtor 0x00497FD7.
// Evidence: unlock lane stores vtable 0x0084FBAC; base dtor 0x0024A797 rowed MI 0x20 with order +0x10/+0/+0xC; second base at +0x20 vtable 0x0084FB7C; array 4x0x10 at +0x44 with element dtor pin 0x0010F149 via EH vector dtor; virtual slot 0x6c on global 0x009FE6E8 with arg +0x84; neighbours BattlePlanUpdate TUs
extern class AudioManager *TheAudio;

struct BfmeStringTailRecord156
{
	~BfmeStringTailRecord156();
	int m_data;
};

class Rva0049B47C004978A3
{
public:
	virtual ~Rva0049B47C004978A3();
private:
	char m_pad04[8];
};

class MiBase1004978A3
{
public:
	virtual void f1();
};

class PrimaryP004978A3 : public Rva0049B47C004978A3, public MiBase1004978A3
{
public:
	~PrimaryP004978A3() {}
};

// Retail's base +0x10 table (0x00BFBCE4, stored by ~UpdateModule
// 0x0024A797) holds _purecall in slot 0: the slot is pure.
class Rva0024A797_B2004978A3
{
public:
	virtual void f2() = 0;
private:
	char m_pad04[12];
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class __declspec(novtable) SecondBase004978A3
{
public:
	virtual ~SecondBase004978A3() {}
private:
	char m_pad04[0x20];
};

class GlobalMgr004978A3
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27(int v);
};

#define TheGlobalMgr004978A3 (*(GlobalMgr004978A3 **)&TheAudio)

class BattlePlanUpdate : public UpdateModule, public SecondBase004978A3
{
public:
	virtual ~BattlePlanUpdate();
private:
	BfmeStringTailRecord156 m_arr44[0x10];
	int m_84;
public:
	// retail slot 4: the rowed ?getModuleNameKey@BattlePlanUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

BattlePlanUpdate::~BattlePlanUpdate()
{
	TheGlobalMgr004978A3->f27(m_84);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@MiBase1004978A3@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
