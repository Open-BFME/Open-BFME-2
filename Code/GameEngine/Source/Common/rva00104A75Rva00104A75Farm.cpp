// ?rva00104A75@Rva0010461F@@QAEXXZ
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
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"

#define COORD2D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord2DCtorView.h"

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
	void rva00104A75();

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


class TextureClass;
class Render2DClass
{
public:
	int m_state;
	char m_04[0x48 - 4];
	bool m_48;
	void Render();
};

void Rva001049C7AddTriangle(Render2DClass *renderer,
	const Coord2D *v0, const Coord2D *v1, const Coord2D *v2,
	const Coord2D *uv0, const Coord2D *uv1, const Coord2D *uv2);

// The renderer's texture setter, rowed under an address-derived owner.
class Rva000456C9
{
public:
	void rva000456C9(const RefCountPtr<TextureClass> *texture);
};

// The UV rectangle the source carries at +0x14.
struct Rva00104A75Rect
{
	Coord2D lo;
	Coord2D hi;
};

struct Rva00104A75Source
{
	char m_00[0x14];
	Rva00104A75Rect m_uv;
};

// Holds the renderer's first word at a value for a scope and restores it.
struct Rva00104A75StateHold
{
	Rva00104A75StateHold(Render2DClass *renderer, int value)
		: m_renderer(renderer), m_saved(renderer->m_state)
	{
		renderer->m_state = value;
	}
	~Rva00104A75StateHold() { m_renderer->m_state = m_saved; }
	Render2DClass *m_renderer;
	int m_saved;
};

// The saved-corner check 0x00104195 is rowed under its own owner.
class Rva00104195
{
public:
	bool rva00104195();
};


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
 virtual void f17();
 virtual void f18();
 virtual void f19();
 virtual void f20();
 virtual void f21();
 virtual void f22();
 virtual void f23();
 virtual void f24();
 virtual void f25();
 virtual void f26();
 virtual void f27();
 virtual void f28();
 virtual void f29();
 virtual void f30();
 virtual void f31();
 virtual void f32();
 virtual void f33();
 virtual void f34();
 virtual void f35();
 virtual void f36();
 virtual void f37();
 virtual void f38();
 virtual void f39();
 virtual void f40();
 virtual void f41();
 virtual void f42();
 virtual void f43();
 virtual void f44();
 virtual void f45();
 virtual void f46();
 virtual void f47();
 virtual void f48();
 virtual void f49();
 virtual void f50();
 virtual void f51();
 virtual void f52();
 virtual void f53();
 virtual void f54();
 virtual void f55();
 virtual void f56();
 virtual void f57();
 virtual void f58();
 virtual void f59();
 virtual void f60();
 virtual void f61();
 virtual void f62();
 virtual void f63();
 virtual void f64();
 virtual void f65();
 virtual void f66();
 virtual void f67();
 virtual void f68();
 virtual void f69();
 virtual void f70();
 virtual void f71();
 virtual void f72();
 virtual void f73();
 virtual void f74();
 virtual void f75();
 virtual void f76();
 virtual void f77();
 virtual void f78();
 virtual void f79();
 virtual void f80();
 virtual void f81();
 virtual void f82();
 virtual void f83();
 virtual void f84();
 virtual void f85();
 virtual void f86();
 virtual void f87();
 virtual void f88();
 virtual void f89();
 virtual void f90();
 virtual void f91();
 virtual void f92();
 virtual void f93();
 virtual void f94();
 virtual Render2DClass *get2DRenderer();
};
extern Display *TheDisplay;

class Rva002D3850
{
public:
	float *GetRadarViewBoxCorner(int index);
};

inline float sqr(float operand) { return operand * operand; }

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


void Rva0010461F::rva00104A75()
{
	if (!m_edgeImage)
		return;
	Render2DClass *renderer = TheDisplay->get2DRenderer();
	if (!renderer)
		return;
	if (((Rva00104195 *)this)->rva00104195())
		rva00104359();
	renderer->m_48 = true;
	((Rva000456C9 *)renderer)->rva000456C9((const RefCountPtr<TextureClass> *)&m_edgeTexture);
	Rva00104A75StateHold hold(renderer, 1);
	const Rva00104A75Rect *uv = &((const Rva00104A75Source *)m_edgeImage)->m_uv;
	for (int i = 0; i < 4; i++) {
		int next = i + 1;
		if (next >= 4)
			next -= 4;
		Coord2D *innerNext = &m_68[next];
		Coord2D *outerNext = &m_48[next];
		Coord2D uvTopLeft;		uvTopLeft.x = uv->lo.x;
		uvTopLeft.y = uv->lo.y;
		Coord2D uvTopRight;
		uvTopRight.x = uv->hi.x;
		uvTopRight.y = uv->lo.y;
		Coord2D uvBottomRight;
		uvBottomRight.x = uv->hi.x;
		uvBottomRight.y = uv->hi.y;
		Coord2D uvBottomLeft;
		uvBottomLeft.x = uv->lo.x;
		uvBottomLeft.y = uv->hi.y;
		Coord2D *outer = &m_48[i];
		Coord2D *inner = &m_68[i];
		Rva001049C7AddTriangle(renderer, outer, inner, innerNext, &uvTopLeft, &uvTopRight, &uvBottomRight);
		Rva001049C7AddTriangle(renderer, outer, innerNext, outerNext, &uvTopLeft, &uvBottomRight, &uvBottomLeft);
	}
	renderer->Render();
}
