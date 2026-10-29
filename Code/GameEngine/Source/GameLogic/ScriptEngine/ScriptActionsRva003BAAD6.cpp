// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
// stlport


// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva003BAAD6@ScriptActions@@QAEXXZ @0x003BAAD6 14B: free forwarder to virtual slot 0x1A0 via global 0xDFEA3C.
// Evidence: mov ecx,[0xDFEA3C] mov eax,[ecx] jmp [eax+0x1A0]; callers 0x3CAD41 0x3CC8DF in ScriptActions dispatch with mov ecx,edi no pushes.

extern class AudioManager *TheAudio;
extern class RadarWindowOverrideSource *theRadarWindowOverrideSource;

extern class InGameUI *TheInGameUI;
extern class View *TheTacticalView;

template <class T> class StringBase;
struct Rva0033070EEntry;
class Rva0033070E
{
public:
	Rva0033070EEntry *rva0033070E(const StringBase<char> &key);
};

// WorldHeightMapParse.cpp owns this singleton at retail VA 0x00E01DB0.
// The recovered CameraAnimationList name describes that owner; this unit only
// requires the lookup view established by the call at 0x003BB141.
class CameraAnimationList;
extern CameraAnimationList *TheCameraAnimationList;
#define Rva00E01DB0 ((Rva0033070E *)TheCameraAnimationList)

class Rva003BAAD6Holder
{
public:
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026(struct Rva0033070EEntry *e);
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
    virtual void s037(bool v);
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
    virtual void s087(const AsciiString &name);
    virtual void s088();
    virtual void s089(int v);
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
    virtual void target();
};

#define Rva00DFEA3C (*(Rva003BAAD6Holder **)&TheTacticalView)
#define Rva00DFEDF0 (*(Rva003BAAD6Holder **)&TheInGameUI)
#define Rva00DFE6E8 (*(Rva003BAAD6Holder **)&TheAudio)

void ScriptActions::Rva003BAAD6()
{
    Rva00DFEA3C->target();
}

// ?Rva003BB141Notify@ScriptActions@@QAEXABV?$StringBase@D@@@Z @0x003BB141 34B chain via 0x0033070E caller 0x003CAE0D globals 0xE01DB0 0xDFEA3C slot 0x68
void ScriptActions::Rva003BB141Notify(const StringBase<char> &key)
{
	Rva0033070EEntry *cameraAnimation = Rva00E01DB0->rva0033070E(key);
	if (cameraAnimation)
		Rva00DFEA3C->s026(cameraAnimation);
}

// ?doMoviePlayRadar@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BB61E 14B free forwarder to virtual slot 0x15C via global 0xDFEDF0 caller 0x003CBBCE
void ScriptActions::doMoviePlayRadar(const AsciiString &name)
{
	Rva00DFEDF0->s087(name);
}

class RadarWindowOverrideSource
{
public:
	void rva002D3615(bool value);
};

#define Rva00DFF028 theRadarWindowOverrideSource

// ?Rva003BB7E2@ScriptActions@@QAEXXZ @0x003BB7E2 14B free caller of 0x002D3615 with false via global 0xDFF028 caller 0x003CBD39
void ScriptActions::Rva003BB7E2()
{
	Rva00DFF028->rva002D3615(false);
}

// ?Rva003BB7F0@ScriptActions@@QAEXXZ @0x003BB7F0 14B free caller of 0x002D3615 with true via global 0xDFF028 caller 0x003CBD45
void ScriptActions::Rva003BB7F0()
{
	Rva00DFF028->rva002D3615(true);
}

// ?doDisableSpecialPowerDisplay@ScriptActions@@QAEXXZ @0x003BBF8F 17B free caller of vslot 0x94 with false via global 0xDFEDF0 caller 0x003CC44C
void ScriptActions::doDisableSpecialPowerDisplay()
{
	Rva00DFEDF0->s037(false);
}

// ?doEnableSpecialPowerDisplay@ScriptActions@@QAEXXZ @0x003BBFA0 17B free caller of vslot 0x94 with true via global 0xDFEDF0 caller 0x003CC458
void ScriptActions::doEnableSpecialPowerDisplay()
{
	Rva00DFEDF0->s037(true);
}

// ?Rva003BB641@ScriptActions@@QAEXXZ @0x003BB641 19B null-guarded forwarder to vslot 0x16C via global 0xDFE6E8 caller 0x003CE42B
void ScriptActions::Rva003BB641()
{
	Rva003BAAD6Holder *audioManager = Rva00DFE6E8;
	if (audioManager)
		audioManager->s091();
}

// ?Rva003BB62C@ScriptActions@@QAEXH@Z @0x003BB62C 21B null-guarded forwarder to vslot 0x164 via global 0xDFE6E8 caller 0x003CE41F forwards stdcall int
void ScriptActions::Rva003BB62C(int roomType)
{
	Rva003BAAD6Holder *audio = Rva00DFE6E8;
	if (audio)
		audio->s089(roomType);
}

// ?Rva003BB654@ScriptActions@@QAEXXZ @0x003BB654 19B null-guarded forwarder to vslot 0x17C via global 0xDFE6E8 caller 0x003CE477
void ScriptActions::Rva003BB654()
{
	Rva003BAAD6Holder *audioSystem = Rva00DFE6E8;
	if (audioSystem)
		audioSystem->s095();
}

// ?doNamedHideSpecialPowerDisplay@ScriptActions@@QAEXPAVParameter@@@Z @0x003BBFB1 37B leaf caller 0x003CC46D globals 0xDFE16C 0xDFEDF0 slots getUnitNamed 0x9C
// Evidence: push [esp+4] mov ecx,[0xDFE16C] call ?getUnitNamed@ScriptEngine@@QAEPAVObject@@PAVParameter@@@Z test eax je then TheInGameUI vslot 0x9C with Object*.
class Object;
class Parameter;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class Rva003BBFB1Holder
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39(Object *);
};
#define Rva00DFEDF0_BFB1 (*(Rva003BBFB1Holder **)&TheInGameUI)
void ScriptActions::doNamedHideSpecialPowerDisplay(Parameter *unit)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (theObj)
		Rva00DFEDF0_BFB1->s39(theObj);
}

// ?doNamedShowSpecialPowerDisplay@ScriptActions@@QAEXPAVParameter@@@Z @0x003BBFD6 37B leaf caller 0x003CC482 globals 0xDFE16C 0xDFEDF0 slots getUnitNamed 0xA0
// Evidence: same shape as 0x003BBFB1 but InGameUI vslot 0xA0 with Object*.
class Rva003BBFD6Holder
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40(Object *);
};
#define Rva00DFEDF0_BFD6 (*(Rva003BBFD6Holder **)&TheInGameUI)
void ScriptActions::doNamedShowSpecialPowerDisplay(Parameter *unit)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (theObj)
		Rva00DFEDF0_BFD6->s40(theObj);
}

// ?Rva003BB274Ai@ScriptActions@@QAEXPAVParameter@@H@Z @0x003BB274 41B leaf caller 0x003CB376 globals 0xDFE16C callees getUnitNamed rva0026DE3B
// Evidence: push [esp+4] ScriptEngine getUnitNamed test je then [eax+0x258] test je then push [esp+8] AIUpdateInterface::rva0026DE3B ret 8.
class AIUpdateInterface
{
public:
	void rva0026DE3B(int);
};
void ScriptActions::Rva003BB274Ai(Parameter *unitName, int attitude)
{
	Object *o = TheScriptEngine->getUnitNamed(unitName);
	if (!o)
		return;
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)o + 0x258);
	if (!ai)
		return;
	ai->rva0026DE3B(attitude);
}

// ?Rva003BBF23Disable@ScriptActions@@QAEXPAVParameter@@_N@Z @0x003BBF23 46B leaf caller 0x003CC4CC globals 0xDFE16C callees getUnitNamed setDisabledUntil
// Evidence: push [esp+4] getUnitNamed test je then mov cl,[esp+8] neg cl sbb ecx,ecx and ecx,0x3FFFFFFF push ecx push 3 mov ecx,eax call setDisabledUntil ret 8.
enum DisabledType
{
	DISABLED_TYPE_3 = 3
};
class Object
{
public:
	void setDisabledUntil(DisabledType, unsigned int);
};
void ScriptActions::Rva003BBF23Disable(Parameter *unit, bool held)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (!theObj)
		return;
	theObj->setDisabledUntil(DISABLED_TYPE_3, held ? 0x3FFFFFFF : 0);
}

// ?doMilitaryCaption@ScriptActions@@QAEXHM@Z @0x003BBEF4 47B leaf caller 0x003CC3CC globals g_00BBE358 TheInGameUI slot 0x5c ceil ftol2 x87
// Evidence: fld [esp+8] fmul g_00BBE358 fstp call ceil call ftol2 then TheInGameUI vslot 0x5c with first arg and int result ret 8.
// Shape lever x87-operand-order: extern float puts const first; literal loads local first like retail. Trying 1000.0f (msec scale).
extern "C" __declspec(dllimport) double __cdecl ceil(double);
class Rva003BBEF4Holder
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23(int a1, int a2);
};
#define Rva00DFEDF0_BBEF4 (*(Rva003BBEF4Holder **)&TheInGameUI)
void ScriptActions::doMilitaryCaption(int briefing, float duration)
{
	int v = (int)ceil(duration * 1000.0f);
	Rva00DFEDF0_BBEF4->s23(briefing, v);
}
