// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Open-BFME: MeshGeometryClass's base (in-place) destructor at retail 0x00927880.
// Retail body: Reset_Geometry(0,0), then the implicit base-destructor chain in
// reverse declaration order -- MultiListObjectClass (out-of-line call, "this"
// adjusted to the +8 subobject), then RefCountClass (trivial, inlined, which
// is why its own vtable identity re-stamp appears without a separate call).
// W3DMPO is empty and contributes nothing.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
// Retail's RefCountClass inline copies (scalar deleting dtor 0x00072899) are
// the size form: compile this class for size, as hlod.cpp does.
#pragma optimize("s", on)
class RefCountClass
{
public:
	virtual void Delete_This(void) { delete this; }
protected:
	virtual ~RefCountClass(void) {}
private:
	int NumRefs;
};
#pragma optimize("", on)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
#include "../WWLib/MultiListObjectClass.h"

class W3DMPO
{
};

class ChunkLoadClass;
class Vector3;
class Vector4;
enum WW3DErrorType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~MeshGeometryClass();
	// The rest of the RefCountClass-side vtable, as meshgeometry.cpp emits it;
	// declared so this unit's ??_7 copy is the same table.
	virtual bool Load_W3D(ChunkLoadClass &cload);

	void Reset_Geometry(int polycount, int vertcount, bool keepAlloc = true);

protected:
	virtual void Compute_Plane_Equations(Vector4 *array);
	virtual void Compute_Vertex_Normals(Vector3 *array, bool alternate);
	virtual void Compute_Bounds(Vector3 *verts);
};

// ??1MeshGeometryClass@@UAE@XZ
MeshGeometryClass::~MeshGeometryClass()
{
	Reset_Geometry(0, 0, true);
}
