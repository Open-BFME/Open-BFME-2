// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ??0Rva0010461F@@QAE@XZ retail 0x0010461F..0x00104723 (260 bytes EH).
// Constructor of the 0x88-byte object the factory 0x0008F32C creates and
// stores in TheRva002D3627Host (0x009FF028). Base is Rva002D3573 (ctor
// 0x002D638E; MI with vtables at +0 and +0xC; WB names the base
// Palantir::Palantir as a lead only); this class stores vtables 0x00BCF770
// and 0x00BCF760. Members: three zeroed words (+0x14) the mapped image
// "RadarViewBoxEdge" looked up through TheMappedImageCollection
// (findImageByName 0x002D92F6) a texture slot (+0x24; assignment 0x000424D0)
// and three Coord2D[4] arrays (+0x28 +0x48 +0x68) built by the eh vector
// constructor iterator with the exported Coord2D ctor/dtor. When the image
// exists its name is loaded through TextureAsset::Get 0x00132D89
// and stored in the slot; the returned handle releases its texture
// (0x0061ED10). The unwind funclet also destroys the slot (its destructor is
// declared only). Class and member names are unresolved.
//
// ?rva00104359@Rva0010461F@@QAEXXZ retail 0x00104359 (710 bytes) rebuilds
// the bevelled radar view box. It takes the shortest edge of the four
// corners (GetRadarViewBoxCorner 0x002D3850), scales the edge image's size
// (+0x24) by TheDisplay's width over 1024 and caps it at that edge, then
// offsets each corner along the bisector of its two edges (angles through
// 0x0010414C, differences 0x0010416E, wrap 0x0010410F) into the inner
// (+0x48) and outer (+0x68) rings; +0x28 keeps the corners. The offset is
// one MathCoord2D added and subtracted through operator+= and operator-=;
// that is what gives retail's 0x34 frame and the loop pointer on +0x6C.
// It calls sinf and cosf: the <math.h> sin(float) and cos(float) overloads
// would emit copies that differ from retail's.
#include <math.h>
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "BFME2ParticleTextureHandles.h"

#define COORD2D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord2DCtorView.h"

class Image
{
public:
	const AsciiString &getName() const { return m_name; }
	int getImageSize() const { return m_24; }

private:
	char m_pad00[8];
	AsciiString m_name; // +0x08
	char m_pad0C[0x24 - 0x0C];
	int m_24; // +0x24
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *name, int a, int b);
};

struct CursorTextureSlot
{
	CursorTextureSlot() : Ptr(0) {}
	~CursorTextureSlot();
	void operator=(const BFME2ParticleTextureHandle &handle);
	void *Ptr;
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva002D3573 : public GameEngineDeletingBase, public Snapshot
{
public:
	Rva002D3573();
	virtual ~Rva002D3573();

private:
	void *m_holder; // +0x10
};

class Rva0010461F : public Rva002D3573
{
public:
	Rva0010461F();
	virtual ~Rva0010461F();
	void rva00104359();

private:
	int m_14;
	int m_18;
	int m_1C;
	const Image *m_edgeImage; // +0x20
	CursorTextureSlot m_edgeTexture; // +0x24
	Coord2D m_28[4];
	Coord2D m_48[4];
	Coord2D m_68[4];
};

Rva0010461F::Rva0010461F()
	: m_14(0), m_18(0), m_1C(0),
	  m_edgeImage(TheMappedImageCollection->findImageByName(AsciiString("RadarViewBoxEdge")))
{
	if (m_edgeImage != 0)
		m_edgeTexture = TextureAsset::Get(m_edgeImage->getName().str(), 1, 0);
}

class Display
{
public:
	virtual void f00() = 0; virtual void f01() = 0; virtual void f02() = 0;
	virtual void f03() = 0; virtual void f04() = 0; virtual void f05() = 0;
	virtual void f06() = 0; virtual void f07() = 0; virtual void f08() = 0;
	virtual void f09() = 0; virtual void f10() = 0; virtual void f11() = 0;
	virtual void f12() = 0; virtual void f13() = 0; virtual void f14() = 0;
	virtual void f15() = 0;
	virtual unsigned int getWidth() = 0; // slot 16
};
extern Display *TheDisplay;

class Rva002D3850
{
public:
	float *GetRadarViewBoxCorner(int index);
};

inline float sqr(float v) { return v * v; }

// Its inline members compile as PathfinderSidewaysAttack.cpp's (built /Ow)
// do, so the COMDAT copies this unit emits agree with the ones the link keeps.
#pragma optimize("w", on)
class MathCoord2D
{
public:
	MathCoord2D() {}
	MathCoord2D(const MathCoord2D &that) : x(that.x), y(that.y) {}
	MathCoord2D(float ix, float iy) : x(ix), y(iy) {}
	~MathCoord2D() {}
	MathCoord2D &operator-=(const MathCoord2D &c) { x -= c.x; y -= c.y; return *this; }
	MathCoord2D &operator+=(const MathCoord2D &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + sqr(y)); }
	float x;
	float y;
};
#pragma optimize("", on)

// Not expanded at /O1: the COMDAT is 0x001040AE, also emitted by
// PathfinderSidewaysAttack.cpp.
inline MathCoord2D operator-(MathCoord2D left, const MathCoord2D &right)
{
	left -= right;
	return left;
}

float __cdecl Rva0010410FWrap(float a);
float __cdecl Rva0010414CGet(float *p);
float __cdecl Rva0010416EFloat(float a, float b);

inline float angleOf(const MathCoord2D &mathCoord2D) { return Rva0010414CGet((float *)&mathCoord2D); }

void Rva0010461F::rva00104359()
{
	float minLength = 3.402823466e+38F;
	for (int i = 0; i < 4; ++i)
	{
		const MathCoord2D *cur = (const MathCoord2D *)((Rva002D3850 *)this)->GetRadarViewBoxCorner(i);
		int j = i + 1;
		if (j >= 4)
			j -= 4;
		const MathCoord2D *next = (const MathCoord2D *)((Rva002D3850 *)this)->GetRadarViewBoxCorner(j);
		MathCoord2D edge = *next - *cur;
		float length = edge.GetLength();
		if (minLength > length)
			minLength = length;
	}
	float size = (float)m_edgeImage->getImageSize();
	size = (float)TheDisplay->getWidth() * size / 1024.0f;
	if (size > minLength)
		size = minLength;
	const MathCoord2D *prev = (const MathCoord2D *)((Rva002D3850 *)this)->GetRadarViewBoxCorner(3);
	for (int k = 0; k < 4; ++k)
	{
		const MathCoord2D *cur = (const MathCoord2D *)((Rva002D3850 *)this)->GetRadarViewBoxCorner(k);
		int j = k + 1;
		if (j >= 4)
			j -= 4;
		const MathCoord2D *next = (const MathCoord2D *)((Rva002D3850 *)this)->GetRadarViewBoxCorner(j);
		m_48[k] = *(const Coord2D *)cur;
		m_68[k] = *(const Coord2D *)cur;
		if ((cur->x != next->x || cur->y != next->y) && (cur->x != prev->x || cur->y != prev->y))
		{
			float nextAngle = angleOf(*next - *cur);
			float prevAngle = angleOf(*prev - *cur);
			float bisector = Rva0010410FWrap(Rva0010416EFloat(prevAngle, nextAngle) * 0.5f + nextAngle);
			float half = Rva0010416EFloat(bisector, nextAngle);
			if (fabs(half) > 0.00001f)
			{
				float dist = size * 0.5f / sinf(half);
				float cosBisector = cosf(bisector);
				float sinBisector = sinf(bisector);
				MathCoord2D offset(cosBisector * dist, sinBisector * dist);
				*(MathCoord2D *)&m_48[k] += offset;
				*(MathCoord2D *)&m_68[k] -= offset;
			}
		}
		prev = cur;
	}
	for (int n = 0; n < 4; ++n)
		m_28[n] = *(const Coord2D *)((Rva002D3850 *)this)->GetRadarViewBoxCorner(n);
}
