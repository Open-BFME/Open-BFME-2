// ?rva000FF5E6@Rva0007E90ECallee@@QAEXH@Z
// partial score=0.592 date=2026-10-09
// stlport
// cl: /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference guide: BFME1 9cbfb551fe20 W3DWaterTracks.cpp loadTracks and
// TestWaterUpdate midpoint/perpendicular construction, ZH water tracks.
// Target FF5E6..FF8FA RET4 reads map spline records rather than .wak files.
// Filename28, map collection124, 8B key/value records and point vector38/3C
// are native facts; map/point record original identities remain unclaimed.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <utility>
#include "ascii_string.h"
#define _OPERATOR_NEW_DEFINED_
#include "vector2.h"
struct Rva001408C0Target;
typedef Rva001408C0Target *AssetKey;
struct Q1ReceiverLocalSet {
 _STL::set<AssetKey,_STL::less<AssetKey>,_STL::allocator<AssetKey> > assets;
 int unknown0c;bool changed;
 // ?Q1ReceiverLocalSet::Q1ReceiverLocalSet present-unmatched
 Q1ReceiverLocalSet():unknown0c(0),changed(true){}
 // ?Q1ReceiverLocalSet::~Q1ReceiverLocalSet present-unmatched
 ~Q1ReceiverLocalSet(){}

};
struct AssetList00208F90 { AssetList00208F90 &operator<<(const AsciiString&); };
class Rva0030C94ADwordField {public:int get()const;};
class Rva0030C91AIntGetter {public:int get()const;};
class Rva0030C890IntGetter {public:int get()const;};
class Rva0030C896DwordField {public:int get()const;};
class Rva000B28F2LeaGetter {public:void*get()const;};
struct Rva0007E394Element {char unknown00[0x38];Vector2 *begin,*end,*capacity;};
typedef _STL::pair<const unsigned,Rva0007E394Element*> IndexPair;
namespace _STL { template<> bool operator==(const IndexPair&,const IndexPair&); }

struct MapEntry {unsigned key;Rva0007E394Element *value;};
struct TrackCollection {
 char unknown00[0x14];MapEntry *begin,*end,*capacity;
 int size()const {return end-begin;}
 IndexPair first(){return IndexPair(reinterpret_cast<unsigned>(this),0);}
 IndexPair last(){return IndexPair(reinterpret_cast<unsigned>(this),reinterpret_cast<Rva0007E394Element*>(size()));}
};
struct WaterMapView {char unknown00[0x124];TrackCollection *tracks;};
extern void *W3DGCData00DE2000;
class Rva009EB960;extern Rva009EB960 *Rva0134FAA0;
void Rva009EBAC0(int);
struct FeNode;
class WaterTracksObj {public:char unknown00[0xac];float flipU;void init(float,float,Vector2&,Vector2&,char*,int,void*);};
enum waveType {WaveTypePond,WaveTypeOcean};
class WaterTracksRenderSystem {public:WaterTracksObj *bindTrack(waveType);void rva000FE188();FeNode*rva000FE207(const float*,const float*,int);};
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
class Rva0007E90ECallee {public:char unknown00[0x28];AsciiString file;void rva000FF5E6(int);};
struct TrackPoint : Vector2 {
 // ?TrackPoint::TrackPoint present-unmatched
 TrackPoint(){}
 // ?TrackPoint::~TrackPoint present-unmatched
 ~TrackPoint();
};
float GetGameClientRandomValueReal(float,float,char*,int);
void Rva0007E90ECallee::rva000FF5E6(int filename)
{
 file=*reinterpret_cast<const AsciiString*>(filename);
 reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE188();
 int flipU=0;TrackPoint startPos,endPos;Q1ReceiverLocalSet assets;
 if(W3DGCData00DE2000) {
  TrackCollection *collection=reinterpret_cast<WaterMapView*>(W3DGCData00DE2000)->tracks;
  for(IndexPair it=collection->first();!(it==collection->last());it.second=reinterpret_cast<Rva0007E394Element*>(reinterpret_cast<int>(it.second)+1)) {
   Rva0007E394Element *record=collection->begin[reinterpret_cast<int>(it.second)].value;
   if(reinterpret_cast<Rva0030C94ADwordField*>(record)->get())continue;
   int count=record->end-record->begin;
   if(count<2)continue;
   int segments=count-1;
   for(int i=0;i<segments;++i) {
    Vector2 *start=&record->begin[i];Vector2 *end=&record->begin[i+1];
    Vector2 midpoint=*end-*start;
    Vector2 perp=midpoint;
    midpoint=*start+midpoint*0.5f;
    perp.Rotate(1.57079632679f);perp.Normalize();
    startPos.Set(midpoint);endPos.Set(midpoint+perp);
    if(reinterpret_cast<WaterTracksRenderSystem*>(this)->rva000FE207(&startPos.X,&endPos.X,1))continue;
    WaterTracksObj *track=TheWaterTracksRenderSystem->bindTrack(WaveTypeOcean);
    if(track) {
     float fraction=GetGameClientRandomValueReal(0.0f,1.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Water\\W3DWaterTracks.cpp",1141);
     int offset=fraction*reinterpret_cast<Rva0030C91AIntGetter*>(record)->get();
     flipU^=1;
     AsciiString &texture=*reinterpret_cast<AsciiString*>(reinterpret_cast<Rva000B28F2LeaGetter*>(record)->get());
     track->init(float(reinterpret_cast<Rva0030C896DwordField*>(record)->get()),float(reinterpret_cast<Rva0030C890IntGetter*>(record)->get()),startPos,endPos,const_cast<char*>(texture.str()),offset,record);
     *reinterpret_cast<AssetList00208F90*>(&assets)<<*reinterpret_cast<AsciiString*>(reinterpret_cast<Rva000B28F2LeaGetter*>(record)->get());
     track->flipU=flipU;
    }
   }
  }
  if(Rva0134FAA0)Rva009EBAC0(reinterpret_cast<int>(&assets));
 }
}

// Empty point cleanup is defined after the caller, matching native null actions.
TrackPoint::~TrackPoint() {}
