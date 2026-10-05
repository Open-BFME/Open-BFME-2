// ?parseAdditionalGeometryRva006BFA60@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.8 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O2 /Ob2 /MD /DNDEBUG /GX-
// Target [6BFA60,6BFB11),177B. Native FieldParse VA00DBF2C8
// names AdditionalGeometry and points at this callback with store offsetA0.
// The third callback argument is the geometry store. Full rowed301B
// calcBoundingStuff6BE700 independently establishes vector+2C and36B
// records; full79B copy63BE4 establishes seven words/string1C/bytes20/21.
// Target creates a type-indexed shape with three1.0f dimensions; zero
// coordinates and string; both flag bytes true. Original role of21 unknown.
// Readable BFME1 and ZH Geometry.cpp support type names and parse semantics;
// BFME2 registration and full providers establish the extra shape behavior.
// Unverified181B trial: immediate dimension stores instead of x87 reuse;
// empty-tag temporary slot differs. Scoped call views have no pins.
#include "ascii_string.h"
#include <new>
extern const char*const GeometryNames[];
class INI {public:const char*getNextToken(const char*)throw();int scanIndexList(const char*,const char*const*)throw();};
struct Rva006BFA60Coord {Rva006BFA60Coord():x(0),y(0),z(0){}float x,y,z;};
struct Rva006BFA60Shape {int type;float height,major,minor;Rva006BFA60Coord offset;AsciiString name;unsigned char enabled,flag21;unsigned char padding[2];
 __forceinline Rva006BFA60Shape():type(0),height(1),major(1),minor(1),enabled(1),flag21(1){}
 Rva006BFA60Shape(const Rva006BFA60Shape&)throw();};
struct Rva006BFA60Tag {Rva006BFA60Tag(){}};
class Rva006BFA60Vector {public:Rva006BFA60Shape*start;Rva006BFA60Shape*finish;Rva006BFA60Shape*limit;
 void overflow(Rva006BFA60Shape*,const Rva006BFA60Shape&,const Rva006BFA60Tag&,unsigned,bool)throw();
 __forceinline void append(const Rva006BFA60Shape&value) {
  if(finish!=limit) {if(finish)new(finish)Rva006BFA60Shape(value);++finish;}
  else overflow(finish,value,Rva006BFA60Tag(),1,true);
 }
};
class Rva006BFA60Geometry {public:unsigned char consumed[0x2c];Rva006BFA60Vector shapes;void calcBoundingStuff()throw();};
void parseAdditionalGeometryRva006BFA60(INI*ini,void*,void*store,const void*) {
 int type=ini->scanIndexList(ini->getNextToken(0),GeometryNames);
 Rva006BFA60Shape shape;shape.type=type;
 Rva006BFA60Geometry*geometry=(Rva006BFA60Geometry*)store;
 geometry->shapes.append(shape);geometry->calcBoundingStuff();
}
