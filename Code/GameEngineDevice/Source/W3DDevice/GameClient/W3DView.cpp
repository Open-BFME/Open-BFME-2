// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// W3DView::setViewFilterPos 0x00085F12 (26B),
// ScreenMotionBlurFilter::setZoomToPos 0x0008553B (24B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
//
// The viewport setters (setHeight 0x00087AF4, setWidth 0x00087B81, setOrigin
// 0x00087C55) are the donor bodies as written, placed by retail's W3DView
// vftable: they sit 3, 5 and 1 slots before the View::getOrigin entry, and
// their own calls reach setWidth and setHeight at slots 0x38 and 0x40.
// Retail differs from the BFME 1 donor in two places: TheDisplay's getWidth and
// getHeight are vtable slots 0x40 and 0x44, not 0x2C and 0x30, and the unit is
// built /arch:SSE, which the int-to-float conversions in setHeight and
// setWidth show (cvtsi2ss/divss) while the unsigned display sizes stay x87.
//
// setPitch (0x0008D1DD), screenToWorldAtZ (0x0008A0E5) and Add_Camera_Shake
// (0x000875F2) were found by compiling the whole donor unit with these flags
// and searching its bodies in game.dat: each places once, at a W3DView vftable
// entry. Their callees setCameraTransform, getPickRay and
// CameraShakeSystemClass::Add_Camera_Shake are pinned from those call sites.
#define Matrix4x4 Matrix4  // BFME renamed it
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DView.cpp //////////////////////////////////////////////////////////////////////////////
//
// W3D implementation of the game view class.  This view allows us to have
// a "window" into the game world that can change its width, height as 
// well as camera positioning controls
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <windows.h>

// BFME added this nonvirtual notifier after the shared Zero Hour declaration;
// injecting it on this TU's first include keeps the vendored header unchanged.
#define forceUnfreezeTime(argument) notifyCameraChange(argument); void forceUnfreezeTime(argument)
#include "GameLogic/ScriptEngine.h"
#undef forceUnfreezeTime

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "Common/BuildAssistant.h"
#include "Common/GlobalData.h"
#include "Common/Module.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingSort.h"
#include "Common/PerfTimer.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"

#include "GameClient/Color.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Image.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Line2D.h"
#include "GameClient/SelectionInfo.h"
#include "GameClient/Shell.h"
#include "GameClient/TerrainVisual.h"
#include "GameClient/Water.h"

#include "GameLogic/AI.h"			///< For AI debug (yes, I'm cheating for now)
#include "GameLogic/AIPathfind.h"			///< For AI debug (yes, I'm cheating for now)
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Object.h"
#include "GameLogic/TerrainLogic.h"									///< @todo This should be TerrainVisual (client side)
#include "Common/AudioEventInfo.h"

#include "W3DDevice/Common/W3DConvert.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#define moveCameraAlongWaypointPath(a, b, c, d, e, f) moveCameraAlongWaypointPath(a, b, c, d, e, f); void moveCameraOrLocatorAlongSplinePathInit(Waypoint *, Int, Int, Real, Real, Real, Bool)
#include "W3DDevice/GameClient/W3DView.h"
#undef moveCameraAlongWaypointPath
#include "D3dx8math.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"

#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Light.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Coltype.h"
#include "WW3D2/PredLod.h"
#include "WW3D2/WW3D.h"

#include "W3DDevice/GameClient/camerashakesystem.h"

#include "WinMain.h"  /** @todo Remove this, it's only here because we
													are using timeGetTime, but we can remove that
													when we have our own timer */
// BFME adds View and Display virtuals that the shared Zero Hour headers omit;
// these scoped views preserve the witnessed slots and +0x104 camera offset.
class BfmeW3DViewViewportVtable
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setWidth(Int width);
	virtual Int getWidth();
	virtual void setHeight(Int height);
	virtual Int getHeight();
};

class BfmeDisplayViewportVtable
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual UnsignedInt getWidth();
	virtual UnsignedInt getHeight();
};

struct BfmeW3DViewViewportFields
{
	void *m_vtable;
	unsigned char m_padding04[0x14];
	Int m_width;
	Int m_height;
	Int m_originX;
	Int m_originY;
	unsigned char m_padding28[0x104 - 0x28];
	CameraClass *m_3DCamera;
};

// BFME inserted view state that the shared Zero Hour header does not expose;
// keeping its witnessed offsets here prevents that ABI from leaking to other TUs.
struct BfmeCameraCoord2D
{
	Real x;
	Real y;
};

struct BfmeCameraCoord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmeCameraRegion2D
{
	BfmeCameraCoord2D lo;
	BfmeCameraCoord2D hi;
};

struct BfmeW3DViewCameraFields
{
	unsigned char m_padding0000[0x0C];
	BfmeCameraCoord3D m_pos;
	unsigned char m_padding0018[0x44 - 0x18];
	bool m_applyCameraConstraints;
	unsigned char m_padding0045[0x6C - 0x45];
	Real m_FOV;
	unsigned char m_padding0070[0x104 - 0x70];
	CameraClass *m_3DCamera;
	unsigned char m_padding0108[0x23C8 - 0x108];
	bool m_cameraHasMovedSinceRequest;
	unsigned char m_padding23C9[0x23FC - 0x23C9];
	BfmeCameraRegion2D m_cameraConstraint;
	bool m_cameraConstraintValid;

	const BfmeCameraCoord3D *getPosition() const { return &m_pos; }
	void setPosition(const BfmeCameraCoord3D *position) { m_pos = *position; }
};

// These debug-camera fields are present in BFME but absent from the shared
// Zero Hour GlobalData definition used by this translation unit.
struct BfmeGlobalDataCameraFields
{
	unsigned char m_padding0000[0xA28];
	Real m_maxCameraHeight;
	unsigned char m_padding0A2C[0xED0 - 0xA2C];
	bool m_debugCamera;
	unsigned char m_padding0ED1[3];
	Real m_debugCameraFOV;
	Real m_debugCameraAngle;
};

#define BFME_UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9(); virtual void prefix##a(); virtual void prefix##b(); \
	virtual void prefix##c(); virtual void prefix##d(); virtual void prefix##e(); virtual void prefix##f()

// BFME's terrain primary vtable places updateCenter at slot 0x21c, three
// entries after the Zero Hour declaration included above.
class BfmeTerrainCameraUpdateVtable
{
public:
	BFME_UNUSED_VIRTUALS_16(slot000_);
	BFME_UNUSED_VIRTUALS_16(slot040_);
	BFME_UNUSED_VIRTUALS_16(slot080_);
	BFME_UNUSED_VIRTUALS_16(slot0c0_);
	BFME_UNUSED_VIRTUALS_16(slot100_);
	BFME_UNUSED_VIRTUALS_16(slot140_);
	BFME_UNUSED_VIRTUALS_16(slot180_);
	BFME_UNUSED_VIRTUALS_16(slot1c0_);
	virtual void slot200();
	virtual void slot204();
	virtual void slot208();
	virtual void slot20c();
	virtual void slot210();
	virtual void slot214();
	virtual void slot218();
	virtual void updateCenter(CameraClass *camera, RefRenderObjListIterator *lights);
};

#undef BFME_UNUSED_VIRTUALS_16

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// 30 fps
extern Int TheW3DFrameLengthInMsec; // default is 33msec/frame == 30fps. but we may change it depending on sys config.
static const Int MAX_REQUEST_CACHE_SIZE = 40;	// Any size larger than 10, or examine code below for changes. jkmcd.
static const Real DRAWABLE_OVERSCAN = 75.0f;


#define TERRAIN_SAMPLE_SIZE 40.0f


//-------------------------------------------------------------------------------------------------
/** @todo This is inefficient. We should construct the matrix directly using vectors. */
//-------------------------------------------------------------------------------------------------
#define MIN_CAPPED_ZOOM (0.5f) //WST 10.19.2002. JSC integrated 5/20/03.
// Retail W3DView::buildCameraTransform (0x00741D30) is implemented in W3DViewBuildCameraTransformBfme.cpp.

// Retail W3DView::calcCameraConstraints (0x00740CF0) is implemented in W3DViewCalcCameraConstraintsBfme.cpp.

//-------------------------------------------------------------------------------------------------
/** Returns a world-space ray originating at a given screen pixel position
	and ending at the far clip plane for current camera.  Screen coordinates
	assumed in absolute values relative to full display resolution.*/
//-------------------------------------------------------------------------------------------------
class BFMERetailW3DViewInterface
{
public:
	virtual void unused00(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused0C(void) = 0;
	virtual void unused10(void) = 0;
	virtual void unused14(void) = 0;
	virtual void unused18(void) = 0;
	virtual void unused1C(void) = 0;
	virtual void unused20(void) = 0;
	virtual void unused24(void) = 0;
	virtual void unused28(void) = 0;
	virtual void unused2C(void) = 0;
	virtual void unused30(void) = 0;
	virtual void unused34(void) = 0;
	virtual void unused38(void) = 0;
	virtual Int getWidth(void) = 0;
	virtual void unused40(void) = 0;
	virtual Int getHeight(void) = 0;
};


#if defined(_DEBUG) || defined(_INTERNAL)


void drawDrawableExtents( Drawable *draw, void *userData );

  // end drawDrawableExtents


void drawAudioLocations( Drawable *draw, void *userData );


#endif


//-------------------------------------------------------------------------------------------------
/** Sets the height of the viewport, while maintaining original camera perspective. */
//-------------------------------------------------------------------------------------------------
void W3DView::setHeight(Int height)
{
	BfmeW3DViewViewportFields *fields = (BfmeW3DViewViewportFields *)this;
	BfmeW3DViewViewportVtable *view = (BfmeW3DViewViewportVtable *)this;
	fields->m_height = height;

	Vector2 vMin,vMax;
	fields->m_3DCamera->Set_Aspect_Ratio((Real)view->getWidth()/(Real)height);
	fields->m_3DCamera->Get_Viewport(vMin,vMax);
	vMax.Y=(Real)(fields->m_originY+height)/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getHeight();
	fields->m_3DCamera->Set_Viewport(vMin,vMax);
}

//-------------------------------------------------------------------------------------------------
/** Sets the width of the viewport, while maintaining original camera perspective. */
//-------------------------------------------------------------------------------------------------
void W3DView::setWidth(Int width)
{
	BfmeW3DViewViewportFields *fields = (BfmeW3DViewViewportFields *)this;
	BfmeW3DViewViewportVtable *view = (BfmeW3DViewViewportVtable *)this;
	fields->m_width = width;

	Vector2 vMin,vMax;
	fields->m_3DCamera->Set_Aspect_Ratio((Real)width/(Real)view->getHeight());
	fields->m_3DCamera->Get_Viewport(vMin,vMax);
	vMax.X=(Real)(fields->m_originX+width)/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getWidth();
	fields->m_3DCamera->Set_Viewport(vMin,vMax);
	fields->m_3DCamera->Set_View_Plane((Real)width/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getWidth()*DEG_TO_RADF(50.0f),-1);
}

//-------------------------------------------------------------------------------------------------
/** Sets location of top-left view corner on display */
//-------------------------------------------------------------------------------------------------
void W3DView::setOrigin( Int x, Int y)
{
	BfmeW3DViewViewportFields *fields = (BfmeW3DViewViewportFields *)this;
	BfmeW3DViewViewportVtable *view = (BfmeW3DViewViewportVtable *)this;
	fields->m_originX = x;
	fields->m_originY = y;

	Vector2 vMin,vMax;

	fields->m_3DCamera->Get_Viewport(vMin,vMax);
	vMin.X=(Real)x/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getWidth();
	vMin.Y=(Real)y/(Real)((BfmeDisplayViewportVtable *)TheDisplay)->getHeight();
	fields->m_3DCamera->Set_Viewport(vMin,vMax);

	view->setWidth(fields->m_width);
	view->setHeight(fields->m_height);
}

//-------------------------------------------------------------------------------------------------
/** Rotate the view around the horizontal (X) axis to the given angle. */
//-------------------------------------------------------------------------------------------------
void W3DView::setPitch( Real angle )
{
	View::setPitch( angle );

	unsigned char *view_bytes = reinterpret_cast<unsigned char *>(this);
	view_bytes[0x1DC] = 0;
	view_bytes[0x204] = 0;
	view_bytes[0x27C] = 0;
	view_bytes[0x228] = 0;
	view_bytes[0x27D] = 0;
	setCameraTransform();
}

//-------------------------------------------------------------------------------------------------
/** Transformt he screen pixel coord passed in, to a world coordinate at the specified
	* z value */
//-------------------------------------------------------------------------------------------------
void W3DView::screenToWorldAtZ( const ICoord2D *s, Coord3D *w, Real z )
{
	Vector3 rayStart, rayEnd;

	getPickRay(s, &rayStart, &rayEnd);
	if (rayStart.Z - z < 120.0f)
		z = rayStart.Z - 120.0f;
	w->x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
	w->y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
	w->z = z;
}

void W3DView::Add_Camera_Shake (const Coord3D & position,float radius,float duration,float power) //WST added 11/13/02
{
	Vector3 vpos;

	vpos.X = position.x;
	vpos.Y = position.y;
	vpos.Z = position.z;

	(*(CameraShakeSystemClass **)&CameraShakerSystem)->Add_Camera_Shake(
		vpos, radius, duration, power);
}

//-------------------------------------------------------------------------------------------------
/** Sets the view filter mode. */
//-------------------------------------------------------------------------------------------------
void W3DView::setViewFilterPos(const Coord3D *pos)
{
	ScreenMotionBlurFilter::setZoomToPos(pos);
}



// BFME's CameraClass keeps ZFar (what Get_Depth returns) at +0xF0, where
// CameraClass::Set_Clip_Planes (0x00133D00) stores it; the shared Zero Hour
// header places it four bytes later.
struct BfmeCameraDepthFields
{
	unsigned char m_padding0000[0xF0];
	float m_zFar;
};

//-------------------------------------------------------------------------------------------------
/** Returns a world-space ray originating at a given screen pixel position
	and ending at the far clip plane for current camera. */
//-------------------------------------------------------------------------------------------------
void W3DView::getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd)
{
	Real logX,logY;

	//W3D Screen coordinates are -1 to 1, so we need to do some conversion:
	PixelScreenToW3DLogicalScreen(screen->x - m_originX,screen->y - m_originY, &logX, &logY,
		reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getWidth(),
		reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getHeight());

	*rayStart = (*reinterpret_cast<CameraClass **>(reinterpret_cast<unsigned char *>(this) + 0x104))->Get_Position();	//get camera location
	(*reinterpret_cast<CameraClass **>(reinterpret_cast<unsigned char *>(this) + 0x104))->Un_Project(*rayEnd,Vector2(logX,logY));	//get world space point
	*rayEnd -= *rayStart;	//vector camera to world space point
	rayEnd->Normalize();	//make unit vector
	*rayEnd *= reinterpret_cast<const BfmeCameraDepthFields *>(*reinterpret_cast<CameraClass **>(reinterpret_cast<unsigned char *>(this) + 0x104))->m_zFar;	//adjust length to reach far clip plane
	*rayEnd += *rayStart;	//get point on far clip plane along ray from camera.
}


// BFME moved the shake state and the GlobalData shake tuning; retail reads
// the angle pair and intensity at W3DView +0x120..+0x128 and the six
// intensities, the intensity cap and the range at GlobalData +0xB74..+0xB90.
struct BfmeW3DViewShakeFields
{
	unsigned char m_padding0000[0x120];
	Real m_shakeAngleCos;
	Real m_shakeAngleSin;
	Real m_shakeIntensity;
};

struct BfmeGlobalDataShakeFields
{
	unsigned char m_padding0000[0xB74];
	Real m_shakeSubtleIntensity;
	Real m_shakeNormalIntensity;
	Real m_shakeStrongIntensity;
	Real m_shakeSevereIntensity;
	Real m_shakeCineExtremeIntensity;
	Real m_shakeCineInsaneIntensity;
	Real m_maxShakeIntensity;
	Real m_maxShakeRange;
};

// ------------------------------------------------------------------------------------------------
/** Add an impulse force to shake the camera.
 * The camera shake is a simple simulation of an oscillating spring/damper.
 * The idea is that some sort of shock has "pushed" the camera once, as an
 * impluse, after which the camera vibrates back to its rest position.
 * @todo This should be part of "View", not "W3DView". */
// ------------------------------------------------------------------------------------------------
#define BFME_SHAKE_DATA ((const BfmeGlobalDataShakeFields *)TheGlobalData)
void W3DView::shake( const Coord3D *epicenter, CameraShakeType shakeType )
{
	BfmeW3DViewShakeFields *fields = (BfmeW3DViewShakeFields *)this;
#line 5735 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DView.cpp"
	Real angle = GameClientRandomValueReal( 0, 2*PI );

	fields->m_shakeAngleCos = (Real)cos( angle );
	fields->m_shakeAngleSin = (Real)sin( angle );

	Real intensity = 0.0f;
	switch( shakeType )
	{
		case SHAKE_SUBTLE:
			intensity = BFME_SHAKE_DATA->m_shakeSubtleIntensity;
			break;

		case SHAKE_NORMAL:
			intensity = BFME_SHAKE_DATA->m_shakeNormalIntensity;
			break;

		case SHAKE_STRONG:
			intensity = BFME_SHAKE_DATA->m_shakeStrongIntensity;
			break;

		case SHAKE_SEVERE:
			intensity = BFME_SHAKE_DATA->m_shakeSevereIntensity;
			break;

		case SHAKE_CINE_EXTREME:
			intensity = BFME_SHAKE_DATA->m_shakeCineExtremeIntensity;
			break;

		case SHAKE_CINE_INSANE:
			intensity = BFME_SHAKE_DATA->m_shakeCineInsaneIntensity;
			break;
	}

	// intensity falls off with distance
	const Coord3D *viewPos = getPosition();
	Coord3D d;
	d.x = epicenter->x - viewPos->x;
	d.y = epicenter->y - viewPos->y;

	Real dist = (Real)sqrt( d.x*d.x + d.y*d.y );

	if (dist > BFME_SHAKE_DATA->m_maxShakeRange)
		return;

	intensity *= 1.0f - (dist/BFME_SHAKE_DATA->m_maxShakeRange);

	// add intensity and clamp
	fields->m_shakeIntensity += intensity;

	if (fields->m_shakeIntensity > BFME_SHAKE_DATA->m_maxShakeIntensity)
		fields->m_shakeIntensity = BFME_SHAKE_DATA->m_maxShakeIntensity;
}
#undef BFME_SHAKE_DATA

// Retail 0x00089E2A..0x00089ED4; WB 0x009977A0 names this initializer
// and corroborates both embedded spline paths and their control sequence.
// BFME2's spline classes are absent from the ZH headers. These views retain
// the retail offsets and unnamed virtual slots without assigning new names.
struct Bfme89E2APathNode
{
	unsigned char m_unknown[0xB4];
	unsigned int m_control;
};

class Rva00312C95
{
public:
	virtual void slot0() = 0;
	virtual void setWaypoint(Waypoint *) = 0;
	virtual void initialize(int enabled, int duration, float easeIn, float easeOut, int extra, int flag) = 0;
	void rva00312118();
	unsigned char m_unknown04[0x2C - 4];
	std::vector<Bfme89E2APathNode> m_nodes;
};

template <int N> class Bfme89E2AViewSlots : public Bfme89E2AViewSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Bfme89E2AViewSlots<0> {};
class Bfme89E2AViewVtable : public Bfme89E2AViewSlots<28>
{
public:
	virtual void setControl(unsigned int value) = 0;
};

void W3DView::moveCameraOrLocatorAlongSplinePathInit(Waypoint *way, Int duration, Int,
	Real easeIn, Real easeOut, Real extra, Bool locator)
{
	if (way == 0 || *(int *)((char *)way + 0x60) != 6)
		return;
	Rva00312C95 *path = locator ? (Rva00312C95 *)((char *)this + 0x2368)
		: (Rva00312C95 *)((char *)this + 0x22F4);
	path->setWaypoint(way);
	path->initialize(*(int *)((char *)this + 0x23D4), duration, easeIn, easeOut, (int)extra, 1);
	if (locator)
		*(bool *)((char *)this + 0x23C8) = true;
	else {
		*(int *)((char *)this + 0x2354) = 2;
		unsigned int count = path->m_nodes.size();
		if (count > 3)
			((Bfme89E2AViewVtable *)this)->setControl(path->m_nodes[1].m_control);
		else
			((Bfme89E2AViewVtable *)this)->setControl(0);
	}
	path->rva00312118();
}
