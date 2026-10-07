// cl: /O2 /MD /EHsc
// Donor 5767d8d001ee10b1 AptMovie.cpp supplies two-pass init/dispatch semantics.
// Native 70F370 extent559 proves frame stride8, controls type1..8, initialization
// record16B and old PlaceObject2-only flow. Target has no later import fixups.
// Character parent+4 and animation array+16 are native data-use evidence.
// E176FC and E17738 are native zero-initialized background guard/callback slots.
// E17784 reuses the existing two-word cdecl external ABI; donor StartSound role
// conflicts with that older external's Free name, so no new semantic pin is made.
// Setup/cleanup bind cohort named providers; recovered init/place suppliers below.
// Existing unresolved globals and deeper core-place dependencies still need census closure.
class AptCIH;
struct Rva00700090Info { void *m_0; int m_4; const char *m_8; int m_c; };
class Rva00700090 {public:void *rva00700090(Rva00700090Info *);};
class Rva007002C0 {public:void rva007002C0(int,void *,int,void *);};
class Rva00706950 {public:void rva00706950(void *,Rva00700090Info *);};
class Rva006CD650 {public:void *rva006CD650();};
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
bool g_aptBackgroundSet = false;
void (__cdecl *g_aptBackgroundCallback)(int) = 0;
// Both this dispatcher and Rva006F3670 reference the same callback slot.
// Retail VA 0xE17784 is four zero-filled bytes before callback registration.
// Retain the existing ABI/name without asserting the conflicting donor role.
void (__cdecl *g_bfmeAptFreeAtE17784)(void *,int) = 0;
void AptDebuggerPrint(int,const char *,...);
#define CHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMovie.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
struct AptFrame; class AptDisplayList; class AptPseudoDisplayList;
class AptMovie {public:int nFrames;AptFrame *frames; void doFrameControls(AptDisplayList *,AptCIH *,int); void DoTemporaryFrameControls(AptPseudoDisplayList *,int);};
struct AptCharacter;
struct AptImportFile {char pad[0x14]; AptCharacter *mainCharacter;};
struct AptExport {const char *name; int id;};
struct AptImport {int a,b,id; AptImportFile *file;};
struct AptCharacterAnimation { AptMovie movie; int unknown8,nCharacters; AptCharacter **characters; char rest[12];int importCount;AptImport *imports;int exportCount;AptExport *exports;
 int IsImport(int id) {for(int i=0;i<importCount;++i)if(imports[i].id==id)return i;return -1;}
 int GetIDFromImportFile(int); void ExecuteInitActions(AptCIH *,int);void ExecuteInitAction(AptCIH *,int);void ExportClassDefinitionAssets(AptCIH *);
};
struct AptCharacter { int type; AptCharacter *parent; union { AptCharacterAnimation animation; void *sound; }; };
struct AptCharacterInst { char pad[12]; AptCharacter *character; int hash,unknown,frame; };
class AptCIH { public: char pad[0x4c]; AptCharacterInst *inst; const AptCIH *rva006E0CB0() const; bool IsSpriteInstBase() const;
 AptCharacterInst *Sprite() const {if(!IsSpriteInstBase()){g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}return inst;} };
struct AptControlPlaceObject2 {int flags,depth,character; float matrix[6]; int cxform[2]; float ratio; const char *name;int clip;void *actions;};
struct AptControl {int type; union {struct {int sprite,stream;} init; AptControlPlaceObject2 place; int value;};};
struct AptFrame {int count; AptControl **controls;};
class EAStringC {void *data; public:bool IsEqualTo(const EAStringC *) const;EAStringC();EAStringC(const char *);~EAStringC();EAStringC &operator=(const EAStringC &);};
class AptDisplayListState {public:void findInst(int,const EAStringC *,AptCIH **,AptCIH **);};
class AptDisplayList {public:AptDisplayListState *state; AptCIH *placeObject(AptControlPlaceObject2 *,AptCIH *); void removeObject(int *);
 AptCIH *placeObjectNCXForm(AptCIH *,int,AptCharacter *,EAStringC *,AptCIH *,int,int,const unsigned int *,const float *,void *,float);
};
class AptPseudoDisplayList;

void AptMovie::doFrameControls(AptDisplayList *display,AptCIH *inst,int frame) {
 CHECK(frame>=0 && frame<nFrames,0x110,"nFrame >= 0 && nFrame < (int)nFrames");
 for(int i=0;i<frames[frame].count;++i) {
  AptControl *control=frames[frame].controls[i];
  if(control->type==8 && control->init.sprite>=0) {
   Rva00700090Info setup={inst,0,"AptDoFrameControls",0x100000};
   void *saved=((Rva00700090 *)&g_aptDateInterpreter)->rva00700090(&setup);
   int before=*(int *)&g_aptDateInterpreter;
   void *character=inst ? ((Rva006CD650 *)inst->rva006E0CB0())->rva006CD650() : 0;
   ((Rva007002C0 *)&g_aptDateInterpreter)->rva007002C0(control->init.stream,inst,-1,character);
   control->init.sprite=-control->init.sprite;
   CHECK(before==*(int *)&g_aptDateInterpreter,0x133,"nStackSizePre == nStackSizePost");
   ((Rva00706950 *)&g_aptDateInterpreter)->rva00706950(saved,&setup);
  }
 }
 for(int i=0;i<frames[frame].count;++i) {
  AptControl *control=frames[frame].controls[i];
  switch(control->type) {
   case 5: if(!g_aptBackgroundSet){g_aptBackgroundCallback(control->value);g_aptBackgroundSet=true;} break;
   case 3: inst->inst->character->parent->animation.ExecuteInitActions(inst,control->place.character);display->placeObject(&control->place,inst);break;
   case 4: display->removeObject(&control->value);break;
   case 6: g_bfmeAptFreeAtE17784(inst->inst->character->parent->animation.characters[control->value]->sound,0);break;
   case 7: AptDebuggerPrint(3,"warning: soundstream level is always 0\n");break;
   case 1:case 2:case 8:break;
   default: CHECK(0,0x178,"NOT_REACHED");
  }
 }
}

#pragma comment(linker, "/alternatename:?rva007002C0@Rva007002C0@@QAEXHPAXH0@Z=?runStream@AptActionInterpreter@@QAEPBEPBEPAVAptCIH@@HPAUAptCharacterInst@@@Z")
#pragma comment(linker, "/alternatename:?removeObject@AptDisplayList@@QAEXPAH@Z=?bfmeForward1279@AptDisplayList@@QAEXPAUBfmeInput1279@@@Z")
#pragma comment(linker, "/alternatename:?AptDebuggerPrint@@YAXHPBDZZ=?Rva006CC110Log@@YAXHPBDZZ")

// Temporary controls: donor semantic guide; native preserves old always-true
// (flags & 1 | 0x98) clause removed in later source. PDB node remains20B.
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
struct AptControlInfo {int unused; float *matrix; int *cxform; void *actions; float ratio; int flags;};
struct AptPseudoCIH_t {AptControl *control;AptControlInfo *info; AptPseudoCIH_t *next,*prev; int depth;
 AptPseudoCIH_t(AptControl *,int,int,AptCharacter *);
 static void *operator new(unsigned int size){return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void *,unsigned int);
};
class AptPseudoDisplayList {public:void *head;AptCIH *parent;void FindInst(int,AptPseudoCIH_t **,AptPseudoCIH_t **);void Insert(AptPseudoCIH_t *); void Remove(AptPseudoCIH_t *); __forceinline void Insert(AptPseudoCIH_t *prev,AptPseudoCIH_t *item) {item->next=prev->next;item->prev=prev;if(item->next)item->next->prev=item;item->prev->next=item;}};
void AptMovie::DoTemporaryFrameControls(AptPseudoDisplayList *display,int frame) {
 CHECK(frame>=0 && frame<nFrames,0xb2,"nFrame >= 0 && nFrame < (int)nFrames");
 if(frame<0 || frame>=nFrames) return;
 AptCIH *sprite=display->parent;
 for(int i=0;i<frames[frame].count;++i){
  AptControl *control=frames[frame].controls[i];
  CHECK(frame==sprite->Sprite()->frame,0xc0,"nFrame == pSprInst->getSpriteInstBase()->nFrame");
  switch(control->type) {
   case 3: {
    AptCharacter *character=0;
    AptPseudoCIH_t *prev,*item;
    AptControlPlaceObject2 *place=&control->place;
    display->FindInst(place->depth,&prev,&item);
    if(place->character!=-1)character=sprite->inst->character->parent->animation.characters[place->character];
    if(item && place->character==-1 && (place->flags & 1 | 0x98)) {
     CHECK(item->info!=0,0xd3,"pItem->pControlInfo != NULL");
     CHECK(item->control->type==3,0xd4,"pItem->pControl->eType == AptControlType_PlaceObject2");
     item->info->matrix=place->flags&4 ? place->matrix : item->info->matrix;
     item->info->cxform=place->flags&8 ? place->cxform : item->info->cxform;
     item->info->actions=place->flags&0x80 ? place->actions : item->info->actions;
     item->info->ratio=place->flags&0x10 ? place->ratio : item->info->ratio;
     item->info->flags|=place->flags;
    } else display->Insert(new AptPseudoCIH_t(control,frame,place->depth,character));
    break;
   }
   case 4:display->Insert(new AptPseudoCIH_t(control,frame,control->value,0));break;
   case 1:case 2:case 5:case 6:case 7:case 8:break;
   default:CHECK(0,0xf1,"NOT_REACHED");
  }
 }
}

#pragma comment(linker, "/alternatename:?IsSpriteInstBase@AptCIH@@QBE_NXZ=?isSpriteInstBase@Rva006CFCD0@@QBE_NXZ")
#pragma comment(linker, "/alternatename:?FindInst@AptPseudoDisplayList@@QAEXHPAPAUAptPseudoCIH_t@@0@Z=?rva006F6AC0@Rva006F6AC0@@QAEXHPAPAX0@Z")
#pragma comment(linker, "/alternatename:??0AptPseudoCIH_t@@QAE@PAUAptControl@@HHPAUAptCharacter@@@Z=??0Rva006F6A50@@QAE@PAXHHH@Z")
#pragma comment(linker, "/alternatename:??3AptPseudoCIH_t@@SAXPAXI@Z=?Rva006D8680Free@@YAXPAXH@Z")

#pragma comment(linker, "/alternatename:?rva00706950@Rva00706950@@QAEXPAXPAURva00700090Info@@@Z=?CleanupAfterExecution@AptActionInterpreter@@QAEXPAXPAUAptActionSetup@@@Z")

// Donor34e2ed58628fb991 preserves Insert(prev,item) in both branches.
// Hoisting it changes native temporary slots and duplicates the epilogue.
void AptPseudoDisplayList::Insert(AptPseudoCIH_t *item) {
 AptPseudoCIH_t *prev,*old;
 FindInst(item->depth,&prev,&old);
 if(old) {Remove(old);FindInst(item->depth,&prev,&old);Insert(prev,item);}
 else Insert(prev,item);
}

#pragma comment(linker, "/alternatename:?Remove@AptPseudoDisplayList@@QAEXPAUAptPseudoCIH_t@@@Z=?Rva006F7C70Free@@YGXPAURva006F7C70Item@@@Z")

// Address-derived identity: the only caller is anonymous ?d_008d3860 and
// there is no named caller, vtable slot, string literal, or witnessed class
// layout for this body.  The offsets below are taken from retail disassembly.
// The body is a thiscall int(int) lookup with inline strcmp and no direct
// retail REL32 callees; the reviewed source probes exact at 135 bytes.
// Existing import-ID provider moved here intact; same native symbol and135B.
extern "C" int strcmp(const char *a, const char *b);

#pragma intrinsic(strcmp)

class Rva008A1CF0Item
{
public:
	const char *m_ptr00;
	int m_value04;
};

class Rva008A1CF0Group
{
public:
	unsigned char m_pad00[0x30];
	int m_count30;
	Rva008A1CF0Item *m_items34;
};

class Rva008A1CF0Owner
{
public:
	unsigned char m_pad00[0x14];
	Rva008A1CF0Group *m_group14;		// BFME1 +0x10; BFME2 retail reads +0x14
};

class Rva008A1CF0Slot
{
public:
	void *m_ptr00;
	const char *m_ptr04;
	unsigned char m_pad08[4];
	Rva008A1CF0Owner *m_owner0c;
};

class Rva008A1CF0
{
public:
	int rva008A1CF0(int idx);

	unsigned char m_pad00[0x24];
	Rva008A1CF0Slot *m_table24;
};

__declspec(noinline) int Rva008A1CF0::rva008A1CF0(int idx)
{
	Rva008A1CF0Group *g = m_table24[idx].m_owner0c->m_group14;
	int n = g->m_count30;
	int i = 0;

	if (n > 0)
	{
		Rva008A1CF0Slot *s = &m_table24[idx];
		Rva008A1CF0Item *items = g->m_items34;
		const char *name = s->m_ptr04;
		Rva008A1CF0Item *item = items;

		do
		{
			if (strcmp(name, item->m_ptr00) == 0)
				return items[i].m_value04;

			++i;
			++item;
		}
		while (i < n);
	}

	return -1;
}

void AptCharacterAnimation::ExecuteInitActions(AptCIH *inst,int id) {
 AptCharacterAnimation *animation=this;
 const AptMovie *movie=&inst->inst->character->animation.movie;
 int imported=animation->IsImport(id);
 if(imported!=-1) {
  id=((Rva008A1CF0 *)animation)->rva008A1CF0(imported);
  if(id!=-1){animation=&animation->imports[imported].file->mainCharacter->animation;movie=&animation->characters[id]->animation.movie;}
 }
 if(movie->nFrames>0){
  for(int i=0;i<movie->frames[0].count;++i){
   const AptControl *control=movie->frames[0].controls[i];
   if(control->type==3 && control->place.character!=-1) animation->ExecuteInitAction(inst,control->place.character);
  }
 }
 if(id!=-1)animation->ExecuteInitAction(inst,id);
}

#pragma comment(linker, "/alternatename:?rva00700090@Rva00700090@@QAEPAXPAURva00700090Info@@@Z=?PrepareForExecution@AptActionInterpreter@@QAEPAXPAUAptActionSetup@@@Z")

// Donor456a41a94fdaff0f init-clip body; native omits later zombie-cleanup flag.
void AptCharacterAnimation::ExecuteInitAction(AptCIH *inst,int id) {
 for(int i=0;i<movie.frames->count;++i) {
  AptControl *control=movie.frames->controls[i];
  if(control->type==8 && control->init.sprite==id) {
   ExportClassDefinitionAssets(inst);
   Rva00700090Info setup={inst,0,"AptImported_Init_Actions",0x100000};
   void *saved=((Rva00700090 *)&g_aptDateInterpreter)->rva00700090(&setup);
   void *character=inst ? ((Rva006CD650 *)inst->rva006E0CB0())->rva006CD650() : 0;
   ((Rva007002C0 *)&g_aptDateInterpreter)->rva007002C0(movie.frames->controls[i]->init.stream,inst,-1,character);
   ((Rva00706950 *)&g_aptDateInterpreter)->rva00706950(saved,&setup);
   control->init.sprite=-control->init.sprite;
   break;
  }
 }
}

extern "C" char *__cdecl strstr(const char *,const char *);
// Donor456a41a94fdaff0f export initialization; target __Packages. literal
// and export-table28/2C references independently support semantic identity.
void AptCharacterAnimation::ExportClassDefinitionAssets(AptCIH *inst) {
 for(int j=0;j<exportCount;++j){
  if(exports[j].id<0)return;
  if(strstr(exports[j].name,"__Packages.")){
   int id=exports[j].id;
   for(int k=0;k<movie.frames->count;++k){
    AptControl *control=movie.frames->controls[k];
    if(control->type==8 && control->init.sprite==id){
     Rva00700090Info setup={inst,0,"AptImported_Init_Actions",0x100000};
     void *saved=((Rva00700090 *)&g_aptDateInterpreter)->rva00700090(&setup);
     void *character=inst ? ((Rva006CD650 *)inst->rva006E0CB0())->rva006CD650() : 0;
     ((Rva007002C0 *)&g_aptDateInterpreter)->rva007002C0(movie.frames->controls[k]->init.stream,inst,-1,character);
     ((Rva00706950 *)&g_aptDateInterpreter)->rva00706950(saved,&setup);
     break;
    }
   }
   exports[j].id=-exports[j].id;
  }
 }
}

#define DL_CHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
void __debugbreak();
#pragma intrinsic(__debugbreak)
class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

struct BfmeQueryNode1279
{
	void *m_bfme00;
	void *m_bfme04;
	void *m_nameHandle;
	char m_pad0C[0x54 - 0x0C];
	BfmeQueryNode1279 *m_next;
	int m_key;
};

class BfmeQuery1279
{
public:
	void bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem);

private:
	BfmeQueryNode1279 *m_root;
};

// ?bfmeQuery1279@BfmeQuery1279@@QAEXHHPAPAXPAPAX@Z
__declspec(noinline) void BfmeQuery1279::bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem)
{
	if (ppPrev == 0) {
		g_bfmeAptAssertAtE17734("ppPrev", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x17D);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (ppItem == 0) {
		g_bfmeAptAssertAtE17734("ppItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x17E);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!(nDepth >= 0)) {
		g_bfmeAptAssertAtE17734("nDepth >= 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x17F);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	BfmeQuery1279 *self = this;
	BfmeQueryNode1279 *node = self->m_root->m_next;
	BfmeQueryNode1279 *namePrevious = self->m_root;

	if (name != 0 && node != 0) {
		do {
			if (((BfmeAptValue006DCD20 *)node)->isUndefined()) {
				if (((EAStringC *)name)->IsEqualTo((EAStringC *)&node->m_nameHandle)) {
					*ppItem = node;
					*ppPrev = namePrevious;
					return;
				}
			}
			namePrevious = node;
			node = node->m_next;
		} while (node != 0);
	}

	node = self->m_root->m_next;
	BfmeQueryNode1279 *keyPrevious = self->m_root;
	while (node != 0 && ((node->m_key << 15) >> 15) < nDepth) {
		keyPrevious = node;
		node = node->m_next;
	}
	if (node != 0 && ((node->m_key << 15) >> 15) == nDepth)
		*ppItem = node;
	else
		*ppItem = 0;
	*ppPrev = keyPrevious;
}


// ?placeObject@AptDisplayList@@QAEPAVAptCIH@@PAUAptControlPlaceObject2@@PAV2@@Z
AptCIH *AptDisplayList::placeObject(AptControlPlaceObject2 *place,AptCIH *parent){
 if(place->flags&2){
  DL_CHECK(place->character>=0 && place->character<parent->inst->character->parent->animation.nCharacters,0x3c1,"pPlaceObject2->nCharacterID >= 0 && pPlaceObject2->nCharacterID < pParent->pData->pCharacter->pParentAnim->animation.nCharacters");
  AptCharacter *character=parent->inst->character->parent->animation.characters[place->character];
  DL_CHECK(character,0x3c3,"pCharacter");if(!character)return 0;
  EAStringC name;EAStringC *pName=0;
  if(place->flags&0x20){name=place->name;pName=&name;}
  return placeObjectNCXForm(0,place->depth,character,pName,parent,0,place->clip,place->flags&8 ? (unsigned *)place->cxform : 0,place->flags&4 ? place->matrix : 0,place->flags&0x80 ? place->actions : 0,place->ratio);
 }else if(place->flags&1){
  AptCIH *cur,*prev;((BfmeQuery1279 *)state)->bfmeQuery1279(place->depth,0,(void **)&prev,(void **)&cur);
  if(cur==0){
   DL_CHECK(place->character>=0 && place->character<parent->inst->character->parent->animation.nCharacters,0x3e8,"pPlaceObject2->nCharacterID >= 0 && pPlaceObject2->nCharacterID < pParent->pData->pCharacter->pParentAnim->animation.nCharacters");
   AptCharacter *character=parent->inst->character->parent->animation.characters[place->character];
   DL_CHECK(character,0x3ea,"pCharacter");
   EAStringC name;EAStringC *pName=0;
   if(place->flags&0x20){name=place->name;pName=&name;}
   return placeObjectNCXForm(0,place->depth,character,pName,parent,0,place->clip,place->flags&8 ? (unsigned *)place->cxform : 0,place->flags&4 ? place->matrix : 0,place->flags&0x80 ? place->actions : 0,place->ratio);
  }else return placeObjectNCXForm(cur,0,0,0,parent,0,-1,place->flags&8 ? (unsigned *)place->cxform : 0,place->flags&4 ? place->matrix : 0,place->flags&0x80 ? place->actions : 0,place->ratio);
 }
 return 0;
}

// Existing provider's machine code preserves EAX from core place operation;
// native caller saves that AptCIH* across its name destructor. The old provider
// uses an opaque void spelling; this direct alias retains its verified ABI.
#pragma comment(linker, "/alternatename:?placeObjectNCXForm@AptDisplayList@@QAEPAVAptCIH@@PAV2@HPAUAptCharacter@@PAVEAStringC@@0HHPBIPBMPAXM@Z=?bfmeSubmitColors1283@BfmeSubmitter1283@@QAEXHHHHHHHPBIHHH@Z")
#pragma comment(linker, "/alternatename:??0EAStringC@@QAE@XZ=?clear@EAStringC@@QAEAAV1@XZ")
