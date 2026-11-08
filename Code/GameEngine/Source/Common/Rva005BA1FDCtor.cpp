// cl: -GR- -EHsc-
// ??0AptOnlineOpenPlay@@QAE@H@Z @0x005BA1FD 55B: composing constructor. Builds
// the base with (arg, 0) through the AptOnlineCustomMatch ctor, installs the
// three polymorphic tables, publishes this to the 0xE06544 global when clear,
// and returns this. The tables are retail's, each slot the ledger row at the native
// address, stored by hand because the classes' own virtuals are still unnamed.
class AptOnlineCustomMatch
{
public:
	AptOnlineCustomMatch(int x, int y);
};

extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_ERva005BA23A@@WGA@AEPAXI@Z")();
void __identifier("??_ERva005BA23A@@WGM@AEPAXI@Z")();
void __identifier("??_ERva005BA2CB@@WGA@AEPAXI@Z")();
void __identifier("??_ERva005BA2CB@@WGM@AEPAXI@Z")();
void __identifier("??_GRva005BA23A@@UAEPAXI@Z")();
void __identifier("??_GRva005BA2CB@@UAEPAXI@Z")();
void __identifier("?GameWindowSystem@AptOnlineCustomMatch@@UAEHPAVGameWindow@@III@Z")();
void __identifier("?InitGadgets@AptOnlineCustomMatch@@UAEXXZ")();
void __identifier("?MpOwnerGetLocalPlayerName@AptOnlineCustomMatch@@QAEXAAVUnicodeString@@@Z")();
void __identifier("?MpOwnerOnReadyChecked@AptOnlineCustomMatch@@UAE_N_N@Z")();
void __identifier("?MpOwnerPrintMessage@AptOnlineCustomMatch@@UAEXABVUnicodeString@@H@Z")();
void __identifier("?MpOwnerSelectColor@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z")();
void __identifier("?MpOwnerSelectHandicap@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z")();
void __identifier("?MpOwnerSelectHero@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@@Z")();
void __identifier("?MpOwnerSelectMap@AptOnlineCustomMatch@@UAE_NABVAsciiString@@@Z")();
void __identifier("?MpOwnerSelectPlayer@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@HH@Z")();
void __identifier("?MpOwnerSelectPlayerTemplate@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z")();
void __identifier("?MpOwnerSelectStartPosition@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z")();
void __identifier("?MpOwnerSelectStrategicScenario@AptOnlineCustomMatch@@UAE_NH@Z")();
void __identifier("?MpOwnerSelectTeam@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z")();
void __identifier("?MpOwnerSetClanID@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@ABVUnicodeString@@@Z")();
void __identifier("?MpOwnerUpdatePlayerTooltip@AptOnlineCustomMatch@@UAEXPAVGameSlot@@@Z")();
void __identifier("?ProcessGameSpyResponses@AptOnlineCustomMatch@@QAEXXZ")();
void __identifier("?Rva005BA234Get@@YAHXZ")();
void __identifier("?Rva005BA2C5Get@@YAHXZ")();
void __identifier("?Update@AptOnlineCustomMatch@@UAEXXZ")();
void __identifier("?get@Rva005A00CCPtrChase32Field@@QBEHXZ")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?rva0059EBDE@AptOnlineCustomMatch@@UAE_NXZ")();
void __identifier("?rva0059EBFE@AptOnlineCustomMatch@@UAEXXZ")();
void __identifier("?rva0059EC50@AptOnlineCustomMatch@@UAE_NXZ")();
void __identifier("?rva0059EF49@AptOnlineCustomMatch@@UAE_NXZ")();
void __identifier("?rva0059EF57@Rva0059EF57@@QAEXHHH@Z")();
void __identifier("?rva0059F35E@Rva0059F35E@@QAEPAVRva004444EBBase@@XZ")();
void __identifier("?rva005A1B4F@AptOnlineCustomMatch@@UAEX_NH@Z")();
void __identifier("?rva005A1C87@AptOnlineCustomMatch@@UAEX_N@Z")();
void __identifier("?rva005A1D32@AptOnlineCustomMatch@@UAEXXZ")();
void __identifier("?rva005A6582@AptOnlineCustomMatch@@UAEHHHEH@Z")();
void __identifier("?rva005A6697@AptOnlineCustomMatch@@UAE_NXZ")();
}

// Retail table at VA 0x00C73D34: Rva005BA23A's compiler table (Rva005BA2CBDtor.cpp emits it).
extern "C" const void *const __identifier("??_7Rva005BA23A@@6BRva005A0009@@@")[];

// Retail table at VA 0x00C73CD8: Rva005BA23A's compiler table (Rva005BA2CBDtor.cpp emits it).
extern "C" const void *const __identifier("??_7Rva005BA23A@@6BRva005BA23ABase60@@@")[];

// Retail table at VA 0x00C73CCC: Rva005BA23A's compiler table (Rva005BA2CBDtor.cpp emits it).
extern "C" const void *const __identifier("??_7Rva005BA23A@@6BRva005BA23ABase6C@@@")[];

// Retail table at VA 0x00C73DCC.
extern "C" const void *const g_customMatchScreenTable00[11] = {
	(const void *)&__identifier("??_GRva005BA2CB@@UAEPAXI@Z"), // slot 0, RVA 0x005BA303
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&__identifier("?InitGadgets@AptOnlineCustomMatch@@UAEXXZ"), // slot 2, RVA 0x0059EFA0
	(const void *)&__identifier("?Update@AptOnlineCustomMatch@@UAEXXZ"), // slot 3, RVA 0x005A61C6
	(const void *)&__identifier("?rva005A6582@AptOnlineCustomMatch@@UAEHHHEH@Z"), // slot 4, RVA 0x005A6582
	(const void *)&__identifier("?GameWindowSystem@AptOnlineCustomMatch@@UAEHPAVGameWindow@@III@Z"), // slot 5, RVA 0x005A52FE
	(const void *)&__identifier("?ProcessGameSpyResponses@AptOnlineCustomMatch@@QAEXXZ"), // slot 6, RVA 0x005A2DB7
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 7, RVA 0x0050B5C6
	(const void *)&__identifier("?rva0059EF49@AptOnlineCustomMatch@@UAE_NXZ"), // slot 8, RVA 0x0059EF49
	(const void *)&__identifier("?rva005A6697@AptOnlineCustomMatch@@UAE_NXZ"), // slot 9, RVA 0x005A6697
	(const void *)&__identifier("?Rva005BA2C5Get@@YAHXZ"), // slot 10, RVA 0x005BA2C5
};

// Retail table at VA 0x00C73D70.
extern "C" const void *const g_customMatchScreenTable60[23] = {
	(const void *)&__identifier("??_ERva005BA2CB@@WGA@AEPAXI@Z"), // slot 0, RVA 0x005BA2F3
	(const void *)&__identifier("?rva0059EBDE@AptOnlineCustomMatch@@UAE_NXZ"), // slot 1, RVA 0x0059EBDE
	(const void *)&__identifier("?rva0059EBFE@AptOnlineCustomMatch@@UAEXXZ"), // slot 2, RVA 0x0059EBFE
	(const void *)&__identifier("?MpOwnerOnReadyChecked@AptOnlineCustomMatch@@UAE_N_N@Z"), // slot 3, RVA 0x005A1DCE
	(const void *)&__identifier("?MpOwnerSelectColor@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z"), // slot 4, RVA 0x005A0F4B
	(const void *)&__identifier("?MpOwnerSelectHandicap@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z"), // slot 5, RVA 0x005A152F
	(const void *)&__identifier("?MpOwnerSelectHero@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@@Z"), // slot 6, RVA 0x005A1281
	(const void *)&__identifier("?MpOwnerSelectMap@AptOnlineCustomMatch@@UAE_NABVAsciiString@@@Z"), // slot 7, RVA 0x005A0B7E
	(const void *)&__identifier("?MpOwnerSelectStrategicScenario@AptOnlineCustomMatch@@UAE_NH@Z"), // slot 8, RVA 0x0059EB6F
	(const void *)&__identifier("?MpOwnerSelectPlayer@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@HH@Z"), // slot 9, RVA 0x005A168D
	(const void *)&__identifier("?MpOwnerSelectPlayerTemplate@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z"), // slot 10, RVA 0x005A10DA
	(const void *)&__identifier("?MpOwnerSelectStartPosition@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z"), // slot 11, RVA 0x005A186B
	(const void *)&__identifier("?MpOwnerSelectTeam@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@H@Z"), // slot 12, RVA 0x005A13D8
	(const void *)&__identifier("?MpOwnerSetClanID@AptOnlineCustomMatch@@UAE_NPAVGameSlot@@ABVUnicodeString@@@Z"), // slot 13, RVA 0x005A19C0
	(const void *)&__identifier("?MpOwnerGetLocalPlayerName@AptOnlineCustomMatch@@QAEXAAVUnicodeString@@@Z"), // slot 14, RVA 0x0059EBAF
	(const void *)&__identifier("?rva005A1D32@AptOnlineCustomMatch@@UAEXXZ"), // slot 15, RVA 0x005A1D32
	(const void *)&__identifier("?rva005A1C87@AptOnlineCustomMatch@@UAEX_N@Z"), // slot 16, RVA 0x005A1C87
	(const void *)&__identifier("?MpOwnerPrintMessage@AptOnlineCustomMatch@@UAEXABVUnicodeString@@H@Z"), // slot 17, RVA 0x0059F043
	(const void *)&__identifier("?rva005A1B4F@AptOnlineCustomMatch@@UAEX_NH@Z"), // slot 18, RVA 0x005A1B4F
	(const void *)&__identifier("?MpOwnerUpdatePlayerTooltip@AptOnlineCustomMatch@@UAEXPAVGameSlot@@@Z"), // slot 19, RVA 0x005A00E6
	(const void *)&__identifier("?rva0059F35E@Rva0059F35E@@QAEPAVRva004444EBBase@@XZ"), // slot 20, RVA 0x0059F35E
	(const void *)&__identifier("?get@Rva005A00CCPtrChase32Field@@QBEHXZ"), // slot 21, RVA 0x005A00CC
	(const void *)&__identifier("?rva0059EC50@AptOnlineCustomMatch@@UAE_NXZ"), // slot 22, RVA 0x0059EC50
};

// Retail table at VA 0x00C73D60.
extern "C" const void *const g_customMatchScreenTable6C[3] = {
	(const void *)&__identifier("?rva0059EF57@Rva0059EF57@@QAEXHHH@Z"), // slot 0, RVA 0x0059EF57
	(const void *)&__identifier("?rva0059EF57@Rva0059EF57@@QAEXHHH@Z"), // slot 1, RVA 0x0059EF57
	(const void *)&__identifier("??_ERva005BA2CB@@WGM@AEPAXI@Z"), // slot 2, RVA 0x005BA2FB
};

class AptOnlineOpenPlay;
// g_rva005BA1FDInst is only an alias of the owned global g_Va00E06544 (ledger names column); this unit reads through it.
extern int g_Va00E06544;
#define g_rva005BA1FDInst (*(AptOnlineOpenPlay * *)&g_Va00E06544)

class AptOnlineOpenPlay : public AptOnlineCustomMatch
{
public:
	AptOnlineOpenPlay(int arg);

private:
	const void *const *m_table00;
	char m_pad04[0x60 - 4];
	const void *const *m_table60;
	char m_pad64[8];
	const void *const *m_table6C;
};

AptOnlineOpenPlay::AptOnlineOpenPlay(int arg)
	: AptOnlineCustomMatch(arg, 0)
{
	m_table00 = __identifier("??_7Rva005BA23A@@6BRva005A0009@@@");
	m_table60 = __identifier("??_7Rva005BA23A@@6BRva005BA23ABase60@@@");
	m_table6C = __identifier("??_7Rva005BA23A@@6BRva005BA23ABase6C@@@");
	if (g_rva005BA1FDInst == 0)
		g_rva005BA1FDInst = this;
}

// ??0Rva005BA28E@@QAE@H@Z @0x005BA28E 55B: sibling composing constructor,
// same skeleton as AptOnlineOpenPlay above. Builds the shared base with
// (arg, 1), installs its three tables and publishes this to the 0xE06548
// screen-instance global that the rowed destructor 0x005BA2CB clears.
// Original class name unknown.
class Rva005BA28E;
extern int g_Va00E06548;
#define g_rva005BA28EInst (*(Rva005BA28E * *)&g_Va00E06548)

class Rva005BA28E : public AptOnlineCustomMatch
{
public:
	Rva005BA28E(int arg);

private:
	const void *const *m_table00;
	char m_pad04[0x60 - 4];
	const void *const *m_table60;
	char m_pad64[8];
	const void *const *m_table6C;
};

Rva005BA28E::Rva005BA28E(int arg)
	: AptOnlineCustomMatch(arg, 1)
{
	m_table00 = g_customMatchScreenTable00;
	m_table60 = g_customMatchScreenTable60;
	m_table6C = g_customMatchScreenTable6C;
	if (g_rva005BA28EInst == 0)
		g_rva005BA28EInst = this;
}
