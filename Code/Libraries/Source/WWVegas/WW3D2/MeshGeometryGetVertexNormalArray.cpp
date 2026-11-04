// cl: /O1 /Ob1 /G7 /arch:SSE /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native16AB90..16ABBC is the dirty-normal validation wrapper. WB A0CF10
// and the ZH MeshGeometryClass::Get_Vertex_Normal_Array donor establish its
// role. Target get_vert_normals16AAE0 and vtable BD43D0 slot10 establish the
// bool format argument and typed result/virtual callback independently.
// Flags18 is confirmed by matched geometry siblings. Both44B accessor and
// native143A90..143A9A forwarding wrapper are exact; original holder name is
// unknown. This retires the old BfmeC998 view and its raw-int allocator alias.
// The class is the canonical MeshGeometryClass.h; /Ob1 keeps the wrapper's
// call out of line, as retail's separate caller TU does.
// Reference: open-bfme-1@89f1588225645d9fb90151bd651aa62c489f36ae,
// game/Libraries/Source/WWVegas/WW3D2/meshgeometry.cpp (semantic lead only).
#include "MeshGeometryClass.h"
const Vector3 *MeshGeometryClass::Get_Vertex_Normal_Array(bool alternate) {
 if(Flags&4) Compute_Vertex_Normals(get_vert_normals(alternate),alternate);
 return get_vert_normals(alternate);
}
struct Rva00143A90ProviderHolder {
 MeshGeometryClass *provider;
 const Vector3 *queryZero() const;
};
const Vector3 *Rva00143A90ProviderHolder::queryZero() const {
 return provider->Get_Vertex_Normal_Array(false);
}
