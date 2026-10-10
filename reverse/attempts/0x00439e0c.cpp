// ?rva00439E0C@Rva00439E0C@@QAE_NPAVObject@@0HH@Z
// partial score=0.9609120521 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmelist /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <map>
struct Coord3D {float x,y,z;};
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
struct Rva0043822EParam;
void __stdcall Rva0043822ESet(Rva0043822EParam*,unsigned int);
class Rva00439E0C {public:void *vtable;InvisibilityRecordMap records;
 bool rva00439E0C(Object*,Object*,int,int);
 void rva0043822E(Rva0043822EParam*,unsigned int);
 int rva0043966A(Object*,const Coord3D*,Rva004393D6*,Rva00438389*);
 bool rva00438E5B(Object*,int,Rva004393D6*,Rva00438389*,int);
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
 rva0043822E((Rva0043822EParam*)scratch.record,duration);
 Rva00438389 info;info.rva00438389();
 int state=rva0043966A(object,&object->position,scratch.record,&info);
 info.allied=allied;info.detector=detector;
 if(rva00438E5B(object,state,scratch.record,&info,duration)) {rva004389DB(object,(Rva004389DBInfo*)&info,feedback);return true;}
 return false;
}
