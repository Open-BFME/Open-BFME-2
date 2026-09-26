// ?initAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@@Z
// partial score=0.85 date=2026-09-26
// ?initAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@@Z
// partial score=0.85 date=2026-09-26
// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Shard for SlideFromTop::initAnimateWindow: retail 0x005C55E4/208 is a framed
// /O1 body between SlideFromTop ctor 0x005C55A5 and SlideFromBottom ctor 0x005C56B4.
// Donor-verbatim ZH transcription from ProcessAnimateWindow.cpp; Top shape proved
// by sub esi,eax on restPos.y (startPos.y = restPos.y - travelDistance) with
// startPos.x = curPos.x = restPos.x; vel = m_maxVel via movss; calls winGetPosition
// 0x00313AE4, getWidth slot 0x40, winSetPosition 0x00313A9E, setAnimData 0x0053B31C.
#include "PreRTS.h"
#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"

// TU-local display slot view: getWidth at vtable slot 0x40 (16 virtuals,
// all declared-only so no vtable is emitted here).
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

// ?initAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromTop::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel;

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
	vel.x = m_maxVel.x;
	vel.y = m_maxVel.y;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}
