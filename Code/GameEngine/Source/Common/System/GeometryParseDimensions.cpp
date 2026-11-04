// cl: /DNDEBUG /MD /GX- /Ob2
// stlport
// Adapted from BFME1 GeometryParseHeightAndMajorRadius.cpp.
// PC FieldParse C0EC00 identifies GeometryMajorRadius -> ABEA60.
// Same 24-byte shape vector at +2C; PC scanReal is a member, not static.
#include <vector>
#include "../../../Include/Common/Geometry.h"
#include "../../../Include/Common/INI/INI.h"
struct GeometryShape {
    int type; float height, majorRadius, minorRadius, x, y, z;
    char *name; bool active; bool usedForHealthBox; char padding[2];
};
// Keep the existing STLport size operation inline in these native consumers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
vector<GeometryShape, allocator<GeometryShape> >::size_type
vector<GeometryShape, allocator<GeometryShape> >::size() const
{ return size_type(this->_M_finish - this->_M_start); }
}
void GeometryInfo::parseGeometryMajorRadius(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->size()!=0)
        reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->back().majorRadius=ini->scanReal(ini->getNextToken(0));
    geometry->calcBoundingStuff();
}

// BFME1 GeometryParseMinorRadius.cpp; PC field C0EC10 -> ABEAB0.
void GeometryInfo::parseGeometryMinorRadius(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->size()!=0)
        reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->back().minorRadius=ini->scanReal(ini->getNextToken(0));
    geometry->calcBoundingStuff();
}

// Already recovered 6BE450; donor facade for GeometryInfo height-cache refresh.
class BfmeObjEB;
void bfmeApplyEB(BfmeObjEB *);
void GeometryInfo::parseGeometryHeight(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->size()!=0)
        reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->back().height=ini->scanReal(ini->getNextToken(0));
    geometry->calcBoundingStuff();
    bfmeApplyEB((BfmeObjEB *)geometry);
}

// GeneralsMD Geometry.cpp and BFME1 GeometryIsSmall_Thunk.cpp; PC C0EC30.
void GeometryInfo::parseGeometryIsSmall(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    geometry->m_isSmall=ini->scanBool(ini->getNextToken(0));
    geometry->calcBoundingStuff();
}

// Table 0x80EBE0 GeometryUsedForHealthBox entry. Unlike the dimension
// siblings it stores into the last shape without a bounding refresh.
void GeometryInfo::parseGeometryUsedForHealthBox(INI *ini, void *, void *store, const void *) {
    GeometryInfo *geometry=(GeometryInfo *)store;
    if(reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->size()!=0)
        reinterpret_cast<std::vector<GeometryShape> *>(geometry->field2c)->back().usedForHealthBox=ini->scanBool(ini->getNextToken(0));
}
