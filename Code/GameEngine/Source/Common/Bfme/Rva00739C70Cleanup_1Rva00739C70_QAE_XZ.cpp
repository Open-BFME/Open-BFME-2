// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common/Bfme
// 23-byte and 32-byte cleanup routines, 62-byte reset, 109-byte update, and 81-byte destructor
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

struct TexturePtr
{
	TextureBaseClass *m_ptr;
	~TexturePtr()
	{
		if ( m_ptr )
			m_ptr->Release_Ref();
	}
	TextureBaseClass *operator->() { return m_ptr; }
	operator bool() { return m_ptr != 0; }
	TexturePtr& operator=( int val ) { m_ptr = (TextureBaseClass*)val; return *this; }
};

class VirtualReleaser00739E00
{
public:
	virtual void v0();
	virtual void v1();
	virtual unsigned long __stdcall Release();
};

// The three calls made through the pointer at +0x0C are pinned under this
// spelling (clear 0x008FC7D0, methodA 0x008FC710, methodB 0x008FC660); it is a
// second view of the very same bytes W3DRadarResetSurface owns, used only so the
// emitted call names keep their existing pins.
class Member0C00739C70
{
public:
	VirtualReleaser00739E00 *m_obj;

	void clear();
	TextureBaseClass *methodA( int arg, int a, int b, int c, int d );
	TextureBaseClass *methodB( int arg, int a );
};

// Retail's destructor for this sub-object lives at 0x008FC5B0 and is defined as
// W3DRadarResetSurface::~W3DRadarResetSurface, so the member that owns it is
// spelled with that class name.
class W3DRadarResetSurface
{
public:
	VirtualReleaser00739E00 *m_obj;

	~W3DRadarResetSurface();
	void reset()
	{
		if ( m_obj )
		{
			m_obj->Release();
			m_obj = 0;
		}
	}
};

class Rva00739C70
{
public:
	~Rva00739C70();
	void cleanup();
	void reset();
	TextureBaseClass *update( int arg );
	// Retail identity is not recovered; the synthetic name records its exact
	// address while keeping this small predicate attached to the proven object.
	bool rva_00739E50();

	int                  m_int0;
	int                  m_int4;
	TexturePtr           m_ptr08;
	// Both views alias the same four bytes at +0x0C; retail has one class there
	// and only the split spelling is ours.
	W3DRadarResetSurface m_member0c;
	int                  m_flags;

	Member0C00739C70 &calls()
	{
		return *reinterpret_cast<Member0C00739C70 *>( &m_member0c );
	}
};

Rva00739C70::~Rva00739C70()
{
}
