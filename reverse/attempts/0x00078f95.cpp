// ??RRva00078F95Cmp@@QBE_NPBURva00078F95Item@@0@Z
// partial score=0.63899 date=2026-10-08
// cl: /O1 /G7 /arch:SSE
class Rva00078C10 {
public:
 bool rva00078C10(const Rva00078C10 *, int *, int *);
 char pad00[8];
 struct Detail {char pad[0x200]; float priority;} *detail;
 char pad0c[12]; void *handle;
 char pad1c[0x110-0x1c];
 struct Slot {void *key; float amount; char gap[8]; int order; int rank; bool enabled; char tail[3];} slots[2];
};
struct Rva00078F95Item { Rva00078C10 *object; int priority; };
struct Rva00078F95Cmp { bool operator()(const Rva00078F95Item *,const Rva00078F95Item *) const; };
bool Rva00078F95Cmp::operator()(const Rva00078F95Item *a,const Rva00078F95Item *b) const {
 bool answer;
 if(a->priority!=b->priority) {answer=a->priority>b->priority; goto result;}
 if(!a->priority) {answer=a->object<b->object; goto result;}
 if(!a->object->detail) {answer=true; goto result;} if(!b->object->detail) {answer=true; goto result;}
 if(a->object->detail->priority!=b->object->detail->priority)
   {answer=a->object->detail->priority<b->object->detail->priority; goto result;}
 if(a->object->handle!=b->object->handle) {answer=a->object->handle<b->object->handle; goto result;}
 const Rva00078F95Item *savedA=a,*savedB=b;
 int ai,bi;
 if(savedA->object->rva00078C10(savedB->object,&ai,&bi)) {
   if(ai!=bi) {answer=ai<bi; goto result;}
   {answer=savedA->object<savedB->object; goto result;}
 }
 Rva00078C10 *x=savedA->object,*y=savedB->object;
 for(int i=0;i<=1;++i) {
  if(x->slots[i].key!=y->slots[i].key) {answer=x->slots[i].key<y->slots[i].key; goto result;}
  if(x->slots[i].key) {
   if(x->slots[i].rank!=y->slots[i].rank) {answer=x->slots[i].rank<y->slots[i].rank; goto result;}
   if(x->slots[i].order!=y->slots[i].order) {answer=x->slots[i].order<y->slots[i].order; goto result;}
   if(x->slots[i].enabled!=y->slots[i].enabled) {answer=x->slots[i].enabled; goto result;}
  }
 }
 float xx=x->slots[0].amount+(x->slots[1].key?x->slots[1].amount:0.0f);
 float yy=y->slots[0].amount+(y->slots[1].key?y->slots[1].amount:0.0f);
 if(xx!=yy) {answer=xx<yy; goto result;}
 {answer=x<y; goto result;}

result: return answer;
}
