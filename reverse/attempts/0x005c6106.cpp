// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.998 date=2026-10-05
// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// @0x005C6106 232B. Finishing pass on the banked 0.997 body (see
// reverse/attempts/0x005c6106.cpp and the re_attempts.log rows).
// RESIDUE (232B, 3 differing lines, all ONE load-schedule swap): the frame is
// now RIGHT -- sub esp,0x14 with curPos at -0x14/-0x10, vel at -0xc/-0x8 and
// the this-save at -0x4 -- because there is NO endPos aggregate local at all:
// endPos is reduced to the single scalar the code actually needs.
// `const Int endY = animWin->getEndPos().y;` declared BEFORE getCurPos() is what
// removes the 8-byte endPos home the banked body allocated (sub esp,0x1c).
// What remains is the field-load ORDER: retail loads curPos.y [esi+0x18] first,
// then endPos.x [esi+0x14] into EDI, then curPos.x [esi+0x10]; this build loads
// curPos.x [esi+0x10] first, then [esi+0x14] into EDI, then [esi+0x18].
// MEASURED, and the constraint is a hard three-way coupling in MSVC 7.1:
// a NAMED endPos aggregate is what produces retail's exact [0x18],[0x14],[0x10]
// order (the banked body) but it necessarily also allocates the 8-byte home
// (0x1c); dropping it fixes the frame and MSVC always emits the curPos pair
// first. Neither the frame nor the order is reachable without the other.
// Refuted this pass, all at 232B with the frame STILL 0x14 unless noted:
// endPos aggregate first then curPos (v8/v9/v11/v12/v18), the aggregate with a
// (void)endPos.x (v16), const-qualified endPos (v17), non-const endY (v20), a
// dead compare pinning endY early (v21), an endPos aggregate whose .x is forced
// live (v23/v24), reading .x as a second scalar (v15), and declaring the endY
// read after getCurPos() (v19, back to 0x1c). v22 (vel between endY and curPos)
// does emit retail's load ORDER but drops the curPos.y load entirely at 228B.
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

	const Int endY = animWin->getEndPos().y;
	ICoord2D curPos = animWin->getCurPos();
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
