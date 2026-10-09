// ??0BfmeStrVM0@@QAE@XZ
// partial score=0.925 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /GX
// ??1BfmeStrVM0@@UAE@XZ, retail 0x0025D686, 111 bytes.
// Destructor of BfmeStrVM0: stores vtable 0x7F5DA0 then runs the field-reset
// helper rva0025D19E and the list-clear rva0025C0FF on the same this, then
// destroys AsciiString at +0xF0/+0xD0 and Unicode string at +0xB0 in reverse
// order, then the GameEngineDeletingBase base dtor.
// Evidence: same-this calls at 0x0025D6A4/0x0025D6AB; vtable shared with ctor
// 0x0025D489 which inits the same D0/E0/E4/C8/CC/F0 fields; base call
// 0x001B4E74; deleting-dtor caller 0x0025DA57.
template <typename T> class StringBase
{
public:
 StringBase():m_data(0){}
 void clear(){releaseBuffer();}
	~StringBase() { releaseBuffer(); }
	void set(const StringBase &o);
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva0025C0FF
{
public:
	void rva0025C0FF();
};

class AsciiString : private StringBase<char>
{
public:
	__forceinline AsciiString() {}
	__forceinline AsciiString(const AsciiString &o) : StringBase<char>(o) {}
	__forceinline ~AsciiString() {}
	AsciiString &operator=(const AsciiString &o);
};

class W3DDisplay
{
public:
	void rva0025D2F6();
};

class ListNode0025D9E3
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void v005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014(int x);
	virtual int s015();
	virtual void s016(int y);
	virtual int s017();
	virtual void s018(int x, int y);
	virtual void s019(int *a, int *b);
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void s131();
	virtual void s132();
	virtual void s133();
	virtual void s134();
	virtual void s135();
	virtual void s136();
	virtual void s137();
	virtual void s138();
	virtual void s139();
	virtual void s140();
	virtual void s141();
	virtual void s142();
	virtual void s143();
	virtual void s144();
	virtual void s145();
	virtual void s146();
	virtual void s147();
	virtual void s148();
	virtual void s149();
	virtual void s150();
	virtual void s151();
	virtual ListNode0025D9E3 *getNext();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
 virtual ~GameEngineDeletingBase();
private:
	char m_pad[8];
};

class GameLogic
{
public:
	bool rva00085124();
};
extern GameLogic *TheGameLogic;

struct GlobalA01E48
{
	char pad[0x5d];
	unsigned char flag;
};
// ?g_Va00A01E48@@3PAUGlobalA01E48@@A: the global at this VA is ?TheShell@@3PAVShell@@A; this name is an alias for it.
extern GlobalA01E48 * g_Va00A01E48;
#pragma comment(linker, "/alternatename:?g_Va00A01E48@@3PAUGlobalA01E48@@A=?TheShell@@3PAVShell@@A")

struct Rva0025C18BCoord
{
	float x;
	float y;
};

class Rva0025C09E {public: Rva0025C09E(); char data[24];};
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();
struct DisplayCriticalSection {char data[24];};
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(DisplayCriticalSection*);
extern DisplayCriticalSection DisplayMovieCriticalSection;
struct DisplayVideoConfig {
 int pointer3c,pointer40,pointer44;bool flag48;char gap49[3];
 __forceinline DisplayVideoConfig():pointer3c(0),pointer40(0),pointer44(0),flag48(false){}
};
struct DisplayTick50 {
 int tick50,word54,word58;bool flag5c,flag5d;char gap5e[2];int word60;bool flag64;char gap65[3];
 __forceinline DisplayTick50():tick50(GetTickCount()),flag5d(false){word54=0;word58=0;flag5c=false;word60=0;flag64=false;}
};
struct DisplayTextF0 {
 StringBase<char> text;
 int wordF4,wordF8;float fFC,f100,f104,f108;bool flag10c;char gap10d[3];
 int word110;bool m_b114,flag115;char gap116[2];int word118;
 float f11c,m_f120;
 __forceinline DisplayTextF0():wordF4(0),wordF8(0),fFC(0),f100(0),f104(0),f108(0),flag10c(false),word110(0),m_b114(false),flag115(false),word118(0),f11c(1.0f),m_f120(0){}
};
class BfmeStrVM0 : public GameEngineDeletingBase
{
public:
	BfmeStrVM0();
 __forceinline int resetVideoPointers(){pointer2c=0;pointer30=0;pointer34=0;pointer38=0;return 0;}
 virtual ~BfmeStrVM0();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30();
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void rva0025C14D();
	virtual void rva0025C18B(Rva0025C18BCoord *a, Rva0025C18BCoord *b);
	virtual void v40();
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual void v64() = 0;
	virtual void v65() = 0;
	virtual void v66();
	virtual void v67();
	virtual void v68();
	void rva0025D19E();
	void rva0025D358(StringBase<unsigned short> s, float fC0, float fC4, int iB4, int iB8, int iBC);
	void rva0025D9E3();
	void rva00049F94(AsciiString s);
private:
int widthC,height10,bitDepth14; bool window18; char gap19[3];
 ListNode0025D9E3 *m_head1C;
 float x20,y24,z28;
 int pointer2c,pointer30,pointer34,pointer38;
 DisplayVideoConfig video;int word4c;DisplayTick50 tick;
 Rva0025C09E records[3];
 StringBase<unsigned short> m_sB0;
 int m_iB4,m_iB8,m_iBC;
 float m_fC0,m_fC4,m_fC8,m_fCC;
 StringBase<char> m_sD0;
 float m_fD4;bool m_bD8;char gapD9[3];int wordDC,wordE0,wordE4,wordE8,wordEC;
 DisplayTextF0 textF0; int word124;float f128,f12c,f130,f134;
 int word138,word13c;bool flag140,flag141;char gap142[2];
};

BfmeStrVM0::~BfmeStrVM0()
{
	rva0025D19E();
	((Rva0025C0FF *)this)->rva0025C0FF();
}

// ?rva0025D358@BfmeStrVM0@@QAEXV?$StringBase@G@@MMHHH@Z, retail 0x0025D358, 112 bytes.
// Sets the +0xB0 display block: Unicode string via set plus ints at +0xB4/+0xB8/+0xBC
// and floats at +0xC0/+0xC4; by-value string temp released at the end.
// Evidence: same +0xB0/+0xD0/+0xF0 layout as the dtor in this TU and ctor 0x0025D489;
// callees rowed/pinned set 0x00037150 plus releaseBuffer 0x00036E70; caller 0x00356AC1.
void BfmeStrVM0::rva0025D358(StringBase<unsigned short> s, float fC0, float fC4, int iB4, int iB8, int iBC)
{
	StringBase<unsigned short> &dst = m_sB0;
	dst.set(s);
	m_iB4 = iB4;
	m_iB8 = iB8;
	m_iBC = iBC;
	m_fC0 = fC0;
	m_fC4 = fC4;
}

// ?rva0025D9E3@BfmeStrVM0@@QAEXXZ, retail 0x0025D9E3, 116 bytes.
// Slot-9 virtual of BfmeStrVM0: when +0x114 is clear, zeroes +0xD4/+0xD8, runs
// the slot-68 virtual plus the W3DDisplay clear helper; then always clears
// +0x114/+0x120, walks the +0x1C list via slot-5 plus getNext, and zeroes
// +0xC8/+0xCC.
// Evidence: vtable slot 9 of 0x7F5DA0; same +0xB0/+0xC8/+0xD0/+0x114/+0x120
// layout as this TU and ctor 0x0025D489; callees slot-68 plus rowed
// rva0025D2F6 plus node slots 5/152; caller 0x00043427.
void BfmeStrVM0::rva0025D9E3()
{
	if (textF0.m_b114 == 0)
	{
		m_fD4 = 0.0f;
		m_bD8 = 0;
		v68();
		((W3DDisplay *)this)->rva0025D2F6();
	}
	ListNode0025D9E3 *cur = m_head1C;
	textF0.m_b114 = 0;
	textF0.m_f120 = 0.0f;
	if (cur != 0)
	{
		ListNode0025D9E3 *next;
		do
		{
			cur->v005();
			next = cur->getNext();
			cur = next;
		} while (next != 0);
	}
	m_fC8 = 0.0f;
	m_fCC = 0.0f;
}

// ?rva0025C14D@BfmeStrVM0@@UAEXXZ, retail 0x0025C14D, 62 bytes.
// Slot-38 virtual of BfmeStrVM0: unless the GameLogic mode predicate says
// otherwise with the global 0xA01E48 byte at +0x5D set, walks the +0x1C
// node list calling slot-94 on each node and advancing via getNext.
// Evidence: vtable slot 38 of 0x7F5DA0; same +0x1C list as rva0025D9E3 and
// rva0025C18B in this TU; callees rowed rva00085124 0x00085124 plus node
// slots 94/152 predeclared in this TU; no callers.
void BfmeStrVM0::rva0025C14D()
{
	if (TheGameLogic->rva00085124())
	{
		if (g_Va00A01E48->flag != 0)
			return;
	}
	ListNode0025D9E3 *node = m_head1C;
	while (node != 0)
	{
		node->s094();
		node = node->getNext();
	}
}

// ?rva0025C18B@BfmeStrVM0@@UAEXPAURva0025C18BCoord@@0@Z, retail 0x0025C18B, 173 bytes.
// Slot-39 virtual of BfmeStrVM0: walks the +0x1C node list; per node it takes
// two no-arg ints plus an out-pair, converts both float args to int for the
// first round of node slots, then replays the saved values through the same
// slots and advances via getNext.
// Evidence: vtable slot 39 of 0x7F5DA0; same +0x1C list as rva0025D9E3 in this
// TU; node slots 14-19/94/152 predeclared in this TU; no callers.
void BfmeStrVM0::rva0025C18B(Rva0025C18BCoord *a, Rva0025C18BCoord *b)
{
	ListNode0025D9E3 *node = m_head1C;
	while (node != 0)
	{
		int t15 = node->s015();
		int t17 = node->s017();
		int t8;
		int t4;
		node->s019(&t8, &t4);
		node->s014((int)b->x);
		node->s016((int)b->y);
		node->s018((int)a->x, (int)a->y);
		node->s094();
		node->s014(t15);
		node->s016(t17);
		node->s018(t8, t4);
		node = node->getNext();
	}
}

// ?rva00049F94@BfmeStrVM0@@QAEXVAsciiString@@@Z, retail 0x00049F94, 55 bytes.
// Slot-89 virtual of BfmeStrVM0: sets the +0xF0 AsciiString from a by-value
// string arg; the by-value temp is released at the end under EH.
// Evidence: vtable slot 89 of 0x7F5DA0; same +0xF0 layout as the dtor in this
// TU; callees AsciiString::operator= 0x000366F0 plus releaseBuffer 0x00036410.
void BfmeStrVM0::rva00049F94(AsciiString s)
{
	AsciiString &dst = *(AsciiString *)&textF0.text;
	dst = s;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v01@BfmeStrVM0@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v03@BfmeStrVM0@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v04@BfmeStrVM0@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?v05@BfmeStrVM0@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?v06@BfmeStrVM0@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?v08@BfmeStrVM0@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v09@BfmeStrVM0@@UAEXXZ=?rva0025D9E3@BfmeStrVM0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?v11@BfmeStrVM0@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?v14@BfmeStrVM0@@UAEXXZ=?setHeight@Display@@UAEXI@Z")
#pragma comment(linker, "/alternatename:?v15@BfmeStrVM0@@UAEXXZ=?setWidth@Display@@UAEXI@Z")
#pragma comment(linker, "/alternatename:?v16@BfmeStrVM0@@UAEXXZ=?getNext@?$CategoryModuleClass@$0A@@FXParticleSystem@@QBEPBV12@XZ")
#pragma comment(linker, "/alternatename:?v17@BfmeStrVM0@@UAEXXZ=?get@Rva001DB09DDwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?v19@BfmeStrVM0@@UAEXXZ=?get@Rva0057E556DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?v21@BfmeStrVM0@@UAEXXZ=?get@Rva004C9990ByteField@@QBEEXZ")
#pragma comment(linker, "/alternatename:?v23@BfmeStrVM0@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?v30@BfmeStrVM0@@UAEXXZ=?Set_Fog_Color@SceneClass@@UAEXABVVector3@@@Z")
#pragma comment(linker, "/alternatename:?v35@BfmeStrVM0@@UAEXXZ=?rva0025C134@BfmeStrVM0@@UAEXPAV1@@Z")
#pragma comment(linker, "/alternatename:?v36@BfmeStrVM0@@UAEXXZ=?getData@NetWrapperCommandMsg@@QAEPAEXZ")
#pragma comment(linker, "/alternatename:?v68@BfmeStrVM0@@UAEXXZ=?rva0025D19E@BfmeStrVM0@@QAEXXZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v07@BfmeStrVM0@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?v13@BfmeStrVM0@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

BfmeStrVM0::BfmeStrVM0(): widthC(0),height10(0),bitDepth14(0),window18(false),m_head1C(0),
 x20(0),y24(0),z28(0),word4c(resetVideoPointers()),
 m_iB4(0),m_iB8(0),m_iBC(0),m_fC0(0),m_fC4(0),m_fC8(0),m_fCC(0),
 wordE0(-1),wordE4(-1),m_fD4(0),m_bD8(false),wordDC(0),wordE8(0),wordEC(0),
word124(0),
 f128(0),f12c(0),f130(0),f134(0),word138(0),word13c(0),flag140(true),flag141(false)
{
 m_sD0.clear();
 InitializeCriticalSection(&DisplayMovieCriticalSection);
 ((W3DDisplay*)this)->rva0025D2F6();
 word124=0;word138=0;f128=0;f12c=0;f130=0;f134=0;
}
