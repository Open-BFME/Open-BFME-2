// ?remove@Rva00532DF6@@QAE_NGG@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /Oy- /G7 /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
void __cdecl operator delete[](void*);
struct Rva00532DF6Entry {unsigned short id,count;};
struct Rva00532DF6Less {bool operator()(const Rva00532DF6Entry&a,unsigned short b)const{return a.id<b;}};
struct Rva00532DF6Node {Rva00532DF6Node*next;unsigned short id,count;union{Rva00532DF6Entry one;Rva00532DF6Entry*array;};};
class Rva00532DF6 {public:bool remove(unsigned short a,unsigned short b);Rva00532DF6Node*buckets[4001];Rva00532DF6Node*freeNodes;};
bool Rva00532DF6::remove(unsigned short a,unsigned short b) {
 if(b<a){unsigned short temp=a;a=b;b=temp;}
 Rva00532DF6Node **p=buckets+(a%4001u);
 while(true){
  if(!*p)break;
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
  p=&n->next;
 }
 return false;
}
