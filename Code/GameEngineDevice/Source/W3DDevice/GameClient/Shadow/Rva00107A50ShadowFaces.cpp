// cl: /DNDEBUG /MD /O1 /G7 /arch:SSE /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?rva00107A50@Rva00107E76Elem@@QAEXPAX@Z, native 0x107A50..0x107B41 (241 B), RET4.
// Original method name unknown. Per-triangle light facing for the volumetric
// shadow: each face flag is set when the triangle normal points away from the
// light. WorldBuilder twin 0x008DE030 (vector3.h asserts) gives the statements:
// two copies of the middle vertex, -= the third and the first vertex, then the
// cross product dotted with the light accumulated term by term. Called by the
// rowed UpdateAndRenderZfail 0x00107E76 (Rva00107E76Update.cpp).
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
        const Vector3 &vert0 = vertices[triangle->i];
        const Vector3 &vert1 = vertices[triangle->j];
        const Vector3 &vert2 = vertices[triangle->k];
        Vector3 a = vert1;
        Vector3 b = vert1;
        a -= vert2;
        b -= vert0;
        float dot = (a.Y*b.Z - a.Z*b.Y)*light->X;
        dot += (a.Z*b.X - a.X*b.Z)*light->Y;
        dot += (a.X*b.Y - a.Y*b.X)*light->Z;
        *face++ = static_cast<unsigned char>(static_cast<int>(dot < 0.0f));
    }
}
