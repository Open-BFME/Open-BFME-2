// ?detected@Rva00439E0C@@QAE_NPAVObject@@0HH@Z, retail 0x00439E0C (307 bytes),
// WorldBuilder's InvisibilityManager::detected (explicit WB boundary 0x00839E0C).
// Finds or creates the object's detection record in the manager's int-keyed map
// (subscript 0x00439C73), extends its duration (0x0043822E), runs the detection
// walk 0x0043966A and, when 0x00438E5B accepts it, the feedback 0x004389DB.
// Body carried from the banked attempt (score 0.96), callee spellings now bound
// to the rowed/pinned members of the Rva00439E0C view.
// cl: /I. /O1 /D_STLP_NO_EXCEPTIONS /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmelist /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <map>
#include <vector>
// max<unsigned> only inlines here; keep it inline-only (retail 0x00013740).
namespace _STL {
template <> __declspec(dllimport) __forceinline
const unsigned int &max<unsigned int>(const unsigned int &__a, const unsigned int &__b)
{ return __a < __b ? __b : __a; }
}
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
// map<int,int> find otherwise instantiates the less<int>::operator() COMDAT
// (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
#include "Code/Libraries/Include/Lib/Coord3D.h"
enum Relationship { ENEMIES,NEUTRAL,ALLIES };class Team;
#include "../../../../Include/Common/Player.h"
struct DetectionTemplate {char pad[0x115];unsigned char kind;};
class Object {public:void *vtable;DetectionTemplate *objectTemplate;char pad8[0x30];Coord3D position;char pad44[0x30];int id;Object *rva002931F5(bool);Player *getControllingPlayer()const;};
struct BfmePod196 {int a[49];};
struct Rva004393D6:public _STL::list<BfmePod196> {int a,b,c;Rva004393D6();~Rva004393D6();Rva004393D6 &operator=(const Rva004393D6&);};
typedef _STL::map<int,Rva004393D6,_STL::less<int>,_STL::allocator<_STL::pair<const int,Rva004393D6> > > InvisibilityRecordMap;
template<> Rva004393D6 &InvisibilityRecordMap::operator[](const int&);
typedef _STL::pair<const int,int> IntIntPair;
typedef _STL::_Rb_tree<int,IntIntPair,_STL::_Select1st<IntIntPair>,_STL::less<int>,_STL::allocator<IntIntPair> > MapIntIntTree;
// The int-keyed lookup ICF-folds onto the rowed map<int,int> _M_find 0x00388F63.
struct DetectionTreeNode {unsigned color;void *parent,*left,*right;int key;Rva004393D6 record;};
struct Rva004389DBInfo;
class Rva00438389 {public:Object *detector;unsigned char allied;char pad5[31];Rva00438389 &rva00438389();};
class Xfer;
class Rva00439E0C {public:void *vtable;InvisibilityRecordMap records;unsigned word10,nextFrame;
 bool rva0043979D(Object*,Rva004393D6*);
 void rva00439F3F(Xfer*);
 bool detected(Object*,Object*,int,int);
 void rva0043822E(Rva004393D6*,unsigned int);
 int rva0043966A(Object*,const Coord3D*,Rva004393D6*,Rva004389DBInfo*);
 bool rva00438E5B(Object*,int,Rva004393D6*,Rva004389DBInfo*,unsigned int);
 void rva004389DB(Object*,Rva004389DBInfo*,int);
};
bool Rva00439E0C::detected(Object *object,Object *volatile detectorInput,int duration,int feedback)
{
 if(!object)return false;
 if(!(object->objectTemplate->kind&0x20) && object->rva002931F5(false))return false;
 union RecordScratch {int id;Rva004393D6 *record;} scratch;
 scratch.id=object->id;
 DetectionTreeNode *node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find(scratch.id)._M_node;
 if(node==*(DetectionTreeNode**)&records) {
  Rva004393D6 empty;
  records[scratch.id]=(const Rva004393D6&)empty;
  node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find(scratch.id)._M_node;
 }
 Object *detector=detectorInput;
 scratch.record=&node->record;
 bool allied=false;
 if(detector) {Player *detectorPlayer=detector->getControllingPlayer();allied=detectorPlayer->getRelationship(object->getControllingPlayer()->m_defaultTeam)==2;}
 rva0043822E(scratch.record,duration);
 Rva00438389 info;info.rva00438389();
 int state=rva0043966A(object,&object->position,scratch.record,(Rva004389DBInfo*)&info);
 info.allied=allied;info.detector=detector;
 if(rva00438E5B(object,state,scratch.record,(Rva004389DBInfo*)&info,duration)) {rva004389DB(object,(Rva004389DBInfo*)&info,feedback);return true;}
 return false;
}

typedef bool Bool;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version { public:unsigned char version,current;};
void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00438758Interface;
class Rva004382FC
{
public:
	Rva004382FC();
	void rva00438758(Rva00438758Interface*);
private:
	char bytes[196];
};
struct Rva004390F7Element;
namespace _STL {
	template<> void list<Rva004390F7Element>::push_back(const Rva004390F7Element&);
}

// Native00439F3F..0043A047, RET4: receive keyed detection records and append
// their transferred 196-byte entries. Prologue/EH and complete return prove
// the boundary; earlier no-boundary reports decoded another image address.
// Field access and transfer ordering are target facts; original method and
// record identities remain unknown. Existing record constructor/destructor
// bindings and the rowed list append retain their provider spellings.
void Rva00439E0C::rva00439F3F(Xfer *xfer)
{
	int count;
	xfer->operator==(reinterpret_cast<unsigned &>(count));
	while (count)
	{
		--count;
		ObjectID id;
		XferObjectID(xfer,&id);
		DetectionTreeNode *node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find((int&)id)._M_node;
		if (node == *(DetectionTreeNode**)&records)
		{
			Rva004393D6 empty;
			records[(int&)id]=(const Rva004393D6&)empty;
			node=(DetectionTreeNode*)((MapIntIntTree*)&records)->find((int&)id)._M_node;
		}
		Rva004393D6 *record=&node->record;
		xfer->operator==(reinterpret_cast<unsigned &>(record->a));
		xfer->operator==(reinterpret_cast<unsigned &>(record->b));
		xfer->operator==(reinterpret_cast<unsigned &>(record->c));
		int n;
		xfer->operator==(reinterpret_cast<unsigned &>(n));
		while (n)
		{
			--n;
			Rva004382FC entry;
			entry.rva00438758((Rva00438758Interface*)xfer);
			((_STL::list<Rva004390F7Element>*)record)->push_back((const Rva004390F7Element&)entry);
		}
		--n;
	}
}

// Use the established four-byte vector providers. These ABI views carry
// ObjectIDs, as proven by the lookup call; no new folded identity is pinned.
// The vector's empty-base constructor (0x00211E58) and push_back (0x002E01C6)
// are left to STLport (not declared-only specializations): with their bodies
// in the unit cl knows the gathered id vector never escapes, so the erase loop
// keeps its begin in edi for the final free and is pre-tested as in retail;
// declared only, the begin was reloaded and the loop bottom-tested.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
 template<> __declspec(dllimport) __forceinline _Vector_base<ObjectID,allocator<ObjectID> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
}
struct Rva00439862Element {char bytes[8];};
typedef _STL::_Rb_tree<Rva00439862Element,Rva00439862Element,_STL::_Identity<Rva00439862Element>,_STL::less<Rva00439862Element>,_STL::allocator<Rva00439862Element> > InvisibilityEraseProvider;
namespace _STL {template<> unsigned InvisibilityEraseProvider::erase(const Rva00439862Element&);}
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond; // VA 0x00DBA4E4
class Rva000D3FA0Map {public:void rva00439965();};

// Native00439965..00439A22 is a complete EH-prologue/RET body. WB127FD30
// independently confirms the frame gate and gather-then-erase traversal.
// Manager +4 tree, +14 next frame, node +10 ObjectID and +14 record are
// target accesses. Established provider spellings do not resolve the original
// manager name or the erase provider's donor-derived element type.
void Rva000D3FA0Map::rva00439965()
{
 Rva00439E0C *manager=(Rva00439E0C*)this;
 unsigned frame=TheGameLogic->getFrame();
 if(frame<manager->nextFrame)return;
 manager->nextFrame=frame+BfmeLogicFramesPerSecond;
 _STL::vector<ObjectID> remove;
 InvisibilityRecordMap *records=&manager->records;
 DetectionTreeNode *node=(DetectionTreeNode*)((DetectionTreeNode*)*(void**)records)->left;
 while(node!=*(DetectionTreeNode**)records) {
  Object *object=TheGameLogic->findObjectByID((ObjectID)node->key);
  Rva004393D6 *record=&node->record;
  if(!object || !manager->rva0043979D(object,record))remove.push_back((const ObjectID&)node->key);
  node=(DetectionTreeNode*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)node);
 }
 ObjectID *id=remove.begin();
 if(id!=remove.end())do {
  ((InvisibilityEraseProvider*)records)->erase((const Rva00439862Element&)*id);
  ++id;
 }while(id!=remove.end());
}
