// ?rva006F9350@AptDisplayList@@QAEXPAVAptNativeHash@@PAVAptCIH@@PAUAptPseudoCIH_t@@1@Z
// partial score=0.8 date=2026-10-09
// cl: /O2 /MD /EHsc
// Native6F91F0..6F92D0 materializes a pseudo display-list item. Existing
// AptMovieFrameControls.cpp/6F9410 bank supplies old PlaceObject2 semantics.
// Native node0/control flags4/name34, info0..1A, depth17/created14 atCIH58.
// The original helper spelling is unproven; callback/provider names are owned.
class EAStringC {void *data;public:EAStringC();EAStringC(const char*);~EAStringC();EAStringC&operator=(const EAStringC&);bool IsEmpty()const;};
class AptCIH;
class AptValue {public:virtual void AddRef();virtual void Release();};
class AptNativeHash {public:void Set(const EAStringC*const,AptValue*const);};
struct AptCharacter {int type;AptCharacter *parent;char animation[8];};
struct AptCharacterInst {char pad[12];AptCharacter *character;};
class AptCharacterAnimation {public:void ExecuteInitActions(AptCIH*,int);};
struct AptPlaceControl {int flags,depth,character;float matrix[6];int cxform[2];float ratio;const char *name;int clip;void *actions;};
struct AptControl {int type;AptPlaceControl place;};
struct AptControlInfo {int character;const float *matrix;const unsigned int *cxform;int actions;int ratio;int flags;short created,clip;};
struct AptPseudoCIH_t {AptControl *control;AptControlInfo *info;AptPseudoCIH_t *next,*prev;int depth;};
class AptCIH:public AptValue {public:char unknown04[4];EAStringC name;int matrix[6];float colors[8];int unknown44;AptCIH *parent;AptCharacterInst *inst;AptCIH *prev,*next;int depth:17;int created:14;unsigned top:1;short unknown5c;unsigned char changed;int GetDepth()const{return depth;}};
class BfmeSubmitter1283 {public:void bfmeSubmitColors1283(int,int,int,int,int,int,int,const unsigned int*,int,int,int);};
class AptDisplayList {public:AptCIH *rva006F91F0(AptPseudoCIH_t*,AptCIH*);__declspec(noinline) AptCIH *rva006F92D0(AptNativeHash*,AptPseudoCIH_t*,AptCIH*);void bfmeProcess1279(void*);void rva006F9350(AptNativeHash*,AptCIH*,AptPseudoCIH_t*,AptCIH*);};
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
 result->created=item->info->created;
 return result;
}

class Rva006E34D0 {public:AptCIH **data;int count;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
// Native6F92D0..6F934B: initialize character, materialize, bind name,
// then append/AddRef/increment in the existing animation-pool root.
AptCIH *AptDisplayList::rva006F92D0(AptNativeHash *hash,AptPseudoCIH_t *item,AptCIH *parent)
{
 reinterpret_cast<AptCharacterAnimation*>(parent->inst->character->parent->animation)->ExecuteInitActions(parent,item->control->place.character);
 AptCIH *result=rva006F91F0(item,parent);
 if(!result->name.IsEmpty())hash->Set(&result->name,result);
 g_bfmeAptPtrAtE176D0->data[g_bfmeAptPtrAtE176D0->count]=result;
 g_bfmeAptPtrAtE176D0->data[g_bfmeAptPtrAtE176D0->count]->AddRef();
 ++g_bfmeAptPtrAtE176D0->count;
 return result;
}

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
void bfmeUnpackTwoColors1280(float*,const unsigned int*);
// Native6F9350..6F940A replaces a pseudo item, unless an unchanged-character
// placement can update the original CIH's colors/matrix in place.
void AptDisplayList::rva006F9350(AptNativeHash *hash,AptCIH *original,AptPseudoCIH_t *item,AptCIH *parent)
{
 if(item->depth!=original->GetDepth()) {
  g_bfmeAptAssertAtE17734("pNewItem->nDepth == pOriginalItem->nDepth","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",0x67D);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 if(item->info->character) {
  bfmeProcess1279(original);
  rva006F92D0(hash,item,parent);
  return;
 }
 if(!(original->changed&1)) {
  if(item->info->flags&8)bfmeUnpackTwoColors1280(original->colors,item->info->cxform);
  if(item->info->flags&4) {
   const int *matrix=reinterpret_cast<const int*>(item->info->matrix);
   original->matrix[0]=matrix[0];original->matrix[1]=matrix[1];
   original->matrix[2]=matrix[2];original->matrix[3]=matrix[3];
   original->matrix[4]=matrix[4];original->matrix[5]=matrix[5];
  }
 }
}
