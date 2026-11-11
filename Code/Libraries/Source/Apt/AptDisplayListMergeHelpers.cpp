// cl: /O2 /MD /EHsc
// Native6F91F0..6F92D0 materializes a pseudo display-list item. Existing
// AptMovieFrameControls.cpp/6F9410 bank supplies old PlaceObject2 semantics.
// Native node0/control flags4/name34, info0..1A, depth17/created14 atCIH58.
// The original helper spelling is unproven; callback/provider names are owned.
#include "EAStringC.h"
class AptCIH;
class AptValue;
class Rva006DBB30SarDwordField {public:int get()const;};
class AptNativeHash {public:void Set(const EAStringC*const,AptValue*const);AptValue *Lookup(const EAStringC*const)const;void Unset(const EAStringC*const);};
struct AptCharacter {int type;AptCharacter *parent;char animation[8];};
struct AptCharacterInst {char pad[12];AptCharacter *character;int hash,unknown,frame;char rest[16];int dynamic;};
class AptCharacterAnimation {public:void ExecuteInitActions(AptCIH*,int);};
struct AptPlaceControl {int flags,depth,character;float matrix[6];int cxform[2];float ratio;const char *name;int clip;void *actions;};
struct AptControl {int type;AptPlaceControl place;};
struct AptControlInfo {int character;const float *matrix;const unsigned int *cxform;int actions;int ratio;int flags;short created,clip;};
struct BfmeMatrix6 { int v[6]; };
struct AptPseudoCIH_t {AptControl *control;AptControlInfo *info;AptPseudoCIH_t *next,*prev;int depth;};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "AptCIHClass.h"
struct AptCIHKeyBits {int depth:17;int created:14;unsigned top:1;};
static __forceinline AptCIHKeyBits &cihKeyBits(AptCIH *cih){return *(AptCIHKeyBits *)&cih->field58;}
static __forceinline int cihDepth(const AptCIH *cih){return ((const AptCIHKeyBits *)&cih->field58)->depth;}
static __forceinline int cihCreated(const AptCIH *cih){return ((const AptCIHKeyBits *)&cih->field58)->created;}
static __forceinline AptCIH *cihNext(const AptCIH *cih){return cih->field54;}
static __forceinline bool cihASChanged(const AptCIH *cih){return (((const unsigned char *)&cih->field5C)[2]&1)!=0;}
static __forceinline int cihType(const AptCIH *cih){return ((const Rva006DBB30SarDwordField *)cih)->get();}
static __forceinline AptCharacterInst *cihInst(const AptCIH *cih){return (AptCharacterInst *)cih->field4C;}
static __forceinline AptCharacterInst *cihSpriteInstBase(const AptCIH *cih){if(!cih->IsSpriteInstBase()){g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}return (AptCharacterInst *)cih->field4C;}
#include "BfmeSubmitter1283.h"
struct AptDisplayListState {AptCIH *head;};
class AptPseudoDisplayList {public:AptPseudoCIH_t *head;AptCIH *parent;};
class AptDisplayList {public:AptDisplayListState *state;AptCIH *rva006F91F0(AptPseudoCIH_t*,AptCIH*);__declspec(noinline) AptCIH *AddToDisplayList(AptNativeHash*,AptPseudoCIH_t*,AptCIH*);void bfmeProcess1279(void*);__declspec(noinline) void rva006F9350(AptNativeHash*,AptCIH*,AptPseudoCIH_t*,AptCIH*);void mergeState(AptPseudoDisplayList*,AptNativeHash*,bool);};
AptCIH *AptDisplayList::rva006F91F0(AptPseudoCIH_t *item,AptCIH *parent)
{
 EAStringC name;
 EAStringC *pName=0;
 if(item->control->place.flags&0x20) {
  { EAStringC temporary(item->control->place.name);
    name=temporary; }
  pName=&name;
 }
 typedef AptCIH *(BfmeSubmitter1283::*Submit)(int,int,int,int,int,int,int,const unsigned int*,int,int,int);
 Submit submit=reinterpret_cast<Submit>(&BfmeSubmitter1283::bfmeSubmitColors1283);
 AptCIH *result=(reinterpret_cast<BfmeSubmitter1283*>(this)->*submit)(0,item->depth,item->info->character,(int)pName,(int)parent,1,item->info->clip,item->info->cxform,(int)item->info->matrix,item->info->actions,item->info->ratio);
 cihKeyBits(result).created=item->info->created;
 return result;
}

class Rva006E34D0 {public:AptCIH **data;int count;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
// WB 0x01793D00 AptDisplayList::AddToDisplayList (callgraph lead, 3 args, ret 0xC).
// Native6F92D0..6F934B: initialize character, materialize, bind name,
// then append/AddRef/increment in the existing animation-pool root.
AptCIH *AptDisplayList::AddToDisplayList(AptNativeHash *hash,AptPseudoCIH_t *item,AptCIH *parent)
{
 reinterpret_cast<AptCharacterAnimation*>(cihInst(parent)->character->parent->animation)->ExecuteInitActions(parent,item->control->place.character);
 AptCIH *result=rva006F91F0(item,parent);
 if(!result->field08.IsEmpty())hash->Set(&result->field08,result);
 g_bfmeAptPtrAtE176D0->data[g_bfmeAptPtrAtE176D0->count]=result;
 g_bfmeAptPtrAtE176D0->data[g_bfmeAptPtrAtE176D0->count]->AddRef();
 ++g_bfmeAptPtrAtE176D0->count;
 return result;
}

void bfmeUnpackTwoColors1280(float*,const unsigned int*);
// Native6F9350..6F940A replaces a pseudo item, unless an unchanged-character
// placement can update the original CIH's colors/matrix in place.
void AptDisplayList::rva006F9350(AptNativeHash *hash,AptCIH *original,AptPseudoCIH_t *item,AptCIH *parent)
{
 if(item->depth!=cihDepth(original))
 {
  g_bfmeAptAssertAtE17734("pNewItem->nDepth == pOriginalItem->nDepth","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",0x67D);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 if(item->info->character)
 {
  bfmeProcess1279(original);
  AddToDisplayList(hash,item,parent);
  return;
 }
 if(!cihASChanged(original))
 {
  if(item->info->flags&8)bfmeUnpackTwoColors1280(&original->field24,item->info->cxform);
  if(item->info->flags&4)
  {
   *(BfmeMatrix6 *)(void *)&original->field0C = *(const BfmeMatrix6 *)(const void *)item->info->matrix;
  }
 }
}

// Donor 34e2ed58628fb991 AptDisplayList depth-ordered merge semantics; native
// 6F9410..6F97A9 asserts pNewControl == NULL at AptDisplayList.cpp:0x6C7 and is
// the old PlaceObject2-only flow. Native E8 targets: 6DC010/6DBB30 AptValue
// undefined/type (6DBB30 via its rowed accessor), 6CFCD0 sprite predicate, 6F67E0 type map, 6F7230 removal,
// 6F7090 unlink, 6E2B40 finish, 70B380/70B2C0 name hash lookup/unset.
class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE*);
class BfmeNode1279 {public:void bfmeFinish1279();};
int Rva006F67E0(int);
class AptCIHHashOwner {public:virtual void v00();virtual void v01();virtual void v02();virtual AptNativeHash *Hash();};
void AptDisplayList::mergeState(AptPseudoDisplayList *incoming,AptNativeHash *hash,bool ahead)
{
 AptPseudoCIH_t *control=incoming->head->next;
 AptCIH *current=state->head->field54;
 while(current)
 {
  if(cihDepth(current)>=16384)
  {
   while(control && control->depth<cihDepth(current)){if(control->control->type==3)AddToDisplayList(hash,control,incoming->parent);control=control->next;}
   if(!(control==0))
   {
    g_bfmeAptAssertAtE17734("pNewControl == NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",0x6c7);
    if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
   }
   break;
  }
  if(control && control->depth==cihDepth(current))
  {
   if(!current->isUndefined() && (cihType(current)==13 || cihType(current)==18) && cihSpriteInstBase(current)->dynamic){current=cihNext(current);control=control->next;continue;}
   AptCIH *next=cihNext(current);
   if(control->control->type==3)
   {
    if(control->info && (control->info->created==cihCreated(current) || cihType(current)==18))
    {
     if(control->info->character==0)
     {
      if(!cihASChanged(current))
      {
       if(control->info->flags&8)bfmeUnpackTwoColors1280(&current->field24,control->info->cxform);
       if(control->info->flags&4)*(BfmeMatrix6 *)(void *)&current->field0C=*(const BfmeMatrix6 *)(const void *)control->info->matrix;
      }
     }
     else
     {
      int mappedType=Rva006F67E0(((AptCharacter *)control->info->character)->type);
      if((cihType(current)==mappedType && (AptCharacter *)control->info->character==cihInst(current)->character && control->info->created==cihCreated(current))||cihType(current)==18)
      {
       if(!cihASChanged(current))
       {
        if(control->info->flags&8)bfmeUnpackTwoColors1280(&current->field24,control->info->cxform);
        if(control->info->flags&4)*(BfmeMatrix6 *)(void *)&current->field0C=*(const BfmeMatrix6 *)(const void *)control->info->matrix;
       }
      }
      else rva006F9350(hash,current,control,incoming->parent);
     }
    }
    else rva006F9350(hash,current,control,incoming->parent);
   }
   else bfmeProcess1279(current);
   control=control->next;
   current=next;
  }
  else if(control==0 || control->depth>cihDepth(current))
  {
   AptCIH *next=cihNext(current);
   if(!ahead)
   {
    if(!current->isUndefined())
    {
     if(current->field48)
     {
      AptNativeHash *lookup=((AptCIHHashOwner *)current->field48)->Hash();
      EAStringC &key=current->field08;
      if(!key.IsEmpty() && lookup && lookup->Lookup(&key)==current)lookup->Unset(&key);
     }
     bfmeUnlinkNestedBE((BfmeNestedBE *)current);
     ((BfmeNode1279 *)current)->bfmeFinish1279();
    }
   }
   current=next;
  }
  else
  {
   while(control){if(control->depth>=cihDepth(current))break;if(control->control->type==3)AddToDisplayList(hash,control,incoming->parent);control=control->next;}
  }
 }
 if(control){while(control){if(control->control->type==3)AddToDisplayList(hash,control,incoming->parent);control=control->next;}}
}
