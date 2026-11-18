// cl: /O1 /G7 /Oy- /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native438FF4..4390A2 RET4 is a complete entry; earlier no-boundary log
// inspected a VA instead of the RVA. The transfer sequence is native evidence:
// owner count8, tree header4, node key10 and value14/18/1C/20, then each
// circular-list payload via the owned438758 transfer wrapper. Xfer slot30
// and ObjectID3060B2 follow already owned transfer routines. Original method
// and record names remain unknown. Isolated inline listSize keeps the count
// in EDX before assigning the address-taken transfer local.
#include <map>
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
#include "../../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/ObjectID.h"



void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00438758Interface;
class Rva004382FC {public:void rva00438758(Rva00438758Interface*);};
struct InvisibilityListNode {InvisibilityListNode*next,*previous;};
struct InvisibilityTreeNode {unsigned color;InvisibilityTreeNode*parent,*left,*right;ObjectID id;InvisibilityListNode*list;int expiry,refresh,other;};
__forceinline unsigned listSize(InvisibilityListNode*head){unsigned n=0;for(InvisibilityListNode*j=head->next;j!=head;j=j->next)++n;return n;}
class Rva00439E0C {public:void rva00438FF4(Xfer*);unsigned word0;InvisibilityTreeNode*header;int count;};
void Rva00439E0C::rva00438FF4(Xfer*xfer){
 int size=count;
 xfer->operator==(reinterpret_cast<unsigned &>(size));
 for(InvisibilityTreeNode*i=header->left;i!=header;i=(InvisibilityTreeNode*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)i)){
  ObjectID id=i->id;
  XferObjectID(xfer,&id);
  xfer->operator==(reinterpret_cast<unsigned &>(i->expiry));
  xfer->operator==(reinterpret_cast<unsigned &>(i->refresh));
  xfer->operator==(reinterpret_cast<unsigned &>(i->other));
  int n=listSize(i->list);
  xfer->operator==(reinterpret_cast<unsigned &>(n));
  for(InvisibilityListNode*j=i->list->next;j!=i->list;j=j->next)
   reinterpret_cast<Rva004382FC*>(j+1)->rva00438758(reinterpret_cast<Rva00438758Interface*>(xfer));
 }
}
