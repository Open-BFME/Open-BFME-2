// cl: /G7 /O2 /DNDEBUG /MD /EHsc /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
//
// Six WWLib VectorClass<T> global teardowns at 0x007B7280, 0x007B72C0,
// 0x007B7300, 0x007B7340, 0x007B7380 and 0x007B7400 (59 bytes each).
//
// Retail stores the matching VectorClass<T> vtable and then clears the
// allocation. Use the real qualified destructor so its vptr store refers to
// that canonical vtable instead of a second zero-filled address anchor.
// The six 59-byte bodies and the 16-byte VectorClass layout are independently
// checked against BFME2 retail; the implementation comes from the committed
// BFME1 vector.h (32774ab03393709a7f14331ba8d98d281a55ffd9).
#include "vector3.h"
#include "vector4.h"
#include "vector.h"
// These existing virtuals belong to their already linked providers.
template <> bool VectorClass<Vector3>::operator==(VectorClass<Vector3> const &) const;
template <> int VectorClass<Vector3>::ID(Vector3 const &);
template <> int VectorClass<Vector3>::ID(Vector3 const *);

void rva007B7280();
void rva007B72C0();
void rva007B7300();
void rva007B7340();
void rva007B7380();

class PointGroupClass
{
	friend void rva007B7280();
	friend void rva007B72C0();
	friend void rva007B7300();
	friend void rva007B7340();
	friend void rva007B7380();
	static VectorClass<Vector3> compressed_loc;		// VA 0x00DF94D0, vtable 0x00BCEFAC
	static VectorClass<Vector4> compressed_diffuse;		// VA 0x00DF94B0, vtable 0x00BD4EB4
	static VectorClass<float> compressed_size;		// VA 0x00DB6488, vtable 0x00BD4ECC
	static VectorClass<unsigned char> compressed_orient;	// VA 0x00DB6498, vtable 0x00BD4E9C
	static VectorClass<unsigned char> compressed_frame;	// VA 0x00DB64A8, vtable 0x00BD4E9C
};
extern VectorClass<Vector3> VertexLoc;			// VA 0x00DF708C, vtable 0x00BCEFAC

// Retail compiler-generated global teardowns occupy .text$yd.
#pragma code_seg(".text$yd")
void rva007B7280()
{
	PointGroupClass::compressed_loc.VectorClass<Vector3>::~VectorClass();
}

void rva007B72C0()
{
	PointGroupClass::compressed_diffuse.VectorClass<Vector4>::~VectorClass();
}

void rva007B7300()
{
	PointGroupClass::compressed_size.VectorClass<float>::~VectorClass();
}

void rva007B7340()
{
	PointGroupClass::compressed_orient.VectorClass<unsigned char>::~VectorClass();
}

void rva007B7380()
{
	PointGroupClass::compressed_frame.VectorClass<unsigned char>::~VectorClass();
}

void rva007B7400()
{
	VertexLoc.VectorClass<Vector3>::~VectorClass();
}

#pragma code_seg()
