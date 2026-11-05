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
	__declspec(dllimport) __forceinline W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();
	void *m_surface;
};

struct Rva00156540Param
{
	int pad[11];
	int m_charHeight;
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

// This local geometry record owns a COM surface. The append provider keeps
// its existing opaque element spelling, also used by a texture-owning view
// elsewhere; that view's destructor is not this record's cleanup operation.
struct RenderSentenceGeometryView
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

#include "../../../../../reference/shims/wwmath/Vector2.h"

class Vector2i
{
public:
	int X;
	int Y;
};

#include "Render2DSentenceClass.h"

void Render2DSentenceClass::rva00156540(Rva00156540Param const *param)
{
	int width = TextureOffset.X - TextureStartX;
	if (0 >= width)
		return;
	float charHeight = (float)param->m_charHeight;
	RenderSentenceGeometryView chunk;
	SurfaceClass *surface = CurSurface;
	if (surface != 0)
		surface->ops->add_ref(surface);
	if (chunk.tex.m_surface != 0)
		((SurfaceClass *)chunk.tex.m_surface)->ops->release_ref((SurfaceClass *)chunk.tex.m_surface);
	chunk.f04 = Cursor.X;
	chunk.f0c = (float)Cursor.X + width;
	chunk.f08 = Cursor.Y;
	chunk.f10 = charHeight + Cursor.Y;
	chunk.f14 = (float)TextureStartX;
	chunk.tex.m_surface = CurSurface;
	chunk.f18 = (float)TextureOffset.Y;
	chunk.f1c = (float)TextureOffset.X;
	chunk.f20 = (float)TextureOffset.Y + charHeight;
	reinterpret_cast<DynamicVectorClassWide<TextureStatisticsStructWide> *>(field04)->Add(reinterpret_cast<const TextureStatisticsStructWide &>(chunk));
}
