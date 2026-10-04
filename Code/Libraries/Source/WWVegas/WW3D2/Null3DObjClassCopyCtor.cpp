// cl: /Ob1 /G7 /arch:SSE /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Null3DObjClass name ctor (0x00180EB0 / 51B), copy ctor (0x00180EF0 / 56B)
// and operator= (0x00180F30 / 49B). Dedicated TU so nullrobj.cpp Clone keeps
// its inc-eax strcpy; /G7 emits add eax,1.
//
// ?Rva00181040@Rva00180EA0@@UAEPAXXZ @ 0x00181040 (135B): slot 15 offset 0x3C
// of vtable 0x007D5090 (class of ??1Rva00180EA0@@UAE@XZ). Factory that
// news a Null3DObjClass with literal "NULL": new(0xE4) + RenderObjClass ctor
// + Null vtables 0xBD50D0/0xBD473C + strcpy from 0xBBE8D4 "NULL" via add
// loop. Same-TU inline of the name ctor (now inline + /Ob1) reproduces the
// retail inlined RenderObj call; slot 0 returns the same "NULL" string
// (0x00180E60) and slot 13 the 'NULL' tag (0x00180E70).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include "rendobj.h"
#include "nullrobj.h"
#include <string.h>

void * __cdecl operator new(unsigned int);

inline Null3DObjClass::Null3DObjClass(const char * name)
{
	strcpy(Name, name);
}

Null3DObjClass::Null3DObjClass(const Null3DObjClass & src)
{
	strcpy(Name, src.Name);
}

Null3DObjClass & Null3DObjClass::operator = (const Null3DObjClass & that)
{
	strcpy(Name, that.Name);
	RenderObjClass::operator = (that);
	return *this;
}

// Slot 15 factory of the 16-slot prototype vtable 0x007D5090. The 15
// placeholders pad slots 0-14 (slot 0 is the "NULL" name getter 0x00180E60,
// slot 13 the 'NULL' tag 0x00180E70); they are never defined here so only
// this body's bytes are verified, following the Rva0035D0D1 vslot precedent.
class Rva00180EA0
{
public:
	virtual void _slot000();
	virtual void _slot001();
	virtual void _slot002();
	virtual void _slot003();
	virtual void _slot004();
	virtual void _slot005();
	virtual void _slot006();
	virtual void _slot007();
	virtual void _slot008();
	virtual void _slot009();
	virtual void _slot010();
	virtual void _slot011();
	virtual void _slot012();
	virtual void _slot013();
	virtual void _slot014();
	virtual void *Rva00181040();
};

void *Rva00180EA0::Rva00181040()
{
	return new Null3DObjClass("NULL");
}

// Zero Hour's nullrobj.cpp bounds (vtable 0x00BD50D0 slots 67 and 68,
// retail 0x00180FE0 and 0x00181010): a 0.1 sphere and box about the origin,
// stored with SSE as this unit's /arch:SSE emits them.
void Null3DObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	sphere.Center.Set(0,0,0);
	sphere.Radius = 0.1f;
}

void Null3DObjClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	box.Center.Set(0,0,0);
	box.Extent.Set(0.1f,0.1f,0.1f);
}
