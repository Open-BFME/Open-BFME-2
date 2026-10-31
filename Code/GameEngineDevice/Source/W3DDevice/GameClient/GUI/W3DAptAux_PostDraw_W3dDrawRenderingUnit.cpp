// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB

// stlport
// Split from W3DAptAux_PostDraw.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

class WW3D
{
public:
	static void Get_Device_Resolution(int &width, int &height, int &bits, bool &windowed);
	static void Sync(unsigned int sync_time);	// 0x00117490
};

void Rva00118990();					// 0x00118990

// The renderer behind s_renderer, placeholder-named by its bracketing calls.
class BfmeHub982
{
public:
	void * __fastcall rva00111312(int count);
	void rva001116E2();				// 0x001116E2
	void bfmeBegin982C();				// 0x00111319
	void bfmeEnd982C();				// 0x00110611
};

// g_Va00DB5FB0 is only an alias of the owned global g_00DB5FB0 (ledger names column); this unit reads the owner through its own view type.
extern int g_00DB5FB0;
#define g_Va00DB5FB0 (*(int *)&g_00DB5FB0)
extern float g_Va00DEC49C;

class BfmeT982;
class AptRenderingUnit;

class W3DAptAux
{
	friend void rebuildMask();
	friend void bfmeGo982C(BfmeT982 *);
	friend void w3dDrawRenderingUnit(AptRenderingUnit *, int);
	friend void w3dCustomControlRender(const char *name, int arg1, AptRenderingUnit *renderingUnit, int arg3);

public:
	static void PostDraw();

private:
	static BfmeHub982 *s_renderer;			// 0x00DE6170
	static unsigned int s_syncTime0;			// 0x00DE6174
	static unsigned int s_syncTime1;			// 0x00DE6178
};

const char *getNameAndIndex(const AsciiString &path, Int *index, Bool fullPath);


// Retail sets up no unwind frame around the getText() temporary, so the
// compare it calls cannot throw.
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();

// The game-client DisplayString as W3DAptDisplayString reaches it (virtual
// slots by offset; target evidence).
class GameFont;
class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);		// +0x04
	virtual UnicodeString getText();			// +0x08 (WB debug block)
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void setFont(GameFont *font);			// +0x18
	virtual void slot1C();
	virtual void setWordWrap(Int wordWrap);			// +0x20
	virtual void setWordWrapCentered(Bool isCentered);	// +0x24
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void getSize(Int *width, Int *height);		// +0x3C
	virtual void slot40(); virtual void slot44();
	virtual void slot48(Real x, Real y);			// +0x48, called with (0, 0)
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"



// The Apt-side render transform copied into each shape container before it
// draws (six dwords at 0x00DE6148; target evidence).
struct AptRenderTransform
{
	float a, b, c, d, tx, ty;
};

extern AptRenderTransform g_aptRenderTransform; // native zero-filled DE6148..DE6160

class AptShape;

class AptShapeContainer
{
public:
	int unknown00;
	AptShape **first, **last;
	int unknown0C;
	AptRenderTransform matrix;			// +0x10
	void getRenderRegion(Coord2D &, Coord2D &);	// 0x000A99B8
	void render();					// 0x000A9F98
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

class AptPlayer
{
public:
 void OnCommand(const char *name, int value);
 void SetExtern(const char *name, int value);
	void OnCustomRender(const char *name, int topLeft, int bottomRight, int arg1, int arg3);	// 0x00223D8D
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

static inline Real roundToPixel(Real value)
{
	return (Real)(Int)(value + 0.5f);
}
void w3dCustomControlRender(const char *name, Int arg1, AptRenderingUnit *renderingUnit, Int arg3);


// WB 8A7590 names w3dDrawRenderingUnit at W3DAptAux.cpp lines968..973.
// Native AA8D1..AA966 proves the 149B cdecl boundary, renderer guard,
// six-word transform copy, modes -1/0/1 and pointer-valued queue operations.
// BFME1 Apt flush/rounded-bounds donors supply the established transform and
// queue views; native data/call relocations independently verify their use.
namespace _STL {
template list<AptShapeContainer*>::_Node *list<AptShapeContainer*>::_M_create_node(AptShapeContainer*const&);
}
struct Rva00785FD0Node;
// g_rva00785FD0Queue is only an alias of the owned global g_Va00DE6194 (ledger names column); this unit reads the owner through its own view type.
extern unsigned int g_Va00DE6194;
#define g_rva00785FD0Queue (*(Rva00785FD0Node * *)&g_Va00DE6194)
extern char g_rva00785FD0Dirty;
void w3dDrawRenderingUnit(AptRenderingUnit *renderingUnit,Int mode)
{
 if(!W3DAptAux::s_renderer || !renderingUnit) return;
 AptShapeContainer *const renderShape=renderingUnit->getShapes();
 AptShapeContainer *shapes=renderShape;
 if(!renderShape) return;
 renderShape->matrix=g_aptRenderTransform;
 // The existing flush names the sentinel pointer; the list header is that
 // one pointer, and the native queue stores AptShapeContainer pointers.
 _STL::list<AptShapeContainer*> &queue=*(_STL::list<AptShapeContainer*>*)&g_rva00785FD0Queue;
 switch(mode) {
 case 1: queue.insert(queue.end(),shapes);g_rva00785FD0Dirty=1;return;
 case -1: if(!queue.empty()) {queue.remove(shapes);g_rva00785FD0Dirty=1;return;}
 case 0: rebuildMask();renderShape->render();return;
 }
}
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


class Rva00786BD0Owner
{
public:
	void *find(unsigned key);
};
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


class W3DAptRenderer {public:void *__fastcall BeginTriangleList(int count);};


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
void Rva000A9192TransformPointCaller(const Rva000A9192Point *p, const Rva000A9192Matrix *m, Rva000A9192Point *out);

