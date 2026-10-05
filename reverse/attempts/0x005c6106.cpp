// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.995 date=2026-10-05
// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z @0x005C6106 232B.
// Target identity: the matched ProcessAnimateWindowSlideFromTop constructor at
// 0x005C55A5 installs vptr 0x00C74884 whose slot +0x0C lands here; the body
// reads the Top velocity/threshold fields and updates the current position.
// Callee evidence is retail: winSetPosition 0x00313A9E, the out-of-line getVel
// helper 0x005C5046 (copies both components to a hidden result pointer, returns
// ret 4) and timeGetTime through the import 0x00BBA918.
// Donor body carried from BFME1 GeneralsMD revision
// 10af19f44a89ab7ecc23195bb9a842ceafbc02c9 under /O1 /arch:SSE, the tier retail's
// frame and register shape require (/O2 drops the push ebp frame and goes 177B).
//
// RESIDUE (232B, 3 differing bytes: +0x46 and +0x4F are ONE swapped field load,
// +0x56 is that load's dead-store slot). Retail's prologue load schedule is
// endPos.y (mov eax,[esi+0x18]), endPos.x (mov edi,[esi+0x14]), store endPos.x,
// curPos.x (mov eax,[esi+0x10]), store curPos.y, then the vel pushes. Declaring
// getEndPos() BEFORE getCurPos() is what reproduces the 20B frame (sub esp,0x14)
// and keeps endPos.x's dead store at [ebp-0xc]; the reverse order emits
// sub esp,0x1c and moves the store to [ebp-0x1c]. Measured alternatives that do
// NOT close it are listed in reverse/re_attempts.log: getEndPos() at each use
// with no local, vel declared first, declaration split from initialization, and
// four #pragma optimize spellings are all byte-identical to the two shapes here.
//
// The remaining byte pair is a load-scheduling difference MSVC 7.1 resolves the
// other way: it prefers the curPos loads at the first initializer and hoists the
// endPos pair, retail interleaves them. No /O1 /arch:SSE spelling tried so far
// satisfies both the frame and the schedule at once.
// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Donor revision 10af19f44a89ab7ecc23195bb9a842ceafbc02c9.
#pragma optimize("y", on)
#define Coord2D ZHTrivialCoord2D
#include "Lib/BaseType.h"
#undef Coord2D
struct Coord2D {
    Coord2D() {}
    ~Coord2D() {}
    Coord2D(const Coord2D& other): x(other.x), y(other.y) {}
    float x,y;
};
#include "PreRTS.h"
#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"
#pragma optimize("", on)

Bool ProcessAnimateWindowSlideFromTop::updateAnimateWindow( AnimateWindow *animWin )
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

	ICoord2D endPos = animWin->getEndPos();
	ICoord2D curPos = animWin->getCurPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > endPos.y)
	{
		curPos.y = endPos.y;
		win->winSetPosition(curPos.x, curPos.y);
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( endPos.y - curPos.y  <= m_slowDownThreshold )
	{
		*(volatile Real *)&vel.y = m_slowDownRatio * vel.y;
	}
	if( vel.y < 1.0f)
		*(volatile Real *)&vel.y = 1.0f;
	animWin->setVel(vel);
	return FALSE;
}
