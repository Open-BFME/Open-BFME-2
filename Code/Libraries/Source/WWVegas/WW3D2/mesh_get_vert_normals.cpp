// cl: /Ireference/shims/bfmerendobj /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include <string.h>
// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call); this TU builds /G7 which emits add esp,4
// instead. Compile just the base class for size so our COMDAT matches the
// first copy in link order. Code this TU's rows inline keeps this TU's flags.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "sharebuf.h"
#include "vector3.h"

// Their byte-matched specializations live in MeshGeometryShareBufferInstantiations.cpp.
// Do not implicitly re-emit their virtual destructors in this TU.
template <> ShareBufferClass<Vector3>::~ShareBufferClass();

// MeshGeometryClass::get_vert_normals(bool), retail 0x0016AAE0, 170 bytes.
// VertexCount is at +0x28, VertexNorm at +0x38, AlternateVertexNorm at +0x3C.
class MeshGeometryClass
{
public:
	typedef Vector3 *(MeshGeometryClass::*GetVertNormalsFn)(bool);
	static GetVertNormalsFn emit_get_vert_normals()
	{
		return &MeshGeometryClass::get_vert_normals;
	}

protected:
	Vector3 *get_vert_normals(bool alternate_format);

private:
	unsigned char m_prefix[0x28];
	int VertexCount;
	unsigned char m_pad2c[0x0c];
	ShareBufferClass<Vector3> *VertexNorm;
	ShareBufferClass<Vector3> *AlternateVertexNorm;
};

MeshGeometryClass::GetVertNormalsFn kGetVertNormals = MeshGeometryClass::emit_get_vert_normals();

Vector3 *MeshGeometryClass::get_vert_normals(bool alternate_format)
{
	if (alternate_format) {
		if (!AlternateVertexNorm) {
			AlternateVertexNorm = new ShareBufferClass<Vector3>(VertexCount, "MeshGeometryClass::VertexNorm", 0);
			AlternateVertexNorm->Clear();
		}
		return AlternateVertexNorm->Get_Array();
	}
	return VertexNorm->Get_Array();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeConv998@BfmeC998@@QAEHH@Z=?get_vert_normals@MeshGeometryClass@@IAEPAVVector3@@_N@Z")
