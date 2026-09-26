// cl: /O2 /DNDEBUG /MD /GX- /Ob2
// stlport
// Adapted from BFME1 GeometryParseHeightAndMajorRadius.cpp.
// PC FieldParse C0EC00 identifies GeometryMajorRadius -> ABEA60.
// Same 24-byte shape vector at +2C; PC scanReal is a member, not static.
#include <vector>
class INI {
public:
    const char *getNextToken(const char *);
    bool scanBool(const char *);
    float scanReal(const char *);
};
struct GeometryShape {
    int type; float height, majorRadius, minorRadius, x, y, z;
    char *name; bool active; bool usedForHealthBox; char padding[2];
};
class GeometryInfo {
public:
    static void parseGeometryMajorRadius(INI *, void *, void *, const void *);
    static void parseGeometryMinorRadius(INI *, void *, void *, const void *);
    static void parseGeometryHeight(INI *, void *, void *, const void *);
    static void parseGeometryIsSmall(INI *, void *, void *, const void *);
    static void parseGeometryUsedForHealthBox(INI *, void *, void *, const void *);
    void calcBoundingStuff();
    char unmodelled00[4]; bool isSmall; char unmodelled05[0x27];
    std::vector<GeometryShape> shapes;
};
void GeometryInfo::parseGeometryMajorRadius(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(geometry->shapes.size()!=0)
        geometry->shapes.back().majorRadius=ini->scanReal(ini->getNextToken(0));
    geometry->calcBoundingStuff();
}

// BFME1 GeometryParseMinorRadius.cpp; PC field C0EC10 -> ABEAB0.
void GeometryInfo::parseGeometryMinorRadius(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(geometry->shapes.size()!=0)
        geometry->shapes.back().minorRadius=ini->scanReal(ini->getNextToken(0));
    geometry->calcBoundingStuff();
}

// Already recovered 6BE450; donor facade for GeometryInfo height-cache refresh.
class BfmeObjEB;
void bfmeApplyEB(BfmeObjEB *);
void GeometryInfo::parseGeometryHeight(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(geometry->shapes.size()!=0)
        geometry->shapes.back().height=ini->scanReal(ini->getNextToken(0));
    geometry->calcBoundingStuff();
    bfmeApplyEB((BfmeObjEB *)geometry);
}

// GeneralsMD Geometry.cpp and BFME1 GeometryIsSmall_Thunk.cpp; PC C0EC30.
void GeometryInfo::parseGeometryIsSmall(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    geometry->isSmall=ini->scanBool(ini->getNextToken(0));
    geometry->calcBoundingStuff();
}

// Table 0x80EBE0 GeometryUsedForHealthBox entry. Unlike the dimension
// siblings it stores into the last shape without a bounding refresh.
void GeometryInfo::parseGeometryUsedForHealthBox(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(geometry->shapes.size()!=0)
        geometry->shapes.back().usedForHealthBox=ini->scanBool(ini->getNextToken(0));
}
