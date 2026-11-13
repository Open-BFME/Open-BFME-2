// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z, retail 0x00302907, 511B.
// MapUtil ParseObjectDataChunk (ZH MapUtil.cpp:ParseObjectDataChunk; registered by ParseObjectsDataChunk 0x00302B06):
// reads loc/angle/flags/name/Dict, builds the MapObject (0x0030DBD5) with Coord3D passed BY VALUE, files waypoint
// (_m_waypoints) or supply (_m_supplyPositions) positions.
// Target evidence: the by-value Coord3D argument is three scalar movss stores plus an ESP save; that needs the
// non-POD Coord3D (Lib/Coord3DCtorView.h: retail's user ctors, exports 0x0047A6A9/0x004216D3). The canonical POD
// Coord3D.h gives movsd and a different frame (nd 88).
// stlport
#include "ascii_string.h"
#include "Lib/Coord3DCtorView.h"
#include <map>
#include <list>
#include "../../Include/Common/DataChunkInfo.h"
class Dict { public:
 enum DataType {NONE=-1,BOOL,INT,REAL,ASCII,UNICODE};
 Dict(int=0); Dict &operator=(const Dict&); ~Dict() {releaseData();}
 DataType getType(int) const;
 private:void releaseData();void *data;
};
#include "../../Include/Common/DataChunk.h"
#include "../../Include/Common/ThingTemplate.h"
#include "../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
#include "../../Include/Common/Rva0030D748.h"
class MapObject {public:const ThingTemplate *getThingTemplate() const;};
class Rva0030DBD5 {public:
 virtual ~Rva0030DBD5();
 Rva0030DBD5(Coord3D,const AsciiString&,float,int,const Dict*,void*);
 char unknown04[0x24-4]; Dict dict; char unknown28[0x44-0x28]; unsigned flags; char unknown48[0x5C-0x48];
};
class MapObjectDeleteSlotView {public:virtual void *destroy(unsigned flags)=0;};
enum NameKeyType { NAMEKEY_INVALID=0 };
class Rva00148F5ECache {public: NameKeyType get(); NameKeyType key;const char *name;};
extern Rva00148F5ECache g_00DBDC74;
#include "../../Include/Common/TreeHintPayload003012F0.h"
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
 if(TheThingFactory->rva002D06AA(name))object=new Rva0030DBD5(loc,name,angle,flags,&d,const_cast<ThingTemplate *>(TheThingFactory->findTemplate(name)));
 else object=new Rva0030DBD5(loc,name,angle,flags,&d,0);
 if(object->dict.getType(g_00DBDC74.get())==Dict::INT) {
  object->flags|=4;
  *reinterpret_cast<Coord3D *>(&(*m_waypoints)[reinterpret_cast<Rva0030D748 *>(object)->rva0030D748()])=loc;
 } else if(reinterpret_cast<MapObject *>(object)->getThingTemplate() && (reinterpret_cast<MapObject *>(object)->getThingTemplate()->m_kindof[2] & 0x2000U)) m_supplyPositions.push_back(loc);
 void *allocation=object ? reinterpret_cast<MapObjectDeleteSlotView *>(object)->destroy(0):0;
 ::operator delete(allocation);
 return true;
}
