// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?draw@W3DView@@UAEXXZ, retail 0x00087DA0, 3941 bytes. W3DView vtable 0x007C7530 slot 12:
// the entry sits on the secondary base at +0xB4, so `this` is that sub-object
// (camera +0x50, filter mode/filter +0x58/+0x5C, wireframe flags +0x60/+0x61) and
// the primary View vtable / calcDeltaScroll 0x00085FA8 run on this-0xB4.
// Zero Hour / BFME1 W3DView::draw is the donor; WB 0x0098CCC0 gives the BFME2
// statement order: scene custom pass modes 0/3/4/5/6 with the rowed screen-filter
// select 0x000756BF / dispatch 0x000756F1 (display-size Coord2D), the 0x00DFF490 (g_screenFilterPass)
// pass setter, the debug-AI path / goal (3) / waypoint (7) / bridge (2) overlays
// drawn through W3DDisplay 0x0004D664, then the post-draw iterate, ten layer
// flushes 0x0023998E and the 2D scene render 0x0006EE27.
// Byte levers: Clear's opacity through an inline getter (loaded before the 1.0f
// default); field-wise waypoint copies; double interpolation factors in the
// waypoint loop keep both factors on the x87 stack.
#include "Coord2D.h"
#include "Coord3D.h"
#include "ICoord2D.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

class CameraClass;
#include "../../../Include/W3DDevice/GameClient/RTS3DScene.h"
class RTS2DScene {
public:
	void doRender(CameraClass *camera); // 0x0006EE27 (Rva0006ED36Call.cpp)
};
class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
	static RTS2DScene *m_2DScene;
	void rva0004D664(float x0, float y0, float x1, float y1, float width, int color);
};

#define SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define SLOTS16(p) SLOTS4(p##a) SLOTS4(p##b) SLOTS4(p##c) SLOTS4(p##d)

#include "../../../../GameEngine/Include/GameClient/Display.h"

// The overlays call W3DDisplay's rowed line drawer 0x0004D664 directly.
static __forceinline void drawDisplayLine(Display *display, Real x0, Real y0, Real x1, Real y1, Real width, UnsignedInt color)
{
	((W3DDisplay *)display)->rva0004D664(x0, y0, x1, y1, width, color);
}

class BaseHeightMapRenderObjClass { public: char m_pad[0x37E8]; float m_minWaterOpacity; Real getMinOpacity() const { return m_minWaterOpacity; } };
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

#include "../../../../GameEngine/Include/Common/GameLODManager.h"
extern GameLODManager *TheGameLODManager;

int Rva00309E4BGet();
class Rva00101EC3 { public: void rva00101EC3(); };
class Rva001021F7 { public: int m_active; bool isActive() { return m_active != 0; } void run() { ((Rva00101EC3 *)this)->rva00101EC3(); } };
Rva001021F7 *Rva00102215Get();

bool Rva000756BFSelect(int filter, int skip, int mode);
bool Rva000756F1Dispatch(int filter, int mode, int delta, int extra, int size);

extern int g_screenFilterPass;
static inline void setFilterPass(int pass) { g_screenFilterPass = (pass == -1) ? g_screenFilterPass : pass; }

bool ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2, IRegion2D *clipRegion);

#include "../../../../GameEngine/Include/GameLogic/PathNode.h"
#include "../../../../GameEngine/Include/GameLogic/PathfindPath.h"
class Rva003F3FCEDwordField { public: int get() const; };
#include "../../../../GameEngine/Include/GameLogic/Rva003EFDD7LeaField.h"
#include "../../../../GameEngine/Include/GameLogic/BridgeClass.h"
class Pathfinder {
public:
	char m_pad00[0x5C];
	Bridge *m_firstBridge;
	Path *getDebugPath() { return (Path *)((Rva003F3FCEDwordField *)this)->get(); }
	const Coord3D *getDebugPathPosition() { return (const Coord3D *)((Rva003EFDD7LeaField *)this)->get(); }
	Bridge *getFirstBridge() { return m_firstBridge; }
};
class AIData007446A0;
#include "../../../../GameEngine/Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../../GameEngine/Source/GameLogic/Object/object.h"
#include "../../../../GameEngine/Include/GameClient/Drawable.h"
void drawablePostDraw(Drawable *draw, void *userData);

#include "../../../../GameEngine/Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

class Waypoint {
public:
	char m_pad00[0xC];
	Coord3D m_location;
	char m_pad18[4];
	Waypoint *m_next;
	char m_pad20[0x44 - 0x20];
	Waypoint *m_link44;
	char m_pad48[4];
	int m_numLinks;
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getNext() const { return m_next; }
	int getNumLinks() const { return m_numLinks; }
	Waypoint *getLink(int index) const;
};

class TerrainLogic {
public:
	SLOTS4(a) virtual void b0(); virtual void b1(); virtual void b2();
	virtual Real getGroundHeight(Real x, Real y, Int a, void *normal, Int b);
	SLOTS16(c) SLOTS4(d) SLOTS4(e) virtual void e9();
	virtual Waypoint *getFirstWaypoint();
};
extern TerrainLogic *TheTerrainLogic;

typedef void (*GameClientFuncPtr)(Drawable *draw, void *userData);
class GameClient {
public:
	SLOTS16(a) SLOTS4(b) SLOTS4(c) virtual void d0(); virtual void d1(); virtual void d2();
	virtual void iterateDrawables(GameClientFuncPtr func, void *userData);
	char m_pad04[0xC4 - 4];
	int m_renderedObjectCount;
	void resetRenderedObjectCount() { m_renderedObjectCount = 0; }
	void flushLayer(int layer) { ((Drawable *)this)->rva0023998E(layer); }
};
extern GameClient *TheGameClient;

class Rva00085FA8
{
public:
	void calcDeltaScroll(float *out);
	char m_pad00[0xC];
	float m_C; // +0x0C
	float m_10; // +0x10
	char m_pad14[0xF0];
	class CameraClass *m_104; // +0x104
	char m_pad108[0x22EC];
	float m_23F4; // +0x23F4
	float m_23F8; // +0x23F8
	char m_pad23FC[0xC];
	float m_2408; // +0x2408
};

#include "../../../../GameEngine/Include/GameClient/View.h"

class ViewDrawInterface {
public:
	SLOTS4(a) SLOTS4(b) SLOTS4(c)
	virtual void draw();
};

class W3DView : public View, public ViewDrawInterface {
public:
	char m_padB8[0x104 - 0xB8];
	CameraClass *m_3DCamera;
	CameraClass *m_2DCamera;
	int m_viewFilterMode;
	int m_viewFilter;
	bool m_isWireFrameEnabled;
	bool m_nextWireFrameEnabled;
	virtual void draw();
	void calcDeltaScroll(Coord2D &screenDelta) { ((Rva00085FA8 *)this)->calcDeltaScroll(&screenDelta.x); }
};

void W3DView::draw( void )
{
	Bool skipRender = false;
	Bool doExtraRender = false;
	Int origPassMode = W3DDisplay::m_3DScene->m_customPassMode;
	Int customScenePassMode = origPassMode;
	Bool preRenderResult = false;

	if (m_viewFilterMode &&
			m_viewFilter > 0 &&
			m_viewFilter < 10)
	{
		preRenderResult = Rva000756BFSelect(m_viewFilter, (int)&skipRender, (int)&customScenePassMode);
	}

	if (!skipRender)
	{
		W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)customScenePassMode);
		W3DDisplay::m_3DScene->doRender( m_3DCamera );
		W3DDisplay::m_3DScene->ExtraPassPolyRenderMode = 0;
		m_isWireFrameEnabled = m_nextWireFrameEnabled;
	}

	if (m_viewFilterMode &&
			preRenderResult &&
			m_viewFilter > 0 &&
			m_viewFilter < 10)
	{
		Coord2D deltaScroll;
		calcDeltaScroll(deltaScroll);
		Coord2D displaySize;
		displaySize.x = (Real)TheDisplay->getWidth();
		displaySize.y = (Real)TheDisplay->getHeight();
		Bool continueTheEffect = false;
		if (preRenderResult)
			continueTheEffect = Rva000756F1Dispatch(m_viewFilter, m_viewFilterMode, (int)&deltaScroll, (int)&doExtraRender, (int)&displaySize);
		if (!continueTheEffect)
		{
			m_viewFilter = 9;
			m_viewFilterMode = 15;
		}
	}

	if (doExtraRender)
	{
		DX8Wrapper::Clear(false, true, true, Vector3(0.0f,0.0f,0.0f), TheTerrainRenderObject->getMinOpacity());
		W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)0);
		W3DDisplay::m_3DScene->doRender( m_3DCamera );
		Coord2D deltaScroll;
		Coord2D displaySize;
		displaySize.x = (Real)TheDisplay->getWidth();
		displaySize.y = (Real)TheDisplay->getHeight();
		Rva000756F1Dispatch(m_viewFilter, m_viewFilterMode, (int)&deltaScroll, (int)&doExtraRender, (int)&displaySize);
	}

	Bool lowLOD = false;
	if (TheGameLODManager && TheGameLODManager->word1778 <= 1)
		lowLOD = true;

	Bool specialFilter = false;
	if (m_viewFilter == 7 || m_viewFilter == 6 || m_viewFilter == 8)
		specialFilter = true;

	if (origPassMode == 0 && specialFilter)
	{
		Bool skip = false;
		Bool always = true;
		customScenePassMode = origPassMode;
		if (m_viewFilter == 8)
			always = false;
		if (!*(char *)Rva00309E4BGet() && !always)
			skip = true;
		else
			Rva000756BFSelect(4, (int)&skip, (int)&origPassMode);
		if (!skip)
		{
			Coord2D delta;
			delta.x = 0.0f;
			delta.y = 0.0f;
			Coord2D size;
			size.x = (Real)TheDisplay->getWidth();
			size.y = (Real)TheDisplay->getHeight();
			DX8Wrapper::Clear(false, true, true, Vector3(0.0f,0.0f,0.0f), TheTerrainRenderObject->getMinOpacity());
			W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)6);
			W3DDisplay::m_3DScene->doRender( m_3DCamera );
			setFilterPass(0);
			Bool extra;
			Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
			Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
		}
		W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)0);
	}
	else if (origPassMode == 0 && Rva00102215Get()->isActive() && !lowLOD)
	{
		Rva00102215Get()->run();
	}
	else if (origPassMode == 0 && *(char *)Rva00309E4BGet() && !lowLOD)
	{
		Bool skip = true;
		Rva000756BFSelect(4, (int)&skip, (int)&origPassMode);
		if (!skip)
		{
			Coord2D delta;
			delta.x = 0.0f;
			delta.y = 0.0f;
			Coord2D size;
			size.x = (Real)TheDisplay->getWidth();
			size.y = (Real)TheDisplay->getHeight();
			DX8Wrapper::Clear(false, true, true, Vector3(0.0f,0.0f,0.0f), TheTerrainRenderObject->getMinOpacity());
			Bool extra;
			if (!((char *)Rva00309E4BGet())[0x21])
			{
				W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)3);
				if (!TheWritableGlobalData->field0D34)
					W3DDisplay::m_3DScene->doRender( m_3DCamera );
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
			}
			else
			{
				W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)6);
				W3DDisplay::m_3DScene->doRender( m_3DCamera );
				setFilterPass(0);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
				Rva000756BFSelect(4, (int)&skip, (int)&origPassMode);
				W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)4);
				W3DDisplay::m_3DScene->doRender( m_3DCamera );
				setFilterPass(1);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
				Rva000756BFSelect(4, (int)&skip, (int)&origPassMode);
				W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)5);
				W3DDisplay::m_3DScene->doRender( m_3DCamera );
				setFilterPass(2);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
				Rva000756F1Dispatch(4, 6, (int)&delta, (int)&extra, (int)&size);
			}
			W3DDisplay::m_3DScene->setCustomPassMode((CustomScenePassModes)0);
		}
	}

	if( TheWritableGlobalData->field09B8 )
	{
		// setup screen clipping region
		IRegion2D clipRegion;
		clipRegion.lo.x = 0;
		clipRegion.lo.y = 0;
		clipRegion.hi.x = getWidth();
		clipRegion.hi.y = getHeight();

		if (TheAI->pathfinder()->getDebugPath())
		{
			UnsignedInt color = 0xFFFFFF00;  //0xAARRGGBB
			ICoord2D start, end;
			PathNode *prevNode = TheAI->pathfinder()->getDebugPath()->getFirstNode();

			if (worldToScreenTriReturn( prevNode->getPosition(), &start ) == 0) {
				drawDisplayLine( TheDisplay, start.x-3, start.y-3, start.x+3, start.y-3, 1.0f, color );
				drawDisplayLine( TheDisplay, start.x+3, start.y-3, start.x+3, start.y+3, 1.0f, color );
				drawDisplayLine( TheDisplay, start.x+3, start.y+3, start.x-3, start.y+3, 1.0f, color );
				drawDisplayLine( TheDisplay, start.x-3, start.y+3, start.x-3, start.y-3, 1.0f, color );
			}
			for( PathNode *node = prevNode->getNext(); node; node = node->getNext() )
			{
				Int k;
				Coord3D s, e;
				Coord3D delta;
				s = *node->getPosition();
				e = *prevNode->getPosition();
				delta.x = e.x-s.x;
				delta.y = e.y-s.y;
				delta.z = e.z-s.z;
				color = 0xFFFFFF00;
				if (node->getLayer() == 16)
					color = 0xFF0000FF;
				else if (node->getLayer() > 1 && node->getLayer() < 16)
					color = 0xFF00FFFF;
				for (k = 0; k<10; k++) {
					Real factor1 = (k)/10.0;
					Real factor2 = (k+1)/10.0;
					s = *node->getPosition();
					e = *node->getPosition();
					s.x += delta.x*factor1;
					s.y += delta.y*factor1;
					s.z += delta.z*factor1;
					e.x += delta.x*factor2;
					e.y += delta.y*factor2;
					e.z += delta.z*factor2;
					Bool onScreen1 = worldToScreenTriReturn( &e, &end ) == 0;
					Bool onScreen2 = worldToScreenTriReturn( &s, &start ) == 0;
					if (!onScreen1 && !onScreen2) {
						continue; // neither point visible.
					}
					ICoord2D clipStart, clipEnd;

					if( ClipLine2D( &start, &end, &clipStart, &clipEnd, &clipRegion ) ) {
						drawDisplayLine( TheDisplay, clipStart.x, clipStart.y, clipEnd.x, clipEnd.y, 1.0f, color );
					}
				}
				prevNode = node;
				if (node->getNext()) {
					if (worldToScreenTriReturn( node->getPosition(), &start ) == 0) {
						drawDisplayLine( TheDisplay, start.x-4, start.y, start.x+3, start.y, 1.0f, color );
					}
				}
			}
			color = 0xFFFFFF00;
			if (prevNode && worldToScreenTriReturn( prevNode->getPosition(), &start ) == 0) {
				drawDisplayLine( TheDisplay, start.x-4, start.y, start.x+3, start.y, 1.0f, color );
				drawDisplayLine( TheDisplay, start.x, start.y-4, start.x, start.y+3, 1.0f, color );
			}
			color = 0xFFFF0000;  //0xAARRGGBB
			const Coord3D *debugPos = TheAI->pathfinder()->getDebugPathPosition();
			if (worldToScreenTriReturn( debugPos, &start ) == 0) {
				drawDisplayLine( TheDisplay, start.x-3, start.y, start.x+3, start.y, 1.0f, color );
				drawDisplayLine( TheDisplay, start.x, start.y-3, start.x, start.y+3, 1.0f, color );
			}
		}

		if (TheWritableGlobalData->field09B8 == 3 && TheInGameUI->getSelectCount() == 1)
		{
			Object *obj = TheInGameUI->getFirstSelectedDrawable()->getObject();
			Coord3D goalPos, pathPos;
			if (obj->GetGoalPosition(&goalPos) && obj->GetPathfinderPos(&pathPos))
			{
				goalPos.z = TheTerrainLogic->getGroundHeight(goalPos.x, goalPos.y, 1, 0, 1);
				pathPos.z = TheTerrainLogic->getGroundHeight(pathPos.x, pathPos.y, 1, 0, 1);
				ICoord2D start, end, clipStart, clipEnd;
				UnsignedInt color = 0xFF00FF00;
				Bool onScreen1 = worldToScreenTriReturn( &goalPos, &start ) == 0;
				Bool onScreen2 = worldToScreenTriReturn( &pathPos, &end ) == 0;
				if ((onScreen1 || onScreen2) && ClipLine2D( &start, &end, &clipStart, &clipEnd, &clipRegion ))
					drawDisplayLine( TheDisplay, clipStart.x, clipStart.y, clipEnd.x, clipEnd.y, 1.0f, color );
			}
		}

		if (TheWritableGlobalData->field09B8 == 7)
		{
			IRegion2D clipRegion;
			clipRegion.lo.x = 0;
			clipRegion.lo.y = 0;
			clipRegion.hi.x = getWidth();
			clipRegion.hi.y = getHeight();
			for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext())
			{
				for (Int i = -1; i < way->getNumLinks(); i++)
				{
					Waypoint *link = (i < 0) ? way->m_link44 : way->getLink(i);
					if (!link)
						continue;
					Coord3D s, e, delta;
					const Coord3D *sp = way->getLocation();
					s.x = sp->x; s.y = sp->y; s.z = sp->z;
					const Coord3D *ep = link->getLocation();
					e.x = ep->x; e.y = ep->y; e.z = ep->z;
					delta.x = e.x - s.x;
					delta.y = e.y - s.y;
					delta.z = e.z - s.z;
					for (Int k = 0; k < 10; k++)
					{
						double factor1 = k/10.0;
						double factor2 = (k+1)/10.0;
						s = *way->getLocation();
						e = *way->getLocation();
						s.x += delta.x*factor1;
						s.y += delta.y*factor1;
						s.z += delta.z*factor1;
						e.x += delta.x*factor2;
						e.y += delta.y*factor2;
						e.z += delta.z*factor2;
						ICoord2D start, end;
						Bool onScreen1 = worldToScreenTriReturn( &e, &end ) == 0;
						Bool onScreen2 = worldToScreenTriReturn( &s, &start ) == 0;
						if (!onScreen1 && !onScreen2)
							continue;
						ICoord2D clipStart, clipEnd;
						if (ClipLine2D( &start, &end, &clipStart, &clipEnd, &clipRegion ))
							drawDisplayLine( TheDisplay, clipStart.x, clipStart.y, clipEnd.x, clipEnd.y, 1.0f, i < 0 ? 0xFFFF0000 : 0xFFFFFF00 );
					}
				}
			}
		}

		if (TheWritableGlobalData->field09B8 == 2)
		{
			IRegion2D clipRegion;
			clipRegion.lo.x = 0;
			clipRegion.lo.y = 0;
			clipRegion.hi.x = getWidth();
			clipRegion.hi.y = getHeight();
			for (Bridge *bridge = TheAI->pathfinder()->getFirstBridge(); bridge; bridge = bridge->getNext())
			{
				Rva0027C36A info;
				bridge->getBridgeInfo(&info);
				for (Int i = 0; i < 3; i++)
				{
					Coord3D from, to;
					UnsignedInt color = 0xFFFF0000;
					if (i == 0) {
						from = info.from;
						to = info.to;
					} else if (i == 1) {
						color = 0xFF00FF00;
						from = info.fromLeft;
						to = info.fromRight;
					} else {
						color = 0xFF00FF00;
						from = info.toLeft;
						to = info.toRight;
					}
					ICoord2D start, end;
					Bool onScreen1 = worldToScreenTriReturn( &to, &end ) == 0;
					Bool onScreen2 = worldToScreenTriReturn( &from, &start ) == 0;
					if (!onScreen1 || !onScreen2)
						continue;
					ICoord2D clipStart, clipEnd;
					if (ClipLine2D( &start, &end, &clipStart, &clipEnd, &clipRegion ))
						drawDisplayLine( TheDisplay, clipStart.x, clipStart.y, clipEnd.x, clipEnd.y, 1.0f, color );
				}
			}
		}
	}  // end if, show debug AI

	TheGameClient->resetRenderedObjectCount();
	TheGameClient->iterateDrawables( drawablePostDraw, this );

	for (Int layer = 0; layer < 10; layer++)
		TheGameClient->flushLayer(layer);

	// Render 2D scene
	W3DDisplay::m_2DScene->doRender( m_2DCamera );
}
