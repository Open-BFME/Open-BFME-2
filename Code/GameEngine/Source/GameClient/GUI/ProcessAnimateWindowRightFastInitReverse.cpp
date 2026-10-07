// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Reference: GeneralsMD ProcessAnimateWindow.cpp at BFME1 revision
// 10af19f44a89ab7ecc23195bb9a842ceafbc02c9, with target copy semantics.
// Identity: matched RightFast ctor 0x005C62D8 installs VA 0x00C748D0;
// vtable slot 2 points to this 175-byte method at RVA 0x005C631E.
// Layout: the original AnimateWindow fields agree with this retail body;
// matched getVel at 0x005C5046 separately proves Coord2D's hidden-result ABI.
// Its matched source uses a memberwise copy constructor, unlike the ZH header.
// The inner lifetime ends before setVel copies the flipped pair, permitting
// retail's stack-home reuse and three-register SSE schedule. No assembly.

#pragma optimize("y", on)
// Emit the shared compiler iterator under this TU's existing retail context.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }

// Keep source headers untouched; the target copied Coord2D nontrivially.
#define Coord2D ZHTrivialCoord2D
#include "Lib/BaseType.h"
#undef Coord2D
struct Coord2D {
    Coord2D() {}
    // Matched empty destructor: coord2d.cpp, RVA 0x000B3FD0.
    ~Coord2D() {}
    Coord2D(const Coord2D& other): x(other.x), y(other.y) {}
    float x,y;
};
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// PreRTS includes the shared STL iterator shim; restore this TU's verified
// frame-pointer setting before AnimateWindow emits its inline accessors.
#pragma optimize("y", on)
#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"
#pragma optimize("", on)

void ProcessAnimateWindowSlideFromRightFast::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D flipped;
	{
		const Coord2D& vel = animWin->getVel();
		flipped.x = vel.x * -1;
		flipped.y = vel.y * -1;
	}
	animWin->setVel(flipped);
	animWin->setFinished( FALSE );
	GameWindow * win = animWin->getGameWindow();
	ICoord2D pos, tempPos;
	win->winGetPosition(&pos.x, &pos.y);
	tempPos = animWin->getCurPos();
	tempPos.y = pos.y;
	animWin->setCurPos(tempPos);

	tempPos = animWin->getEndPos();
	tempPos.y = pos.y;
	animWin->setEndPos(tempPos);

	tempPos = animWin->getStartPos();
	tempPos.y = pos.y;
	animWin->setStartPos(tempPos);
}

// Right ctor RVA 0x005C5069 installs VA 0x00C7484C, slot 2 at
// RVA 0x005C50A8 (106 bytes). The same copy/lifetime delta applies.
void ProcessAnimateWindowSlideFromRight::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D flipped;
	{
		const Coord2D& vel = animWin->getVel();
		flipped.x = vel.x * -1;
		flipped.y = vel.y * -1;
	}
	animWin->setVel(flipped);
	animWin->setFinished( FALSE );

}

// TopFast ctor RVA 0x005C5F85 installs VA 0x00C748B4, slot 2 at
// RVA 0x005C5FC4 (102 bytes). Left/Top/Bottom vtables share this body;
// the ledger records one proven method at this address, without alias rows.
void ProcessAnimateWindowSlideFromTopFast::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D flipped;
	{
		const Coord2D& vel = animWin->getVel();
		flipped.x = vel.x * -1;
		flipped.y = vel.y * -1;
	}
	animWin->setVel(flipped);

}

// Same display view as the matched Spiral constructor: target slot 0x40.
class BFMEDisplayWidthSlot
{
public:
	virtual ~BFMEDisplayWidthSlot();
	virtual void _slot001();
	virtual void _slot002();
	virtual void _slot003();
	virtual void _slot004();
	virtual void _slot005();
	virtual void _slot006();
	virtual void _slot007();
	virtual void _slot008();
	virtual void _slot009();
	virtual void _slot010();
	virtual void _slot011();
	virtual void _slot012();
	virtual void _slot013();
	virtual void _slot014();
	virtual void _slot015();
	virtual unsigned getWidth();
};

// BottomTimed ctor 0x005C4FEF installs VA 0x00C7481C, slot 2 at
// 0x005C59AC (140 bytes); restPos +0x20/+0x24 and window +0x28 agree.
// The by-value velocity copy retains its argument home because Coord2D
// has an explicit destructor, even though that destructor has no operations.
void ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	restPos = animWin->getRestPos();
	startPos.x = restPos.x;
	curPos.y = startPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Bottom of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	endPos.x = curPos.x = restPos.x;
	endPos.y = restPos.y + travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	UnsignedInt now = timeGetTime();

	DEBUG_LOG(("initReverseAnimateWindow at %d (%d->%d)\n", now, now, now + m_maxDuration));
	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, now, now + m_maxDuration);
}

// BottomTimed ctor 0x005C4FEF installs VA 0x00C7481C, slot 1 at
// 0x005C5A38 (191 bytes). The same by-value coordinate lifetime applies.
void ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Bottom of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x;
	startPos.y = curPos.y = restPos.y + travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	UnsignedInt now = timeGetTime();
	UnsignedInt delay = animWin->getDelay();

	DEBUG_LOG(("initAnimateWindow at %d (%d->%d)\n", now, now + delay, now + m_maxDuration + delay));
	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, now + delay, now + m_maxDuration + delay);
}

// Right ctor 0x005C5069 installs VA 0x00C7484C; slot 1 is 0x005C5112 (211 bytes).
void ProcessAnimateWindowSlideFromRight::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	animWin->setFinished( FALSE );

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Right of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x + travelDistance;
	startPos.y = curPos.y = restPos.y;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel.x = m_maxVel.x;
	vel.y = 0.0f;


	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// Top ctor 0x005C55A5 installs VA 0x00C74884; slot 1 is 0x005C55E4 (208 bytes).
void ProcessAnimateWindowSlideFromTop::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Top of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x ;
	startPos.y = curPos.y = restPos.y - travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// Left ctor 0x005C52CE installs VA 0x00C7486C; slot 1 is 0x005C530D (208 bytes).
void ProcessAnimateWindowSlideFromLeft::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Left of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x - travelDistance;
	startPos.y = curPos.y = restPos.y;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// Bottom ctor 0x005C56B4 installs VA 0x00C7489C; slot 1 is 0x005C56F3 (209 bytes).
void ProcessAnimateWindowSlideFromBottom::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Bottom of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x;
	startPos.y = curPos.y = restPos.y + travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// TopFast ctor 0x005C5F85 installs VA 0x00C748B4; slot 1 is 0x005C602A (220 bytes).
void ProcessAnimateWindowSlideFromTopFast::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;
	ICoord2D size = {0,0};

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	win->winGetSize(&size.x, &size.y);

	//set the initial positions for the window. In this case, off the Top of the screen
	//Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x ;
	startPos.y = curPos.y = -size.y;//restPos.y - travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// RightFast ctor 0x005C62D8 installs VA 0x00C748D0; slot 1 is 0x005C63CD (241 bytes). Local size follows endPos to preserve retail stack homes.
void ProcessAnimateWindowSlideFromRightFast::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	ICoord2D size = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	animWin->setFinished( FALSE );

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	win->winGetSize(&size.x, &size.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Right of the screen
	Int travelDistance = reinterpret_cast<BFMEDisplayWidthSlot *>(TheDisplay)->getWidth() - restPos.x + size.x ;// / 4 * 3;
	startPos.x = curPos.x = restPos.x + travelDistance;
	startPos.y = curPos.y = restPos.y;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel.x = m_maxVel.x;
	vel.y = 0.0f;


	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// Spiral ctor 0x005C4FFF installs VA 0x00C74834; slot 1 is 0x005C5C31 (258 bytes). Explicit double math matches native _cos/_sin and avoids wrong float wrappers.
void ProcessAnimateWindowSpiral::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	ICoord2D size = {0,0};
	Coord2D vel; vel.x = 0.0f; vel.y = 0.0f;

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	win->winGetSize(&size.x,&size.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;
	//set the initial positions for the window. In this case, off the Bottom of the screen
	vel.x = 0;
	vel.y = m_maxR;
	startPos.x = curPos.x = (vel.y * cos((double)vel.x)) + endPos.x;
	startPos.y = curPos.y = (vel.y * sin((double)vel.x)) + endPos.y;


	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// Bottom ctor 0x005C56B4 installs VA 0x00C7489C; slot 4 is 0x005C58A8 (232 bytes). The donor acceleration/clamp flow matches with the proven Coord2D ABI.
Bool ProcessAnimateWindowSlideFromBottom::reverseAnimateWindow( AnimateWindow *animWin )
{

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > startPos.y)
	{
		curPos.y = startPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( curPos.y - endPos.y <= m_slowDownThreshold )
	{
		vel.y *= m_speedUpRatio;
	}
	else
	{
		vel.y = -m_maxVel.y;
	}
	if( vel.y > -m_maxVel.y)
		vel.y = -m_maxVel.y;
	animWin->setVel(vel);
	return FALSE;
}

// Bottom ctor 0x005C56B4 installs VA 0x00C7489C; slot 3 is 0x005C57C4 (228 bytes). Ratio-first multiplication and the observed clamp-home store preserve the retail schedule.
Bool ProcessAnimateWindowSlideFromBottom::updateAnimateWindow( AnimateWindow *animWin )
{

	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y < endPos.y)
	{
		curPos.y = endPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
    Real slowedY;
    if (curPos.y - endPos.y <= m_slowDownThreshold)
        slowedY = m_slowDownRatio * vel.y;
    else
        slowedY = vel.y;
    if (slowedY >= -1.0f) {
        *(volatile Real *)&vel.y = -1.0f;
        slowedY = -1.0f;
    }
    Coord2D slowedVel;
    slowedVel.x = vel.x;
    slowedVel.y = slowedY;
    animWin->setVel(slowedVel);
    return FALSE;
}
