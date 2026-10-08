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

// BF1 9cb DX8WebBrowserInitialize.cpp COM-pointer AddRef is a semantic lead.
// Target 176CC0..176CCCD is independently INT3-bounded: conditional stdcall
// slot 1 invocation on the held pointer. Original holder identity unknown.
typedef void (__stdcall *Rva00176CC0Slot)(void *);
struct Rva00176CC0Holder
{
    void *pointer;
    void invokeSlot1();
};
void Rva00176CC0Holder::invokeSlot1()
{
    void *p = pointer;
    if (p) {
        void **vtable = *(void ***)p;
        ((Rva00176CC0Slot)vtable[1])(p);
    }
}
