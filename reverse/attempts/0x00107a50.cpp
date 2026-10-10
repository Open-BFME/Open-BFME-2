// ?rva00107A50@Rva00107E76Elem@@QAEXPAX@Z
// partial score=0.9338362881931347 date=2026-10-10
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
const Vector3&middle=vertices[triangle->j];const Vector3&left=vertices[triangle->i];const Vector3&right=vertices[triangle->k];float my=middle.Y,mz=middle.Z,mx=middle.X;float aZ=mz-left.Z;float bZ=mz-right.Z;float aX=mx-left.X;float aY=my-left.Y;float bX=mx-right.X;float bY=my-right.Y;float dot=(aZ*bY-aY*bZ)*light->X+(aX*bZ-bX*aZ)*light->Y+(bX*aY-aX*bY)*light->Z;
        *face++ = static_cast<unsigned char>(static_cast<int>(dot < 0.0f));
    }
}
