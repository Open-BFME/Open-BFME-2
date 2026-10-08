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
//
// W3DCommandBarForegroundDraw @0x0009FB63 (225B): ZH body, the background
// draw's twin: guard 0x00DE6100, ZH's getForegroundMarkerPos is the rowed
// ControlBar copy-out 0x0031AE93 and the offset goes to
// ControlBarSchemeManager::drawForeground 0x0031FA9A.
//
// W3DCommandBarGridDraw @0x0009DE26 (372B): ZH body. W3DGameWinDefaultDraw
// is the rowed GameWindow draw 0x0009DC32, the border color is TheControlBar
// +0x22C and Display::drawLine is the out-of-line W3DDisplay wrapper
// 0x0004D664 (begin/line/end), called on TheDisplay.
//
// W3DPowerDraw @0x0009E365 (951B): ZH body. ZH's observer-or-local player
// choice is the rowed PlayerList helper 0x002A7E14 (local player unless it
// is inactive, then TheControlBar's observed player); the Energy is embedded
// at Player +0x1BC; the power-bar fields are TheGlobalData +0xBC0 (base),
// +0xBC4 (intervals) and +0xBC8 (yellow range); logN is the rowed
// log-ratio helper 0x0009DE01; winDrawImage is TheWindowManager slot +0x108
// and the clip calls are TheDisplay slots +0xA8 and +0xB0.
//
// W3DPowerDrawA @0x0009E71C (1649B): ZH body, the unused end-capped power
// bar that follows W3DPowerDraw (its PowerBar*EndL/EndR/center images name
// it), with the same BFME 2 player, Energy and settings deltas.
//
// W3DCommandBarGenExpDraw @0x0009ED8D (827B): ZH body. Player skill points
// are a Real at +0x14 (level up/down Ints at +0x28/+0x2C), so the progress
// percentage is computed in float; isPlayerActive is the pinned 0x002AA231.
//
// W3DDrawMapPreview @0x0009DFDD (904B): ZH body, trimmed in BFME 2: no
// default draw or skinny border without map data or after the preview, and
// no tech/supply markers; a second enabled image (+0x54) is drawn under the
// first. The Real-coordinate drawFillRect, drawLine and drawImage are the
// out-of-line display wrappers 0x0004263F, 0x0004D664 and 0x0004D6B3,
// called on TheDisplay. The by-value Region3D goes through its out-of-line
// copy constructor 0x0009AC04, with the argument-temp shape of a class with
// a destructor.
//
// W3DCommandBarHelpPopupDraw @0x0009F796 (719B): ZH body unchanged; the
// Helpbox images share guard 0x00DE60E0.
//
// drawSkinnyBorder @0x0009F0C8 (1742B): ZH body unchanged (Frame*
// edge and corner images), drawing through the Real-coordinate drawImage
// wrapper 0x0004D6B3 on TheDisplay.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef Int Color;
typedef unsigned char UnsignedByte;

#include "ascii_string.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

enum
{
	WIN_STATUS_IMAGE = 0x00000080
};

#define BitTest(x, i) (((x) & (i)) != 0)
#define INT_TO_REAL(x) ((Real)(x))

class WinInstanceData;
class VideoBuffer;
class Image;
struct IRegion2D;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

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
	Int winSetEnabledBorderColor(Int index, Color color);
	void *winGetUserData(void);
	Image *winGetEnabledImage(Int index) { return m_enabledDrawData[index].image; }
	UnsignedInt winGetStatus(void);
	Bool winIsHidden(void);
	Int rva0009DC32(WinInstanceData *instData);

private:
	struct WinDrawData
	{
		Image *image;
		Color color;
		Color borderColor;
	};
	char m_pad00[0x48];
	WinDrawData m_enabledDrawData[2];   // +0x48
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
	virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65();
	virtual void winDrawImage(const Image *image, Int startX, Int startY,
		Int endX, Int endY, Color color = 0xFFFFFFFF);   // +0x108
};

class Energy
{
public:
	Int getProduction(void) const { return m_energyProduction; }
	Int getConsumption(void) const { return m_energyConsumption; }

private:
	char m_pad00[0x04];
	Int m_energyProduction;    // +0x04
	Int m_energyConsumption;   // +0x08
};

class Player
{
public:
	Bool hasRadar(void) const;
	Bool isPlayerActive(void) const;
	Energy *getEnergy(void) { return &m_energy; }
	Real getSkillPoints(void) const { return m_skillPoints; }
	Int getSkillPointsLevelUp(void) const { return m_levelUp; }
	Int getSkillPointsLevelDown(void) const { return m_levelDown; }

private:
	char m_pad00[0x14];
	Real m_skillPoints;   // +0x14
	char m_pad18[0x28 - 0x18];
	Int m_levelUp;        // +0x28
	Int m_levelDown;      // +0x2C
	char m_pad30[0x1BC - 0x30];
	Energy m_energy;      // +0x1BC
};

class BfmeMemberRV;

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV(void);   // PlayerList: local player, else the observed one
};

struct GlobalData
{
	char m_pad000[0xBC0];
	Int m_powerBarBase;          // +0xBC0
	Real m_powerBarIntervals;    // +0xBC4
	Int m_powerBarYellowRange;   // +0xBC8
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
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
	virtual void v40(); virtual void v41();
	virtual void setClipRegion(IRegion2D *region);   // +0xA8
	virtual void v43();
	virtual void enableClipping(Bool onoff);         // +0xB0
	virtual void v45(); virtual void v46(); virtual void v47();
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
	Bool rva002A7DD0(void);
};

struct ICoord2D
{
	ICoord2D() {}
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Image
{
public:
	Int getImageWidth(void) const { return m_imageSize.x; }
	Int getImageHeight(void) const { return m_imageSize.y; }

private:
	char m_pad00[0x24];
	ICoord2D m_imageSize;   // +0x24
};

class ControlBarSchemeManager
{
public:
	void drawForeground(ICoord2D offset);
	void drawBackground(ICoord2D offset);
};

class ControlBar
{
public:
	ControlBarSchemeManager *getControlBarSchemeManager(void) { return m_controlBarSchemeManager; }
	void rva0031AE93(Int *x, Int *y);   // ZH getForegroundMarkerPos
	void rva0031AEAE(Int *x, Int *y);   // ZH getBackgroundMarkerPos
	Color getBorderColor(void) { return m_borderColor; }

private:
	char m_pad00[0x44];
	ControlBarSchemeManager *m_controlBarSchemeManager;   // +0x44
	char m_pad48[0x22C - 0x48];
	Color m_borderColor;                                  // +0x22C
};

class W3DDisplay
{
public:
	void rva0004D664(Real startX, Real startY, Real endX, Real endY,
		Real lineWidth, Color lineColor);   // ZH Display::drawLine
	void rva0004D6B3(Image *image, Real startX, Real startY, Real endX, Real endY,
		Color color = 0xFFFFFFFF, Int mode = 2);   // ZH Display::drawImage (DRAW_IMAGE_ALPHA)
};

class Rva0004263F
{
public:
	void rva0004263F(Real startX, Real startY, Real width, Real height,
		Color color);   // ZH Display::drawFillRect
};

struct Region3D
{
	Region3D() {}
	Region3D(const Region3D &that);
	~Region3D() {}
	Real width(void) const { return hi.x - lo.x; }
	Real height(void) const { return hi.y - lo.y; }
	Coord3D lo;
	Coord3D hi;
};

class MapMetaData
{
public:
	char m_pad00[0x08];
	Region3D m_extent;   // +0x08
};

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void findDrawPositions(Int startX, Int startY, Int width, Int height, Region3D extent,
	ICoord2D *ul, ICoord2D *lr);

extern InGameUI *TheInGameUI;
extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern Radar *TheRadar;
extern ControlBar *TheControlBar;
extern ImageCollection *TheMappedImageCollection;
extern GlobalData *TheGlobalData;

float Rva0009DE01Get(float value, float base);   // ZH logN

void W3DLeftHUDDraw(GameWindow *window, WinInstanceData *instData)
{
	Player *player = ThePlayerList->m_local;
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

void W3DCommandBarForegroundDraw(GameWindow *window, WinInstanceData *instData)
{
	ControlBarSchemeManager *man = TheControlBar->getControlBarSchemeManager();
	if (!man)
		return;

	static NameKeyType winNamekey = TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker"));
	GameWindow *win = TheWindowManager->winGetWindowFromId(0, winNamekey);
	static ICoord2D basePos;
	if (!win)
		return;
	TheControlBar->rva0031AE93(&basePos.x, &basePos.y);
	ICoord2D pos, offset;
	win->winGetScreenPosition(&pos.x, &pos.y);
	offset.x = pos.x - basePos.x;
	offset.y = pos.y - basePos.y;

	man->drawForeground(offset);
}

void W3DCommandBarGridDraw(GameWindow *window, WinInstanceData *instData)
{
	if (BitTest(window->winGetStatus(), WIN_STATUS_IMAGE))
	{
		window->rva0009DC32(instData);
		return;
	}

	ICoord2D pos, size;
	window->winGetScreenPosition(&pos.x, &pos.y);
	window->winGetSize(&size.x, &size.y);

	Color color = TheControlBar->getBorderColor();
	window->winSetEnabledBorderColor(0, color);
	window->rva0009DC32(instData);

	((W3DDisplay *)TheDisplay)->rva0004D664(pos.x, pos.y + size.y * .33, pos.x + size.x, pos.y + size.y * .33, 1, color);
	((W3DDisplay *)TheDisplay)->rva0004D664(pos.x, pos.y + size.y * .66, pos.x + size.x, pos.y + size.y * .66, 1, color);
	((W3DDisplay *)TheDisplay)->rva0004D664(pos.x + size.x * .33, pos.y, pos.x + size.x * .33, pos.y + size.y, 1, color);
	((W3DDisplay *)TheDisplay)->rva0004D664(pos.x + size.x * .66, pos.y, pos.x + size.x * .66, pos.y + size.y, 1, color);
}

void W3DPowerDraw(GameWindow *window, WinInstanceData *instData)
{
	static const Image *centerBarYellow = TheMappedImageCollection->findImageByName("PowerPointY");
	static const Image *centerBarRed = TheMappedImageCollection->findImageByName("PowerPointR");
	static const Image *centerBarGreen = TheMappedImageCollection->findImageByName("PowerPointG");
	const Image *centerBar = 0;
	static const Image *slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	Player *player = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();

	if (!player || !TheGlobalData)
		return;
	Energy *energy = player->getEnergy();
	if (energy == 0)
		return;

	Int consumption = energy->getConsumption();
	Int production = energy->getProduction();

	ICoord2D pos, size;
	window->winGetScreenPosition(&pos.x, &pos.y);
	window->winGetSize(&size.x, &size.y);

	static Real pixelsPerInterval = size.x / TheGlobalData->m_powerBarIntervals;
	Int delta = TheGlobalData->m_powerBarYellowRange;

	if ((consumption > energy->getProduction() - delta) && (consumption <= energy->getProduction()))
		centerBar = centerBarYellow;
	else if (consumption > production)
		centerBar = centerBarRed;
	else
		centerBar = centerBarGreen;
	if (!slider || !centerBar)
		return;

	Int range;
	range = Rva0009DE01Get(production, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
	if (range >= size.x)
		range = size.x;

	// draw the center repeating bar
	Int centerWidth, pieces;
	centerWidth = range;
	if (centerWidth > 0)
	{
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageWidth();
		ICoord2D start, end;
		start.x = pos.x;
		start.y = pos.y;
		end.y = start.y + size.y;
		for (Int i = 0; i < pieces; i++)
		{
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage(centerBar, start.x, start.y, end.x, end.y);
			start.x += centerBar->getImageWidth();
		}

		// draw the last piece clipped to the window
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = pos.x + size.x;
		reg.hi.y = pos.y + size.y;
		centerWidth = pos.x + size.x - start.x;
		if (centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage(centerBar, start.x, start.y, end.x, end.y);
			TheDisplay->enableClipping(false);
		}
	}
	Int posXstart;
	Int posXend;
	Real consumptionForNeedle = (consumption == 1) ? 1.5f : INT_TO_REAL(consumption);   // log(1) == 0
	range = Rva0009DE01Get(consumptionForNeedle, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
	if (centerWidth <= 0 && range <= 0)
		return;
	if (range >= size.x)
	{
		posXstart = pos.x + size.x - slider->getImageWidth();
		posXend = pos.x + size.x;
	}
	else
	{
		posXstart = pos.x + range - slider->getImageWidth() / 2;
		posXend = pos.x + range + slider->getImageWidth() / 2;
	}
	if (posXstart <= pos.x)
	{
		posXstart = pos.x;
		posXend = pos.x + slider->getImageWidth();
	}
	TheWindowManager->winDrawImage(slider, posXstart, pos.y + size.y - slider->getImageHeight(), posXend, pos.y + size.y);
}

void W3DPowerDrawA( GameWindow *window, WinInstanceData *instData )
{
	static const Image *endBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellowEndR");
	static const Image *beginBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellowEndL");
	static const Image *centerBarYellow = TheMappedImageCollection->findImageByName("PowerBarYellow");
	static const Image *endBarRed = TheMappedImageCollection->findImageByName("PowerBarRedEndR");
	static const Image *beginBarRed = TheMappedImageCollection->findImageByName("PowerBarRedEndL");
	static const Image *centerBarRed = TheMappedImageCollection->findImageByName("PowerBarRed");
	static const Image *endBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreenEndR");
	static const Image *beginBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreenEndL");
	static const Image *centerBarGreen = TheMappedImageCollection->findImageByName("PowerBarGreen");
	const Image *endBar = 0;
	const Image *beginBar = 0;
	const Image *centerBar = 0;
	static const Image *slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	Player *player = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
	


	if(!player || !TheGlobalData)
		return;
	Energy *energy = player->getEnergy();
	if( energy == 0 )
		return;

	Int consumption = energy->getConsumption();
	Int production = energy->getProduction();	

	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );

	static Real pixelsPerInterval = size.x / TheGlobalData->m_powerBarIntervals;
	Int delta = TheGlobalData->m_powerBarYellowRange;
	
	if((consumption > energy->getProduction() - delta) && (consumption <= energy->getProduction()))
	{
		// 6 and 1 is Green, 6 and 2 is yellow, 6 and 6 is yellow
		endBar = endBarYellow;
		beginBar = beginBarYellow;
		centerBar = centerBarYellow;
	}
	else if( consumption > production)
	{
		endBar = endBarRed;
		beginBar = beginBarRed;
		centerBar = centerBarRed;
	}
	else
	{
		endBar = endBarGreen;
		beginBar = beginBarGreen;
		centerBar = centerBarGreen;
	}
	//slider = TheMappedImageCollection->findImageByName("PowerBarSlider");
	if( !slider || !endBar || !beginBar || !centerBar)
		return;

	Int range;
	range = Rva0009DE01Get(production, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
	if(range >= size.x)
		range = size.x;
	if(range < endBar->getImageWidth() + beginBar->getImageWidth())
		range = endBar->getImageWidth() + beginBar->getImageWidth();



	// get image sizes for the ends
	ICoord2D leftSize, rightSize, start, end;
	leftSize.x = beginBar->getImageWidth();
	leftSize.y = beginBar->getImageHeight();
	rightSize.x = endBar->getImageWidth();
	rightSize.y = endBar->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D leftEnd, rightStart;
	leftEnd.x = pos.x + leftSize.x;
	leftEnd.y = pos.y + size.y;
	rightStart.x = pos.x + range - rightSize.x;
	rightStart.y = pos.y;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = pos.x;
		start.y = pos.y;
		end.y = leftEnd.y;
		end.x = pos.x + range/2;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.y = rightStart.y;
		start.x = end.x;
		end.x = pos.x + range;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageWidth();

		// draw the pieces
		start.x = leftEnd.x;
		start.y = pos.y;
		end.y = start.y + size.y; //centerImage->getImageHeight() + yOffset;
		for( Int i = 0; i < pieces; i++ )
		{

			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar, 
																			start.x, start.y,
																			end.x, end.y );
			start.x += centerBar->getImageWidth();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = rightStart.x;
		reg.hi.y = end.y;
		centerWidth = rightStart.x - start.x;
		if( centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.x = start.x + centerBar->getImageWidth();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			TheDisplay->enableClipping(false);
		}

		// draw left end
		start.x = pos.x;
		start.y = pos.y;
		end = leftEnd;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start = rightStart;
		end.x = start.x + rightSize.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	Int posXstart;
	Int posXend;
	Real consumptionForNeedle = (consumption == 1) ? 1.5f : INT_TO_REAL(consumption);//Log(1) == 0, but we need to show something for 1 power used.
	range = Rva0009DE01Get(consumptionForNeedle, TheGlobalData->m_powerBarBase) * (size.x / TheGlobalData->m_powerBarIntervals);
	if(range >= size.x)
	{
		posXstart = pos.x + size.x - slider->getImageWidth();
		posXend = pos.x + size.x;
	}
	else
	{
		posXstart = pos.x + range - slider->getImageWidth()/2;
		posXend = pos.x + range + slider->getImageWidth()/2;
	}
	if(posXstart <=pos.x)
	{
		posXstart	 = pos.x;
		posXend	= pos.x + slider->getImageWidth();
	}
	TheWindowManager->winDrawImage(slider, posXstart, pos.y + size.y - slider->getImageHeight(), posXend, pos.y + size.y);
}

void W3DCommandBarGenExpDraw( GameWindow *window, WinInstanceData *instData )
{
	Player *player = ThePlayerList->m_local;
	if(!player->isPlayerActive())
		return;
	static const Image *endBar = TheMappedImageCollection->findImageByName("GenExpBarTop1");
	static const Image *beginBar = TheMappedImageCollection->findImageByName("GenExpBarBottom1");
	static const Image *centerBar = TheMappedImageCollection->findImageByName("GenExpBar1");
	Int progress;
	progress = ((player->getSkillPoints() - player->getSkillPointsLevelDown()) * 100) /(player->getSkillPointsLevelUp() - player->getSkillPointsLevelDown());
	
	if(progress <= 0)
		return;

	// GS This should never be necessary, but scripts can change the points required or even disable a level.
	// A disabled level will be -1 for points required.  Just be totally safe and bind to 100, and we will
	// fix the scripts to bind the points gained later.
	if( progress > 100 )
		progress = 100;

	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );



	if( !endBar || !beginBar || !centerBar)
		return;

	Int range;
	range = size.y * progress / 100;


	// get image sizes for the ends
	ICoord2D topSize, bottomSize, start, end;
	bottomSize.x = beginBar->getImageWidth();
	bottomSize.y = beginBar->getImageHeight();
	topSize.x = endBar->getImageWidth();
	topSize.y = endBar->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D bottomEnd, topStart;
	bottomEnd.x = pos.x + size.x;
	bottomEnd.y = pos.y + size.y - bottomSize.y;
	topStart.x = pos.x;
	topStart.y = pos.y +size.y - range - topSize.y;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = bottomEnd.y - topStart.y;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = pos.x;
		start.y = pos.y + size.y - bottomSize.y;
		end.y = pos.y + size.y;
		end.x = pos.x + size.x;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.y = pos.y + size.y - bottomSize.y - topSize.y;
		start.x = pos.x;
		end.x = pos.x + size.x;
		end.y = start.y + topSize.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageHeight();

		// draw the pieces
		start.x = pos.x;
		start.y = topStart.y;
		end.x = start.x + size.x; //centerImage->getImageHeight() + yOffset;
		for( Int i = 0; i < pieces; i++ )
		{

			end.y = start.y + centerBar->getImageHeight();
			TheWindowManager->winDrawImage( centerBar, 
																			start.x, start.y,
																			end.x, end.y );
			start.y += centerBar->getImageHeight();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = bottomEnd.x;
		reg.hi.y = bottomEnd.y;
		centerWidth = bottomEnd.y - start.y;
		if( centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.y = start.y + centerBar->getImageHeight();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			TheDisplay->enableClipping(false);
		}

		// draw left end
		end.x = pos.x + size.x;
		end.y = pos.y + size.y;
		start.x = pos.x;
		start.y = bottomEnd.y;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.x = pos.x;
		start.y = pos.y +size.y - range;
		end.x = pos.x + size.x;
		end.y = pos.y +size.y - range - topSize.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}

}

void W3DDrawMapPreview(GameWindow *window, WinInstanceData *instData)
{
	MapMetaData *mmData = (MapMetaData *)window->winGetUserData();
	Int pixelX, pixelY, width, height;
	window->winGetScreenPosition(&pixelX, &pixelY);
	window->winGetSize(&width, &height);
	if (!mmData)
		return;

	//
	// given a upper left corner at pixelX|Y and a width and height to draw into, figure out
	// where we should start and end the image so that the final drawn image has the
	// same ratio as the map and isn't stretched or distorted
	//
	ICoord2D ul, lr;
	findDrawPositions(pixelX, pixelY, width, height, mmData->m_extent, &ul, &lr);

	// draw black border areas where we need map
	Color fillColor = GameMakeColor(0, 0, 0, 255);
	Color lineColor = GameMakeColor(50, 50, 50, 255);

	if (mmData->m_extent.width() / width >= mmData->m_extent.height() / height)
	{
		// draw horizontal bars at top and bottom
		((Rva0004263F *)TheDisplay)->rva0004263F(pixelX, pixelY, width, ul.y - pixelY - 1, fillColor);
		((Rva0004263F *)TheDisplay)->rva0004263F(pixelX, lr.y + 1, width, pixelY + height - lr.y - 1, fillColor);
		((W3DDisplay *)TheDisplay)->rva0004D664(pixelX, ul.y, pixelX + width, ul.y, 1, lineColor);
		((W3DDisplay *)TheDisplay)->rva0004D664(pixelX, lr.y + 1, pixelX + width, lr.y + 1, 1, lineColor);
	}
	else
	{
		// draw vertical bars to the left and right
		((Rva0004263F *)TheDisplay)->rva0004263F(pixelX, pixelY, ul.x - pixelX - 1, height, fillColor);
		((Rva0004263F *)TheDisplay)->rva0004263F(lr.x + 1, pixelY, width - (lr.x - pixelX) - 1, height, fillColor);
		((W3DDisplay *)TheDisplay)->rva0004D664(ul.x, pixelY, ul.x, pixelY + height, 1, lineColor);
		((W3DDisplay *)TheDisplay)->rva0004D664(lr.x + 1, pixelY, lr.x + 1, pixelY + height, 1, lineColor);
	}

	if (!BitTest(window->winGetStatus(), WIN_STATUS_IMAGE) || !window->winGetEnabledImage(0))
		((Rva0004263F *)TheDisplay)->rva0004263F(ul.x, ul.y, lr.x - ul.x, lr.y - ul.y, lineColor);
	else
	{
		if (window->winGetEnabledImage(1))
			((W3DDisplay *)TheDisplay)->rva0004D6B3(window->winGetEnabledImage(1), ul.x, ul.y, lr.x, lr.y);
		((W3DDisplay *)TheDisplay)->rva0004D6B3(window->winGetEnabledImage(0), ul.x, ul.y, lr.x, lr.y);
	}
}

void W3DCommandBarHelpPopupDraw( GameWindow *window, WinInstanceData *instData )
{
	
	static const Image *endBar = TheMappedImageCollection->findImageByName("Helpbox-top");
	static const Image *beginBar = TheMappedImageCollection->findImageByName("Helpbox-bottom");
	static const Image *centerBar = TheMappedImageCollection->findImageByName("Helpbox-middle");
	
	ICoord2D pos, size;
	window->winGetScreenPosition( &pos.x, &pos.y );
	window->winGetSize( &size.x, &size.y );



	if( !endBar || !beginBar || !centerBar)
		return;
	

//	Int range;
//	range = size.y;


	// get image sizes for the ends
	ICoord2D topSize, bottomSize, start, end;
	bottomSize.x = beginBar->getImageWidth();
	bottomSize.y = beginBar->getImageHeight();
	topSize.x = endBar->getImageWidth();
	topSize.y = endBar->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D bottomEnd, topStart;
	bottomEnd.x = pos.x + size.x;
	bottomEnd.y = pos.y + size.y - bottomSize.y;
	topStart.x = pos.x;
	topStart.y = pos.y +size.y - topSize.y;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = size.y - topSize.y - bottomSize.y;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = pos.x;
		start.y = pos.y + size.y - bottomSize.y;
		end.y = pos.y + size.y;
		end.x = pos.x + size.x;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.y = pos.y + size.y - bottomSize.y - topSize.y;
		start.x = pos.x;
		end.x = pos.x + size.x;
		end.y = start.y + topSize.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerBar->getImageHeight();

		// draw the pieces
		start.x = pos.x;
		start.y = pos.y + topSize.y ;
		end.x = start.x + size.x; //centerImage->getImageHeight() + yOffset;
		for( Int i = 0; i < pieces; i++ )
		{

			end.y = start.y + centerBar->getImageHeight();
			TheWindowManager->winDrawImage( centerBar, 
																			start.x, start.y,
																			end.x, end.y );
			start.y += centerBar->getImageHeight();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = pos.x + size.x;
		reg.hi.y = pos.y + size.y - bottomSize.y;
		centerWidth = pos.y + size.y - bottomSize.y - start.y;
		if( centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.y = start.y + centerBar->getImageHeight();
			TheWindowManager->winDrawImage( centerBar,
																			start.x, start.y,
																			end.x, end.y );
			TheDisplay->enableClipping(false);
		}

		// draw left end
		end.x = pos.x + size.x;
		end.y = pos.y + size.y;
		start.x = pos.x;
		start.y = pos.y + size.y - bottomSize.y;
		TheWindowManager->winDrawImage(beginBar, start.x, start.y, end.x, end.y);

		// draw right end
		start.x = pos.x;
		start.y = pos.y ;
		end.x = pos.x + size.x;
		end.y = pos.y + topSize.y;
		TheWindowManager->winDrawImage(endBar, start.x, start.y, end.x, end.y);
	}
	

}

void drawSkinnyBorder( Int x, Int y, Int width, Int height)
{

	enum
	{
		BORDER_CORNER_SIZE	= 5,
		BORDER_LINE_SIZE		= 5,
	};
	Int Offset = 2;
	Int OffsetLower = 5;

	// save original x, y
	Int originalX = x;
	Int originalY = y;
	Int maxX = x + width;
	Int maxY = y + height;
	Int x2, y2;			// used for simultaneous drawing of line pairs
	Int size = 5;
	Int halfSize = size / 2;
	Image *image1, *image2;
	// Draw Horizontal Lines
	// All border pieces are based on a 10 pixel offset from the centerline
	y = originalY - Offset;
	y2 = maxY - OffsetLower;
	x2 = maxX - (OffsetLower + BORDER_LINE_SIZE);
	image1 = (Image *)TheMappedImageCollection->findImageByName("FrameT");
	image2 = (Image *)TheMappedImageCollection->findImageByName("FrameB");
	for( x=(originalX + 3); x <= x2; x += BORDER_LINE_SIZE )
	{

		((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
													 x, y, x + size, y + size );
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image2,
													 x, y2, x + size, y2 + size );

	}

	x2 = maxX - 5;//BORDER_CORNER_SIZE;

	// x == place to draw remainder if any
	if( (x2 - x) >= (BORDER_LINE_SIZE / 2) )
	{
		
		//Blit Half piece
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
													 x, y, x + halfSize, y + size );
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image2,
													 x, y2, x + halfSize, y2 + size );

		x += (BORDER_LINE_SIZE / 2);

	}

	// x2 - x ... must now be less than a half piece
	// check for equals and if not blit an adjusted half piece border pieces have
	// a two pixel repeat so we will blit one pixel over if necessary to line up
	// the art, but we'll cover-up the overlap with the corners
	if( x < x2 )
	{
		x -= ((BORDER_LINE_SIZE / 2) - (((x2 - x) + 1) & ~1));

		//Blit Half piece
		((W3DDisplay *)TheDisplay)->rva0004D6B3(image1,
													 x, y, x + halfSize, y + size );
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image2,
													 x, y2, x + halfSize, y2 + size );

	}

	// Draw Vertical Lines
	// All border pieces are based on a 10 pixel offset from the centerline
	image1 = (Image *)TheMappedImageCollection->findImageByName("FrameL");
	image2 = (Image *)TheMappedImageCollection->findImageByName("FrameR");

	x = originalX - Offset;
	x2 = maxX - OffsetLower;
	y2 = maxY - (OffsetLower + BORDER_LINE_SIZE);

	for( y=(originalY + 3); y <= y2; y += BORDER_LINE_SIZE )
	{

		((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
													 x, y, x + size, y + size );
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image2,
													 x2, y, x2 + size, y + size );

	}

	y2 = maxY - OffsetLower;//BORDER_CORNER_SIZE;

	// y == place to draw remainder if any
	if( (y2 - y) >= (BORDER_LINE_SIZE / 2) )
	{

		//Blit Half piece
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
													 x, y, x + size, y + halfSize );
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image2,
													 x2, y, x2 + size, y + halfSize );

		y += (BORDER_LINE_SIZE / 2);
	}

	// y2 - y ... must now be less than a half piece
	// check for equals and if not blit an adjusted half piece border pieces have
	// a two pixel repeat so we will blit one pixel over if necessary to line up
	// the art, but we'll cover-up the overlap with the corners
	if( y < y2 )
	{
		y -= ((BORDER_LINE_SIZE / 2) - (((y2 - y) + 1) & ~1));

		//Blit Half piece
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
													 x, y, x + size, y + halfSize );
		((W3DDisplay *)TheDisplay)->rva0004D6B3( image2,
													 x2, y, x2 + size, y + halfSize );

	}

	// Draw Corners
	x = originalX - 2;//BORDER_CORNER_SIZE ;
	y = originalY - 2;//BORDER_CORNER_SIZE;
	image1 = (Image *)TheMappedImageCollection->findImageByName("FrameCornerUL");
	((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
												 x, y, x + size, y + size );
	x = maxX - 5;//BORDER_CORNER_SIZE;
	y = originalY - 2;//BORDER_CORNER_SIZE;
	image1 = (Image *)TheMappedImageCollection->findImageByName("FrameCornerUR");
	((W3DDisplay *)TheDisplay)->rva0004D6B3(image1,
												 x, y, x + size, y + size );
	x = originalX - 2;//BORDER_CORNER_SIZE;
	y = maxY - 5;//BORDER_CORNER_SIZE;
	image1 = (Image *)TheMappedImageCollection->findImageByName("FrameCornerLL");
	((W3DDisplay *)TheDisplay)->rva0004D6B3( image1,
												 x, y, x + size, y + size );
	x = maxX - 5;//BORDER_CORNER_SIZE;
	y = maxY - 5;//BORDER_CORNER_SIZE;
	image1 = (Image *)TheMappedImageCollection->findImageByName("FrameCornerLR");
	((W3DDisplay *)TheDisplay)->rva0004D6B3(image1,
												 x, y, x + size, y + size );


}
