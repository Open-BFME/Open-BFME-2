// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/mouselayout /Ireference/open-bfme-1/reference/shims/asciistring8 /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DMouse.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Mark W.
// Desc:   W3D Mouse cursor implementations
///////////////////////////////////////////////////////////////////////////////////////////////////


#include "Common/GameMemory.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/RendObj.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/Camera.h"

#include "assetmgr.h"

#include "W3DDevice/Common/W3DConvert.h"
#include "W3DDevice/GameClient/W3DMouse.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "GameClient/Display.h"
#include "GameClient/Image.h"
#include "GameClient/InGameUI.h"
#include "mutex.h"
#include "thread.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma message("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//Since there can't be more than 1 mouse, might as well keep these static.
static CriticalSectionClass mutex;
static MutexClass threadMutex;
static Bool isThread;
static TextureClass *cursorTextures[Mouse::NUM_MOUSE_CURSORS][MAX_2D_CURSOR_ANIM_FRAMES];	///<Textures for each cursor type
// Native image table spans DE4A50..DE4B30: 56 pointers, not the donor enum count.
enum { RETAIL_WORLD_CURSOR_COUNT = 56 };
static const Image *cursorImages[RETAIL_WORLD_CURSOR_COUNT];			///<Images for use with the RM_POLYGON method.
// Retail freeW3DAssets traverses 0xE0 bytes in each of these tables.
static RenderObjClass *cursorModels[RETAIL_WORLD_CURSOR_COUNT];	///< W3D models for each cursor type
static HAnimClass			*cursorAnims[RETAIL_WORLD_CURSOR_COUNT];		///< W3D animations for each cursor type

///Mouse polling/update thread function
// Retail reaches Mouse::draw through [eax+0x30]; the reference Mouse header
// puts it at [eax+0x14]. Spelled TU-locally as a facade with the intervening
// slots left anonymous, because Mouse.h is shared and only this body proves
// where draw ended up in BFME.
class BfmeMouseDrawCall
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void draw();
};
static class MouseThreadClass : public ThreadClass
{

public:
// ??0MouseThreadClass@@ present-unmatched
	MouseThreadClass::MouseThreadClass() : ThreadClass() {}

	void Thread_Function();

} thread;

void MouseThreadClass::Thread_Function()
{

	//poll mouse and update position

	for (;;)
	{
		MutexClass::LockClass lock(threadMutex, 1);
		if (!lock.Failed())
			break;
		isThread=TRUE;
		if (TheMouse != 0)
			((BfmeMouseDrawCall *)TheMouse)->draw();
		isThread=FALSE;
	}
}

// ??0W3DMouse@@ present-unmatched
W3DMouse::W3DMouse( void )
{
	// zero our event list
	for (Int i=0; i<NUM_MOUSE_CURSORS; i++)
	{
		for (Int j=0; j<MAX_2D_CURSOR_ANIM_FRAMES; j++)
			cursorTextures[i][j]=NULL;
		cursorModels[i]=NULL;
		cursorAnims[i]=NULL;
	}

	m_currentD3DCursor=NONE;
	m_currentW3DCursor=NONE;
	m_currentPolygonCursor=NONE;
	m_currentAnimFrame = 0;
	m_currentD3DFrame = 0;
	m_currentFrames = 0;
	m_currentFMS= 1.0f/1000.0f;

	m_camera = NULL;
	m_drawing = FALSE;

}  // end Win32Mouse

// ??1W3DMouse@@ present-unmatched
W3DMouse::~W3DMouse( void )
{
	LPDIRECT3DDEVICE8 m_pDev=DX8Wrapper::_Get_D3D_Device8();

	if (m_pDev)
	{
		m_pDev->ShowCursor(FALSE);	//kill DX8 cursor
// ?setCursor@Win32Mouse@@ present-unmatched
		Win32Mouse::setCursor(ARROW); //enable default windows cursor
	}

	freeD3DAssets();
	freeW3DAssets();

	thread.Stop();

}  // end Win32Mouse

// Retail W3DMouse layout (proven by matched freeW3DAssets/initPolygonAssets
// bodies): cursor records start at this+0x38 with a 0x54 stride and the
// image name at record+0 (56 records: 0x38+56*0x54 = 0xF98); the live
// cursors ride at +0x4FA4/+0x60A4 and the redraw mode at +0x12DC. The
// shared view is shorter on all three, so this body goes through a
// TU-local view that keeps member-access codegen with retail constants.
struct BfmeInitPolygonCursorRec
{
	AsciiString imageName;
	char pad[0x54 - sizeof(AsciiString)];
};
struct BfmeInitPolygonMouseView
{
	char pad0[0x38];
	BfmeInitPolygonCursorRec cursorInfo[56];
	char pad1[0x4FA4 - (0x38 + 56*0x54)];
	Mouse::MouseCursor currentCursor;
	char pad2[0x60A4 - (0x4FA4 + 4)];
	Mouse::MouseCursor currentPolygonCursor;
};
void W3DMouse::initPolygonAssets(void)
{
	CriticalSectionClass::LockClass m(mutex);

	//don't allow the mouse thread to initialize
	//wait for main app to do initialization.
	if (isThread)
		return;

	BfmeInitPolygonMouseView *v = reinterpret_cast<BfmeInitPolygonMouseView *>(this);

	//Check if texture assets already loaded
	if (*reinterpret_cast<RedrawMode *>(reinterpret_cast<char *>(this)+0x12DC) == RM_POLYGON && cursorImages[1] == NULL)
	{
		for (Int i=0; i<RETAIL_WORLD_CURSOR_COUNT; i++)
		{
			v->currentPolygonCursor = v->currentCursor;
			if (!v->cursorInfo[i].imageName.isEmpty())
				cursorImages[i]=TheMappedImageCollection->findImageByName(v->cursorInfo[i].imageName);
		}
	}
}

// ?freePolygonAssets@W3DMouse@@AAEXXZ present-unmatched
void W3DMouse::freePolygonAssets(void)
{

	for (Int i=0; i<NUM_MOUSE_CURSORS; i++)
	{
		cursorImages[i]=NULL;
	}
}

/**Load the textures required to display the selected cursor*/
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouseLoadD3DCursorTexturesThunk.cpp
// ?loadD3DCursorTextures@W3DMouse@@ present-unmatched
Bool W3DMouse::loadD3DCursorTextures(MouseCursor cursor)
{
	if (cursor == NONE || cursorTextures[cursor][0])
		return TRUE;	//no texture for this cursor or texture already loaded

	WW3DAssetManager *am=WW3DAssetManager::Get_Instance();
	Int animFrames=m_cursorInfo[cursor].numFrames;

	if (!animFrames)
		return FALSE;	//no animation frames defined.
	
	const char *baseName=m_cursorInfo[cursor].textureName.str();
	char FrameName[64];

	//Clamp to reasonable number
	if (animFrames > MAX_2D_CURSOR_ANIM_FRAMES)
		animFrames = MAX_2D_CURSOR_ANIM_FRAMES;

	m_currentFrames=0;

	if (animFrames == 1)
	{	//single animation frame without trailing numbers
		sprintf(FrameName,"%s.tga",baseName);
		cursorTextures[cursor][0]=	am->Get_Texture(FrameName);
		m_currentD3DSurface[0]=cursorTextures[cursor][0]->Get_Surface_Level();
		m_currentFrames = 1;
	}
	else
	for (Int i=0; i<animFrames; i++)
	{
		sprintf(FrameName,"%s%04d.tga",baseName,i);
		if ((cursorTextures[cursor][i]=am->Get_Texture(FrameName)) != NULL)
		{	m_currentD3DSurface[m_currentFrames]=cursorTextures[cursor][i]->Get_Surface_Level();
			m_currentFrames++;
		}
	}
	return TRUE;
}

void W3DMouse::initD3DAssets(void)
{
	//Nothing to do here unless we want to preload all possible cursors which would
	//probably not be practical for memory reasons.

	CriticalSectionClass::LockClass m(mutex);

	//don't allow the mouse thread to initialize
	//wait for main app to do initialization.
	if (isThread)
		return;

	WW3DAssetManager *am=WW3DAssetManager::Get_Instance();

	//Check if texture assets already loaded
	if (m_currentRedrawMode == RM_DX8 && cursorTextures[1] == NULL && am)
	{
		for (Int i=0; i<NUM_MOUSE_CURSORS; i++)
		{	
			for (Int j=0; j < MAX_2D_CURSOR_ANIM_FRAMES; j++)
			{
				cursorTextures[i][j]=NULL;//am->Get_Texture(m_cursorInfo[i].textureName.str());
				m_currentD3DSurface[i]=NULL;
			}
		}
	}
}

// W3DMouse::initW3DAssets is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouseInitW3DAssets.cpp (0x00099B6F).

// BFME reaches Remove_Render_Object at the interface scene's vtable +0x0c, one
// slot ahead of where the ZH SceneClass declaration puts it.
class BfmeInterfaceScene
{
public:
	virtual void bfme_scene_0( void ) = 0;
	virtual void bfme_scene_4( void ) = 0;
	virtual void Add_Render_Object( RenderObjClass *obj ) = 0;
	virtual void Remove_Render_Object( RenderObjClass *obj ) = 0;
};

// The BFME render-object ABI retains five virtual slots that the ZH header
// omits before the animation overload used by the cursor models.
class BfmeCursorRenderObject
{
public:
	virtual void bfme_render_0( void ) = 0;
	virtual void bfme_render_4( void ) = 0;
	virtual void bfme_render_8( void ) = 0;
	virtual void bfme_render_c( void ) = 0;
	virtual void bfme_render_10( void ) = 0;
	virtual void bfme_render_14( void ) = 0;
	virtual void bfme_render_18( void ) = 0;
	virtual void bfme_render_1c( void ) = 0;
	virtual void bfme_render_20( void ) = 0;
	virtual void bfme_render_24( void ) = 0;
	virtual void bfme_render_28( void ) = 0;
	virtual void bfme_render_2c( void ) = 0;
	virtual void bfme_render_30( void ) = 0;
	virtual void bfme_render_34( void ) = 0;
	virtual void bfme_render_38( void ) = 0;
	virtual void bfme_render_3c( void ) = 0;
	virtual void bfme_render_40( void ) = 0;
	virtual void bfme_render_44( void ) = 0;
	virtual void bfme_render_48( void ) = 0;
	virtual void bfme_render_4c( void ) = 0;
	virtual void bfme_render_50( void ) = 0;
	virtual void bfme_render_54( void ) = 0;
	virtual void bfme_render_58( void ) = 0;
	virtual void bfme_render_5c( void ) = 0;
	virtual void bfme_render_60( void ) = 0;
	virtual void bfme_render_64( void ) = 0;
	virtual void bfme_render_68( void ) = 0;
	virtual void bfme_render_6c( void ) = 0;
	virtual void bfme_render_70( void ) = 0;
	virtual void bfme_render_74( void ) = 0;
	virtual void bfme_render_78( void ) = 0;
	virtual void bfme_render_7c( void ) = 0;
	virtual void bfme_render_80( void ) = 0;
	virtual void bfme_render_84( void ) = 0;
	virtual void bfme_render_88( void ) = 0;
	virtual void bfme_render_8c( void ) = 0;
	virtual void bfme_render_90( void ) = 0;
	virtual void bfme_render_94( void ) = 0;
	virtual void bfme_render_98( void ) = 0;
	virtual void bfme_render_9c( void ) = 0;
	virtual void bfme_render_a0( void ) = 0;
	virtual void bfme_render_a4( void ) = 0;
	virtual void bfme_render_a8( void ) = 0;
	virtual void bfme_render_ac( void ) = 0;
	virtual void Set_Animation( HAnimClass *anim, float frame, int mode ) = 0;
};

void W3DMouse::freeW3DAssets(void)
{
	// The retail model and animation tables span 56 entries (0xE0 bytes),
	// independent of the shorter reference enum bound.
	for (Int i=0; i<RETAIL_WORLD_CURSOR_COUNT; i++)
	{
		if (W3DDisplay::m_3DInterfaceScene && cursorModels[i])
		{
			((BfmeInterfaceScene *)W3DDisplay::m_3DInterfaceScene)->Remove_Render_Object(cursorModels[i]);
		}
		// BFME's REF_PTR_RELEASE nulls the pointer inside the guard; ZH's macro
		// leaves the store outside it, which costs a reload after the release.
		if (cursorModels[i]) { cursorModels[i]->Release_Ref(); cursorModels[i] = NULL; }
		if (cursorAnims[i]) { cursorAnims[i]->Release_Ref(); cursorAnims[i] = NULL; }
	}

	CameraClass *&retailCamera = *reinterpret_cast<CameraClass **>(reinterpret_cast<char *>(this) + 0x609C);
	if (retailCamera) { retailCamera->Release_Ref(); retailCamera = NULL; }
}

//-------------------------------------------------------------------------------------------------
/** Initialize our device */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Open-BFME5: Mouse::setCursor is four vtable slots later in BFME. Retail
// reaches it through [eax+0x38]; the reference GameClient/Mouse.h puts it at
// [eax+0x28]. Spelled TU-locally as a facade with the intervening slots left
// anonymous, because Mouse.h is included across the whole GameClient and the
// four slots that were inserted ahead of setCursor are not something this
// body identifies -- it only shows where setCursor ended up.
//-------------------------------------------------------------------------------------------------
class BfmeVirtualMouseSetCursor
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	// Int and not Mouse::MouseCursor: the enum is nested in the class this
	// facade stands in for, and the argument is a four-byte push either way.
	virtual void setCursor( Int cursor ) = 0;
};

// The BFME Display layout moves the width/height pair to slots 0x2c/0x30
// and getWindowed to slot 0x40.  Keep this draw-only view declaration local;
// it emits no table and does not change the shared Display header.
class BfmeMouseDisplayDraw
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot0c( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot1c( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void slot28( void ) = 0;
	virtual UnsignedInt getWidth( void ) = 0;
	virtual UnsignedInt getHeight( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void slot38( void ) = 0;
	virtual void slot3c( void ) = 0;
	virtual Bool getWindowed( void ) = 0;
};

// RenderObjClass::Set_Transform is the 0x54 slot in the BFME cursor-model
// layout.  This facade is used only for that proven call site.
class BfmeMouseRenderTransform
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot0c( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot1c( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void slot28( void ) = 0;
	virtual void slot2c( void ) = 0;
	virtual void slot30( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void slot38( void ) = 0;
	virtual void slot3c( void ) = 0;
	virtual void slot40( void ) = 0;
	virtual void slot44( void ) = 0;
	virtual void slot48( void ) = 0;
	virtual void slot4c( void ) = 0;
	virtual void slot50( void ) = 0;
	virtual void Set_Transform( const Matrix3D &transform ) = 0;
};

// The retail draw entry reads the cursor point at this BFME layout offset;
// the reference Mouse header's inherited Coord2D is eight bytes earlier.
// This view is limited to draw and has no virtual members or emitted table.
struct BfmeMouseDrawPoint
{
	Int first;
	Int second;
};

struct BfmeMouseDrawLayout
{
	UnsignedByte pad[0x4d10];
	BfmeMouseDrawPoint pos;
};

// These three BFME GlobalData reads are the retail tooltip gate.  Keep their
// offsets neutral here rather than borrowing the shifted reference names.
struct BfmeMouseTooltipGlobalData
{
	UnsignedByte padA88[0xa88];
	Int fieldA88;
	UnsignedByte padA8c[4];
	Bool fieldA90;
	UnsignedByte padA91[0xe54 - 0xa91];
	Bool fieldE54;
};

// W3D's retail camera depth is read from the BFME camera layout at +0xf4;
// the common declaration's accessor uses a different object view here.
struct BfmeMouseCameraDepth
{
	UnsignedByte padF4[0xf4];
	Real depth;
};

// Keep the inline CameraClass accessor COMDAT available to the existing
// same-TU alias row at 0x006E2440; draw itself uses the proven BFME +0xf4
// field and must not call the shifted reference accessor.
typedef Real (CameraClass::*BfmeMouseCameraDepthAccessor)( void ) const;
static volatile BfmeMouseCameraDepthAccessor BfmeMouseCameraDepthMethod =
	&CameraClass::Get_Depth;

// The generated thunk is the proven direct route to Display::drawImage's
// float-coordinate implementation.  Its placeholder declaration is void(),
// so the call site supplies the recovered ABI through a typed cast.
extern void j_0000a114( void );
extern void j_00023fa6( void );
extern void j_00032e39( void );
extern void j_000350bc( void );
class GlobalData;
extern GlobalData *TheWritableGlobalData;

// ?init@W3DMouse@@UAEXXZ present-unmatched
void W3DMouse::init( void )
{

	//check if system already initialized and texture assets loaded.
	Win32Mouse::init();
	((BfmeVirtualMouseSetCursor *)this)->setCursor(ARROW);	//set default starting cursor image

	WWASSERT(!thread.Is_Running());


	isThread=FALSE;
	if (m_currentRedrawMode == RM_DX8)
		thread.Execute();
	thread.Set_Priority(0);
	
}  // end int

//-------------------------------------------------------------------------------------------------
/** Reset */
//-------------------------------------------------------------------------------------------------
// The reset body uses setCursor at vtable slot 0x4C, five slots after the
// cursor-only facade above.  The retail redraw-mode field is at this+0x12DC;
// the reference class view puts it at +0x10E0.
class BfmeW3DMouseResetVtable
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void setCursor(Int cursor) = 0;
};
void W3DMouse::reset( void )
{

	// extend
	Win32Mouse::reset();
	((BfmeW3DMouseResetVtable *)this)->setCursor(ARROW);

	isThread=FALSE;
	if (*reinterpret_cast<RedrawMode *>(reinterpret_cast<char *>(this)+0x12DC) == RM_DX8)
		thread.Execute();
	thread.Set_Priority(0);

}  // end reset

//-------------------------------------------------------------------------------------------------
/** Super basic simplistic cursor */
//-------------------------------------------------------------------------------------------------
// W3DMouse::setCursor is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouseInitW3DAssets.cpp (0x00099DCC).

extern HWND ApplicationHWnd;

// ?draw@W3DMouse@@UAEXXZ present-unmatched
void W3DMouse::draw(void)
{
	CriticalSectionClass::LockClass m(mutex);

	m_drawing = 1;

	//make sure the correct cursor image is selected
	((BfmeVirtualMouseSetCursor *)this)->setCursor(m_currentCursor);

	if (m_currentRedrawMode == RM_DX8 && m_currentD3DCursor != NONE)
	{
		//called from upate thread or rendering loop.  Tells D3D where
		//to draw the mouse cursor.
		LPDIRECT3DDEVICE8 m_pDev=DX8Wrapper::_Get_D3D_Device8();
		if (m_pDev)
		{	m_pDev->ShowCursor(1);	//Enable DX8 cursor

			if (TheDisplay && !((BfmeMouseDisplayDraw *)TheDisplay)->getWindowed())
			{	//if we're full-screen, need to manually move cursor image
				POINT ptCursor;

				GetCursorPos( &ptCursor );
				ScreenToClient( ApplicationHWnd, &ptCursor );
				m_pDev->SetCursorPosition( ptCursor.x, ptCursor.y, 1);
			}
			//Check if animated cursor and new frame
			if (m_currentFrames > 1)
			{
				Int msTime=timeGetTime();
				m_currentAnimFrame += (msTime-m_lastAnimTime) * m_currentFMS;
				m_currentAnimFrame=fmod(m_currentAnimFrame,m_currentFrames);
				m_lastAnimTime=msTime;

				if ((Int)m_currentAnimFrame != m_currentD3DFrame)
				{
					m_currentD3DFrame=(Int)m_currentAnimFrame;
					IDirect3DSurface8 *surface = (IDirect3DSurface8 *)m_currentD3DSurface[m_currentD3DFrame];
					m_pDev->SetCursorProperties(m_currentHotSpot.x,m_currentHotSpot.y,surface);
				}
			}
		}
	}
	else if (m_currentRedrawMode == RM_POLYGON)
	{	
		const Image *image=cursorImages[m_currentPolygonCursor];
		if (image)
		{
			typedef void (Display::*BfmeDisplayDrawImage)(const Image *, Real, Real, Real, Real, Int, Int);
			union
			{
				void (*function)(void);
				BfmeDisplayDrawImage member;
			} drawImageThunk;
			drawImageThunk.function = j_0000a114;
			(TheDisplay->*drawImageThunk.member)(
				image,
				((BfmeMouseDrawLayout *)this)->pos.first-m_currentHotSpot.x,
				((BfmeMouseDrawLayout *)this)->pos.second-m_currentHotSpot.y,
				((BfmeMouseDrawLayout *)this)->pos.first+image->getImageWidth()-m_currentHotSpot.x,
				((BfmeMouseDrawLayout *)this)->pos.second+image->getImageHeight()-m_currentHotSpot.y, -1, 2);
		}
	}
	else if (m_currentRedrawMode == RM_WINDOWS)
	{
	}
	else if (m_currentRedrawMode == RM_W3D)
	{
		typedef bool (Win32Mouse::*BfmeCursorVisibility)(void);
		union
		{
			void (*function)(void);
			BfmeCursorVisibility member;
		} cursorVisibilityThunk;
		cursorVisibilityThunk.function = j_00023fa6;
		if ( W3DDisplay::m_3DInterfaceScene && m_camera &&
			(this->*cursorVisibilityThunk.member)())
		{
			if (cursorModels[m_currentW3DCursor])
			{
				Real xPercent = (1.0f - (((BfmeMouseDisplayDraw *)TheDisplay)->getWidth() - ((BfmeMouseDrawLayout *)this)->pos.first) / (Real)((BfmeMouseDisplayDraw *)TheDisplay)->getWidth());
				Real yPercent = ((((BfmeMouseDisplayDraw *)TheDisplay)->getHeight() - ((BfmeMouseDrawLayout *)this)->pos.second) / (Real)((BfmeMouseDisplayDraw *)TheDisplay)->getHeight());

				Real x, y, z = -1.0f;

				if (m_orthoCamera)
				{
					x = xPercent*2 - 1;
					y = yPercent*2;
				}
				else
				{
					//W3D Screen coordinates are -1 to 1, so we need to do some conversion:
					Real logX, logY;
					PixelScreenToW3DLogicalScreen(((BfmeMouseDrawLayout *)this)->pos.first - 0, ((BfmeMouseDrawLayout *)this)->pos.second - 0, &logX, &logY, ((BfmeMouseDisplayDraw *)TheDisplay)->getWidth(), ((BfmeMouseDisplayDraw *)TheDisplay)->getHeight());

					Vector3 rayStart;
					Vector3 rayEnd;
					rayStart = m_camera->Get_Position();							//get camera location
					m_camera->Un_Project(rayEnd,Vector2(logX,logY));	//get world space point
					rayEnd -= rayStart;																//vector camera to world space point
					rayEnd.Normalize();																//make unit vector
					rayEnd *= ((BfmeMouseCameraDepth *)m_camera)->depth;									//adjust length to reach far clip plane
					rayEnd += rayStart;																//get point on far clip plane along ray from camera.

					x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
					y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
				}

				Matrix3D tm(1);
				tm.Set_Translation(Vector3(x, y, z));
				Coord2D offset = {0, 0};
				if (TheInGameUI && TheInGameUI->isScrolling())
				{
					offset = TheInGameUI->getScrollAmount();
					offset.normalize();
					Real theta = atan2(-offset.y, offset.x);
					theta -= (Real)M_PI/2;
					tm.Rotate_Z(theta);
				}
				((BfmeMouseRenderTransform *)cursorModels[m_currentW3DCursor])->Set_Transform(tm);

				WW3D::Render( W3DDisplay::m_3DInterfaceScene, m_camera );
			}
		}
	}

	//@todo: In DX8 mode the mouse is drawn in another thread which isn't allowed
	//access to D3D so we can't do any drawing here.
	// draw the cursor text through the existing BFME ILT.  The generated
	// thunk is the actual route used by this body, not a new identity pin.
	if (!isThread)
	{
		typedef void (Mouse::*BfmeDrawCursorText)(void);
		union
		{
			void (*function)(void);
			BfmeDrawCursorText member;
		} drawCursorTextThunk;
		drawCursorTextThunk.function = j_00032e39;
		(reinterpret_cast<Mouse *>(this)->*drawCursorTextThunk.member)();
	}

	// BFME's tooltip gate uses the three GlobalData flags and the Win32
	// visibility predicate before taking the existing tooltip ILT.
	BfmeMouseTooltipGlobalData *tooltipData =
		(BfmeMouseTooltipGlobalData *)TheWritableGlobalData;
	typedef bool (Win32Mouse::*BfmeCursorVisibility)(void);
	union
	{
		void (*function)(void);
		BfmeCursorVisibility member;
	} tooltipVisibilityThunk;
	tooltipVisibilityThunk.function = j_00023fa6;
	Bool tooltipFlagE54 = tooltipData->fieldE54;
	if ((tooltipData->fieldA90 || tooltipData->fieldA88 || tooltipFlagE54) &&
		(reinterpret_cast<Win32Mouse *>(this)->*tooltipVisibilityThunk.member)() && !isThread)
	{
		typedef void (Mouse::*BfmeDrawTooltip)(void);
		union
		{
			void (*function)(void);
			BfmeDrawTooltip member;
		} drawTooltipThunk;
		drawTooltipThunk.function = j_000350bc;
		(reinterpret_cast<Mouse *>(this)->*drawTooltipThunk.member)();
	}

	m_drawing = FALSE;
}

// W3DMouse::setRedrawMode is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouseInitW3DAssets.cpp (0x0009A04A).

// ?setCursorDirection@W3DMouse@@AAEXW4MouseCursor@Mouse@@@Z present-unmatched
void W3DMouse::setCursorDirection(MouseCursor cursor)
{
	Coord2D offset = {0, 0};
	//Check if we have a directional cursor that needs different images for each direction
	if (m_cursorInfo[cursor].numDirections > 1 && TheInGameUI && TheInGameUI->isScrolling())
	{
		offset = TheInGameUI->getScrollAmount();
		if (offset.x || offset.y)
		{
			offset.normalize();
			Real theta = atan2(offset.y, offset.x);
			theta = fmod(theta+M_PI*2,M_PI*2);
			Int numDirections=m_cursorInfo[m_currentCursor].numDirections;
			//Figure out which of our predrawn cursor orientations best matches the
			//actual cursor direction.  Frame 0 is assumed to point right and continue
			//clockwise.
			m_directionFrame=(Int)(theta/(2.0f*M_PI/(Real)numDirections)+0.5f);
			if (m_directionFrame >= numDirections)
				m_directionFrame = 0;
		}
		else
		{
			m_directionFrame=0;
		}
	}
	else
		m_directionFrame = 0;
}
