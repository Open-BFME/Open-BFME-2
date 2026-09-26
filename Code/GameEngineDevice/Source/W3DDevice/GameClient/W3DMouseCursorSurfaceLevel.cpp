// cl: /O1 /Oy- /MD /EHsc /DNDEBUG

// ?Get_Surface_Level@CursorTextureSlot@@QAE?AVW3DRadarResetSurface@@XZ,
// retail 0x00132D70, 25 bytes. Zero-level forwarder: the cursor loader keeps
// the per-slot leveled fetcher (0x0013289D) as the worker and exposes the
// common case (mip level 0) under the BFME1 Get_Surface_Level spelling.

class W3DRadarResetSurface
{
	void *m_surface;

public:
	~W3DRadarResetSurface();
};

struct CursorTextureSlot
{
	void *Ptr;

	W3DRadarResetSurface Get_Surface_Level(void);
	W3DRadarResetSurface Get_Surface_Level(int level);
};

// ?Get_Surface_Level@CursorTextureSlot@@QAE?AVW3DRadarResetSurface@@XZ
W3DRadarResetSurface CursorTextureSlot::Get_Surface_Level(void)
{
	return Get_Surface_Level(0);
}
