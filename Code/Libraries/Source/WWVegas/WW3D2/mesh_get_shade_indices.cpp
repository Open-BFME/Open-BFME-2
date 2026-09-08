// cl: /Ireference/shims/bfmerendobj /arch:SSE2 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "rendobj.h"
#include "sharebuf.h"

// MeshGeometryClass's BFME2 VertexShadeIdx slot is at +0x4C.  The vendored
// header's helper still uses its BFME1 +0x54 spelling, so keep this accessor's
// proven retail offsets local while leaving the shared mesh header untouched.
class MeshGeometryClass
{
public:
	typedef uint32 *(MeshGeometryClass::*GetShadeIndicesFn)(bool);
	static GetShadeIndicesFn emit_get_shade_indices()
	{
		return &MeshGeometryClass::get_shade_indices;
	}

protected:
	uint32 *get_shade_indices(bool create);

private:
	unsigned char m_prefix[0x28];			// VertexCount is at +0x28
	int VertexCount;
	unsigned char m_before_shade[0x20];
	ShareBufferClass<uint32> *VertexShadeIdx;	// retail pointer is at +0x4C
};

MeshGeometryClass::GetShadeIndicesFn kGetShadeIndices = MeshGeometryClass::emit_get_shade_indices();

uint32 *MeshGeometryClass::get_shade_indices(bool create)
{
	if (create && !VertexShadeIdx) {
		VertexShadeIdx = NEW_REF(ShareBufferClass<uint32>,(VertexCount, "MeshGeometryClass::VertexShadeIdx"));
	}
	if (VertexShadeIdx) {
		return VertexShadeIdx->Get_Array();
	}
	return NULL;
}
