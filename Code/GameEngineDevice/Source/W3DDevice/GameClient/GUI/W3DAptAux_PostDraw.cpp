// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Split from W3DAptAux.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
#include <math.h>

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
extern float g_Va00DEC49C;

class W3DAptAux
{
 friend void w3dDrawRenderingUnit(class AptRenderingUnit*,Int);
	friend void w3dCustomControlRender(const char *name, Int arg1, class AptRenderingUnit *renderingUnit, Int arg3);

public:
	static void PostDraw();

private:
	static BfmeHub982 *s_renderer;			// 0x00DE6170
	static UnsignedInt s_syncTime0;			// 0x00DE6174
	static UnsignedInt s_syncTime1;			// 0x00DE6178
};

// W3DAptAux::PostDraw, retail 0x000A9071.
void W3DAptAux::PostDraw()
{
	if (s_renderer)
	{
		s_renderer->rva001116E2();
		Rva00118990();
		g_Va00DB5FB0 = 0;
		g_Va00DEC49C = 0.0f;
		WW3D::Sync(s_syncTime0);
		WW3D::Sync(s_syncTime1);
	}
}
const char *getNameAndIndex(const AsciiString &path, Int *index, Bool fullPath);


// Retail sets up no unwind frame around the getText() temporary, so the
// compare it calls cannot throw.
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();

// The game-client DisplayString as W3DAptDisplayString reaches it (virtual
// slots by offset; target evidence).
#include "../../../../../GameEngine/Include/GameClient/DisplayString.h"

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


// The Apt-side render transform copied into each shape container before it
// draws (six dwords at 0x00DE6148; target evidence).
struct AptRenderTransform
{
	int m_data[6];
};

extern AptRenderTransform g_aptRenderTransform; // native zero-filled DE6148..DE6160

class AptShapeContainer
{
public:
	void getRenderRegion(Coord2D &topLeft, Coord2D &bottomRight);	// 0x000A99B8

	unsigned char m_pad00[0x10];
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
extern int g_Va00DB5FC8;

#include "../../../../../Libraries/Source/Apt/AptPlayerClass.h"

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

static inline Real roundToPixel(Real value)
{
	return (Real)(Int)(value + 0.5f);
}

// w3dCustomControlRender, retail 0x000AA645.
void w3dCustomControlRender(const char *name, Int arg1, AptRenderingUnit *renderingUnit, Int arg3)
{
	if (!renderingUnit)
		return;
	AptShapeContainer *shapes = renderingUnit->getShapes();
	if (!shapes)
		return;
	rebuildMask();
	int savedCallback = g_Va00DB5FC8;
	g_Va00DB5FC8 = (int)&Rva000A90B0;
	W3DAptAux::s_renderer->bfmeBegin982C();
	shapes->m_transform = g_aptRenderTransform;
	Coord2D topLeft, bottomRight;
	shapes->getRenderRegion(topLeft, bottomRight);
	topLeft.x = roundToPixel(topLeft.x);
	topLeft.y = roundToPixel(topLeft.y);
	bottomRight.x = roundToPixel(bottomRight.x);
	bottomRight.y = roundToPixel(bottomRight.y);
	((AptPlayer *)g_bfmeAptWindowManager)->OnCustomRender(name, (int)&topLeft, (int)&bottomRight, arg1, arg3);
	g_Va00DB5FC8 = savedCallback;
	W3DAptAux::s_renderer->bfmeEnd982C();
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
struct Rva00785FD0Node;
// g_rva00785FD0Queue is only an alias of the owned global g_Va00DE6194 (ledger names column); this unit reads the owner through its own view type.
extern unsigned int g_Va00DE6194;
#define g_rva00785FD0Queue (*(Rva00785FD0Node * *)&g_Va00DE6194)
extern char g_rva00785FD0Dirty;

void *Rva000A91D3AptAlloc(unsigned int bytes);

void Rva000A91D8AptFree(void *memory);

void Rva000A91DDOnCommand(const char *name, int value);


void *Rva006CB9D0(const char *text);
void *Rva000A91F1EmptyValue();

void Rva000A91FDSetExtern(const char *name, int value);


// The Apt string-release callback observes only a virtual destructor.
// Its concrete string type and original declaration remain unknown.
class Rva000A923EString
{
public:
 virtual ~Rva000A923EString();
};
void Rva000A923EReleaseString(Rva000A923EString *value, unsigned int flags);


// Native A994C..A99B8 copies eight floats in two four-component groups.
// WB 8A7370 independently preserves the same argument and assignment order.
// The Apt slot is SetColourTransform; component meanings and the original
// global names are not established, so the two destination blocks stay neutral.
struct Rva000A994CColors
{
 float x, y, z, w;
 void set(float a, float b, float c, float d) { x=a; y=b; z=c; w=d; }
};
extern Rva000A994CColors g_aptHostColorBlock0; // native DE6198..DE61A8
extern Rva000A994CColors g_aptHostColorBlock1;void Rva000A994CSetColor(const float *value);


#include "../../../../Include/W3DDevice/GameClient/Rva00786BD0Owner.h"
void *Rva000AA8C3LoadRenderingUnit(Rva00786BD0Owner *owner, unsigned int key);


extern unsigned char g_aptHostStateStorage[32];
// Pair comparison follows the Vector2i operation visible in WB 8A6D50.
// Keep a local neutral type: its use here proves two integers, not a class name.
struct AptSizePair {
 int x,y;
 __forceinline bool operator!=(const AptSizePair &b) const {
  return !(x==b.x && y==b.y);
 }
};
extern AptSizePair g_aptLastStageSize,g_aptLastDeviceSize; // DE61B8 and DE61C0, zero-filled
extern AptRenderTransform g_aptTransformBeforeLinearScale; // DE6130, before the linear scale
void Rva006CD6F0Get(void **,void **);
static __forceinline bool aptFar(float value) {
 float magnitude=fabs(value);
 return magnitude>0.0001f;
}
#define aptScaleX (*reinterpret_cast<float*>(g_aptHostStateStorage+0x10))
#define aptScaleY (*reinterpret_cast<float*>(g_aptHostStateStorage+0x14))
#define aptInvScaleX (*reinterpret_cast<float*>(g_aptHostStateStorage+0x18))
#define aptInvScaleY (*reinterpret_cast<float*>(g_aptHostStateStorage+0x1c))
#define aptMatrixMode (*reinterpret_cast<int*>(g_aptHostStateStorage+4))
void Rva000A92B0SetMatrix(const AptRenderTransform *input);

unsigned long Rva000A90B0(unsigned long color);


// Native A9192..A91D3 (65B, RET 0), between A90B0 and A91D3: a 2D affine
// transform of one point (out = M * p + t with a six-float a/b/c/d/tx/ty
// matrix, the Apt render-transform shape). Retail passes the matrix in EAX,
// the point in ECX and the output in EDX with no stack arguments: the private
// convention cl 7.1 picks for a file-static noinline function (the point-first
// parameter order is the one that yields retail's operand order). No retail
// call reaches this copy, so a source-only caller emits it. Names are neutral.
#include "../../../../Include/W3DDevice/GameClient/Rva000A9192Matrix.h"
struct Rva000A9192Point { float x, y; };
static __declspec(noinline) void Rva000A9192TransformPoint(const Rva000A9192Point *p, const Rva000A9192Matrix *m, Rva000A9192Point *out)
{
	out->x = m->a * p->x + m->c * p->y + m->tx;
	out->y = m->b * p->x + m->d * p->y + m->ty;
}
void Rva000A9192TransformPointCaller(const Rva000A9192Point *p, const Rva000A9192Matrix *m, Rva000A9192Point *out);

