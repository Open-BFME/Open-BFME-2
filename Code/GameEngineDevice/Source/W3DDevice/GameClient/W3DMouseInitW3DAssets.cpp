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

#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

#define NULL 0

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

struct CursorInfo
{
	char m_pad00[0x30];
	AsciiString W3DModelName;
	AsciiString W3DAnimName;
	Real W3DScale;
	Bool loop;
	char m_pad3D[0x54 - 0x3D];
};

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0,
		NUM_MOUSE_CURSORS = 0x38
	};

	virtual ~Mouse();

protected:
	char m_pad004[0x0C - 4];
	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
	char m_pad126C[0x12E3 - 0x126C];
	Bool m_orthoCamera;
	Real m_orthoZoom;
	char m_pad12E8[0x6024 - 0x12E8];
};

class W3DMouse : public Mouse
{
private:
	char m_pad6024[0x609C - 0x6024];
	CameraClass *m_camera;

	void initW3DAssets( void );
};

extern "C" CriticalSectionClass mutex;
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
