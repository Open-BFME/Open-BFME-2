// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Shard for Spiral::updateAnimateWindow: retail 0x005C5D33 is a framed
// manual-prologue body; the home TU builds this family under /G7 and emits a
// different shape, so this body lives here under /O1. Donor-verbatim home
// transcription (matches BFME1 reverse shape); getVel is out-of-line (call)
// and setVel/setCurPos inline to stores.
#include "PreRTS.h"
#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"

// ?updateAnimateWindow@ProcessAnimateWindowSpiral@@UAE_NPAVAnimateWindow@@@Z @0x005C5D33
Bool ProcessAnimateWindowSpiral::updateAnimateWindow( AnimateWindow *animWin )
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

	curPos.x = (vel.y * cos(vel.x)) + endPos.x;
	curPos.y = (vel.y * sin(vel.x)) + endPos.y;

	vel.x = vel.x + m_deltaTheta;
	vel.y -=5;

	ICoord2D size;
	win->winGetSize(&size.x, &size.y);
	Int halfWidth = size.y / 2;
	Int halfHeight = size.x / 2;
	Int *m_max = halfHeight < halfWidth ? &halfHeight : &halfWidth;

	if(vel.y < *m_max)
	{
		ICoord2D restPos = animWin->getRestPos();
		animWin->setFinished( TRUE );
		win->winSetPosition(restPos.x, restPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	Coord2D storedVel = {vel.x, vel.y};
	animWin->setVel(storedVel);
	return FALSE;
}
