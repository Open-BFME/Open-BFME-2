// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

typedef int Int;
typedef float Real;
typedef unsigned long UnsignedLong;

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};

class SurfaceResource
{
public:
	virtual void unused00();
	virtual UnsignedLong __stdcall addRef();
};

class W3DRadarResetSurface
{
public:
	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) : m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}

	~W3DRadarResetSurface();

private:
	SurfaceResource *m_surface;
};


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h

W3DRadarResetSurface getBackBufferSurface(Int index);
void copySurfaceRects(W3DRadarResetSurface source, const BfmeRect *sourceRect,
	W3DRadarResetSurface destination, const BfmeRect *destinationRect, Int mode);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h

// The copy constructor is emitted out of line only when something in this unit copies a surface
// reference; the drawImage that used to do so now lives in W3DDisplayDrawImageBFME2.cpp, so this
// stand-in keeps row 0x000425A9 backed by this unit.
// ?bfmeSurfaceCopyAnchor@@YAXABVW3DRadarResetSurface@@@Z absent-from-retail
void bfmeSurfaceCopyAnchor(const W3DRadarResetSurface &source)
{
	W3DRadarResetSurface copy(source);
}
