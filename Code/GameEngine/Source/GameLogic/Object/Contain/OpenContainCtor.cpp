// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004649F8, 386 bytes.
// OpenContain behavior ctor over the rowed UpdateModule base (0x253390,
// thing plus data). Substantial reconstruction from retail plus the BFME1
// rider-map concept (BFME1 OpenContain tracks riders in 12-byte maps; the
// element spellings here match the rowed bodies, so the member types are
// proven even though the offsets differ from BFME1 and the names below are
// TU-local descriptive, not donor-proven).
//
// Layout (retail-measured): UpdateModule base 0x20, six secondary interface
// vptrs at +0x20..+0x34 (installed inline by their implicit ctors, then
// re-stored by the derived class, DieModule precedent), int at +0x38,
// map<int,void*> at +0x3C/+0x48/+0x5C/+0xF0 (rowed 0x33C432 spelling),
// list<int> at +0x54/+0x74 (rowed 0x4EC36C spelling, 1-byte stack allocator
// temp idiom, FloodUpdate precedent), bulk-zero member at +0x84 (rowed
// Rva0042526Member 0x42526, 0x4C memset), three floats at +0xD0, bytes and
// ints to +0xEC. The full 0xFC matches the rowed CaveContain factory news.
//
// Schedule (all probe-proven): the init list runs the five dtor members in
// retail call order (+0x3C/+0x48/+0x54/+0x5C/+0x74, EH states 1-5) with the
// trivial +0x84 member last and no state; the +0xF0 map is constructed
// explicitly in the body over raw storage (an init-list entry would arm a
// sixth state retail never has); the float pointer is declared immediately
// before its stores (an early declaration folds to direct movss, adjacency
// keeps the lea+indexed form, AssaultTransport precedent); the tail reads a
// ModuleData+0x84 flag byte into +0xDE with a null guard. The construct-
// then-memset order at +0x84 is genuine retail. Zero new pins (all callees
// rowed). Row supersedes the ctor pin.
// STLport's tree-node allocator must see the C++-linkage free wrapper at
// 0x00030830, not the CRT import, for the retail destructor shape.
#define _INC_STDLIB
typedef unsigned int size_t;
typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;
extern "C" void __cdecl free(void *block);
extern "C" {
void __cdecl abort(void);
int __cdecl abs(int value);
int __cdecl atexit(void (__cdecl *routine)(void));
double __cdecl atof(const char *string);
int __cdecl atoi(const char *string);
long __cdecl atol(const char *string);
void *__cdecl bsearch(const void *key, const void *base, size_t count,
        size_t width, int (__cdecl *compare)(const void *, const void *));
void *__cdecl calloc(size_t count, size_t size);
div_t __cdecl div(int numerator, int denominator);
void __cdecl exit(int status);
char *__cdecl getenv(const char *string);
long __cdecl labs(long value);
ldiv_t __cdecl ldiv(long numerator, long denominator);
void *__cdecl malloc(size_t size);
int __cdecl mblen(const char *string, size_t count);
size_t __cdecl mbstowcs(unsigned short *dest, const char *source, size_t count);
int __cdecl mbtowc(unsigned short *dest, const char *source, size_t count);
void __cdecl qsort(void *base, size_t count, size_t width,
        int (__cdecl *compare)(const void *, const void *));
int __cdecl rand(void);
void *__cdecl realloc(void *block, size_t size);
void __cdecl srand(unsigned int seed);
double __cdecl strtod(const char *string, char **end);
long __cdecl strtol(const char *string, char **end, int radix);
unsigned long __cdecl strtoul(const char *string, char **end, int radix);
int __cdecl system(const char *string);
size_t __cdecl wcstombs(char *dest, const unsigned short *source, size_t count);
int __cdecl wctomb(char *dest, unsigned short ch);
}

#include <map>
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <string.h>

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

class Thing;
class ModuleData;
class Object;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };
template <int NUMBITS> class BitFlags;
// Slot shapes from OpenContain.cpp, whose ??_7OpenContain@@6BUpdateModule@@@ this unit must reproduce.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


struct ContainIface20 { virtual void containIface20() = 0; };
struct ContainIface24 { virtual void containIface24() = 0; };
struct ContainIface28 { virtual void containIface28() = 0; };
struct ContainIface2C { virtual void containIface2C() = 0; };
struct ContainIface30 { virtual void containIface30() = 0; };
struct ContainIface34 { virtual void containIface34() = 0; };

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

// map<ObjectID, int>: the tree family dtor 0x00286852 -> clear 0x00286656 ->
// erase 0x00286183 (one instantiation: the self-recursive erase is not ICF-folded;
// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6 keys it by object ID).
enum ObjectID { INVALID_ID = 0 };
typedef _STL::map<ObjectID, int> ObjectIDIntMap;
class OpenContain : public UpdateModule, public ContainIface20, public ContainIface24, public ContainIface28, public ContainIface2C, public ContainIface30, public ContainIface34
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
	virtual UpdateSleepTime update();
private:
	int m_bfme38;
	_STL::map<int, void *> m_riderMapA;
	ObjectIDIntMap m_riderMapB;
	_STL::list<int> m_riderIdListA;
	int m_bfme58;
	_STL::map<int, void *> m_riderMapC;
	int m_bfme68;
	int m_bfme6C;
	int m_bfme70;
	_STL::list<int> m_riderIdListB;
	int m_bfme78;
	int m_bfme7C;
	int m_bfme80;
	Rva0042526Member m_store84;
	float m_bfmeD0;
	float m_bfmeD4;
	float m_bfmeD8;
	unsigned char m_bfmeDC;
	unsigned char m_bfmeDD;
	unsigned char m_bfmeDE;
	unsigned char m_bfmeDF;
	unsigned char m_bfmeE0;
	unsigned char m_bfmeE1;
	unsigned char m_padE2[2];
	int m_bfmeE4;
	int m_bfmeE8;
	int m_bfmeEC;
	unsigned char m_riderMapDraw[0x0C];
public:
	// retail slot 4: the rowed ?getModuleNameKey@OpenContain@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x004649F8
OpenContain::OpenContain(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_bfme38(0)
	, m_riderMapA()
	, m_riderMapB()
	, m_riderIdListA()
	, m_riderMapC()
	, m_riderIdListB()
	, m_store84()
{
	(((_STL::map<int, void *> *)(void *)m_riderMapDraw))->_STL::map<int, void *>::map<int, void *>();
	m_bfme78 = 0;
	m_bfme7C = 0;
	m_bfme80 = 0;
	m_bfme58 = 0;
	m_bfme68 = 0;
	m_bfme70 = 0;
	m_bfmeDF = 0;
	m_bfmeE0 = 0;
	m_bfmeE1 = 1;
	float *floatCells = &m_bfmeD0;
	floatCells[0] = 0.0f;
	floatCells[1] = 0.0f;
	floatCells[2] = 0.0f;
	m_bfmeDC = 0;
	memset(&m_store84, 0, 0x4C);
	m_bfme6C = 1;
	m_bfmeDD = 1;
	m_bfmeE4 = 0;
	m_bfmeEC = 0;
	m_bfmeE8 = 0;
	m_bfmeDE = m_moduleData ? *(const unsigned char *)((const char *)m_moduleData + 0x84) : 0;
}
