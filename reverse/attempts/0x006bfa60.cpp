// ?parseAdditionalGeometryRva006BFA60@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.993209 date=2026-10-09
// cl: /O2 /Ob2 /MD /DNDEBUG /GX- /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <new>
extern const char *const GeometryNames[];
class INI { public: const char *getNextToken(const char *);int scanIndexList(const char *,const char *const *); };
static const volatile float kDefaultDimension=1.0f;
struct DimensionTriple { float height,major,minor;DimensionTriple(){double value=kDefaultDimension;height=(float)value;major=(float)value;minor=(float)value;} };
struct GeometryShape { int type;DimensionTriple dimensions;float x,y,z;AsciiString name;unsigned char active,flag21;GeometryShape(int t):type(t),dimensions(),x(0),y(0),z(0),active(1),flag21(1){} };
struct BfmeStringRecord00063BE4 {unsigned int words[7];AsciiString text;unsigned char tail0,tail1;BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &);};
struct BfmeElemBE { char data[36]; };
struct BfmeFalseBE {};
class BfmeVecBE { public:
 void overflow(BfmeElemBE *,const BfmeElemBE &,const BfmeFalseBE &,unsigned,bool);
 BfmeElemBE *start,*finish,*limit;
 void append(const GeometryShape &shape) {
  if(finish!=limit) {if(finish)new(finish)BfmeStringRecord00063BE4(*reinterpret_cast<const BfmeStringRecord00063BE4 *>(&shape));++finish;}
  else {BfmeFalseBE tag;overflow(finish,*reinterpret_cast<const BfmeElemBE *>(&shape),tag,1,true); }
 }
};
class GeometryInfo { public: char prefix[0x2c];BfmeVecBE shapes;void calcBoundingStuff(); };
void parseAdditionalGeometryRva006BFA60(INI *ini,void *,void *store,const void *) {
 GeometryShape shape(ini->scanIndexList(ini->getNextToken(0),GeometryNames));
 GeometryInfo *geometry=static_cast<GeometryInfo *>(store);
 geometry->shapes.append(shape);geometry->calcBoundingStuff();
}
