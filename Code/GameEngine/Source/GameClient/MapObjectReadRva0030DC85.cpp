// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// ?Rva0030DC85ReadMapObject@@YAPAVRva0030DBD5@@AAVDataChunkInput@@PAUDataChunkInfo@@@Z,
// retail 0x0030DC85..0x0030DE61
// (476B, cdecl). Reads one map object record from a DataChunkInput and
// returns the new MapObject (0x0030DA25 constructor), or null when its height
// lies outside [-1000, 12799.8]. The sole caller 0x0030DE61 (bfmeGoEYF in
// BfmeConv888.cpp) appends the result to its list through its pinned
// void-pointer spelling (bfmeMakeEYF); the typed reference parameter is what
// keeps the name string out of the dead file-argument slot, as retail does. WorldBuilder's twin 0x00A7F0B0 (MapObject.cpp, "Removing
// object at z height") and Zero Hour's WorldHeightMap::ParseObjectData give
// the flow: loc/angle/flags/name, a Dict for version >= 2 (z zeroed for
// version <= 2), template lookup, then the waypoint (4), +0x20, light (2)
// and scorch (8) runtime flags from the property types.
// The by-value Coord3D argument is three movss stores plus an ESP save, so
// this unit takes the non-POD Coord3D view as MapUtilParseObjectDataChunk.cpp
// does.
#include "ascii_string.h"
#include "Lib/Coord3DCtorView.h"

#include "../../Include/Common/DataChunkInfo.h"
class Dict { public:
 enum DataType {NONE=-1,BOOL,INT,REAL,ASCII,UNICODE};
 Dict(int=0); Dict &operator=(const Dict&); ~Dict() {releaseData();}
 DataType getType(int) const;
 private:void releaseData();void *data;
};
#include "../../Include/Common/DataChunk.h"
class ThingTemplate;
#include "../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
class Rva0030DBD5 {public:
 virtual ~Rva0030DBD5();
 Rva0030DBD5(Coord3D,const AsciiString&,float,int,const Dict*,void*);
 char unknown04[0x24-4]; Dict dict; char unknown28[0x44-0x28]; unsigned flags; char unknown48[0x5C-0x48];
};
enum NameKeyType { NAMEKEY_INVALID=0 };
class Rva00148F5ECache {public: NameKeyType get(); NameKeyType key;const char *name;};
class StaticNameKey;
extern Rva00148F5ECache g_00DBDC74;			// "waypointID"
extern Rva00148F5ECache MapGenericAIObjectIDCache;	// "GenericAIObjectID"
extern const StaticNameKey TheKey_lightHeightAboveTerrain;
extern const StaticNameKey TheKey_scorchType;

Rva0030DBD5 *Rva0030DC85ReadMapObject(DataChunkInput &file, DataChunkInfo *info)
{
 Coord3D loc;
 loc.x=file.readReal();
 loc.y=file.readReal();
 loc.z=file.readReal();
 float minZ=-1000.0f;
 float maxZ=12799.8046875f;
 if(info->version<=2)
  loc.z=0;
 float angle=file.readReal();
 int flags=file.readInt();
 AsciiString name=file.readAsciiString();
 Dict d;
 if(info->version>=2)
  d=file.readDict();
 if(loc.z<minZ || loc.z>maxZ)
  return 0;
 const ThingTemplate *thing=0;
 if(TheThingFactory->rva002D06AA(name))
  thing=TheThingFactory->findTemplate(name);
 Rva0030DBD5 *object=new Rva0030DBD5(loc,name,angle,flags,&d,const_cast<ThingTemplate *>(thing));
 if(object->dict.getType(g_00DBDC74.get())==Dict::INT)
  object->flags|=4;
 if(object->dict.getType(MapGenericAIObjectIDCache.get())==Dict::INT)
  object->flags|=0x20;
 if(object->dict.getType(((Rva00148F5ECache *)&TheKey_lightHeightAboveTerrain)->get())==Dict::REAL)
  object->flags|=2;
 if(object->dict.getType(((Rva00148F5ECache *)&TheKey_scorchType)->get())==Dict::INT)
  object->flags|=8;
 return object;
}
