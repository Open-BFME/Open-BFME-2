// cl: /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc
//
// VectorClass<Vector3>::VectorClass(int, Vector3 const *) at 0x000F0D2F,
// 150 bytes. It is the base-class constructor of every DynamicVectorClass
// <Vector3> (pointgr.h's compressed_loc/transformed_loc, snappts.h, the
// DX8 temp vertex buffers) and its only per-instantiation operand is the
// class vftable reloc.
//
// It was served as ??0?$VectorClass@VKeyClass@Curve3DClass@@@@... from the
// reloc harvested at 0xF1C85, a call from the byte-true curve.cpp
// DynamicVectorClass<Curve3DClass::KeyClass> constructor. That attribution is
// an ICF fold artifact: Curve3DClass::KeyClass is {Vector3 Point; float Time;}
// = 16 bytes, and curve.cpp's own instantiation of this ctor differs from
// retail in exactly one instruction, 20 0x4e:
//
//     retail  imul eax, eax, 0xc      (element stride 12)
//     curve   shl  eax, 4             (element stride 16)
//
// The vftable 0x00BCEFAC this constructor stores confirms a 12-byte element:
// its ID(const T *) slot divides by 12, its ID(const T&) slot compares three
// floats, and its operator== walks the elements. Vector3 (three floats,
// WWINLINE empty default constructor, so the array-construction iterator is
// emitted) is the 12-byte non-trivial representative, matching the existing
// VectorClass<Vector3> rows for ID(const T *) at 0x001298B0 and the deleting
// destructor at 0x001A3B90.
//
// The body is Vector.H's constructor, reached through the array-construction
// iterator because T is non-trivial; cl 13.10 emits it only under /O1 and
// /arch:SSE2 (the same flags curve.cpp uses).

#include "always.h"
#include <new.h>
#include "vector3.h"
#include "vector.h"

template <> void VectorClass<Vector3>::Clear();
// operator==, ID(T const &) and ID(T const *) compile here to retail's table
// slots 0x000F1C16, 0x000F0DC5 and 0x000F0E20 (vtable 0x00BCEFAC).

template VectorClass<Vector3>::VectorClass(int, Vector3 const *);
