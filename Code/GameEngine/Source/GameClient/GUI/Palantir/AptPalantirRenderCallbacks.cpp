// cl: /DNDEBUG /MD
//
// BFME2's palantir Apt render callbacks, 0x002D3125 onward, bound by these
// names ("AptPalantir::ClipRadar" ...) as member pointers by the screen's
// registration 0x002D57B6; that binding is their only reference. The
// screen's other callbacks are in AptPalantirCallbacks.cpp; these take the
// render arguments (ret 0x10) and convert with SSE, so they build here.
//
// Target facts: each pops four dword arguments and reads only the first
// two, as pairs of floats. The parameter types are inferred from that use
// (BFME1's AptPalantirClipRadar.cpp calls the pair PalantirPoint); the last
// two are never read and their types are unknown.

struct PalantirPoint
{
	float x;
	float y;
};

// The radar window override at +0x58 (RadarWindowOverride.cpp's class):
// vslot 15 draws a line, vslot 16 draws the radar's view box.
class RadarWindowOverrideSource
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void drawLine(int x0, int y0, int x1, int y1);
	virtual void drawViewBox();
};

// The movie window at +0x78: Rva00524A2D.cpp's four-int setter, then its
// vslot 12.
class Rva00524A2D
{
public:
	void rva00524A2D(int a, int b, int c, int d);
};

class PalantirMovieWindow
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void refresh();
};

class AptPalantir
{
public:
	void ClipRadar(const PalantirPoint *origin, const PalantirPoint *extent, void *unused3, void *unused4);
	void RenderRadarViewBox(const PalantirPoint *origin, const PalantirPoint *extent, void *unused3, void *unused4);
	void RenderMovie(const PalantirPoint *origin, const PalantirPoint *extent, void *unused3, void *unused4);
	void RenderGlobe(const PalantirPoint *from, const PalantirPoint *to, void *unused3, void *unused4);

private:
	unsigned char m_pad000[0x58];
	RadarWindowOverrideSource *m_radar; // +0x58
	unsigned char m_pad05c[0x68 - 0x5C];
	int m_radarLeft; // +0x68
	int m_radarTop; // +0x6C
	int m_radarRight; // +0x70
	int m_radarBottom; // +0x74
	PalantirMovieWindow *m_movieWindow; // +0x78
};

// Retail 0x002D3125, 87 bytes: "AptPalantir::ClipRadar".
void AptPalantir::ClipRadar(const PalantirPoint *origin, const PalantirPoint *extent, void *unused3, void *unused4)
{
	m_radarLeft = (int)(origin->x + 0.5f);
	m_radarTop = (int)(origin->y + 0.5f);
	m_radarRight = m_radarLeft + (int)(extent->x + 0.5f);
	m_radarBottom = m_radarTop + (int)(extent->y + 0.5f);
}

// Retail 0x002D32A3, 11 bytes: "AptPalantir::RenderRadarViewBox".
void AptPalantir::RenderRadarViewBox(const PalantirPoint *origin, const PalantirPoint *extent, void *unused3, void *unused4)
{
	m_radar->drawViewBox();
}

// Retail 0x002D32AE, 70 bytes: "AptPalantir::RenderMovie".
void AptPalantir::RenderMovie(const PalantirPoint *origin, const PalantirPoint *extent, void *unused3, void *unused4)
{
	((Rva00524A2D *)m_movieWindow)->rva00524A2D((int)origin->x, (int)origin->y,
		(int)(origin->x + extent->x), (int)(origin->y + extent->y));
	m_movieWindow->refresh();
}

// Retail 0x002D32F4, 96 bytes: "AptPalantir::RenderGlobe".
void AptPalantir::RenderGlobe(const PalantirPoint *from, const PalantirPoint *to, void *unused3, void *unused4)
{
	m_radar->drawLine((int)(from->x + 0.5f), (int)(from->y + 0.5f),
		(int)(to->x + 0.5f), (int)(to->y + 0.5f));
}
