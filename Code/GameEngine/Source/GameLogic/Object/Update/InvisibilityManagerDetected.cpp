// ?rva00439E0C@Rva00439E0C@@QAE_NPAVObject@@0HH@Z, retail 0x00439E0C (307 bytes),
// WorldBuilder's InvisibilityManager::detected (explicit WB boundary 0x00839E0C).
// Finds or creates the object's detection record in the manager's int-keyed map
// (subscript 0x00439C73), extends its duration (0x0043822E), runs the detection
// walk 0x0043966A and, when 0x00438E5B accepts it, the feedback 0x004389DB.
// Body carried from the banked attempt (score 0.96), callee spellings now bound
// to the rowed/pinned members of the Rva00439E0C view.
// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmelist /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <map>
#include "Code/Libraries/Include/Lib/Coord3D.h"
enum Relationship { ENEMIES,NEUTRAL,ALLIES };class Team;
class Player {public:Relationship getRelationship(const Team*)const;char pad[0x2EC];const Team *team;};
struct DetectionTemplate {char pad[0x115];unsigned char kind;};
class Object {public:void *vtable;DetectionTemplate *objectTemplate;char pad8[0x30];Coord3D position;char pad44[0x30];int id;Object *rva002931F5(bool);Player *getControllingPlayer()const;};
struct BfmePod196 {int a[49];};
struct Rva004393D6:public _STL::list<BfmePod196> {int a,b,c;Rva004393D6();~Rva004393D6();Rva004393D6 &operator=(const Rva004393D6&);};
typedef _STL::map<int,Rva004393D6,_STL::less<int>,_STL::allocator<_STL::pair<const int,Rva004393D6> > > InvisibilityRecordMap;
template<> Rva004393D6 &InvisibilityRecordMap::operator[](const int&);
class Rva00388F63Map {public:void *find(int*);};
struct DetectionTreeNode {unsigned color;void *parent,*left,*right;int key;Rva004393D6 record;};
struct Rva004389DBInfo;
class Rva00438389 {public:Object *detector;unsigned char allied;char pad5[31];Rva00438389 &rva00438389();};
class Rva00439E0C {public:void *vtable;InvisibilityRecordMap records;
 bool rva00439E0C(Object*,Object*,int,int);
 void rva0043822E(Rva004393D6*,unsigned int);
 int rva0043966A(Object*,const Coord3D*,Rva004393D6*,Rva004389DBInfo*);
 bool rva00438E5B(Object*,int,Rva004393D6*,Rva004389DBInfo*,unsigned int);
 void rva004389DB(Object*,Rva004389DBInfo*,int);
};
bool Rva00439E0C::rva00439E0C(Object *object,Object *volatile detectorInput,int duration,int feedback)
{
 if(!object)return false;
 if(!(object->objectTemplate->kind&0x20) && object->rva002931F5(false))return false;
 union RecordScratch {int id;Rva004393D6 *record;} scratch;
 scratch.id=object->id;
 DetectionTreeNode *node=(DetectionTreeNode*)((Rva00388F63Map*)&records)->find(&scratch.id);
 if(node==*(DetectionTreeNode**)&records) {
  Rva004393D6 empty;
  records[scratch.id]=empty;
  node=(DetectionTreeNode*)((Rva00388F63Map*)&records)->find(&scratch.id);
 }
 Object *detector=detectorInput;
 scratch.record=&node->record;
 bool allied=false;
 if(detector) {Player *detectorPlayer=detector->getControllingPlayer();allied=detectorPlayer->getRelationship(object->getControllingPlayer()->team)==2;}
 rva0043822E(scratch.record,duration);
 Rva00438389 info;info.rva00438389();
 int state=rva0043966A(object,&object->position,scratch.record,(Rva004389DBInfo*)&info);
 info.allied=allied;info.detector=detector;
 if(rva00438E5B(object,state,scratch.record,(Rva004389DBInfo*)&info,duration)) {rva004389DB(object,(Rva004389DBInfo*)&info,feedback);return true;}
 return false;
}
