// platformsdk
// ??0Display@@QAE@XZ
// partial score=1.0 date=2026-10-13
// ??0Display@@QAE@XZ
// partial score=0.9919880250725045 date=2026-10-13
// ??0Display@@QAE@XZ
// partial score=0.9919880250725045 date=2026-10-10
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
#include "../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ??0Display@@QAE@XZ
// partial score=0.925 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /I. /Oy- /DNDEBUG /MD /GX /O1 /G7 /arch:SSE
// ??1Display@@UAE@XZ, retail 0x0025D686, 111 bytes.
// Destructor of Display: stores vtable 0x7F5DA0 then runs the field-reset
// helper rva0025D19E and the list-clear rva0025C0FF on the same this, then
// destroys AsciiString at +0xF0/+0xD0 and Unicode string at +0xB0 in reverse
// order, then the SubsystemInterface base dtor (0x001B4E74).
// Evidence: same-this calls at 0x0025D6A4/0x0025D6AB; vtable shared with ctor
// 0x0025D489 which inits the same D0/E0/E4/C8/CC/F0 fields; base call
// 0x001B4E74; deleting-dtor caller 0x0025DA57.
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

class Image;
class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
	void rva0025D2F6();
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual unsigned unused16();
	virtual unsigned unused17();
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

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

extern GameLogic *TheGameLogic;

// ?g_Va00A01E48@@3PAUGlobalA01E48@@A: the global at this VA is ?TheShell@@3PAVShell@@A; this name is an alias for it.

struct Rva0025C18BCoord
{
	float x;
	float y;
};

class Rva0025C09E {public: Rva0025C09E(); char data[24];};
struct DisplayCriticalSection {LARGE_INTEGER frequency; char data[16];};
// 0x00DFE9E0 has no tree name; declared here as an address-derived global so the row links
DisplayCriticalSection g_00DFE9E0;
struct DisplayVideoConfig {
 int pointer3c,pointer40,pointer44;bool flag48;char gap49[3];
 __forceinline DisplayVideoConfig():pointer3c(0),pointer40(0),pointer44(0),flag48(false){}
};
struct DisplayTick50 {
 int tick50,word54,word58;volatile bool flag5c,flag5d;char gap5e[2];int word60;bool flag64;char gap65[3];
 __forceinline DisplayTick50():tick50(GetCurrentThreadId()),flag5d(false){word54=0;word58=0;flag5c=false;word60=0;flag64=false;}
};
struct DisplayTextF0 {
 AsciiString text;
 int wordF4,wordF8;float fFC,f100,f104,f108;bool flag10c;char gap10d[3];
 int word110;bool m_b114,flag115;char gap116[2];int word118;
 float f11c,m_f120;
 __forceinline DisplayTextF0():wordF4((_ReadWriteBarrier(),0)),wordF8(0),fFC(0),f100(0),f104(0),f108(0),flag10c(false),word110(0),m_b114(false),flag115(false),word118(0),f11c(1.0f),m_f120(0){}
};
class Display : public SubsystemInterface
{
public:
	Display();
 __forceinline int resetVideoPointers(){pointer2c=0;pointer30=0;pointer34=0;pointer38=0;return 0;}
 virtual ~Display();
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
	virtual void rva0025C238();
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
	void rva0025D358(UnicodeString s, float fC0, float fC4, int iB4, int iB8, int iBC);
	void reset();
	void rva00049F94(AsciiString s);
private:
int widthC,height10,bitDepth14; bool window18; char gap19[3];
 ListNode0025D9E3 *m_head1C;
 float x20,y24,z28;
 int pointer2c,pointer30,pointer34,pointer38;
 DisplayVideoConfig video;int word4c;DisplayTick50 tick;
 Rva0025C09E records[3];
 UnicodeString m_sB0;
 int m_iB4,m_iB8,m_iBC;
 float m_fC0,m_fC4,m_fC8,m_fCC;
 AsciiString m_sD0;
 float m_fD4;bool m_bD8;char gapD9[3];int wordDC,wordE0,wordE4,wordE8,wordEC;
 DisplayTextF0 textF0; int word124;float f128,f12c,f130,f134;
 int word138,word13c;bool flag140,flag141;char gap142[2];
};

#pragma comment(linker, "/alternatename:?v01@Display@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v03@Display@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v04@Display@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?v05@Display@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?v06@Display@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?v08@Display@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v09@Display@@UAEXXZ=?reset@Display@@QAEXXZ")
#pragma comment(linker, "/alternatename:?v11@Display@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?v14@Display@@UAEXXZ=?setHeight@Display@@UAEXI@Z")
#pragma comment(linker, "/alternatename:?v15@Display@@UAEXXZ=?setWidth@Display@@UAEXI@Z")
#pragma comment(linker, "/alternatename:?v16@Display@@UAEXXZ=?getNext@?$CategoryModuleClass@$0A@@FXParticleSystem@@QBEPBV12@XZ")
#pragma comment(linker, "/alternatename:?v17@Display@@UAEXXZ=?get@Rva001DB09DDwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?v19@Display@@UAEXXZ=?get@Rva0057E556DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?v21@Display@@UAEXXZ=?get@Rva004C9990ByteField@@QBEEXZ")
#pragma comment(linker, "/alternatename:?v23@Display@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?v30@Display@@UAEXXZ=?Set_Fog_Color@SceneClass@@UAEXABVVector3@@@Z")
#pragma comment(linker, "/alternatename:?v35@Display@@UAEXXZ=?rva0025C134@Display@@UAEXPAVView@@@Z")
#pragma comment(linker, "/alternatename:?v36@Display@@UAEXXZ=?getData@NetWrapperCommandMsg@@QAEPAEXZ")
#pragma comment(linker, "/alternatename:?v68@Display@@UAEXXZ=?rva0025D19E@Display@@QAEXXZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v07@Display@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?v13@Display@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

Display::Display(): widthC(0),height10(0),bitDepth14(0),window18(false),m_head1C(0),
 x20(0),y24(0),z28(0),word4c(resetVideoPointers()),
 m_iB4(0),m_iB8(0),m_iBC(0),m_fC0(0),m_fC4(0),m_fC8(0),m_fCC(0),
 wordE0(-1),wordE4(-1),m_fD4(0),m_bD8(false),wordDC(0),wordE8(0),wordEC(0),
word124(0),
 f128(0),f12c(0),f130(0),f134(0),word138(0),word13c(0),flag140(true),flag141(false)
{
 m_sD0.clear();
 QueryPerformanceFrequency(&g_00DFE9E0.frequency);
 ((W3DDisplay*)this)->rva0025D2F6();
 word124=0;word138=0;f128=0;f12c=0;f130=0;f134=0;
}
