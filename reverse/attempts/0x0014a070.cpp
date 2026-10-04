// ?Get_Sort_Level@MeshClass@@UBEHXZ
// partial score=1.0 date=2026-10-05
// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Native MeshClass vtable slot94 at14A070 reads Model+C4 then signed byte+1C.
// Reuse the shared MeshClass declaration. MeshGeometry's donor header currently
// puts SortLevel at+20; this local data-offset adaptation records only the
// independently observed byte and does not alter that shared donor layout.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4
#include "rendobj.h"
#include "mesh.h"
#include "meshmdl.h"
int MeshClass::Get_Sort_Level(void) const
{
    if (Model)
        return *((const signed char *)Model+0x1C);
    return SORT_LEVEL_NONE;
}
