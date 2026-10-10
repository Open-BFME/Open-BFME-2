// cl: /O1 /G7 /MD
// Native 109129..1091A8 127B RET8. ZH removeShadow list walk is semantic
// guide; BFME target recycles to the receiver's +10 free list and decrements
// the +250 decal count for six exact native type values. WB has an unnamed
//243B analogue. Original helper name remains unknown.
class W3DProjectedShadow {public:void rva007AEC10();char pad[0x34];int type;char pad38[0xdc];W3DProjectedShadow*next;};
struct ShadowList {W3DProjectedShadow*head;};
class Rva00109129 {public:bool rva00109129(W3DProjectedShadow*,ShadowList*);char pad[0x10];W3DProjectedShadow*free;char pad14[0x23c];int decalCount;};
bool Rva00109129::rva00109129(W3DProjectedShadow*shadow,ShadowList*list){
 W3DProjectedShadow*prev=0;
 for(W3DProjectedShadow*cur=list->head;cur;prev=cur,cur=cur->next){
  if(cur==shadow){
   if(prev)prev->next=shadow->next;else list->head=shadow->next;
   switch(shadow->type){case 1:case 0x20:case 0x40:case 0x400:case 0x800:case 0x2000:--decalCount;break;}
   shadow->next=free;free=shadow;shadow->rva007AEC10();return true;
  }
 }
 return false;
}
