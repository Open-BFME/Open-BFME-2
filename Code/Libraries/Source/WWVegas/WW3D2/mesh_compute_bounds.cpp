// cl: /Ireference/shims/bfmerendobj /arch:SSE2 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "rendobj.h"
#include "vector3.h"
#include "vp.h"
#include <math.h>

// The vendored MeshGeometryClass header has the BFME1 field run: its bounds
// start at +0x4C.  BFME2 keeps VertexCount at +0x28 and Vertex at +0x30, and
// retail reads the bounds at +0x60 through +0x84.  The intervening fields are
// not independently identified; this TU-local declaration carries only the
// proven offsets without changing the shared header used by the other mesh
// bodies.
template <class T>
class ShareBufferClass
{
private:
	unsigned char m_header[0x0C];

public:
	T *Array;
	T *Get_Array() { return Array; }
};

class MeshGeometryClass
{
public:
	static void (MeshGeometryClass::*emit_compute_bounds())(Vector3 *)
	{
		return &MeshGeometryClass::Compute_Bounds;
	}

	void Set_Flag(int flag, bool onoff)
	{
		if (onoff) {
			Flags |= flag;
		} else {
			Flags &= ~flag;
		}
	}

protected:
	virtual void Compute_Bounds(Vector3 *verts);

private:
	unsigned char m_prefix[0x14];			// vptr + prefix places Flags at +0x18
	int Flags;
	int m_before_vertex_count[3];		// VertexCount at +0x28
	int VertexCount;
	int m_before_vertex;
	ShareBufferClass<Vector3> *Vertex;		// ShareBuffer array at +0xC
	void *m_before_bounds[11];			// BoundBoxMin at +0x60
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	Vector3 BoundSphereCenter;
	float BoundSphereRadius;
};

void (MeshGeometryClass::*kComputeBounds)(Vector3 *) = MeshGeometryClass::emit_compute_bounds();

void MeshGeometryClass::Compute_Bounds(Vector3 *verts)
{
	BoundBoxMin.Set(0,0,0);
	BoundBoxMax.Set(0,0,0);
	BoundSphereCenter.Set(0,0,0);
	BoundSphereRadius = 0.0;

	if (VertexCount == 0) {
		return;
	}

	if (verts == NULL) {
		verts = Vertex->Get_Array();
	}
	VectorProcessorClass::MinMax(verts,BoundBoxMin,BoundBoxMax,VertexCount);

	BoundSphereCenter = (BoundBoxMin + BoundBoxMax)/2.0f;
	BoundSphereRadius = (float)(BoundBoxMax-BoundSphereCenter).Length2();
	BoundSphereRadius = ((float)sqrt(BoundSphereRadius))*1.00001f;
	Set_Flag(1,false);
}
