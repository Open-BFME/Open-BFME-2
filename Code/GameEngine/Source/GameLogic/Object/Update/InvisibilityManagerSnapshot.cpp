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
struct XferVersion {unsigned char version,current;};
class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferSlot90(int *value);
};
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00438758Interface;
class Rva004382FC {public:void rva00438758(Rva00438758Interface*);};
struct InvisibilityListNode {InvisibilityListNode*next,*previous;};
struct InvisibilityTreeNode {unsigned color;InvisibilityTreeNode*parent,*left,*right;ObjectID id;InvisibilityListNode*list;int expiry,refresh,other;};
__forceinline unsigned listSize(InvisibilityListNode*head){unsigned n=0;for(InvisibilityListNode*j=head->next;j!=head;j=j->next)++n;return n;}
class Rva00439E0C {public:void rva00438FF4(Xfer*);unsigned word0;InvisibilityTreeNode*header;int count;};
void Rva00439E0C::rva00438FF4(Xfer*xfer){
 int size=count;
 xfer->xferInt(&size);
 for(InvisibilityTreeNode*i=header->left;i!=header;i=(InvisibilityTreeNode*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)i)){
  ObjectID id=i->id;
  XferObjectID(xfer,&id);
  xfer->xferInt(&i->expiry);
  xfer->xferInt(&i->refresh);
  xfer->xferInt(&i->other);
  int n=listSize(i->list);
  xfer->xferInt(&n);
  for(InvisibilityListNode*j=i->list->next;j!=i->list;j=j->next)
   reinterpret_cast<Rva004382FC*>(j+1)->rva00438758(reinterpret_cast<Rva00438758Interface*>(xfer));
 }
}
