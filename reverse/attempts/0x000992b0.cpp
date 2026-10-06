// ?draw@W3DMouse@@UAEXXZ
// partial score=0.99 date=2026-10-06
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

class WWMath
{
public:
	static float __fastcall Inv_Sqrt( float a );
};

class Vector3
{
public:
	__forceinline Vector3( void ) {}
	__forceinline Vector3( const Vector3 & v ) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3( float x, float y, float z ) { X = x; Y = y; Z = z; }

	__forceinline Vector3 & operator = ( const Vector3 & v ) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline Vector3 & operator += ( const Vector3 & v ) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	__forceinline Vector3 & operator -= ( const Vector3 & v ) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
	__forceinline Vector3 & operator *= ( float k ) { X = X*k; Y=Y*k; Z=Z*k; return *this; }

	__forceinline float Length2( void ) const { return X*X + Y*Y + Z*Z; }
	__forceinline void Normalize( void )
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}

	static __forceinline float Find_X_At_Z( float z, const Vector3 &p1, const Vector3 &p2 )
	{
		return(p1.X + ((z - p1.Z) * ((p2.X - p1.X) / (p2.Z - p1.Z))));
	}
	static __forceinline float Find_Y_At_Z( float z, const Vector3 &p1, const Vector3 &p2 )
	{
		return(p1.Y + ((z - p1.Z) * ((p2.Y - p1.Y) / (p2.Z - p1.Z))));
	}

	__forceinline const float & operator [] ( int i ) const { return (&X)[i]; }

	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	__forceinline void Set( float x, float y, float z, float w ) { X = x; Y = y; Z = z; W = w; }
	__forceinline float & operator []( int i ) { return (&X)[i]; }

	float X;
	float Y;
	float Z;
	float W;
};

extern "C" double __cdecl cos( double x );
extern "C" double __cdecl sin( double x );
extern "C" float __cdecl atan2f( float y, float x );
inline float __cdecl cosf( float _X ) { return ((float)cos((double)_X)); }
inline float __cdecl sinf( float _X ) { return ((float)sin((double)_X)); }

#define M_PI 3.14159265358979323846

class Matrix3D
{
public:
	__forceinline explicit Matrix3D( bool init ) { if (init) Make_Identity(); }

	__forceinline void Make_Identity( void )
	{
		Row[0].Set(1.0f,0.0f,0.0f,0.0f);
		Row[1].Set(0.0f,1.0f,0.0f,0.0f);
		Row[2].Set(0.0f,0.0f,1.0f,0.0f);
	}
	__forceinline void Set_Translation( const Vector3 & t ) { Row[0][3] = t[0]; Row[1][3] = t[1]; Row[2][3] = t[2]; }
	__forceinline void Rotate_Z( float theta )
	{
		float tmp1,tmp2;
		float c,s;

		c = cosf(theta);
		s = sinf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}

	Vector4 Row[3];
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
	virtual void slot20();
	virtual void Set_Transform( const Matrix3D &m );	// slot 21 (+0x54)
	virtual void Set_Position( const Vector3 &v );		// slot 22 (+0x58)
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43(); virtual void slot44();
	virtual void Set_Animation( HAnimClass *motion, float frame, int anim_mode );	// slot 45 (+0xB4)

	Vector3 Get_Position( void ) const;
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
	void Un_Project( Vector3 & dest, const Vector2 & view_point ) const;
	float Get_Depth( void ) const { return ZFar; }

private:
	char m_pad004[0xC4 - 4];
	ProjectionType Projection;
	char m_padC8[0xF0 - 0xC8];
	float ZFar;
	char m_padF4[0xFC - 0xF4];
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
	virtual void __stdcall SetCursorPosition( int x, int y, unsigned long flags );	// slot 11 (+0x2C)
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

class Image;

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual unsigned int getWidth( void );		// slot 16 (+0x40)
	virtual unsigned int getHeight( void );		// slot 17 (+0x44)
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual Bool getWindowed( void );			// slot 21 (+0x54)
};
extern Display *TheDisplay;

class W3DDisplay : public Display
{
public:
	void rva0004D6B3( Image *image, Real startX, Real startY, Real endX, Real endY, Int color = 0xFFFFFFFF, Int mode = 2 );

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

struct POINT
{
	long x;
	long y;
};
extern "C" __declspec(dllimport) int __stdcall GetCursorPos( POINT *point );
extern "C" __declspec(dllimport) int __stdcall ScreenToClient( void *hwnd, POINT *point );
extern void *ApplicationHWnd;

// class-gate: allow Coord2D the canonical header carries no members; this view adds only the rowed normalize 0x0000378A on the same 8-byte layout
class Coord2D
{
public:
	float x;
	float y;

	void normalize( void );
};

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41();
	virtual Bool isScrolling( void );					// slot 42 (+0xA8)
	virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual Coord2D getScrollAmount( void );			// slot 46 (+0xB8)
};
extern InGameUI *TheInGameUI;

// The three GlobalData fields the retail tooltip gate reads; their BFME 2
// meaning is not established, so they keep offset names.
struct MouseTooltipGlobalData
{
	char m_pad000[0x9B8];
	Int m_field9B8;
	char m_pad9BC[0x9C1 - 0x9BC];
	Bool m_field9C1;
	char m_pad9C2[0xDD0 - 0x9C2];
	Bool m_fieldDD0;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;

class Image
{
public:
	Int getImageWidth( void ) const { return m_imageSize.x; }
	Int getImageHeight( void ) const { return m_imageSize.y; }

private:
	char m_pad00[0x24];
	struct { Int x; Int y; } m_imageSize;
};

float __cdecl Rva000930C0( float lhs, float rhs );
void Rva00118660Call( void *scene, void *camera );
void PixelScreenToW3DLogicalScreen( Int x, Int y, Real *screenX, Real *screenY, Int screenWidth, Int screenHeight );

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
	bool rva001EDE26( void ) const;
	void drawCursorText( void );
	void drawTooltip( void );

protected:
	char m_pad004[0x0C - 4];
	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
	char m_pad126C[0x12DC - 0x126C];
	RedrawMode m_currentRedrawMode;
	char m_pad12E0[0x12E3 - 0x12E0];
	Bool m_orthoCamera;
	Real m_orthoZoom;
	char m_pad12E8[0x4F0C - 0x12E8];
	struct { ICoord2D pos; } m_currMouse;
	char m_pad4F14[0x4FA4 - 0x4F14];
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

extern "C" Image *cursorImages[Mouse::NUM_MOUSE_CURSORS];

class W3DMouse : public Win32Mouse
{
public:
	virtual void setCursor( MouseCursor cursor );
	virtual void draw( void );
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

void W3DMouse::draw(void)
{
	CriticalSectionClass::LockClass m(mutex);

	m_drawing = TRUE;

	//make sure the correct cursor image is selected
	setCursor(m_currentCursor);

	if (m_currentRedrawMode == RM_DX8 && m_currentD3DCursor != NONE)
	{
		//called from upate thread or rendering loop.  Tells D3D where
		//to draw the mouse cursor.
		IDirect3DDevice8 *m_pDev=DX8Wrapper::_Get_D3D_Device8();
		if (m_pDev)
		{	m_pDev->ShowCursor(TRUE);	//Enable DX8 cursor

			if (TheDisplay && !TheDisplay->getWindowed())
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
				m_currentAnimFrame=Rva000930C0(m_currentAnimFrame,(Real)m_currentFrames);
				m_lastAnimTime=msTime;

				if ((Int)m_currentAnimFrame != m_currentD3DFrame)
				{
					m_currentD3DFrame=(Int)m_currentAnimFrame;
					m_pDev->SetCursorProperties(m_currentHotSpot.x,m_currentHotSpot.y,m_currentD3DSurface[m_currentD3DFrame]);
				}
			}
		}
	}
	else if (m_currentRedrawMode == RM_POLYGON)
	{
		Image *image=cursorImages[m_currentPolygonCursor];
		if (image)
		{
			((W3DDisplay *)TheDisplay)->rva0004D6B3(image,m_currMouse.pos.x-m_currentHotSpot.x,m_currMouse.pos.y-m_currentHotSpot.y,
				m_currMouse.pos.x+image->getImageWidth()-m_currentHotSpot.x, m_currMouse.pos.y+image->getImageHeight()-m_currentHotSpot.y);
		}
	}
	else if (m_currentRedrawMode == RM_WINDOWS)
	{
	}
	else if (m_currentRedrawMode == RM_W3D)
	{
		if ( W3DDisplay::m_3DInterfaceScene && m_camera && rva001EDE26())
		{
			if (cursorModels[m_currentW3DCursor])
			{
				Real xPercent = (1.0f - (TheDisplay->getWidth() - m_currMouse.pos.x) / (Real)TheDisplay->getWidth());
				Real yPercent = ((TheDisplay->getHeight() - m_currMouse.pos.y) / (Real)TheDisplay->getHeight());

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
					PixelScreenToW3DLogicalScreen(m_currMouse.pos.x - 0, m_currMouse.pos.y - 0, &logX, &logY, TheDisplay->getWidth(), TheDisplay->getHeight());

					Vector3 rayStart;
					Vector3 rayEnd;
					rayStart = m_camera->Get_Position();							//get camera location
					m_camera->Un_Project(rayEnd,Vector2(logX,logY));	//get world space point
					rayEnd -= rayStart;																//vector camera to world space point
					rayEnd.Normalize();																//make unit vector
					rayEnd *= m_camera->Get_Depth();									//adjust length to reach far clip plane
					rayEnd += rayStart;																//get point on far clip plane along ray from camera.

					x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
					y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
				}

				Matrix3D tm(1);
				tm.Set_Translation(Vector3(x, y, z));
				if (TheInGameUI && TheInGameUI->isScrolling())
				{
					Coord2D offset;
					offset = TheInGameUI->getScrollAmount();
					offset.normalize();
					Real theta = atan2f(-offset.y, offset.x);
					theta -= (Real)M_PI/2;
					tm.Rotate_Z(theta);
				}
				cursorModels[m_currentW3DCursor]->Set_Transform(tm);

				Rva00118660Call( W3DDisplay::m_3DInterfaceScene, m_camera );
			}
		}
	}

	//@todo: In DX8 mode the mouse is drawn in another thread which isn't allowed
	//access to D3D so we can't do any drawing here.
	// draw the cursor text
	if (!isThread)
		drawCursorText();

	// draw tooltip text
	MouseTooltipGlobalData *data = (MouseTooltipGlobalData *)TheWritableGlobalData;
	Bool showTooltip = data->m_fieldDD0;
	if (data->m_field9C1 || data->m_field9B8)
		showTooltip = TRUE;
	if (showTooltip && rva001EDE26() && !isThread)
		drawTooltip();

	m_drawing = FALSE;
}
