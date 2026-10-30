// cl: /O1 /G7 /arch:SSE /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Formation grid dimensions; optimizer lives in FormationOptimizeUnits.cpp.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Native 0x00422377..0x0042245F, RET0: output pointer followed by object view.
// Formation placement at 0x0042481E consumes the two grid dimensions. Native
// establishes the input radius at +0xB8 and template bit test at +0x11F.
// GeometryInfo's verified aggregate-shape provider supplies the 36-byte shape
// contract; its StringBase cleanup is independently owned at 0x00036410.
// The original helper name and dimension-structure name remain unknown.
#include "ascii_string.h"

struct FormationGeometryOffset : Coord3D {
 FormationGeometryOffset() { x=0.0f; y=0.0f; z=0.0f; }
};
static __forceinline int formationCellExtent(float radius) {
 return (int)(radius*2.0f+4.0f);
}
struct GeometryShape {
 int m_type;
 float m_height;
 float m_majorRadius;
 float m_minorRadius;
 FormationGeometryOffset m_offset;
 AsciiString m_name;
 bool m_enabled;
 bool m_flag21;
 char m_22[2];
 GeometryShape() : m_type(0),m_height(1.0f),m_majorRadius(1.0f),
  m_minorRadius(1.0f),m_enabled(true),m_flag21(true) {}
};
class GeometryInfo {
public:
 void rva006BD9C0(GeometryShape &out) const;
private:
 char unknown00[0x10];
public:
 float m_boundingCircleRadius;
private:
 char unknown14[0x24];
};
struct Rva00422377Flag {
 char unknown00[0x11F];
 unsigned char m_11F;
};
struct Rva00422377In {
 char unknown00[4];
 Rva00422377Flag *m_template;
 char unknown08[0xA0];
 GeometryInfo m_geometry;
};
struct Rva00422377Out { int x,y; };

void Rva00422377Get(Rva00422377Out *out,Rva00422377In *in) {
 if(!in) { out->x=0; out->y=0; return; }
 float extent=1.0f+2.0f*in->m_geometry.m_boundingCircleRadius;
 Rva00422377Flag *flag=in->m_template;
 int y=(int)extent;
 int x=y;
 if((flag->m_11F&4)!=0) {
  GeometryShape shape;
  in->m_geometry.rva006BD9C0(shape);
  y=formationCellExtent(shape.m_majorRadius);
  x=formationCellExtent(shape.m_minorRadius);
 }
 out->x=x;
 out->y=y;
}
