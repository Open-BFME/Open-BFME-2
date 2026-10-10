// cl: /O1 /G7 /arch:SSE -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringinline -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
#include "StringInline.h"

// 0x003BE290 (104B). Load-game parchment fade: setGroup("PreParchmentMapFade_LoadGame", 0)
// on TheTransitionHandler, poke TheShell and TheWindowManager, else poll isFinished.

// Retail defines this singleton once, in
// game/GameEngine/Source/GameClient/GUI/GameWindowTransitions.cpp, as
// GameWindowTransitionsHandler *TheTransitionHandler.  Reference it by that
// class name so the mangled global is ?TheTransitionHandler@@3PAV
// GameWindowTransitionsHandler@@A, the one recorded at 0x012F3330.
class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name, bool immediate);
	void reverse(AsciiString name);
	bool isFinished(void);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

// Retail global 0x012F4B58 is EA's shell singleton, defined once under the
// canonical spelling (Shell *TheShell).
class Shell
{
public:
	void rva0035BF4C(bool shutdownImmediate);
};

// game/GameEngine/Source/Common/S3GuardedIndirectRelease.cpp owns the
// giveBack body at 0x0057F100, so the call is made through that view, exactly
// as Rva0051DD10StartBattleSchool.cpp does.
class Rva0057F100
{
public:
	void giveBack(void);
};
extern Shell *TheShell;

class WindowManager
{
public:
	void unidentified_0002e9a1(int a);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

// ?parchmentMapFadeLoadGame@@YAHH_N@Z
int parchmentMapFadeLoadGame(int, bool start)
{
	const bool startRequested = start;
	int result = 1;
	if (startRequested)
	{
		TheTransitionHandler->setGroup(AsciiString("PreParchmentMapFade_LoadGame"), 0);
		if (TheShell)
			((Rva0057F100 *)TheShell)->giveBack();
		if ((*(WindowManager **)&g_bfmeAptWindowManager))
			(*(WindowManager **)&g_bfmeAptWindowManager)->unidentified_0002e9a1(-1);
	}
	else if (TheTransitionHandler->isFinished())
		result = 3;
	return result;
}

// Native 0x002B513E..0x002B5195: sibling of the adjacent load-game fade callback.
// Shared callback thunk 0x00211216 forwards float/bool; both are unused here.
// Target alone proves PopFocus(-1), display slot+110, shell shutdown(true),
// scene slot+28(true), and reverse("SoloMordorFade_LoadGame").
// Pointer-only dispatch views preserve the canonical singleton data owners.
class AptFocusTarget;
class AptPlayer { public: void PopFocus(AptFocusTarget *); };
class Display; extern Display *TheDisplay;
class LoadGameFadeDisplayDispatch { public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2A();
	virtual void slot2B();
	virtual void slot2C();
	virtual void slot2D();
	virtual void slot2E();
	virtual void slot2F();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3A();
	virtual void slot3B();
	virtual void slot3C();
	virtual void slot3D();
	virtual void slot3E();
	virtual void slot3F();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void refresh();
};
class Rva002D3627Host; extern Rva002D3627Host *g_00DFEF18;
class LoadGameFadeSceneDispatch { public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void activate(bool);
};
int rva002B513E(float, bool)
{
	((AptPlayer *)g_bfmeAptWindowManager)->PopFocus((AptFocusTarget *)-1);
	((LoadGameFadeDisplayDispatch *)TheDisplay)->refresh();
	TheShell->rva0035BF4C(true);
	((LoadGameFadeSceneDispatch *)g_00DFEF18)->activate(true);
	TheTransitionHandler->reverse(AsciiString("SoloMordorFade_LoadGame"));
	return 2;
}

// Native2B50BD..2B513E RET0 callback; WB D8B7C0 supplies Map_Roll lead.
// Sibling51573A establishes float/bool sequencer ABI; time is unused here.
// Start sets normalized display rect before movie flag C0; finish polls slot71
// or global9AD. Movie argument placement uses the native by-value string lifetime.
class Display {public:
 virtual void v00();
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
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual bool playMovie(AsciiString,int,int,int);
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual bool rva_slot71();
 void rva002B2466(float,float,float,float);
};
extern Display *TheDisplay;
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct MapRollGlobalView {char m_pad[0x9ad];bool m_9ad;};
int rva002B50BD(float time,bool start)
{
 int result=1;
 if(start) {
  TheDisplay->rva002B2466(0.0f,0.0f,1.0f,1.0f);
  if(!TheDisplay->playMovie(AsciiString("Map_Roll"),0xc0,-1,-1)) result=3;
 } else if(TheDisplay->rva_slot71() || ((MapRollGlobalView*)TheWritableGlobalData)->m_9ad) result=3;
 return result;
}
