// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

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

#include "meshgeometry.h"

void MeshGeometryShareBufferInstantiations( int count )
{
	ShareBufferClass<TriIndex> *poly = new ShareBufferClass<TriIndex>( count, "MeshGeometryClass::Poly" );
	poly->Clear();

	ShareBufferClass<uint8> *surface = new ShareBufferClass<uint8>( count, "MeshGeometryClass::PolySurfaceType" );
	surface->Clear();

	ShareBufferClass<Vector3> *vertex = new ShareBufferClass<Vector3>( count, "MeshGeometryClass::Vertex" );
	vertex->Clear();
}
