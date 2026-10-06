// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
//
// ?rva00156540@Render2DSentenceClass@@QAEXPBURva00156540Param@@@Z, retail 0x00156540, 256 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: offsets 0x60 cursor 0x68 texoffset 0x70 startx 0x7c cursurface match Reset 0x00155A20 donor render2dsentence.h; callees Add 0x00155630 and dtor 0x00176CB0 rowed; callers 0x00158E90.

class SurfaceClass;

struct SurfaceOps
{
	void (__stdcall *unused)(SurfaceClass *surface);
	void (__stdcall *add_ref)(SurfaceClass *surface);
	void (__stdcall *release_ref)(SurfaceClass *surface);
};

class SurfaceClass
{
public:
	SurfaceOps *ops;
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();
	void *m_surface;
};

struct Rva00156540Param
{
	int pad[11];
	int field2c;
};

struct TextureStatisticsStructWide;

template<class T>
class DynamicVectorClassWide
{
public:
	virtual ~DynamicVectorClassWide();
	virtual bool operator==(DynamicVectorClassWide const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	bool Add(T const &object);
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	char pad[2];
	int ActiveCount;
	int GrowthStep;
};

struct TextureStatisticsStructWide
{
	W3DRadarResetSurface tex;
	float f04;
	float f08;
	float f0c;
	float f10;
	float f14;
	float f18;
	float f1c;
	float f20;
};

class Vector2
{
public:
	float X;
	float Y;
};

class Vector2i
{
public:
	int X;
	int Y;
};

class Render2DSentenceClass
{
public:
	virtual ~Render2DSentenceClass();
	virtual void Reset();
	void rva00156540(Rva00156540Param const *param);
private:
	DynamicVectorClassWide<TextureStatisticsStructWide> m_sentenceData; // +4
	unsigned char m_pendingSurfaces[0x18]; // +1C
	unsigned char m_renderers[0x18]; // +34
	void *m_font; // +4C
	Vector2 m_baseLocation; // +50
	Vector2 m_location; // +58
	Vector2 m_cursor; // +60
	Vector2i m_textureOffset; // +68
	int m_textureStartX; // +70
	int m_currTextureSize; // +74
	int m_textureSizeHint; // +78
	SurfaceClass *m_curSurface; // +7C
};

void Render2DSentenceClass::rva00156540(Rva00156540Param const *param)
{
	int width = m_textureOffset.X - m_textureStartX;
	if (0 >= width)
		return;
	float charHeight = (float)param->field2c;
	TextureStatisticsStructWide chunk;
	SurfaceClass *tmpCur = m_curSurface;
	if (tmpCur != 0)
		tmpCur->ops->add_ref(tmpCur);
	if (chunk.tex.m_surface != 0)
		((SurfaceClass *)chunk.tex.m_surface)->ops->release_ref((SurfaceClass *)chunk.tex.m_surface);
	chunk.f04 = m_cursor.X;
	chunk.f0c = (float)m_cursor.X + width;
	chunk.f08 = m_cursor.Y;
	chunk.f10 = charHeight + m_cursor.Y;
	chunk.f14 = (float)m_textureStartX;
	chunk.tex.m_surface = m_curSurface;
	chunk.f18 = (float)m_textureOffset.Y;
	chunk.f1c = (float)m_textureOffset.X;
	chunk.f20 = (float)m_textureOffset.Y + charHeight;
	m_sentenceData.Add(chunk);
}
