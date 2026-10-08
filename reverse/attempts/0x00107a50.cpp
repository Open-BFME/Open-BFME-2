// ?rva00107A50@Rva00107E76Elem@@QAEXPAX@Z
// partial score=0.8 date=2026-10-08
// cl: /DNDEBUG /MD /O1 /G7 /arch:SSE /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native 0x107A50..0x107B41, RET4. Original method name unknown.
// WB sibling UpdateWorldSpaceVertices supports Submesh ownership; target
// independently establishes mesh model+C4, count24, triangle-holder2C,
// holder data0C, world vertices4 and face flags8. BFME1 34f59164
// WWMath/vector3.h supplies only the established vector arithmetic.
#include "vector3.h"
struct ShadowTriangleIndices { unsigned short i, j, k; };
struct ShadowTriangleHolder { char opaque00[0x0C]; ShadowTriangleIndices *data; };
struct ShadowTriangleModel {
    char opaque00[0x24]; int count; int opaque28;
    ShadowTriangleHolder *triangles;
};
struct ShadowTriangleMesh { char opaque00[0xC4]; ShadowTriangleModel *model; };
class Rva00107E76Elem {
public:
    void rva00107A50(void *block);
    ShadowTriangleMesh *mesh;
    Vector3 *vertices;
    unsigned char *faces;
};
void Rva00107E76Elem::rva00107A50(void *block)
{
    ShadowTriangleIndices *triangle = mesh->model->triangles->data;
    int count = mesh->model->count;
    unsigned char *face = faces;
    Vector3 *light = static_cast<Vector3 *>(block);
    for (; count > 0; --count, ++triangle) {
        Vector3 middle = vertices[triangle->j];
        Vector3 a = middle - vertices[triangle->i];
        Vector3 b = middle - vertices[triangle->k];
        float dot = (a.Z*b.Y-a.Y*b.Z)*light->X
                  + (a.X*b.Z-b.X*a.Z)*light->Y
                  + (b.X*a.Y-a.X*b.Y)*light->Z;
        *face++ = static_cast<unsigned char>(static_cast<int>(dot < 0.0f));
    }
}
