// cl: /O1 /DNDEBUG /MD /EHsc

// Retail layout: 0x005B5470 installs vftable 0x0110DE48, already pinned as
// ??_7BfmeOwnVVD@@6B@ by the landed destructor
// Code/GameEngine/Source/Common/BfmeConv1663.cpp (??1BfmeOwnVVD@@QAE@XZ,
// 0x005B5330), and stores `this` into the singleton at 0x012F4C84, already
// pinned in reverse/symbols.csv both as TheLookAtTranslator and as
// g_bfmeSingletonVVD -- but that name pin is stale for this address: the
// real ??0LookAtTranslator@@QAE@XZ is already matched elsewhere at
// 0x005A6580 (Code/GameEngine/Source/GameClient/MessageStream/
// LookAtTranslator_ctor.cpp, vtable 0x0110D62C), a different class entirely.
// This constructor is therefore address-derived, not LookAtTranslator; the
// BfmeOwnVVD name (shared with the already-landed dtor) is kept for
// consistency with that file. The array-new-with-ctor helper call (element
// size 0x20, count 8) uses the same BfmeElemVVD ctor/dtor pair as that file:
// the dtor is the existing pin ??1BfmeElemVVD@@QAE@XZ,0x0001479A; the ctor
// is newly pinned here as ??0BfmeElemVVD@@QAE@XZ,0x00418A07 (additive; the
// same address already carries an unrelated ??0BfmeS1059@@QAE@XZ pin
// through Code/gen_small/thunks_011.cpp -> FUN_00796AD0).
//
// Retail interleaves two groups of zero-stores around the array
// construction: some fields are zeroed via the (compiler-ordered)
// member-construction phase before the array, and the rest are zeroed by
// ordinary body statements that always run after all member construction
// (including the array) -- exactly the split used here (init-list members
// vs. body-assigned members).

class BfmeElemVVD
{
public:
	BfmeElemVVD();
	~BfmeElemVVD();
	char m_bfmePad00[0x20];
};

class BfmeBaseVVD
{
public:
	BfmeBaseVVD() { }
	~BfmeBaseVVD() { }
	virtual void bfmeSlot0VVD();
};

// ?bfmeSlot0VVD@BfmeBaseVVD@@UAEXXZ present-unmatched
void BfmeBaseVVD::bfmeSlot0VVD() { }

class BfmeOwnVVD : public BfmeBaseVVD
{
public:
	BfmeOwnVVD();
	~BfmeOwnVVD();
 unsigned char Rva0042E8C1();
 void rva0042E804();
 void rva0042E75F(unsigned int);

private:
	unsigned int m_04;                    // +0x04 body-set
	unsigned int m_08;                    // +0x08 body-set
	unsigned int m_0c;                    // +0x0c body-set
	unsigned int m_10;                    // +0x10 body-set
	unsigned int m_14;                    // +0x14 body-set
	unsigned int m_18;                    // +0x18 body-set
	unsigned char m_1c;                   // +0x1c init-list
	unsigned char m_pad1d[3];
	unsigned int m_20;                    // +0x20 body-set
	unsigned int m_24;                    // +0x24 body-set
	unsigned int m_28;                    // +0x28 body-set
	unsigned int m_2c;                    // +0x2c body-set
	unsigned int m_30;                    // +0x30 body-set
	unsigned int m_34;                    // +0x34 body-set
	unsigned char m_38;                   // +0x38 init-list
	unsigned char m_39;                   // +0x39 init-list
	unsigned char m_3a;                   // +0x3a init-list
	unsigned char m_3b;                   // +0x3b init-list
	unsigned char m_3c;                   // +0x3c init-list
	unsigned char m_pad3d[3];
	unsigned int m_40;                    // +0x40 init-list
	unsigned int m_44;                    // +0x44 init-list
	BfmeElemVVD m_bfme48[8];              // +0x48 .. +0x148
	unsigned int m_148;                   // +0x148 body-set
	unsigned int m_pad14c;
	unsigned int m_150;                   // +0x150 body-set
	unsigned char m_154;                  // +0x154 body-set
	unsigned char m_155;                  // +0x155 body-set
	unsigned char m_156;                  // +0x156 body-set
	unsigned char m_157;                  // +0x157 body-set
};

extern BfmeOwnVVD *g_bfmeSingletonVVD;
// g_bfmeSingletonVVD: matched references place it at VA 0xe03214 (zero-filled .bss).
BfmeOwnVVD * g_bfmeSingletonVVD;

struct BfmeRva42E8C1Limit { char m_pad[0x40]; unsigned int m_40; };
extern BfmeRva42E8C1Limit *g_bfmeRva42E8C1Holder;
extern unsigned int g_bfmeRva42E8C1Add;

// ??0BfmeOwnVVD@@QAE@XZ
BfmeOwnVVD::BfmeOwnVVD()
	: m_1c(0), m_38(0), m_39(0), m_3a(0), m_3b(0), m_3c(0), m_40(0), m_44(0)
{
	m_148 = 0;
	m_150 = 0;
	m_154 = 0;
	m_155 = 0;
	m_156 = 0;
	m_157 = 0;
	m_08 = 0;
	m_04 = 0;
	m_18 = 0;
	m_14 = 0;
	m_10 = 0;
	m_0c = 0;
	m_24 = 0;
	m_20 = 0;
	m_34 = 0;
	m_30 = 0;
	m_2c = 0;
	m_28 = 0;

	g_bfmeSingletonVVD = this;
}

// ??1BfmeOwnVVD@@QAE@XZ 0x0042E85C 79B: BFME1 donor BfmeConv1663.cpp; vtable 0x0083C938 base 0x007DBA74; caller 0x0042E9D3; singleton 0x00A03214
BfmeOwnVVD::~BfmeOwnVVD()
{
	if (g_bfmeSingletonVVD == this)
		g_bfmeSingletonVVD = 0;
}

// ?Rva0042E8C1@BfmeOwnVVD@@QAEEXZ 0x0042E8C1 44B: uses m_150 plus globals 0x009FE78C 0x009BA4E4; callers 0x0029F2CF 0x0037A90C
unsigned char BfmeOwnVVD::Rva0042E8C1()
{
	unsigned int &slot = m_150;
	if (slot > g_bfmeRva42E8C1Holder->m_40)
		slot = 0;
	return slot + g_bfmeRva42E8C1Add >= g_bfmeRva42E8C1Holder->m_40;
}

// ?rva0042E804@BfmeOwnVVD@@QAEXXZ @0x0042E804 88B evidence: same BfmeOwnVVD layout m_1c m_38 m_39 m_148 callers 0x0042EA56 0x0042ED42 TheInGameUI slot 0xa4 TheTacticalView slot 0x1a4 TheMouse slot 0x4c StatsCollector endScrollTime row
class InGameUI
{
public:
	virtual void i0();
	virtual void i1();
	virtual void i2();
	virtual void i3();
	virtual void i4();
	virtual void i5();
	virtual void i6();
	virtual void i7();
	virtual void i8();
	virtual void i9();
	virtual void i10();
	virtual void i11();
	virtual void i12();
	virtual void i13();
	virtual void i14();
	virtual void i15();
	virtual void i16();
	virtual void i17();
	virtual void i18();
	virtual void i19();
	virtual void i20();
	virtual void i21();
	virtual void i22();
	virtual void i23();
	virtual void i24();
	virtual void i25();
	virtual void i26();
	virtual void i27();
	virtual void i28();
	virtual void i29();
	virtual void i30();
	virtual void i31();
	virtual void i32();
	virtual void i33();
	virtual void i34();
	virtual void i35();
	virtual void i36();
	virtual void i37();
	virtual void i38();
	virtual void i39();
 virtual void i40();
 virtual void i41(int);
 char m_pad04[0x11];
 unsigned char m_15;
 unsigned char m_16;
};
extern InGameUI *TheInGameUI;

class TacticalView
{
public:
	virtual void t0();
	virtual void t1();
	virtual void t2();
	virtual void t3();
	virtual void t4();
	virtual void t5();
	virtual void t6();
	virtual void t7();
	virtual void t8();
	virtual void t9();
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14();
	virtual void t15();
	virtual void t16();
	virtual void t17();
	virtual void t18();
	virtual void t19();
	virtual void t20();
	virtual void t21();
	virtual void t22();
	virtual void t23();
	virtual void t24();
	virtual void t25();
	virtual void t26();
	virtual void t27();
	virtual void t28();
	virtual void t29();
	virtual void t30();
	virtual void t31();
	virtual void t32();
	virtual void t33();
	virtual void t34();
	virtual void t35();
	virtual void t36();
	virtual void t37();
	virtual void t38();
	virtual void t39();
	virtual void t40();
	virtual void t41();
	virtual void t42();
	virtual void t43();
	virtual void t44();
	virtual void t45();
	virtual void t46();
	virtual void t47();
	virtual void t48();
	virtual void t49();
	virtual void t50();
	virtual void t51();
	virtual void t52();
	virtual void t53();
	virtual void t54();
	virtual void t55();
	virtual void t56();
	virtual void t57();
	virtual void t58();
	virtual void t59();
	virtual void t60();
	virtual void t61();
	virtual void t62();
	virtual void t63();
	virtual void t64();
	virtual void t65();
	virtual void t66();
	virtual void t67();
	virtual void t68();
	virtual void t69();
	virtual void t70();
	virtual void t71();
	virtual void t72();
	virtual void t73();
	virtual void t74();
	virtual void t75();
	virtual void t76();
	virtual void t77();
	virtual void t78();
	virtual void t79();
	virtual void t80();
	virtual void t81();
	virtual void t82();
	virtual void t83();
	virtual void t84();
	virtual void t85();
	virtual void t86();
	virtual void t87();
	virtual void t88();
	virtual void t89();
	virtual void t90();
	virtual void t91();
	virtual void t92();
	virtual void t93();
	virtual void t94();
	virtual void t95();
	virtual void t96();
	virtual void t97();
	virtual void t98();
	virtual void t99();
	virtual void t100();
	virtual void t101();
	virtual void t102();
	virtual void t103();
 virtual void t104();
 virtual void t105(int);
 virtual void t106();
 virtual void t107();
 virtual void t108();
 virtual void t109();
 virtual void t110();
 virtual void t111();
 virtual void t112();
 virtual void t113();
 virtual void t114();
 virtual bool t115();
};
extern TacticalView *TheTacticalView;

class Mouse
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6();
	virtual void m7();
	virtual void m8();
	virtual void m9();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
 virtual void m18();
 virtual void m19(void *p);
 char m_pad04[0x4fa4 - 4];
 void *m_4fa4;
};
extern Mouse *TheMouse;

class ClientFrameSubsystem
{
public:
 char m_pad[0xc0];
 unsigned char m_c0;
};
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class StatsCollector
{
public:
 void endScrollTime();
 void startScrollTime();
};
extern StatsCollector *g_00E032F8;
extern void *g_00DC8874;
StatsCollector *g_00E032F8;
void *g_00DC8874;

void BfmeOwnVVD::rva0042E804()
{
 m_38 = 0;
 m_1c = 0;
 TheInGameUI->i41(0);
 if (m_39 == 0)
  TheTacticalView->t105(0);
 TheMouse->m19(g_00DC8874);
 m_148 = 0;
 if (g_00E032F8 == 0)
  return;
 return g_00E032F8->endScrollTime();
}

// ?rva0042E75F@BfmeOwnVVD@@QAEXI@Z @0x0042E75F 165B evidence: same BfmeOwnVVD layout m_38 m_39 m_148 callers 0x0042EBEC 0x0042ED6E 0x0042F187 TheInGameUI +0x15 +0x16 slot 0xa4 TheTacticalView slot 0x1cc 0x1a4 TheGameClient +0xc0 TheMouse +0x4fa4 StatsCollector startScrollTime row timeGetTime IAT
void BfmeOwnVVD::rva0042E75F(unsigned int arg)
{
 if (TheInGameUI->m_15 == 0)
  return;
 if (TheInGameUI->m_16 == 0)
  return;
 if (TheTacticalView->t115())
  return;
 if (((ClientFrameSubsystem *)TheGameClient)->m_c0 != 0)
  return;
 void *tmp = TheMouse->m_4fa4;
 m_38 = 1;
 g_00DC8874 = tmp;
 TheInGameUI->i41(1);
 if (m_39 == 0)
  TheTacticalView->t105(1);
 if (arg != m_148)
 {
  m_148 = arg;
  m_pad14c = timeGetTime();
 }
 if (g_00E032F8 == 0)
  return;
 g_00E032F8->startScrollTime();
}

// ?g_bfmeRva42E8C1Add@@3IA: the global at this VA is ?g_Va00DBA4E4@@3HA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_bfmeRva42E8C1Add@@3IA=?g_Va00DBA4E4@@3HA")
#pragma comment(linker, "/alternatename:?g_009BA4E4@@3HB=?g_Va00DBA4E4@@3HA")
// ?g_bfmeRva42E8C1Holder@@3PAUBfmeRva42E8C1Limit@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?g_bfmeRva42E8C1Holder@@3PAUBfmeRva42E8C1Limit@@A=?TheGameLogic@@3PAVGameLogic@@A")
// ?g_bfmeRva42E8C1Add@@3IA: the global at VA 0xdba4e4 is ?g_Va00DBA4E4@@3HA.
#pragma comment(linker, "/alternatename:?g_bfmeRva42E8C1Add@@3IA=?g_Va00DBA4E4@@3HA")
