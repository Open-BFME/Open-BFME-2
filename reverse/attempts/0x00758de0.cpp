// ?bfmeTwoCGD@BfmeThingCGD@@QAEXXZ
// partial score=0.5916 date=2026-10-08
// cl: /O2 /MD /EHsc
struct ContactVector { float x,y,z; };
struct ContactSource {
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void *prepare(ContactVector *, ContactVector *)=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual bool test(void *)=0;
 virtual void respond(void *)=0;
};
struct ContactData { void *owner; ContactSource *source; };
struct ContactNode {
 ContactData *first,*second;
 unsigned key0,key1,state;
 ContactVector point,normal;
 ContactNode **back;
 ContactNode *next;
};
class BfmeThingCGD {
public:
 void bfmeTwoCGD();
 char pad[0xae10];
 ContactNode *buckets[0x493];
 ContactNode *active;
 int index;
 ContactNode *current;
};
void BfmeThingCGD::bfmeTwoCGD() {
 index=0;
 current=buckets[0];
 for(;;) {
  while(current==0) {
   int i=index+1;
   if(i==0x493) return;
   index=i;
   current=buckets[i];
  }
  ContactNode *node=current;
  current=current->next;
  if(node==0) return;
  if(node->first->source==0 || node->second->source==0) continue;
  if(node->state==0)
   node->state=node->first->source->test(node->second->source->prepare(&node->point,&node->normal))?1:2;
  if(node->state==2) continue;
  node->first->source->respond(node->second->source->prepare(&node->point,&node->normal));
  if(node->first->source==0 || node->second->source==0) continue;
  ContactVector reverse;
  reverse.x=-node->normal.x;
  reverse.y=-node->normal.y;
  reverse.z=-node->normal.z;
  node->second->source->respond(node->first->source->prepare(&node->point,&reverse));
 }
}
