// cl: /EHsc /Ob2
// stlport
// Open-BFME: GeometryInfo::parseGeometryActive, retail 0x0087DE10, and
// GeometryInfo::parseGeometryOffset, retail 0x0087DE50.
//
// The object FieldParse table at 0x010913E0 pairs "GeometryActive" with
// 0x0087DE10 and "GeometryOffset" with 0x0087DE50. Both bodies guard on the
// same 0x24-byte shape vector at +0x2C that the landed
// GeometryInfo::parseGeometryMinorRadius at 0x0087F220 reads, and both sit in
// the Geometry.cpp run that holds GeometryInfo::isIntersectedByLineSegment at
// 0x0087DFC0, so the class is GeometryInfo.
//
// Each body forwards to a stock INI parser with the store pointer aimed at
// one member of the last shape. The Coord3D at +0x10 of a shape is the one
// whose z the GeometryParseMinorRadius shim calls m_offsetZ.

#include <vector>
#include "../../../Include/Common/Geometry.h"

typedef bool Bool;
typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/INI/INI.h"

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_offset;
	char m_name[0x04];
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

// This parser's target shape stride is 0x24. Keep its inlined count local:
// other units emit a different compiler shape for vector::size.
class GeometryShapeRange : public std::vector<GeometryShape>
{
public:
	size_type shapeCount() const
	{
		return size_type(_M_finish - _M_start);
	}
};

/*static*/ void GeometryInfo::parseGeometryActive(INI *ini, void *instance, void *store, const void *)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (reinterpret_cast<GeometryShapeRange *>(geometry->field2c)->shapeCount() != 0)
		INI::parseBool(ini, instance, &reinterpret_cast<GeometryShapeRange *>(geometry->field2c)->back().m_enabled, 0);
}

/*static*/ void GeometryInfo::parseGeometryOffset(INI *ini, void *instance, void *store, const void *userData)
{
	GeometryInfo *geometry = (GeometryInfo *)store;
	if (reinterpret_cast<GeometryShapeRange *>(geometry->field2c)->shapeCount() != 0)
		INI::parseCoord3D(ini, instance, &reinterpret_cast<GeometryShapeRange *>(geometry->field2c)->back().m_offset, userData);
}
