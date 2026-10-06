// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ??0W3DMouse@@QAE@XZ, retail 0x00098E69, 218 bytes.
// Zero Hour's W3DMouse constructor on BFME 2's layout. The game client's
// createMouse slot (0x0004C709) builds the 0x60A8-byte object; the body calls
// the rowed Win32Mouse ctor 0x00041976, writes the W3DMouse vtable 0x00BC86D8
// and eh-vector-constructs m_currentD3DSurface[21] at +0x6028 with the
// null-first-word ctor 0x00326BE6 and the COM-releasing dtor 0x00176CB0
// (W3DRadarResetSurface). The cursor texture table 0x009E4B40 (56 x 21
// CursorTextureSlot holders, owned by W3DMouse_loadD3DCursorTextures.cpp) is
// cleared through the rowed BfmeResetTextureRef::clear 0x0004D75B, reached
// here through a TU-local base so the table keeps its ledger type; the models
// 0x009E4970 and animations 0x009E4890 are nulled per cursor. Member offsets follow the ZH declaration order from
// m_currentD3DCursor +0x6024 to m_currentPolygonCursor +0x60A4; m_camera
// +0x609C and m_currentPolygonCursor +0x60A4 agree with the rowed
// freeW3DAssets and initPolygonAssets.

typedef int Int;
typedef float Real;
typedef bool Bool;

#define NULL 0
#define FALSE 0

class TextureBaseClass;
class RenderObjClass;
class HAnimClass;
class CameraClass;

struct ICoord2D
{
	Int x;
	Int y;
};

struct BfmeResetTextureRef
{
	TextureBaseClass *pointer;

	void clear( void );
};

struct CursorTextureSlot : public BfmeResetTextureRef
{
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface( 0 ) {}
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

enum
{
	MAX_2D_CURSOR_ANIM_FRAMES = 21
};

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0,
		NUM_MOUSE_CURSORS = 0x38
	};
};

class Win32Mouse : public Mouse
{
public:
	Win32Mouse( void );
	virtual ~Win32Mouse( void );

private:
	char m_pad004[0x6024 - 4];
};

extern CursorTextureSlot cursorTextures[Mouse::NUM_MOUSE_CURSORS][MAX_2D_CURSOR_ANIM_FRAMES];
extern "C" RenderObjClass *cursorModels[Mouse::NUM_MOUSE_CURSORS];
extern "C" HAnimClass *cursorAnims[Mouse::NUM_MOUSE_CURSORS];

class W3DMouse : public Win32Mouse
{
public:
	W3DMouse( void );
	virtual ~W3DMouse( void );

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
};

W3DMouse::W3DMouse( void )
{
	m_lastAnimTime = 0;

	// zero our event list
	for (Int i=0; i<NUM_MOUSE_CURSORS; i++)
	{
		for (Int j=0; j<MAX_2D_CURSOR_ANIM_FRAMES; j++)
			cursorTextures[i][j].clear();
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

}  // end W3DMouse
