// ?remove@Rva00532DF6@@QAE_NGG@Z
// Target 0x00532DF6..0x00532ED9: counted ushort link-table removal.
// Layout from native loads/stores: 4001 bucket heads, free head at 0x3E84;
// node next/id/count at 0/4/6, inline counted entry or array at 8.
// Pathfind zone adjacency is a donor-family lead; exact class identity unknown.
// Advancing through the bucket link itself preserves native bottom-test shape.
// cl: /O1 /Oy- /G7 /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
void __cdecl operator delete[](void*);
struct Rva00532DF6Entry {unsigned short id,count;};
struct Rva00532DF6Less {bool operator()(const Rva00532DF6Entry&a,unsigned short b)const{return a.id<b;}};
struct Rva00532DF6Node {Rva00532DF6Node*next;unsigned short id,count;union{Rva00532DF6Entry one;Rva00532DF6Entry*array;};};
class Rva00532DF6 {public:bool remove(unsigned short a,unsigned short b);bool add(unsigned short a,unsigned short b);Rva00532DF6Node*buckets[4001];Rva00532DF6Node*freeNodes;};
bool Rva00532DF6::remove(unsigned short a,unsigned short b) {
 if(b<a){unsigned short temp=a;a=b;b=temp;}
 Rva00532DF6Node **p=buckets+(a%4001u);
 goto check;
body: {
  Rva00532DF6Node*n=*p;
  if(n->id==a){
   if(n->count==1) {
    if(n->one.id!=b)return false;
    if(--n->one.count)return false;
    *p=n->next;n->next=freeNodes;freeNodes=n;return true;
   }
   Rva00532DF6Entry *end=n->array+n->count;
   Rva00532DF6Entry *hit=_STL::lower_bound(n->array,end,b,Rva00532DF6Less());
   if(hit!=end&&hit->id==b) {
    if(--hit->count)return false;
    while(++hit!=end)hit[-1]=*hit;
    if(--n->count==1){Rva00532DF6Entry value=n->array[0];delete[] n->array;n->one=value;}
    return true;
   }
  }
  p=&(*p)->next;
 }
check:
 if(*p)goto body;
 return false;
}

// Native 0x00532C75..0x00532DF6 and WB0x012D4CF0 describe CountedPairSet
// insertion. Increase an existing link's reference count; only a new link
// returns true. Nodes keep one entry inline, promoting to a sorted array.
// The policy/template spelling is from WB, while sizes and offsets are retail.
bool Rva00532DF6::add(unsigned short a,unsigned short b) {
 if(b<a){unsigned short temp=a;a=b;b=temp;}
 Rva00532DF6Node **link=buckets+(a%4001u);
 goto check;
body: {
  if((*link)->id==a) {
  Rva00532DF6Node *node=*link;
  unsigned short count=node->count;
  if(count==1) {
   if(node->one.id==b){++node->one.count;return false;}
   Rva00532DF6Entry old=node->one;
   node->count=2;
   node->array=new Rva00532DF6Entry[2];
   if(b<old.id){node->array[0].id=b;node->array[0].count=1;node->array[1]=old;}
   else {node->array[0]=old;node->array[1].id=b;node->array[1].count=1;}
   return true;
  }
  Rva00532DF6Entry *end=node->array+count;
  Rva00532DF6Entry *hit=_STL::lower_bound(node->array,end,b,Rva00532DF6Less());
  if(hit!=end&&hit->id==b){++hit->count;return false;}
  int before=hit-node->array;
  node->count=count+1;
  Rva00532DF6Entry *array=new Rva00532DF6Entry[node->count];
  Rva00532DF6Entry *out=array,*in=node->array;
  for(int i=before;i;--i)*out++=*in++;
  out->id=b;out->count=1;++out;
  while(in!=end)*out++=*in++;
  delete[]node->array;
  node->array=array;
  return true;
  }
  link=&(*link)->next;
 }
check:
 if(*link)goto body;
 Rva00532DF6Node *node;
 if(!freeNodes)node=new Rva00532DF6Node;else {node=freeNodes;freeNodes=node->next;}
 node->next=*link;node->count=1;node->id=a;node->one.id=b;node->one.count=1;
 *link=node;
 return true;
}
