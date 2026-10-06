// cl: /O1 /arch:SSE /G7 /DNDEBUG /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?initW3DAssets@W3DMouse@@AAEXXZ, retail 0x00099B6F, 605 bytes.
// Zero Hour's W3DMouse::initW3DAssets on BFME 2's layout and loaders. Under
// the file-scope mutex (0x009E4B34) and unless the mouse thread is drawing
// (isThread 0x009E4B30) it fills cursorModels (0x009E4970) and cursorAnims
// (0x009E4890) for cursors 1..55, then builds the cursor camera at +0x609C.
// BFME 2 differs from Zero Hour in three places read off the target:
// - an already loaded model table skips to the animation pass instead of
//   returning, and W3DDisplay's asset manager is no longer consulted;
// - models come from the free loader 0x00137364 (name, scale, options),
//   whose third parameter is a const reference defaulted to an empty
//   Rva0013101E (the 16-byte option block that loader copies through
//   0x0013101E): each call site zeroes the low 31 bits and three dwords;
// - animations come from the free lookup 0x0014CF5F (rowed as
//   Rva0014CF5F_GetAnimTree), whose result is stored as the HAnimClass.
// CursorInfo is the ZH record (stride 0x54 from +0x0C): W3DModelName +0x30,
// W3DAnimName +0x34, W3DScale +0x38, loop +0x3C; m_orthoCamera is the byte at
// +0x12E3 and m_orthoZoom the float at +0x12E4. RenderObjClass::Set_Position
// is slot 22 (+0x58) and Set_Animation slot 45 (+0xB4); CameraClass is
// 0x3FC bytes with the inline Set_Projection_Type writing FrustumValid
// (+0xFC) then Projection (+0xC4).
//
// ?setCursor@W3DMouse@@UAEXW4MouseCursor@Mouse@@@Z, retail 0x00099DCC, 638 bytes.
// Zero Hour's W3DMouse::setCursor for the four redraw modes (+0x12DC:
// windows, W3D, polygon, DX8). The windows mode stores the cursor only when
// it changes. The DX8 mode takes the cursor rate as fps (+0x4C) times
// 1/1000 and hands D3D the raw surface held in m_currentD3DSurface[0]; the
// hot spot is the record's +0x40 pair. W3D mode swaps models in
// W3DDisplay::m_3DInterfaceScene (0x009E1B3C) through Remove/Add_Render_Object
// (slots 3 and 2). The D3D texture helpers keep their rowed names, which spell
// MouseCursor at file scope.
//
// ?setRedrawMode@W3DMouse@@UAEXW4RedrawMode@Mouse@@@Z, retail 0x0009A04A, 438 bytes.
// Zero Hour's W3DMouse::setRedrawMode. BFME 2 holds the thread mutex for the
// DX8 drawing thread: entering DX8 mode hands a new MutexClass::LockClass on
// threadMutex (0x009E5DA0, wait -1) to the file-scope holder at 0x009E5DF8
// (Rva0009990D::set) before Execute, and every mode that stops the thread
// first clears that holder. DX8 mode resets the W3D and polygon cursors
// after the thread block, not before it. The virtual setCursor calls go
// through slot 19 (+0x4C) of the W3DMouse vtable 0x00BC86D8.

#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

#define NULL 0
#define FALSE 0
#define TRUE 1

class Vector2
{
public:
	Vector2( float x, float y ) { X = x; Y = y; }
	float X;
	float Y;
};

class Vector3
{
public:
	Vector3( float x, float y, float z ) { X = x; Y = y; Z = z; }
	float X;
	float Y;
	float Z;
};

class HAnimClass;
class HTreeClass;

class RenderObjClass
{
public:
	enum AnimMode
	{
		ANIM_MODE_MANUAL = 0,
		ANIM_MODE_LOOP,
		ANIM_MODE_ONCE
	};

	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual void Set_Position( const Vector3 &v );		// slot 22 (+0x58)
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43(); virtual void slot44();
	virtual void Set_Animation( HAnimClass *motion, float frame, int anim_mode );	// slot 45 (+0xB4)
};

class CameraClass : public RenderObjClass
{
public:
	enum ProjectionType
	{
		PERSPECTIVE = 0,
		ORTHO
	};

	CameraClass( void );
	void Set_View_Plane( const Vector2 &min, const Vector2 &max );
	void Set_Clip_Planes( float znear, float zfar );
	void Set_Projection_Type( ProjectionType ptype )
	{
		FrustumValid = false;
		Projection = ptype;
	}

private:
	char m_pad004[0xC4 - 4];
	ProjectionType Projection;
	char m_padC8[0xFC - 0xC8];
	bool FrustumValid;
	char m_padFD[0x3FC - 0xFD];
};

class Rva0013101E
{
public:
	Rva0013101E() : m_a( 0 ), m_b( 0 ), m_c( 0 ), m_d1( 0 ), m_d2( 0 ), m_d3( 0 ) {}

	unsigned m_a : 3;
	unsigned m_b : 27;
	unsigned m_c : 1;
	unsigned m_keep : 1;
	unsigned m_d1;
	unsigned m_d2;
	unsigned m_d3;
};

RenderObjClass *Rva00137364CreateRenderObj( const char *name, float scale, const Rva0013101E &options = Rva0013101E() );
HTreeClass *Rva0014CF5F_GetAnimTree( const char *name );

class CriticalSectionClass
{
public:
	class LockClass
	{
	public:
		LockClass( CriticalSectionClass &section );
		~LockClass();

	private:
		CriticalSectionClass &CriticalSection;
	};
};

struct IDirect3DSurface8;

struct IDirect3DDevice8
{
	virtual void __stdcall slot00(); virtual void __stdcall slot01(); virtual void __stdcall slot02();
	virtual void __stdcall slot03(); virtual void __stdcall slot04(); virtual void __stdcall slot05();
	virtual void __stdcall slot06(); virtual void __stdcall slot07(); virtual void __stdcall slot08();
	virtual void __stdcall slot09();
	virtual long __stdcall SetCursorProperties( unsigned int x, unsigned int y, IDirect3DSurface8 *bitmap );	// slot 10 (+0x28)
	virtual void __stdcall slot11();
	virtual int __stdcall ShowCursor( int bShow );		// slot 12 (+0x30)
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8( void ) { return D3DDevice; }

protected:
	static IDirect3DDevice8 *D3DDevice;
};

class RTS3DInterfaceScene
{
public:
	virtual void slot00(); virtual void slot01();
	virtual void Add_Render_Object( RenderObjClass *obj );		// slot 2 (+0x08)
	virtual void Remove_Render_Object( RenderObjClass *obj );	// slot 3 (+0x0C)
};

class W3DDisplay
{
public:
	static RTS3DInterfaceScene *m_3DInterfaceScene;
};

class W3DRadarResetSurface
{
public:
	operator IDirect3DSurface8 *() const { return m_surface; }

private:
	IDirect3DSurface8 *m_surface;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct CursorInfo
{
	char m_pad00[0x30];
	AsciiString W3DModelName;
	AsciiString W3DAnimName;
	Real W3DScale;
	Bool loop;
	ICoord2D hotSpotPosition;
	Int numFrames;
	Real fps;
	Int numDirections;
};

enum MouseCursor
{
	MOUSECURSOR_NONE = 0
};

extern "C" __declspec(dllimport) void *__stdcall SetCursor( void *cursor );
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0,
		NUM_MOUSE_CURSORS = 0x38
	};

	enum RedrawMode
	{
		RM_WINDOWS = 0,
		RM_W3D,
		RM_POLYGON,
		RM_DX8
	};

	virtual ~Mouse();
	virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18();
	virtual void setCursor( MouseCursor cursor );		// slot 19 (+0x4C)
	MouseCursor getMouseCursor( void ) { return m_currentCursor; }

protected:
	char m_pad004[0x0C - 4];
	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
	char m_pad126C[0x12DC - 0x126C];
	RedrawMode m_currentRedrawMode;
	char m_pad12E0[0x12E3 - 0x12E0];
	Bool m_orthoCamera;
	Real m_orthoZoom;
	char m_pad12E8[0x4FA4 - 0x12E8];
	MouseCursor m_currentCursor;
	char m_pad4FA8[0x601C - 0x4FA8];
};

class Win32Mouse : public Mouse
{
public:
	virtual void setCursor( MouseCursor cursor );

protected:
	Int m_directionFrame;
	Bool m_lostFocus;
};

enum
{
	MAX_2D_CURSOR_ANIM_FRAMES = 21
};

class Image;
extern "C" const Image *cursorImages[Mouse::NUM_MOUSE_CURSORS];

class W3DMouse : public Win32Mouse
{
public:
	virtual void setCursor( MouseCursor cursor );
	virtual void setRedrawMode( RedrawMode mode );

private:
	MouseCursor m_currentD3DCursor;
	W3DRadarResetSurface m_currentD3DSurface[MAX_2D_CURSOR_ANIM_FRAMES];
	ICoord2D m_currentHotSpot;
	Int m_currentFrames;
	Real m_currentAnimFrame;
	Int m_currentD3DFrame;
	Int m_lastAnimTime;
	Real m_currentFMS;
	Bool m_drawing;
	CameraClass *m_camera;
	MouseCursor m_currentW3DCursor;
	MouseCursor m_currentPolygonCursor;

	Bool loadD3DCursorTextures( ::MouseCursor cursor );
	Bool releaseD3DCursorTextures( ::MouseCursor cursor );
	void initD3DAssets( void );
	void freeD3DAssets( void );
	void initW3DAssets( void );
	void freeW3DAssets( void );
	void initPolygonAssets( void );
	void freePolygonAssets( void )
	{
		for (Int i=0; i<NUM_MOUSE_CURSORS; i++)
			cursorImages[i]=NULL;
	}
	void setCursorDirection( MouseCursor cursor );
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass( MutexClass &mutex, int time );
		~LockClass();

	private:
		MutexClass &mutex;
		int failed;
	};
};

class ThreadClass
{
public:
	virtual void Execute( void );
	void Stop( void );
	bool Is_Running( void );
};

class Rva0009990D
{
public:
	void set( void *p );
	void clear( void );
};
extern unsigned int g_Va009E5DF8;

extern "C" CriticalSectionClass mutex;
extern "C" MutexClass threadMutex;
extern "C" ThreadClass thread;
extern "C" Bool isThread;
extern "C" RenderObjClass *cursorModels[Mouse::NUM_MOUSE_CURSORS];
extern "C" HAnimClass *cursorAnims[Mouse::NUM_MOUSE_CURSORS];

void W3DMouse::initW3DAssets(void)
{
	CriticalSectionClass::LockClass m(mutex);

	//don't allow the mouse thread to initialize
	if (isThread)
		return;

	//Check if already loaded
	if (!cursorModels[1])
	{
		for (Int i=1; i<NUM_MOUSE_CURSORS; i++)
		{
			if (!m_cursorInfo[i].W3DModelName.isEmpty())
			{
				if (m_orthoCamera)
					cursorModels[i] = Rva00137364CreateRenderObj(m_cursorInfo[i].W3DModelName.str(), m_cursorInfo[i].W3DScale * m_orthoZoom);
				else
					cursorModels[i] = Rva00137364CreateRenderObj(m_cursorInfo[i].W3DModelName.str(), m_cursorInfo[i].W3DScale);
				if (cursorModels[i])
				{
					cursorModels[i]->Set_Position(Vector3(0.0f, 0.0f, -1.0f));
				}
			}
		}
	}

	if (!cursorAnims[1])
	{
		for (Int i=1; i<NUM_MOUSE_CURSORS; i++)
		{
			if (!m_cursorInfo[i].W3DAnimName.isEmpty())
			{
				HAnimClass *anim = (HAnimClass *)Rva0014CF5F_GetAnimTree(m_cursorInfo[i].W3DAnimName.str());
				cursorAnims[i] = anim;
				if (anim && cursorModels[i])
				{
					cursorModels[i]->Set_Animation(anim, 0, (m_cursorInfo[i].loop) ? RenderObjClass::ANIM_MODE_LOOP : RenderObjClass::ANIM_MODE_ONCE);
				}
			}
		}
	}

	// create the camera
	m_camera = new CameraClass();
	m_camera->Set_Position( Vector3( 0, 1, 1 ) );
	Vector2 min = Vector2( -1, -1 );
	Vector2 max = Vector2( +1, +1 );
	m_camera->Set_View_Plane( min, max );
	m_camera->Set_Clip_Planes( 0.995f, 20.0f );
	if (m_orthoCamera)
		m_camera->Set_Projection_Type( CameraClass::ORTHO );
}

void W3DMouse::setCursor( MouseCursor cursor )
{
	CriticalSectionClass::LockClass m(mutex);

	m_directionFrame=0;
	if (m_currentRedrawMode == RM_WINDOWS)
	{	//Windows default cursor needs to refreshed whenever we get a WM_SETCURSOR
		m_currentD3DCursor=NONE;
		m_currentW3DCursor=NONE;
		m_currentPolygonCursor=NONE;
		setCursorDirection(cursor);
		if (m_drawing)	//only allow cursor to change while drawing.
			Win32Mouse::setCursor( cursor );
		if (m_currentCursor != cursor)
			m_currentCursor = cursor;
		return;
	}

	// extend
	Mouse::setCursor( cursor );

	// if we're already on this cursor ignore the rest of code to stop cursor flickering.
	if( m_currentCursor == cursor && m_currentD3DCursor == cursor)
		return;

	//make sure Windows didn't reset our cursor
	if (m_currentRedrawMode == RM_DX8)
	{
		SetCursor(NULL);	//Kill Windows Cursor

		IDirect3DDevice8 *m_pDev=DX8Wrapper::_Get_D3D_Device8();
		if (m_pDev != NULL)
		{
			m_pDev->ShowCursor(FALSE);	//disable DX8 cursor
			if (cursor != m_currentD3DCursor)
			{	if (!isThread)
				{	releaseD3DCursorTextures((::MouseCursor)m_currentD3DCursor);
					//since this function is called from multiple threads, we must make sure the textures are loaded by only 1 thread...
					loadD3DCursorTextures((::MouseCursor)cursor);
				}
			}
			if (m_currentD3DSurface[0])
			{
				m_currentHotSpot = m_cursorInfo[cursor].hotSpotPosition;
				m_currentFMS = m_cursorInfo[cursor].fps*(1.0f/1000.0f);
				m_currentAnimFrame = 0;	//reset animation when cursor changes
				m_pDev->SetCursorProperties(m_currentHotSpot.x,m_currentHotSpot.y,m_currentD3DSurface[(Int)m_currentAnimFrame]);
				m_pDev->ShowCursor(TRUE);	//Enable DX8 cursor
				m_currentD3DFrame=(Int)m_currentAnimFrame;
				m_currentD3DCursor = cursor;
				m_lastAnimTime=timeGetTime();
			}
		}
	}
	else if (m_currentRedrawMode == RM_POLYGON)
	{
		SetCursor(NULL);	//Kill Windows Cursor
		m_currentD3DCursor=NONE;
		m_currentW3DCursor=NONE;
		m_currentPolygonCursor = cursor;
		m_currentHotSpot = m_cursorInfo[cursor].hotSpotPosition;
	}
	else if (m_currentRedrawMode == RM_W3D)
	{
		SetCursor(NULL);	//Kill Windows Cursor
		m_currentD3DCursor=NONE;
		m_currentPolygonCursor=NONE;
		if (cursor != m_currentW3DCursor)
		{
			if (!cursorModels[1])
			{	//check if models are loaded since they are needed for this mode.
				initW3DAssets();
				if (!cursorModels[1])
				{	m_currentCursor = cursor;
					return;
				}
			}
			//remove model from previous cursor
			if (cursorModels[m_currentW3DCursor])
			{	W3DDisplay::m_3DInterfaceScene->Remove_Render_Object(cursorModels[m_currentW3DCursor]);
			}
			m_currentW3DCursor=cursor;
			//add model from new cursor
			if (cursorModels[m_currentW3DCursor])
			{	W3DDisplay::m_3DInterfaceScene->Add_Render_Object(cursorModels[m_currentW3DCursor]);
				if (m_cursorInfo[m_currentW3DCursor].loop == FALSE && cursorAnims[m_currentW3DCursor])
				{
					cursorModels[m_currentW3DCursor]->Set_Animation(cursorAnims[m_currentW3DCursor], 0, RenderObjClass::ANIM_MODE_ONCE);
				}
			}
		}
		else
		{
			m_currentW3DCursor=cursor;
		}
	}

	// save current cursor
	m_currentCursor = cursor;
}

void W3DMouse::setRedrawMode(RedrawMode mode)
{
	MouseCursor cursor = getMouseCursor();

	//Turn off the previous cursor mode
	setCursor(NONE);

	m_currentRedrawMode=mode;

	switch (mode)
	{
		case RM_WINDOWS:
		{	//Windows default cursor needs to refreshed whenever we get a WM_SETCURSOR
			if (thread.Is_Running())
			{	((Rva0009990D *)&g_Va009E5DF8)->clear();
				thread.Stop();
			}
			freeD3DAssets();
			freeW3DAssets();
			freePolygonAssets();
			m_currentD3DCursor=NONE;
			m_currentW3DCursor=NONE;
			m_currentPolygonCursor=NONE;
			break;
		}
		case RM_W3D:
		{	//Model based cursors
			if (thread.Is_Running())
			{	((Rva0009990D *)&g_Va009E5DF8)->clear();
				thread.Stop();
			}
			freeD3DAssets();
			freePolygonAssets();
			m_currentD3DCursor=NONE;
			m_currentPolygonCursor=NONE;
			initW3DAssets();
			break;
		}
		case RM_POLYGON:
		{	//Polygon cursor
			if (thread.Is_Running())
			{	((Rva0009990D *)&g_Va009E5DF8)->clear();
				thread.Stop();
			}
			freeD3DAssets();
			freeW3DAssets();
			m_currentD3DCursor=NONE;
			m_currentW3DCursor=NONE;
			m_currentPolygonCursor=NONE;
			initPolygonAssets();
			break;
		}
		case RM_DX8:
		{	//DX8 cursor
			initD3DAssets();
			freeW3DAssets();
			freePolygonAssets();
			if (!thread.Is_Running())
			{	((Rva0009990D *)&g_Va009E5DF8)->set(new MutexClass::LockClass(threadMutex, -1));
				thread.Execute();
			}
			m_currentW3DCursor=NONE;
			m_currentPolygonCursor=NONE;
			break;
		}
	}

	//Force cursor update since we changed redraw methods.
	setCursor(NONE);
	setCursor(cursor);
}
