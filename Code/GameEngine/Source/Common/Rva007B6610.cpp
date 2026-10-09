// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /GX-
// stlport
//
// ?dup_007b6610@@YAXXZ is intentionally opaque. Retail's data pointer at
// 0x009A5DD0 names VA 0x00BB6610; the 30-byte body returns at 0x007B662D,
// followed by two int3 bytes before the next pointer's target at 0x007B6630.
//
// Target evidence: it calls the rowed 12-byte vector constructor at RVA
// 0x00142E20 on the object at VA 0x00E0ABB4, then registers VA 0x00BB9BC0
// with _atexit. That callback sets ECX to the same object and tail-jumps to
// 0x00689DB0. This establishes the initialization behavior, not the object's
// element type or an owning source-level global.
//
// The BFME1 source
// reference/open-bfme-1/game/GameEngine/Source/Common/StaticInit/Rva00C6C3F0Init.cpp
// compiles the same 30-byte initializer shape under /O2 /MD, but BFME1 folds
// it across eight initializers. Its name is not carried over as target identity.

#include <new>
#include <stdlib.h>
#include <vector>

// Address-derived link alias for the target's direct call to the already-rowed
// vector constructor. The member-pointer cast below supplies the target thiscall
// ABI without asserting that the target object is vector<void *>.
extern void Rva00142E20();
// Existing global owner for the initialized storage at 0x00E0ABB4.
extern unsigned int g_Va00E0ABB4;
// Rowed ten-byte atexit thunk at RVA 0x007B9BC0.
extern void __cdecl rva007B9BC0(void);

struct RvaEmptyAlloc
{
	char unused;
};

void Rva007B6610()
{
	typedef void (_STL::vector<void *>::*Member)(const RvaEmptyAlloc &);
	union { void (*function)(); Member method; } call;
	RvaEmptyAlloc allocator;
	call.function = Rva00142E20;
	(((_STL::vector<void *> *)&g_Va00E0ABB4)->*call.method)(allocator);
	atexit(rva007B9BC0);
}

enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
class GeometryInfo {
public:
	GeometryInfo(GeometryType, bool, float, float, float);
	virtual ~GeometryInfo();
};
extern unsigned g_Va00E0C150;
extern "C" void __cdecl rva007B9BF0(void);

void Rva007B6640InitializeGeometry()
{
	new ((void *)&g_Va00E0C150) GeometryInfo(GEOMETRY_SPHERE, true, 2.0f, 2.0f, 2.0f);
	atexit(rva007B9BF0);
}

