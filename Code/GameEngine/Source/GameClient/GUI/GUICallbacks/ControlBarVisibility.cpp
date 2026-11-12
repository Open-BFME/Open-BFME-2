// stlport
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// HideControlBar 0x00402960 (299B), ShowControlBar 0x00402A8B (102B) and
// ToggleControlBar 0x00402AF1 (40B): Zero Hour ControlBar.cpp's three free
// functions, through BFME1's ControlBarVisibility.cpp donor (Open-BFME-1
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/).
//
// Target evidence: HideControlBar's name is the GameEngine::init pin; its
// body is ZH's (hideReplayControls, the ControlBar.wnd:ControlBarParent
// window, view height from the display, winHide or the reverse animation
// plus animateSpecialPowerShortcut(false), hidePurchaseScience). BFME1/2 add
// the palantir (0x00DFF028), the banner UI and an InGameUI part, each told to
// hide. ShowControlBar calls HideControlBar(true), flips the +0x29C mode
// through 0x0031AFDE when it is 0, and in mode 1 shows the same three; the
// BFME1 donor's mode-2 path is gone. ToggleControlBar hides, then shows when
// the flip returns mode 1. The palantir, banner and InGameUI part names and
// the 0x0031AFDE flip keep their address names.

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../Include/GameClient/GameWindowManager.h"

#include "../../../../Include/GameClient/View.h"

class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual Int getHeight();                                               // +0x44
	virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
	virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
	virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
	virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
	virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
	virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73();
	virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77();
	virtual void v78(); virtual void v79(); virtual void v80(); virtual void v81();
	virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85();
	virtual void setSomeViewFlag(Bool value);                             // slot 86
};

class AnimateWindowManager
{
public:
	void reverseAnimateWindow();
};

// Rowed under address-named owners: 0x0031AF54 and 0x0031AFDE take the
// control bar as ECX.
class Rva0031AF54 { public: void rva0031AF54(bool flag); };
class Rva0031AFDE { public: Int rva0031AFDE(); };

#include "../../../../Include/GameClient/ControlBar.h"

#include "../../../../Include/Common/RadarWindowOverrideSource.h"

#include "../../../../Include/GameClient/BannerUI.h"

#include "../../../../Include/Common/Rva005CB260.h"

#include "../../../../Include/GameClient/InGameUI.h"

void hideReplayControls();

extern ControlBar *TheControlBar;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern View *TheTacticalView;
extern Display *TheDisplay;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern BannerUI *TheBannerUI;
extern InGameUI *TheInGameUI;

void HideControlBar(Bool immediate)
{
	hideReplayControls();
	if (TheControlBar)
		TheControlBar->hideSpecialPowerShortcut();

	if (TheWindowManager)
	{
		Int id = (Int)TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:ControlBarParent"));
		GameWindow *window = TheWindowManager->winGetWindowFromId(0, id);

		if (window)
			TheTacticalView->setHeight(TheDisplay->getHeight());

		if (immediate)
		{
			if (window)
				window->winHide(true);
			if (TheControlBar)
				TheControlBar->hideSpecialPowerShortcut();
		}
		else if (TheControlBar)
		{
			if (TheControlBar->field10)
				TheControlBar->field10->reverseAnimateWindow();
			((Rva0031AF54 *)TheControlBar)->rva0031AF54(false);
		}

		if (TheControlBar)
			TheControlBar->hidePurchaseScience();
	}

	if (theRadarWindowOverrideSource)
		theRadarWindowOverrideSource->rva002D4240(true);
	if (TheBannerUI)
		TheBannerUI->Hide(true);
	if (TheInGameUI)
		TheInGameUI->rva000CF155()->rva005CB260(false);
}

void ShowControlBar(Bool immediate)
{
	HideControlBar(true);
	if (TheControlBar->field29C == 0)
		((Rva0031AFDE *)TheControlBar)->rva0031AFDE();
	switch (TheControlBar->field29C)
	{
	case 1:
		if (theRadarWindowOverrideSource)
			theRadarWindowOverrideSource->rva002D4240(false);
		if (TheBannerUI)
			TheBannerUI->Hide(false);
		if (TheInGameUI)
			TheInGameUI->rva000CF155()->rva005CB260(true);
		break;
	}
}

void ToggleControlBar(Bool immediate)
{
	if (TheWindowManager)
	{
		HideControlBar(true);
		switch (((Rva0031AFDE *)TheControlBar)->rva0031AFDE())
		{
		case 1:
			ShowControlBar(true);
			break;
		}
	}
}

// ?doLetterBoxMode@ScriptActions@@QAEX_N@Z @0x003BBE04, 46 retail bytes. It selects the
// existing control bar callbacks and forwards the same flag to Display slot
// 86; the action's semantic name is not established by target evidence.
void ScriptActions::doLetterBoxMode(Bool immediate)
{
	if (immediate)
	{
		HideControlBar(true);
		TheDisplay->setSomeViewFlag(true);
	}
	else
	{
		ShowControlBar(false);
		TheDisplay->setSomeViewFlag(false);
	}
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.

// Native 3BBE32..3BBE3B and 3BBE3B..3BBE44 (9B each), between the rowed
// ScriptActions::doLetterBoxMode and doBlackWhiteMode: the two control-bar halves
// of doLetterBoxMode on their own - HideControlBar(true) and
// ShowControlBar(false). Neither uses ECX, so they are written as free
// functions; whether retail had them as argument-free ScriptActions members
// is unproven. Address-derived names.
void Rva003BBE32HideControlBar()
{
	HideControlBar(true);
}

void Rva003BBE3BShowControlBar()
{
	ShowControlBar(false);
}
