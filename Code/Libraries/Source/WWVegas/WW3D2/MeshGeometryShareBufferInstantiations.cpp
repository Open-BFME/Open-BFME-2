// cl: /Ireference/shims/bfmerendobj /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Lifting MeshGeometryClass::Reset_Geometry into its own translation unit took
// meshgeometry.cpp's ShareBufferClass instantiations with it, and no other file
// in the tree instantiates them, so four claims were left with no object
// emitting their symbols:
//
//   0x00926520  ??0?$ShareBufferClass@VVector3i16@@@@QAE@HPBDH@Z
//   0x00923DA0  ?Clear@?$ShareBufferClass@E@@QAEXXZ
//   0x00923D70  ?Clear@?$ShareBufferClass@VVector3@@@@QAEXXZ
//   0x00923D50  ?Clear@?$ShareBufferClass@VVector3i16@@@@QAEXXZ
//
// This file instantiates exactly those members, with the same header set and
// the same compiler flags meshgeometry.cpp uses, so the COMDATs come back
// byte-identical to the ones Reset_Geometry used to pull in.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "meshgeometry.h"

extern void __cdecl operator delete[](void *) throw();

// ShareBufferClass<uint8> owns a raw byte array; the destructor frees it.
// The rowed constructor installs vtable 0xBD43F8, whose deleting destructor
// at 0x169D40 calls this body at 0x169D60. Declared before first use so the
// explicit specialization wins over the primary template.
template <>
ShareBufferClass<uint8>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// ShareBufferClass<unsigned long> owns a raw dword array (the vertex shade
// indices); the destructor frees it. The 0x169950 constructor installs vtable
// 0xBD4400, whose deleting destructor at 0x169D80 calls this body at
// 0x169DA0. Same explicit-specialization recipe as the uint8 destructor above.
template <>
ShareBufferClass<unsigned long>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// ShareBufferClass<Vector3> owns a raw vertex array; the destructor frees it.
// The 0x169780 constructor installs vtable 0xBD43F0, whose deleting
// destructor at 0x169D00 calls this body at 0x169D20.
template <>
ShareBufferClass<Vector3>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// ShareBufferClass<Vector3i16> (TriIndex) owns a raw index array; the
// destructor frees it. The 0x169670 constructor installs vtable 0xBD43E8,
// whose deleting destructor at 0x169CC0 calls this body at 0x169CE0.
template <>
ShareBufferClass<Vector3i16>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// ShareBufferClass<unsigned short> owns a raw word array; the destructor
// frees it. The 0x1699E0 constructor (in meshgeometry.cpp) installs vtable
// 0xBD4408, whose deleting destructor at 0x169DC0 calls this body at
// 0x169DE0.
template <>
ShareBufferClass<unsigned short>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// ShareBufferClass<char> owns a raw char array; the destructor frees it.
// The 0x169A70 constructor (in meshgeometry.cpp) installs vtable 0xBD4410,
// whose deleting destructor at 0x169E00 calls this body at 0x169E20.
template <>
ShareBufferClass<char>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// ShareBufferClass<Vector4> owns a raw plane-equation array (MeshGeometry
// PlaneEq); the destructor frees it. The 0x169B90 constructor (in
// part_buf.cpp) installs vtable 0xBD4420, whose deleting destructor at
// 0x169E80 calls this body at 0x169EA0.
template <>
ShareBufferClass<Vector4>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

void MeshGeometryShareBufferInstantiations( int count )
{
	ShareBufferClass<TriIndex> *poly = new ShareBufferClass<TriIndex>( count, "MeshGeometryClass::Poly" );
	poly->Clear();

	ShareBufferClass<uint8> *surface = new ShareBufferClass<uint8>( count, "MeshGeometryClass::PolySurfaceType" );
	surface->Clear();

	ShareBufferClass<Vector3> *vertex = new ShareBufferClass<Vector3>( count, "MeshGeometryClass::Vertex" );
	vertex->Clear();
}
