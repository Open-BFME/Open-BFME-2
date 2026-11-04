// cl: /DNDEBUG /MD /EHsc- /GX- /Ob2 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// BFME2 GeometryOther callback: PC FieldParse row VA C0EC50 stores AC01B0
// and member offset FC. Preview row 820191C0 / callback 82213488 corroborates
// the field family only; all byte proof is against PC 1.06.
// Reference basis: BFME1 GeometryInfoConstructor.cpp and GeometryParseType.cpp,
// GeneralsMD Common/System/Geometry.cpp and Common/INI.h (getSepsColon).
// BFME2-specific multi-shape parsing reconstructed from the complete 500-byte
// PC body. Partial TU-local layout, not a claim to recover the full class.
// Constructors 450B74/4929E8 write the same BC4E94 vtable, initialize/copy
// shape and record vectors at 2C/38, and the 5C-byte extent cache. Destructor
// 450B2A destroys those vectors then restores Snapshot's BBB554 vtable.
// calcBoundingStuff ABE700 walks active 24-byte shapes and updates extents.
// Vector overflow ABFD30 grows/copies/destroys 5C-byte GeometryInfo objects;
// this identity is independently checked, not inferred from a masked call.
#include <vector>
#include <string.h>
#include "../../../Include/Common/Geometry.h"
#include "../../../Include/Common/INI/INI.h"
// Preserve the retail inlined accessor in this TU.
inline const char *INI::getSepsColon() const { return m_sepsColon; }
extern const char *const GeometryNames[];
struct GeometryShape {
    int type; float height, majorRadius, minorRadius, x, y, z;
    char *name; bool active; char padding[3];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<GeometryInfo,GeometryInfo>(GeometryInfo *p,GeometryInfo const &v) { new (p) GeometryInfo(v); } }
void GeometryInfo::parseGeometryOther(INI *ini, void *, void *store, const void *) {
    GeometryInfo geometry(GEOMETRY_SPHERE, false, 10.0f, 10.0f, 10.0f);
    const char *token=ini->getNextTokenOrNull(ini->getSepsColon());
    while(token) {
        const char *value=ini->getNextTokenOrNull(ini->getSepsColon());
        if(!value) break;
        if(!strcmp(token,"GeomType")) static_cast<GeometryShape *>(geometry.field2c[0])->type=ini->scanIndexList(value,GeometryNames);
        else if(!strcmp(token,"IsSmall")) geometry.m_isSmall=ini->scanBool(value);
        else if(!strcmp(token,"Height")) static_cast<GeometryShape *>(geometry.field2c[0])->height=ini->scanReal(value);
        else if(!strcmp(token,"MajorRadius")) static_cast<GeometryShape *>(geometry.field2c[0])->majorRadius=ini->scanReal(value);
        else if(!strcmp(token,"MinorRadius")) static_cast<GeometryShape *>(geometry.field2c[0])->minorRadius=ini->scanReal(value);
        else if(!strcmp(token,"OffsetX")) static_cast<GeometryShape *>(geometry.field2c[0])->x=ini->scanReal(value);
        else if(!strcmp(token,"OffsetY")) static_cast<GeometryShape *>(geometry.field2c[0])->y=ini->scanReal(value);
        else if(!strcmp(token,"OffsetZ")) static_cast<GeometryShape *>(geometry.field2c[0])->z=ini->scanReal(value);
        token=ini->getNextTokenOrNull(ini->getSepsColon());
    }
    geometry.calcBoundingStuff();
    ((std::vector<GeometryInfo> *)store)->push_back(geometry);
}
