// cl: /DNDEBUG /MD /EHsc

// W3DRadarResetSurface::~W3DRadarResetSurface, transferred from the exact
// BFME1 reconstruction
// (Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarResetSurface_destructor.cpp).
// The temporary wrapper owns a SurfaceClass-like pointer at offset zero.
// Retail BFME2 releases that resource through vtable slot 2, identically.

typedef void (__stdcall *SurfaceRelease)( void *surface );

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

// ??1W3DRadarResetSurface@@QAE@XZ
W3DRadarResetSurface::~W3DRadarResetSurface()
{
	void *surface = m_surface;
	if (surface)
	{
		void **vtable = *reinterpret_cast<void ***>( surface );
		SurfaceRelease release = reinterpret_cast<SurfaceRelease>( vtable[ 2 ] );
		release( surface );
	}
}
