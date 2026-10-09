// ?Rva007B6640InitializeGeometry@@YAXXZ
// partial score=1.0 date=2026-10-09
// cl: /O2
// BF1 f98983a7 Rva00C6DBB0StaticAAOInit.cpp clean O2/SSE/G7 source lead.
// Target7B6640..7B6669 is INT3-bounded41B. Native calls actual GeometryInfo
// ctor50B74 on existing globalE0C150 with integer0 boolean1 three2.0f;
// registers existing cleanup7B9BF0 via real CRT atexit6291F8.
// Original static/global names and boolean semantics remain unknown.
// Existing owner's declarations-only callable signatures and global reused;
// no private data layout, new global, pin or selected-provider alias.
enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
class GeometryInfo {
public:
    GeometryInfo(GeometryType, bool, float, float, float);
    virtual ~GeometryInfo();
};
extern unsigned g_Va00E0C150;
void rva007B9BF0();
extern "C" int __cdecl atexit(void (__cdecl *)(void));
__forceinline void *operator new(unsigned int, void *place) { return place; }
void Rva007B6640InitializeGeometry()
{
    new ((void *)&g_Va00E0C150) GeometryInfo(GEOMETRY_SPHERE, true, 2.0f, 2.0f, 2.0f);
    atexit(rva007B9BF0);
}
