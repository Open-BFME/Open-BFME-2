// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.999 date=2026-10-05
// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.999 date=2026-10-05
// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// @0x005C6106 232B. Finishing pass on the banked body (see
// reverse/attempts/0x005c6106.cpp and the re_attempts.log rows).
// IMPROVEMENT over the 0.998 bank: declaring getCurPos() BEFORE the endY read
// reproduces retail's exact field-load SCHEDULE -- the load-order swap that
// was the bank's residue is gone. Retail loads curPos.x [esi+0x18] first, then
// endPos.x [esi+0x14] into EDI, then curPos.x's partner [esi+0x10]; this build
// now emits that identical order. Down from 3 differing bytes to 2, and the
// whole 232B tail remains byte-identical.
// RESIDUE (232B, 2 differing bytes, first diff +0x5): the stack frame.
// Retail has sub esp,0x14 with curPos at -0x14/-0x10, the getVel out-buffer at
// -0xc/-0x8 and the this-save at -0x4. This build emits sub esp,0x1c because
// the dead endPos.x load [esi+0x10] gets its own home at -0x1c instead of
// coalescing into the getVel out-buffer slot -0xc that retail writes and then
// overwrites. So the frame size and the single dead-slot placement are ONE
// MSVC 7.1 stack-colouring decision. MEASURED AND WORSE this pass: vel between
// curPos and endY (13 diff lines), endPos-aggregate-vel-curPos (228B, wrong
// vel slots), curPos+const-ref endPos (same 2 diffs), the full endPos aggregate
// after curPos (same 2 diffs). The load-order/slot coupling the earlier rows
// recorded still holds, but from the OPPOSITE side: fixing the order costs the
// frame, and the frame needs endPos to coalesce into a slot MSVC only reuses
// when endPos is read first.
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

	ICoord2D curPos = animWin->getCurPos();
	const Int endY = animWin->getEndPos().y;
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > endY)
	{
		curPos.y = endY;
		win->winSetPosition(curPos.x, curPos.y);
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( endY - curPos.y  <= m_slowDownThreshold )
	{
		*(volatile Real *)&vel.y = m_slowDownRatio * vel.y;
	}
	if( vel.y < 1.0f)
		*(volatile Real *)&vel.y = 1.0f;
	animWin->setVel(vel);
	return FALSE;
}
