// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// DynamicVectorClass<NamedPivotMapClass::WeightInfoStruct>::Add at 0x00196880,
// split out of hanim.cpp because retail built it with /G7 -- it tests the
// allocation flag with a single cmp byte ptr [esi+0xD],0 -- while hanim.cpp's
// HAnimComboDataClass::Set_HAnim only matches without that flag.
// LINK-DUP: the WeightInfoStruct::operator= and NamedPivotMapClass::Add bodies
// live rowed in hanim.cpp; this unit keeps operator= as inline (select-any,
// inlined into Add) and emits Add via explicit instantiation, so it defines
// no plain duplicate. Element replica is public for access, which changes no
// bytes (hanim_weight_vector_resize.cpp precedent).
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
#include <new.h>
#include <assert.h>
#include "nstrdup.h"
#include "vector.h"

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

// upstream layout: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/hanim.h
// (nested scope replica; public here for access, which changes no bytes)
class NamedPivotMapClass
{
public:
	struct WeightInfoStruct {
		WeightInfoStruct() : Name(0) {}
		~WeightInfoStruct() { if(Name) delete [] Name; }

		char *Name;
		float Weight;

		WeightInfoStruct & operator = (WeightInfoStruct const &that);
		bool operator == (WeightInfoStruct const &that) const { return &that == this; }
		bool operator != (WeightInfoStruct const &that) const { return &that != this; }
	};
};

inline NamedPivotMapClass::WeightInfoStruct & NamedPivotMapClass::WeightInfoStruct::operator = (WeightInfoStruct const &that)
{
	if(Name) delete [] Name;
	assert(that.Name != 0);
	Name = nstrdup(that.Name);
	Weight = that.Weight;
	return *this;
}

// ?Add@?$DynamicVectorClass@UWeightInfoStruct@NamedPivotMapClass@@@@QAE_NABUWeightInfoStruct@NamedPivotMapClass@@@Z
template bool DynamicVectorClass<NamedPivotMapClass::WeightInfoStruct>::Add(NamedPivotMapClass::WeightInfoStruct const &);
