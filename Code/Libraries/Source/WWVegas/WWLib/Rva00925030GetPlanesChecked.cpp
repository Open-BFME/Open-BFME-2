// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?getPlanesChecked@Rva00925030Geometry@@QAEPAVVector4@@_N@Z
#include "../WW3D2/MeshGeometryClass.h"

struct Rva00925030Geometry : MeshGeometryClass {
	Vector4* getPlanesChecked(bool create);
};
Vector4* Rva00925030Geometry::getPlanesChecked(bool create)
{
	Vector4* planes = get_planes(create);
	if (planes && (Flags & MeshGeometryClass::DIRTY_PLANES))
		Compute_Plane_Equations(planes);
	return planes;
}
