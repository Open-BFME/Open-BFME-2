// cl: /O2 /DNDEBUG /MD
// WB1751BF0 remove-node guide; native starts with a head dereference before
// its subsequent null check. Empty-head callers are not assumed safe.
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
struct Rva006D01D0Node {void *value;Rva006D01D0Node *next;};
class Rva006D01D0Tracker {
 Rva006D01D0Node *head;
public:void remove(void *);
 __forceinline void removeRest(void *value){Rva006D01D0Node *node=head; while(node){
  if(node->next && node->next->value==value){
   Rva006D01D0Node *victim=node->next;
   if(victim)node->next=victim->next;
   g_pChainBlockAllocator->freeBlock(victim,8);
   break;
  }
  node=node->next;
 }
} void removeFront(){if(head){Rva006D01D0Node *node=head,*next=node->next;g_pChainBlockAllocator->freeBlock(node,8);head=next;}}
};
void Rva006D01D0Tracker::remove(void *value){
 Rva006D01D0Node *node=head;
 if(node->value==value){removeFront();return;}
 removeRest(value);
}
