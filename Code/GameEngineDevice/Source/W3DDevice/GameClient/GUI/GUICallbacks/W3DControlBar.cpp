// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Zero Hour W3DControlBar.cpp's control-bar draw callbacks, BFME 2 build.
// Each address is named by its entry in the window draw-callback lexicon.
//
// W3DCameoMovieDraw @0x0009DC61 (141B): ZH body. TheInGameUI's
// cameoVideoBuffer is vtable slot +0x170 and TheDisplay's drawVideoBuffer
// (slot +0x104) takes Real corners plus a trailing color (-1), so the Int
// window rectangle converts at the call.
//
// W3DLeftHUDDraw @0x0009DCEE (248B): ZH body. The local player is read
// inline (PlayerList +0x10), TheInGameUI's videoBuffer is slot +0x164, the
// radar flags are TheRadar +0x10 (hidden) and +0x11 (forced) and
// Radar::draw (slot +0x1C) takes a trailing color (-1) like drawVideoBuffer.
//
// W3DRightHUDDraw @0x0009DDE6 (27B): ZH body; ZH's W3DGameWinDefaultDraw is
// the rowed GameWindow method 0x0009DC32 in BFME 2 (the window's own draw,
// else its +0x218 draw delegate). winGetStatus is the pinned out-of-line
// getter 0x0030F45F.
//
// W3DCommandBarTopDraw @0x0009DF9A (67B): ZH body. ZH's third early-out test
// !ThePlayerList->getLocalPlayer()->isPlayerActive() is the rowed PlayerList
// helper 0x002A7DD0 (local player at +0x10, negated active test), reached by
// a tail jump because every path returns.
//
// W3DCommandBarBackgroundDraw @0x0009FA82 (225B): ZH body. The scheme
// manager is TheControlBar +0x44; ZH's getBackgroundMarkerPos is the rowed
// ControlBar copy-out 0x0031AEAE. The static winNamekey and basePos share
// guard 0x00DE60F0 (bits 1 and 2); basePos's guard bit is set with no
// initializer code, the mark of an empty inline ICoord2D constructor.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

enum
{
	WIN_STATUS_IMAGE = 0x00000080
};

#define BitTest(x, i) (((x) & (i)) != 0)

class WinInstanceData;
class VideoBuffer;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStatus(void);
	Bool winIsHidden(void);
	Int rva0009DC32(WinInstanceData *instData);
};

class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);   // +0xF0
};

class Player
{
public:
	Bool hasRadar(void) const;
};

class PlayerList
{
public:
	Player *getLocalPlayer(void) { return m_local; }

private:
	char m_pad00[0x10];
	Player *m_local;   // +0x10
};

class Radar
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual void draw(Int pixelX, Int pixelY, Int width, Int height, UnsignedInt color = 0xFFFFFFFF);   // +0x1C

	Bool isRadarHidden(void) { return m_radarHidden; }
	Bool isRadarForced(void) { return m_radarForceOn; }

private:
	char m_pad04[0x10 - 0x04];
	Bool m_radarHidden;    // +0x10
	Bool m_radarForceOn;   // +0x11
};

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88();
	virtual VideoBuffer *videoBuffer(void);   // +0x164
	virtual void v90(); virtual void v91();
	virtual VideoBuffer *cameoVideoBuffer(void);   // +0x170
};

class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64();
	virtual void drawVideoBuffer(VideoBuffer *buffer, Real startX, Real startY,
		Real endX, Real endY, UnsignedInt color = 0xFFFFFFFF);   // +0x104
};

class Rva002A7DD0
{
public:
	Int rva002A7DD0(void);
};

struct ICoord2D
{
	ICoord2D() {}
	Int x;
	Int y;
};

class ControlBarSchemeManager
{
public:
	void drawBackground(ICoord2D offset);
};

class ControlBar
{
public:
	ControlBarSchemeManager *getControlBarSchemeManager(void) { return m_controlBarSchemeManager; }
	void rva0031AEAE(Int *x, Int *y);   // ZH getBackgroundMarkerPos

private:
	char m_pad00[0x44];
	ControlBarSchemeManager *m_controlBarSchemeManager;   // +0x44
};

extern InGameUI *TheInGameUI;
extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern Radar *TheRadar;
extern ControlBar *TheControlBar;

void W3DLeftHUDDraw(GameWindow *window, WinInstanceData *instData)
{
	Player *player = ThePlayerList->getLocalPlayer();
	VideoBuffer *video = TheInGameUI->videoBuffer();
	if (video)
	{
		ICoord2D pos, size;
		window->winGetScreenPosition(&pos.x, &pos.y);
		window->winGetSize(&size.x, &size.y);

		TheDisplay->drawVideoBuffer(video, pos.x, pos.y, pos.x + size.x, pos.y + size.y);
	}
	else if (TheRadar->isRadarForced() || (TheRadar->isRadarHidden() == false && player->hasRadar()))
	{
		ICoord2D pos, size;
		window->winGetScreenPosition(&pos.x, &pos.y);
		window->winGetSize(&size.x, &size.y);
		TheRadar->draw(pos.x + 1, pos.y + 1, size.x - 2, size.y - 2);
	}
}

void W3DCameoMovieDraw(GameWindow *window, WinInstanceData *instData)
{
	VideoBuffer *video = TheInGameUI->cameoVideoBuffer();
	if (video)
	{
		ICoord2D pos, size;
		window->winGetScreenPosition(&pos.x, &pos.y);
		window->winGetSize(&size.x, &size.y);

		TheDisplay->drawVideoBuffer(video, pos.x, pos.y, pos.x + size.x, pos.y + size.y);
	}
}

void W3DRightHUDDraw(GameWindow *window, WinInstanceData *instData)
{
	if (BitTest(window->winGetStatus(), WIN_STATUS_IMAGE))
		window->rva0009DC32(instData);
}

void W3DCommandBarTopDraw(GameWindow *window, WinInstanceData *instData)
{
	GameWindow *win = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
	if (!win || win->winIsHidden() || ((Rva002A7DD0 *)ThePlayerList)->rva002A7DD0())
		return;
}

void W3DCommandBarBackgroundDraw(GameWindow *window, WinInstanceData *instData)
{
	ControlBarSchemeManager *man = TheControlBar->getControlBarSchemeManager();
	if (!man)
		return;
	static NameKeyType winNamekey = TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker"));
	GameWindow *win = TheWindowManager->winGetWindowFromId(0, winNamekey);
	static ICoord2D basePos;
	if (!win)
		return;
	TheControlBar->rva0031AEAE(&basePos.x, &basePos.y);
	ICoord2D pos, offset;
	win->winGetScreenPosition(&pos.x, &pos.y);
	offset.x = pos.x - basePos.x;
	offset.y = pos.y - basePos.y;

	man->drawBackground(offset);
}
