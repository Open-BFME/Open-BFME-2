// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// W3DAptAux.cpp -- W3DAptAux members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function and
// asserts s_renderer ("Umm, no renderer"); retail compiles out the debug
// timers and statistics and keeps a NULL-renderer guard. Retail supplies the
// bytes.
//
// Target evidence: the renderer pointer at 0x00DE6170 is flushed through a
// thiscall at 0x001116E2 (unrowed, a jump to 0x00111319), then the 2D render
// state reset 0x00118990 runs, a counter (0x00DB5FB0) and a float
// (0x00DEC49C) are cleared and WW3D::Sync is called with the two sync times
// stored after the renderer (0x00DE6174, 0x00DE6178). Their names are
// unknown and keep address tokens.
#include "ascii_string.h"
#include "unicode_string.h"
#include <ctype.h>
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP
#include <list>
#include <vector>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef float Real;

typedef unsigned int UnsignedInt;
typedef int Int;

#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

void Rva00118990();					// 0x00118990

// The renderer behind s_renderer, placeholder-named by its bracketing calls.
#include "../../../../Include/W3DDevice/GameClient/BfmeHub982.h"

// g_Va00DB5FB0 is only an alias of the owned global g_00DB5FB0 (ledger names column); this unit reads the owner through its own view type.
extern int g_00DB5FB0;
#define g_Va00DB5FB0 (*(int *)&g_00DB5FB0)

class W3DAptAux
{
	friend class AptShapeContainer;
 friend void w3dDrawRenderingUnit(class AptRenderingUnit*,Int);
	friend void w3dCustomControlRender(const char *name, Int arg1, class AptRenderingUnit *renderingUnit, Int arg3);

public:
	static void PostDraw();

private:
	static BfmeHub982 *s_renderer;			// 0x00DE6170
	static UnsignedInt s_syncTime0;			// 0x00DE6174
	static UnsignedInt s_syncTime1;			// 0x00DE6178
};


// getNameAndIndex, retail 0x000AA73A. Splits "...\\name123.ext" into the
// trailing frame index (parsed with "%d.") and either the full path or the
// file name after the last backslash. WB asserts both separators exist;
// retail returns NULL instead.
const char *getNameAndIndex(const AsciiString &path, Int *index, Bool fullPath)
{
	const char *fname = path.reverseFind('\\');
	if (!fname)
		return NULL;
	const char *digits = path.reverseFind('.');
	if (!digits)
		return NULL;
	while (isdigit(digits[-1]))
		--digits;
	sscanf(digits, "%d.", index);
	if (fullPath)
		return path.str();
	return fname + 1;
}

// Retail sets up no unwind frame around the getText() temporary, so the
// compare it calls cannot throw.
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();

// The game-client DisplayString as W3DAptDisplayString reaches it (virtual
// slots by offset; target evidence).
class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);		// +0x04
	virtual UnicodeString getText();			// +0x08
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24();
	virtual void slot28(unsigned long color, unsigned long dropColor);	// +0x28
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34(Int x, Int y);				// +0x34
	virtual void slot38(Int x, Int y, Int xDrop, Int yDrop);	// +0x38
	virtual void getSize(Int *width, Int *height);		// +0x3C
	virtual void slot40(); virtual void slot44();
	virtual void slot48(Real x, Real y);			// +0x48, called with (0, 0)
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class W3DAptDisplayString
{
public:
	virtual void SetText(const UnicodeString &text);

private:
	unsigned char m_pad04[4];
	DisplayString *m_displayString;			// +0x08 (WB member name)
	unsigned char m_pad0C[0x1c - 0xc];
	Coord2D m_size;						// +0x1C
};

// W3DAptDisplayString::SetText, retail 0x000AA7B2.
void W3DAptDisplayString::SetText(const UnicodeString &text)
{
	if (m_displayString->getText().compare(text) == 0)
		return;
	m_displayString->slot48(0.0f, 0.0f);
	m_displayString->setText(text);
	Int width, height;
	m_displayString->getSize(&width, &height);
	m_size.x = (Real)width;
	m_size.y = (Real)height;
}

// The Apt-side render transform copied into each shape container before it
// draws (six dwords at 0x00DE6148; target evidence).
struct AptRenderTransform
{
	int m_data[6];
};

AptRenderTransform g_aptRenderTransform; // native zero-filled DE6148..DE6160

class AptShape;
class AptShapeContainer
{
public:
	void render();
	void getRenderRegion(Coord2D &topLeft, Coord2D &bottomRight);	// 0x000A99B8

	unsigned char m_pad00[4];
	_STL::vector<AptShape *> m_shapes;
	AptRenderTransform m_transform;				// +0x10
};

class AptRenderingUnit
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual AptShapeContainer *getShapes();			// +0x08
};

void rebuildMask();						// 0x000AA5E1
unsigned long Rva000A90B0(unsigned long);						// 0x000A90B0

// The Apt draw callback slot (0x00DB5FC8) and the Apt player (0x00DFE4CC),
// whose OnCustomRender identity is corroborated by WB B97350 and retail 223D8D.

#include "../../../../../Libraries/Source/Apt/AptPlayerClass.h"

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

static inline Real roundToPixel(Real value)
{
	return (Real)(Int)(value + 0.5f);
}


// WB 8A7590 names w3dDrawRenderingUnit at W3DAptAux.cpp lines968..973.
// Native AA8D1..AA966 proves the 149B cdecl boundary, renderer guard,
// six-word transform copy, modes -1/0/1 and pointer-valued queue operations.
// BFME1 Apt flush/rounded-bounds donors supply the established transform and
// queue views; native data/call relocations independently verify their use.
// Keep the existing address-neutral cleanup spelling for the unrowed render
// callee; this recovery does not assert its full body is recovered.
namespace _STL {
template list<AptShapeContainer*>::_Node *list<AptShapeContainer*>::_M_create_node(AptShapeContainer*const&);
}
class Rva00785FD0Item { public:void cleanup(); };
struct Rva00785FD0Node;
// g_rva00785FD0Queue is only an alias of the owned global g_Va00DE6194 (ledger names column); this unit reads the owner through its own view type.
extern unsigned int g_Va00DE6194;
#define g_rva00785FD0Queue (*(Rva00785FD0Node * *)&g_Va00DE6194)
extern char g_rva00785FD0Dirty;


// Native ABA2F installs A91D3 at the Apt allocator callback slot E17728.
// The complete five-byte tail jump reaches the verified array allocator.
// WB 8A5F80 independently shows allocation between debug-only Apt timers;
// the original callback name is unknown.
void *Rva000A91D3AptAlloc(unsigned int bytes)
{
 return ::operator new[](bytes);
}

// The adjacent Apt free callback A91D8..A91DD is installed at E1772C
// and E17750. It tail-jumps to array delete without adding a null guard.
void Rva000A91D8AptFree(void *memory)
{
 ::operator delete[](memory);
}


// Apt command slot E17758: native A91DD..A91F1 forwards both cdecl
// arguments to the owned OnCommand member through the established global.
// WB 8A6730 calls the same named member; callback identity remains unknown.
void Rva000A91DDOnCommand(const char *name, int value)
{
 reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->OnCommand(name, value);
}

void *Rva006CB9D0(const char *text);

// Apt callback E1775C: A91F1..A91FD returns the existing string factory's
// result for the native empty literal at BBAC1C. WB 8A6750 agrees.
void *Rva000A91F1EmptyValue()
{
 return Rva006CB9D0("");
}

// Native A91FD..A9211 is the analogous SetExtern callback at E17764.
// WB 8A6770 and the owned member at 223DD7 establish the two-word ABI.
void Rva000A91FDSetExtern(const char *name, int value)
{
 reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->SetExtern(name, value);
}

// The Apt string-release callback observes only a virtual destructor.
// Its concrete string type and original declaration remain unknown.
class Rva000A923EString
{
public:
 virtual ~Rva000A923EString();
};

// Native A923E..A925D, installed at E17774. WB 8A6900 independently
// shows the 0x406 mask, explicit null guard and global-delete expression.
void Rva000A923EReleaseString(Rva000A923EString *value, unsigned int flags)
{
 if ((flags & 0x406) && value)
  ::delete value;
}

// Native A994C..A99B8 copies eight floats in two four-component groups.
// WB 8A7370 independently preserves the same argument and assignment order.
// The Apt slot is SetColourTransform; component meanings and the original
// global names are not established, so the two destination blocks stay neutral.
struct Rva000A994CColors
{
 float x, y, z, w;
 void set(float a, float b, float c, float d) { x=a; y=b; z=c; w=d; }
};
Rva000A994CColors g_aptHostColorBlock0; // native DE6198..DE61A8
Rva000A994CColors g_aptHostColorBlock1; // native DE61A8..DE61B8

void Rva000A994CSetColor(const float *value)
{
 g_aptHostColorBlock0.set(value[0], value[1], value[2], value[3]);
 g_aptHostColorBlock1.set(value[4], value[5], value[6], value[7]);
}

class Rva00786BD0Owner
{
public:
 void *find(unsigned int key);
};

// Native AA8C3..AA8D1 is installed at the Apt LoadRenderingUnit slot
// E17798. Unlike the texture callback AA8AE, it does not guard the owner.
// Reuse that callback's existing lookup spelling and provider binding.
void *Rva000AA8C3LoadRenderingUnit(Rva00786BD0Owner *owner, unsigned int key)
{
 return owner->find(key);
}

extern unsigned char g_aptHostStateStorage[32];
// Pair comparison follows the Vector2i operation visible in WB 8A6D50.
// Keep a local neutral type: its use here proves two integers, not a class name.
struct AptSizePair {
 int x,y;
 __forceinline bool operator!=(const AptSizePair &b) const {
  return !(x==b.x && y==b.y);
 }
};
AptSizePair g_aptLastStageSize,g_aptLastDeviceSize; // DE61B8 and DE61C0, zero-filled
AptRenderTransform g_aptTransformBeforeLinearScale; // DE6130, before the linear scale
void Rva006CD6F0Get(void **,void **);
#include <math.h>
static __forceinline bool aptFar(float value) {
 float magnitude=(float)fabs((double)value);
 return magnitude>0.0001f;
}
#define aptScaleX (*reinterpret_cast<float*>(g_aptHostStateStorage+0x10))
#define aptScaleY (*reinterpret_cast<float*>(g_aptHostStateStorage+0x14))
#define aptInvScaleX (*reinterpret_cast<float*>(g_aptHostStateStorage+0x18))
#define aptInvScaleY (*reinterpret_cast<float*>(g_aptHostStateStorage+0x1c))
#define aptMatrixMode (*reinterpret_cast<int*>(g_aptHostStateStorage+4))
// Apt SetMatrix callback at A92B0..A94F9 (585 bytes, cdecl pointer).
// Retail establishes the six-word transform, dimension-cache comparisons,
// zero-size/zero-scale fallbacks and 0.0001f identity tolerance. WB 8A6D50
// independently preserves the same operations and the Vector2i comparisons.
// Its float temporaries are significant to the native mixed SSE/x87 shape.
// Original callback/global names remain unknown; no donor layout is asserted.
void Rva000A92B0SetMatrix(const AptRenderTransform *input) {
 g_aptRenderTransform=*input;
 AptSizePair stage,device;
 int bits;bool windowed;
 Rva006CD6F0Get(reinterpret_cast<void**>(&stage.x),reinterpret_cast<void**>(&stage.y));
 WW3D::Get_Device_Resolution(device.x,device.y,bits,windowed);
 if(stage!=g_aptLastStageSize || device!=g_aptLastDeviceSize) {
  aptScaleX=stage.x ? (float)device.x/(float)stage.x : 1.0f;
  aptScaleY=stage.y ? (float)device.y/(float)stage.y : 1.0f;
  aptInvScaleX=aptScaleX ? 1.0f/aptScaleX : 1.0f;
  aptInvScaleY=aptScaleY ? 1.0f/aptScaleY : 1.0f;
  g_aptLastStageSize=stage;g_aptLastDeviceSize=device;
 }
 float *m=reinterpret_cast<float*>(&g_aptRenderTransform);
 m[4]*=aptScaleX;m[5]*=aptScaleY;
 g_aptTransformBeforeLinearScale=g_aptRenderTransform;
 m[0]*=aptScaleX;m[2]*=aptScaleX;m[1]*=aptScaleY;m[3]*=aptScaleY;
 if(aptFar(m[0]-1.0f) || aptFar(m[1]) || aptFar(m[2]) || aptFar(m[3]-1.0f)) aptMatrixMode=1;
 else aptMatrixMode=3;
}

// Native A90B0..A9192, 226B. WB8A5E20 independently preserves unsigned
// ARGB decode, divide255, multiplier/addend transform and unbounded packing.
// Timer calls are debug-only. Native channels read the two existing host
// blocks; their original names remain unknown. WB evaluates alpha/red/green/blue,
// while retail schedules red first. No class/layout identity inferred.
unsigned long Rva000A90B0(unsigned long color){
float a=((color>>24)&255u)/255.0f;
float r=((color>>16)&255u)/255.0f;
float g=((color>>8)&255u)/255.0f;
float b=((color>>0)&255u)/255.0f;
a=a*g_aptHostColorBlock0.x+g_aptHostColorBlock1.x;
r=r*g_aptHostColorBlock0.y+g_aptHostColorBlock1.y;
g=g*g_aptHostColorBlock0.z+g_aptHostColorBlock1.z;
b=b*g_aptHostColorBlock0.w+g_aptHostColorBlock1.w;
return (unsigned(a*255.0f)<<24)|(unsigned(r*255.0f)<<16)|(unsigned(g*255.0f)<<8)|unsigned(b*255.0f);
}

class W3DAptRenderer {public:void *__fastcall BeginTriangleList(int count);};
// Native111312 is a whole7B tail wrapper. Unmatched WB979610 independently
// shows the same ECX receiver and EDX count doubled before BeginTriangleList.
// The purpose and original wrapper name remain unknown; this unit reuses
// its established neutral renderer view.
__declspec(noinline) void *__fastcall BfmeHub982::rva00111312(int count)
{
 return reinterpret_cast<W3DAptRenderer *>(this)->BeginTriangleList(count*2);
}

// Native A9192..A91D3 (65B, RET 0), between A90B0 and A91D3: a 2D affine
// transform of one point (out = M * p + t with a six-float a/b/c/d/tx/ty
// matrix, the Apt render-transform shape). Retail passes the matrix in EAX,
// the point in ECX and the output in EDX with no stack arguments: the private
// convention cl 7.1 picks for a file-static noinline function (the point-first
// parameter order is the one that yields retail's operand order). No retail
// call reaches this copy, so a source-only caller emits it. Names are neutral.
struct Rva000A9192Matrix { float a, b, c, d, tx, ty; };
struct Rva000A9192Point { float x, y; };
static __declspec(noinline) void Rva000A9192TransformPoint(const Rva000A9192Point *p, const Rva000A9192Matrix *m, Rva000A9192Point *out)
{
	out->x = m->a * p->x + m->c * p->y + m->tx;
	out->y = m->b * p->x + m->d * p->y + m->ty;
}

// ?Rva000A9192TransformPointCaller absent-from-retail
void Rva000A9192TransformPointCaller(const Rva000A9192Point *p, const Rva000A9192Matrix *m, Rva000A9192Point *out)
{
	Rva000A9192TransformPoint(p, m, out);
}

// Private Apt ratio, retail 0x000A925D (69 bytes). BFME 1 donor
// game/GameEngine/Source/Common/BfmeConv982.cpp at 1399ad37d4 (Rva007845D0Ratio
// logic). Its three direct callers (the display-string render below) consume
// XMM0: MSVC returns a TU-local float there when the caller is visible.
// Native literals BC93B4/BCF628/BBB8D8 are 0.0001f/0.01f/1.0f.

static float rva000A925D(float denominator, float numerator)
{
	if (denominator < 0.0001f)
		return 1.0f;
	if (fabs(numerator - denominator) < 0.01f)
		return 1.0f;
	return numerator / denominator;
}

// W3DAptDisplayString's render, retail 0x000A9570 (569 bytes; WB 0x8AB920, timed as
// "DisplayStringRender"). The same object as W3DAptDisplayString above (display string
// +0x08, size +0x1C); it stays rowed under the placeholder name its BfmeConv982.cpp
// caller and pin use. The two corners go through the Apt transform (WB's inlined
// aptMatrixMul, W3DAptAux.cpp:470: out = in.x*(a,b) + in.y*(c,d) + (tx,ty)). cl 7.1
// picks each product's register operand from how its two address expressions were
// formed, so the corner arithmetic below mixes the float and AptMatrix views of the
// transform and the member and reference views of the corners; every form computes
// the same values, and this mix is the one that reproduces retail's operand order.
class BfmeT982
{
public:
	void bfmeTouch982C();

private:
	unsigned char m_pad00[8];
	DisplayString *m_displayString;			// +0x08
	Coord2D m_topLeft;				// +0x0C
	Coord2D m_bottomRight;				// +0x14
	Coord2D m_size;					// +0x1C
	unsigned long m_color;				// +0x24
	Int m_alignment;				// +0x28
	Bool m_preScaleTransform;			// +0x2C
	Bool m_dropShadow;				// +0x2D
	Bool m_centerVertically;			// +0x2E
};

// The six transform words as WB aptMatrixMul reads them.
struct AptMatrix
{
	float a, b, c, d, tx, ty;
};

void BfmeT982::bfmeTouch982C()
{
	const float *m = m_preScaleTransform ? reinterpret_cast<const float *>(&g_aptTransformBeforeLinearScale) : reinterpret_cast<const float *>(&g_aptRenderTransform);
	Coord2D topLeft, bottomRight;
	const AptMatrix &mm = *(const AptMatrix *)m;
	const Coord2D &tl = m_topLeft;
	const Coord2D &br = m_bottomRight;
	topLeft.x = m_topLeft.y * m[2] + tl.x * mm.a + m[4];
	topLeft.y = tl.x * mm.b + m_topLeft.y * mm.d + mm.ty;
	bottomRight.x = m_bottomRight.x * m[0] + br.y * mm.c + mm.tx;
	bottomRight.y = br.y * m[3] + br.x * mm.b + mm.ty;
	const Coord2D &size = m_size;
	float scaleX = rva000A925D(m_bottomRight.x - m_topLeft.x, bottomRight.x - topLeft.x);
	float scaleY = rva000A925D(m_bottomRight.y - m_topLeft.y, bottomRight.y - topLeft.y);
	float width = scaleX * size.x;
	float height = scaleY * size.y;
	float span = bottomRight.x - topLeft.x;
	if (width > span)
	{
		scaleX = rva000A925D(width, span);
		width = span;
	}
	if (scaleX == 1.0f && scaleY == 1.0f)
		m_displayString->slot48(0.0f, 0.0f);
	else
		m_displayString->slot48(width, height);
	m_displayString->slot28(Rva000A90B0(m_color), Rva000A90B0(0xff000000));
	float x = topLeft.x;
	switch (m_alignment)
	{
	case 1:
		x = bottomRight.x - width;
		break;
	case 2:
		x += (bottomRight.x - topLeft.x - width) * 0.5f;
		break;
	}
	float y = topLeft.y;
	if (m_centerVertically)
		y += (m_bottomRight.y - m_topLeft.y - m_size.y) / 2.0f;
	if (m_dropShadow)
		m_displayString->slot38((int)x, (int)y, 1, 1);
	else
		m_displayString->slot34((int)x, (int)y);
}

// AptShapeContainer::render: native A9F98..AA557; WB 8A7F00 names
// W3DAptAux.cpp:1190..1332. Native accesses establish the shape/vector,
// transform and output-vertex layouts below. Renderer/helper names remain
// neutral where only their address and ABI are established.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template <class T> class RefCountPtr {
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	T *Referent;
};
class AssetReference {
public:
	~AssetReference() { if (m_texture) m_texture->Release_Ref(); }
	operator bool() const { return m_texture != 0; }
	TextureClass *m_texture;
};
class Rva001100A6 { public: void __fastcall rva001100A6(void *vertices); };
class Rva001100C5 { public: void __fastcall rva001100C5(void *lines); };
class Rva001103A5 { public: void __fastcall rva001103A5(const RefCountPtr<TextureClass> &texture); };
class Rva000A9F23 { public: AssetReference rva000A9F23(); };
class ShroudFilter { public: int minFilter, magFilter, unused08, words0C[2]; int getMag() const { return magFilter; } void setMag(int v) { magFilter = v; } void setMin(int v) { minFilter = v; } void SetMip(int); };
#include "../../../../Include/W3DDevice/GameClient/ShroudTexture.h"
struct V2 { float X, Y; };
struct Rva001101D7;
void __fastcall Rva001101D7Draw(void *renderer, Rva001101D7 *sink, const V2 &a, const V2 &b, float width, unsigned long color);
struct AptTriangle { V2 p[3]; };
struct AptLineSegment { V2 a, b; };
struct AptVertex { V2 pos; float z; unsigned long color; V2 uv; float pad[2]; };
class AptTexturedShape {
public:
	void scaleTransformToTexture(const TextureBaseClass *texture);	// 0x000A9C39
	void *m_vptr;
	unsigned long m_color;					// +0x04
	_STL::vector<AptTriangle> m_triangles;			// +0x08
	bool m_14;
	bool m_textureSpace;					// +0x15
	unsigned char m_pad16[2];
	void *m_texture;					// +0x18
	AptRenderTransform m_uvTransform;			// +0x1C
};
class AptSolidShape {
public:
	void *m_vptr;
	unsigned long m_color;					// +0x04
	_STL::vector<AptTriangle> m_triangles;			// +0x08
};
class AptLineShape {
public:
	void *m_vptr;
	float m_width;						// +0x04
	unsigned long m_color;					// +0x08
	_STL::vector<AptLineSegment> m_segments;		// +0x0C
};
class AptShape {
public:
	virtual void slot00();
	virtual int getType();					// +0x04
	virtual AptTexturedShape *asTextured();			// +0x08
	virtual AptSolidShape *asSolid();			// +0x0C
	virtual AptLineShape *asLine();				// +0x10
};

static __forceinline void aptMatrixMul(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	out.X = in.X * m.a + in.Y * m.c + m.tx;
	out.Y = in.X * m.b + in.Y * m.d + m.ty;
}
static __forceinline void aptMatrixMulNamedY(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	out.X = in.X * m.a + in.Y * m.c + m.tx;
	float Y0 = in.X * m.b;
	float Y1 = in.Y * m.d;
	out.Y = Y0 + Y1 + m.ty;
}
static __forceinline void aptMatrixMulNamedProducts(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	float X0 = in.X * m.a;
	float X1 = in.Y * m.c;
	out.X = X0 + X1 + m.tx;
	float Y0 = in.X * m.b;
	float Y1 = in.Y * m.d;
	out.Y = Y0 + Y1 + m.ty;
}
static __forceinline void aptMatrixMulIndexed(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	const float *q = &in.X;
	out.X = q[0] * m.a + q[1] * m.c + m.tx;
	out.Y = q[0] * m.b + q[1] * m.d + m.ty;
}
static __forceinline void aptMatrixMulLineSecond(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	const float *q = &in.X;
	float X0 = (m.a * q[0]);
	float X1 = m.c * q[1];
	out.X = X0 + X1 + m.tx;
	out.Y = (((q[0] * m.b)) + ((q[1] * m.d))) + m.ty;
}
static __forceinline void aptMatrixMulSolidThird(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	const float *q = &in.X;
	float X0 = (m.a * q[0]);
	float X1 = (m.c * q[1]);
	out.X = X0 + X1 + m.tx;
	out.Y = q[0] * m.b + q[1] * m.d + m.ty;
}

static __forceinline void aptMatrixMulUVLast(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	out.X = in.X * m.a + in.Y * m.c + m.tx;
	// Preserve the native load order of the two Y products.
	out.Y = in.X * m.b + *reinterpret_cast<const volatile float *>(&in.Y) * m.d + m.ty;
}

static __forceinline void aptMatrixMulUVFirst(V2 &out, const V2 &in, const AptRenderTransform &transform)
{
	const AptMatrix &m = (const AptMatrix &)transform;
	out.X = ((in.X * m.a) + (in.Y * m.c)) + m.tx;
	// Preserve the native load order of the two Y products.
	out.Y = (in.X * m.b) + *reinterpret_cast<const volatile float *>(&in.Y) * m.d + m.ty;
}
void AptShapeContainer::render()
{
	V2 a, b;
	for (_STL::vector<AptShape *>::iterator it = m_shapes.begin(); it != m_shapes.end(); ++it) {
		AptShape *shape = *it;
		switch (shape->getType()) {
		case 0: {
			AptTexturedShape *textured = shape->asTextured();
			if (!textured)
				break;
			AssetReference texture = ((Rva000A9F23 *)textured)->rva000A9F23();
			if (texture) {
				if (!textured->m_textureSpace)
					textured->scaleTransformToTexture((const TextureBaseClass *)&texture);
				if (aptMatrixMode == 1 && ((ShroudTexture *)&texture)->getFilter()->getMag() != 1) {
					((ShroudTexture *)&texture)->getFilter()->setMag(aptMatrixMode);
					((ShroudTexture *)&texture)->getFilter()->setMin(aptMatrixMode);
					((ShroudTexture *)&texture)->getFilter()->SetMip(aptMatrixMode);
				}
			}
			unsigned long color = Rva000A90B0(textured->m_color);
			((Rva001103A5 *)W3DAptAux::s_renderer)->rva001103A5(*(const RefCountPtr<TextureClass> *)&texture);
			AptVertex *v = (AptVertex *)((W3DAptRenderer *)W3DAptAux::s_renderer)->BeginTriangleList(textured->m_triangles.size());
			if (v) {
				const AptRenderTransform &uvTransform = textured->m_uvTransform;
				// Textured triangles use the native 1/0/2 winding.
				const int firstVertex = 1;
				const int secondVertex = 0;
				const int thirdVertex = 2;
				const int depth = 0;
				const int vertexStep = 1;
				for (_STL::vector<AptTriangle>::iterator t = textured->m_triangles.begin(); t != textured->m_triangles.end(); ++t) {
					const int first = firstVertex;
					const int second = secondVertex;
					const int third = thirdVertex;
					const AptTriangle &tri = *t;
					aptMatrixMul(v->pos, tri.p[first], m_transform);
					v->z = (float)depth;
					v->color = color;
					aptMatrixMulUVFirst(v->uv, tri.p[first], uvTransform);
					v += vertexStep;
					aptMatrixMul(v->pos, tri.p[second], m_transform);
					v->z = (float)depth;
					v->color = color;
					aptMatrixMul(v->uv, tri.p[second], uvTransform);
					v += vertexStep;
					aptMatrixMulIndexed(v->pos, tri.p[third], m_transform);
					v->z = (float)depth;
					v->color = color;
					aptMatrixMulUVLast(v->uv, tri.p[third], uvTransform);
					v += vertexStep;
				}
				((Rva001100A6 *)W3DAptAux::s_renderer)->rva001100A6(v);
			}
			break;
		}
		case 1: {
			AptSolidShape *solid = shape->asSolid();
			if (!solid)
				break;
			unsigned long color = Rva000A90B0(solid->m_color);
			((Rva001103A5 *)W3DAptAux::s_renderer)->rva001103A5(RefCountPtr<TextureClass>());
			AptVertex *v = (AptVertex *)((W3DAptRenderer *)W3DAptAux::s_renderer)->BeginTriangleList(solid->m_triangles.size());
			if (!v)
				break;
			for (_STL::vector<AptTriangle>::iterator t = solid->m_triangles.begin(); t != solid->m_triangles.end(); ++t) {
				// Solid triangles use the native 0/2/1 winding.
				const int first = 0;
				const int second = 2;
				const int third = 1;
				const int depth = 0;
				const int vertexStep = 1;
				const AptTriangle &tri = *t;
				aptMatrixMulNamedProducts(v->pos, tri.p[first], m_transform);
				v->z = (float)depth;
				v->color = color;
				v += vertexStep;
				aptMatrixMul(v->pos, tri.p[second], m_transform);
				v->z = (float)depth;
				v->color = color;
				v += vertexStep;
				aptMatrixMulSolidThird(v->pos, tri.p[third], m_transform);
				v->z = (float)depth;
				v->color = color;
				v += vertexStep;
			}
			((Rva001100A6 *)W3DAptAux::s_renderer)->rva001100A6(v);
			break;
		}
		case 2: {
			AptLineShape *line = shape->asLine();
			if (!line)
				break;
			unsigned long color = Rva000A90B0(line->m_color);
			((Rva001103A5 *)W3DAptAux::s_renderer)->rva001103A5(RefCountPtr<TextureClass>());
			void *lines = W3DAptAux::s_renderer->rva00111312(line->m_segments.size());
			if (!lines)
				break;
			for (_STL::vector<AptLineSegment>::iterator g = line->m_segments.begin(); g != line->m_segments.end(); ++g) {
				const AptLineSegment &segment = *g;
				aptMatrixMulNamedY(a, segment.a, m_transform);
				aptMatrixMulLineSecond(b, segment.b, m_transform);
				Rva001101D7Draw(W3DAptAux::s_renderer, (Rva001101D7 *)&lines, a, b, line->m_width, color);
			}
			((Rva001100C5 *)W3DAptAux::s_renderer)->rva001100C5(lines);
			break;
		}
		}
	}
}
