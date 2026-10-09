// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.7 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <map>
#include <list>
struct DataChunkInfo { char unknown0[8]; unsigned short version; };
class Dict { public:
 enum DataType {NONE=-1,BOOL,INT,REAL,ASCII,UNICODE};
 Dict(int=0); Dict &operator=(const Dict&); ~Dict() {releaseData();}
 DataType getType(int) const;
 private:void releaseData();void *data;
};
class DataChunkInput {public:float readReal();int readInt();AsciiString readAsciiString();Dict readDict();};
class Rva002D06CA {public: bool rva002D06AA(const AsciiString*); void *rva002D06CA(const AsciiString*);};
class ThingFactory;extern ThingFactory *TheThingFactory;
class Rva0030D748 { public: AsciiString rva0030D748(); };
struct BfmeSlotJA { char unknown[0x111]; unsigned char flags; };
class BfmeThing932A {public:BfmeSlotJA *bfmeGo932A();};
class Rva0030DBD5 {public:
 virtual ~Rva0030DBD5();
 Rva0030DBD5(Coord3D,const AsciiString&,float,int,const Dict*,void*);
 char unknown04[0x24-4]; Dict dict; char unknown28[0x44-0x28]; unsigned flags; char unknown48[0x5C-0x48];
};
class MapObjectDeleteSlotView {public:virtual void *destroy(unsigned flags)=0;};
enum NameKeyType { NAMEKEY_INVALID=0 };
class Rva00148F5ECache {public: NameKeyType get(); NameKeyType key;const char *name;};
extern Rva00148F5ECache g_00DBDC74;
struct TreeHintPayload003012F0 {unsigned a,b,c;};
typedef _STL::map<AsciiString,TreeHintPayload003012F0> WaypointMap;
namespace _STL {template<> TreeHintPayload003012F0 &WaypointMap::operator[](const AsciiString &);}
extern "C" WaypointMap *m_waypoints;
extern "C" _STL::list<Coord3D> m_supplyPositions;
namespace _STL {template<> _List_iterator<Coord3D,_Nonconst_traits<Coord3D> > list<Coord3D>::insert(_List_iterator<Coord3D,_Nonconst_traits<Coord3D> >,const Coord3D &);}
bool ParseObjectDataChunk(DataChunkInput &file,DataChunkInfo *info,void *) {
 bool readDict=info->version>=2;
 Coord3D loc;loc.x=file.readReal();loc.y=file.readReal();loc.z=file.readReal();
 if(info->version<=2) loc.z=0;
 float angle=file.readReal();int flags=file.readInt();
 AsciiString name=file.readAsciiString();Dict d;
 if(readDict)d=file.readDict();
 Rva0030DBD5 *object;
 if(reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06AA(&name))object=new Rva0030DBD5(loc,name,angle,flags,&d,reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(&name));
 else object=new Rva0030DBD5(loc,name,angle,flags,&d,0);
 if(object->dict.getType(g_00DBDC74.get())==Dict::INT) {
  object->flags|=4;
  *reinterpret_cast<Coord3D *>(&(*m_waypoints)[reinterpret_cast<Rva0030D748 *>(object)->rva0030D748()])=loc;
 } else if(reinterpret_cast<BfmeThing932A *>(object)->bfmeGo932A() && (reinterpret_cast<BfmeThing932A *>(object)->bfmeGo932A()->flags &0x20)) m_supplyPositions.push_back(loc);
 void *allocation=object ? reinterpret_cast<MapObjectDeleteSlotView *>(object)->destroy(0):0;
 ::operator delete(allocation);
 return true;
}
