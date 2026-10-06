// cl: /DNDEBUG /MD /EHsc- /GX- /Ob2
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
class INI {
public:
    char unused[0x420]; const char *colon;
    const char *getSepsColon() const { return colon; }
    const char *getNextTokenOrNull(const char *);
    int scanIndexList(const char *, const char *const *);
    bool scanBool(const char *);
    float scanReal(const char *);
};
extern const char *const GeometryNames[];
enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
struct GeometryShape {
    int type; float height, majorRadius, minorRadius, x, y, z;
    char *name; bool active; char padding[3];
};
class GeometryInfo {
public:
    GeometryInfo(GeometryType, bool, float, float, float);
    GeometryInfo(const GeometryInfo &);
    virtual ~GeometryInfo();
    static void parseGeometryOther(INI *, void *, void *, const void *);
    bool isSmall; char padding[3]; char head[0x24];
    GeometryShape *begin, *end, *capacity;
    char tail[0x24];
private:
	void calcBoundingStuff();
	friend class GeometryShape;
	friend class INI;
};
void GeometryInfo::parseGeometryOther(INI *ini, void *, void *store, const void *) {
    GeometryInfo geometry(GEOMETRY_SPHERE, false, 10.0f, 10.0f, 10.0f);
    const char *token=ini->getNextTokenOrNull(ini->getSepsColon());
    while(token) {
        const char *value=ini->getNextTokenOrNull(ini->getSepsColon());
        if(!value) break;
        if(!strcmp(token,"GeomType")) geometry.begin->type=ini->scanIndexList(value,GeometryNames);
        else if(!strcmp(token,"IsSmall")) geometry.isSmall=ini->scanBool(value);
        else if(!strcmp(token,"Height")) geometry.begin->height=ini->scanReal(value);
        else if(!strcmp(token,"MajorRadius")) geometry.begin->majorRadius=ini->scanReal(value);
        else if(!strcmp(token,"MinorRadius")) geometry.begin->minorRadius=ini->scanReal(value);
        else if(!strcmp(token,"OffsetX")) geometry.begin->x=ini->scanReal(value);
        else if(!strcmp(token,"OffsetY")) geometry.begin->y=ini->scanReal(value);
        else if(!strcmp(token,"OffsetZ")) geometry.begin->z=ini->scanReal(value);
        token=ini->getNextTokenOrNull(ini->getSepsColon());
    }
    geometry.calcBoundingStuff();
    ((std::vector<GeometryInfo> *)store)->push_back(geometry);
}
