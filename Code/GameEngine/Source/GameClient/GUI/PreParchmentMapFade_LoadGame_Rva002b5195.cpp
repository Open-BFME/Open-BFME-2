// cl: /O1 /G7 /arch:SSE -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

// 0x003BE290 (104B). Load-game parchment fade: setGroup("PreParchmentMapFade_LoadGame", 0)
// on TheTransitionHandler, poke TheShell and TheWindowManager, else poll isFinished.

// Retail defines this singleton once, in
// game/GameEngine/Source/GameClient/GUI/GameWindowTransitions.cpp, as
// GameWindowTransitionsHandler *TheTransitionHandler.  Reference it by that
// class name so the mangled global is ?TheTransitionHandler@@3PAV
// GameWindowTransitionsHandler@@A, the one recorded at 0x012F3330.
#include "../../../Include/GameClient/GameWindowTransitionsHandler.h"
extern GameWindowTransitionsHandler *TheTransitionHandler;

#include "../../../Include/GameClient/Shell.h"
#include "../../../Include/GameClient/Display.h"

// game/GameEngine/Source/Common/S3GuardedIndirectRelease.cpp owns the
// giveBack body at 0x0057F100, so the call is made through that view, exactly
// as Rva0051DD10StartBattleSchool.cpp does.
#include "../../../Include/Common/Rva0035BD3F.h"

class ModuleData;
#include "../../../Include/GameClient/Rva00223CBD.h"
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
			((Rva0035BD3F *)TheShell)->rva0035BD3F();
		if ((*(Rva00223CBD **)&g_bfmeAptWindowManager))
			(*(Rva00223CBD **)&g_bfmeAptWindowManager)->rva00223CBD((const ModuleData *)-1);
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
#include "../../../../Libraries/Source/Apt/AptPlayerClass.h"
class Rva002D3627Host; class LivingWorld; extern LivingWorld *TheLivingWorld;
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
	TheDisplay->stopMovie();
	TheShell->rva0035BF4C(true);
	((LoadGameFadeSceneDispatch *)((Rva002D3627Host *)TheLivingWorld))->activate(true);
	TheTransitionHandler->reverse(AsciiString("SoloMordorFade_LoadGame"));
	return 2;
}

// Native2B50BD..2B513E RET0 callback; WB D8B7C0 supplies Map_Roll lead.
// Sibling51573A establishes float/bool sequencer ABI; time is unused here.
// Start sets normalized display rect before movie flag C0; finish polls slot71
// or global9AD. Movie argument placement uses the native by-value string lifetime.
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct MapRollGlobalView {char m_pad[0x9ad];bool m_9ad;};
int rva002B50BD(float time,bool start)
{
 int result=1;
 if(start) {
  TheDisplay->rva002B2466(0.0f,0.0f,1.0f,1.0f);
  if(!TheDisplay->rva0025C97E(AsciiString("Map_Roll"),0xc0,-1,-1)) result=3;
 } else if(TheDisplay->slot71() || ((MapRollGlobalView*)TheWritableGlobalData)->m_9ad) result=3;
 return result;
}
