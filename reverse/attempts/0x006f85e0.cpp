// AptDisplayList::instantiateCharacter
// partial score=0.2081863091037403 date=2026-10-10
/*
Partial reconstruction evidence, 2026-10-10; not verified recovery.

Native 0x006F85E0..0x006F8B69 is a complete 1417-byte body ending RET 32.
WB 0x01791780 and independent native assertions identify
AptDisplayList::instantiateCharacter. Native CIH/name/parent/payload offsets,
character-kind dispatch and helper call sites establish the target behavior;
WB's different offsets were not imported. BFME1 575ba2b04743 provides no
instantiateCharacter body, only a small unrelated creation stub. Existing
BFME2 Apt family definitions were the structural leads.

The draft implements the whole body in ordinary C++; /O2 /MD /EHsc emits
1424 bytes versus 1417. Concrete same-offset patched-byte agreement is
0.2081863091037403, not a near-exact match. Several control-flow, argument,
typed-field, lifetime and compiler variants leave register allocation and
instruction scheduling differences. The existing visible bfmeQuery1279
control independently emits its complete 297 retail bytes exactly, restoring
the native 12-byte frame in the main draft; that control is already recovered
and earns no new coverage. All new-body relocation names resolve, but that
fact does not prove body identity, relocation correctness or a recovery.

Open contracts: eight word arguments and RET 32 are native facts, while the
original C++ pointer/reference prototype remains partly structural. The
48-byte Rva006F7140Derived/base relationship is an inferred view, not a newly
proven canonical class contract. The draft consumes EAX from the existing
rva006F6ED0 provider through a return-typed member pointer cast, while its
current owned C++ declaration is void. Native final-call behavior suggests
returning the node, but the provider's source/signature contract has not been
reconciled. Do not use the cast as justification for a new alias or ledger row.

No new Code source, pin, class contract, escape hatch, or matched row was
installed. The draft is banked to preserve evidence for a later supported
compiler/ABI repair rather than repeatedly rediscovering the same trial.
*/
// cl: /O2 /MD /EHsc
// Private reconstruction only. Native 6F85E0..6F8B69 and WB1791780 establish
// AptDisplayList::instantiateCharacter. Original argument types remain partly
// structural; every offset below is checked against retail, not WB's +4 view.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
#define POOL_NEW static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
#define POOL_DELETE static void operator delete(void*p,unsigned n){g_pChainBlockAllocator->freeBlock(p,n);}
#define CHECK(c,s,l) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
class EAStringC {void*data;public:EAStringC(const char*);~EAStringC();EAStringC&operator=(const EAStringC&);bool IsEmpty()const;bool IsEqualTo(const EAStringC*)const;};
class AptValue {public:virtual void AddRef();virtual void Release();void setIsDefined(bool);};
class BfmeAptValue006DCD20 {public:bool isUndefined()const;void *rva006E0F40()const;};
class Rva006CFCD0 {public:bool isSpriteInstBase()const;};
class AptNativeHash {public:void Set(const EAStringC*const,AptValue*const);};
struct AptCharacter {int type;char unknown04[0x14];int value18,value1c,value20,value24;char unknown28[0x34-0x28];const char*defaultText;const char*variable;};
struct AptCharacterInst {const void*vtable;int value;int frame;AptCharacter*character;AptNativeHash*hash;int word14,word18;unsigned word1c;int word20,word24;char unknown28[0x3c-0x28];int word3c;char unknown40[0x60-0x40];int word60,word64;char unknown68[0x78-0x68];};
class AptCIH:public AptValue {public:char unknown04[4];EAStringC name;char unknown0c[0x48-0x0c];AptCIH*parent;AptCharacterInst*inst;AptCIH*prev,*next;int depth:17;int created:14;unsigned high:1;
 void *rva006E1170()const;void rva006E1F00(int);
};
class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE*);
struct BfmeQueryNode1279 {void *m_bfme00,*m_bfme04,*m_nameHandle;char m_pad0C[0x54-0x0c];BfmeQueryNode1279*m_next;int m_key;};
class BfmeQuery1279 {public:BfmeQueryNode1279*m_root;void bfmeQuery1279(int,int,void**,void**);void rva006F6ED0(int,int,void*);void rva006F6FB0(int,AptCIH*);};
class Rva006ED150 {public:Rva006ED150();virtual ~Rva006ED150();char rest[0x30-4];};
class Rva006F7140Derived:public Rva006ED150 {public:POOL_NEW POOL_DELETE Rva006F7140Derived(){} };
class Rva006F8D70 {public:Rva006F8D70();char storage[0x20];POOL_NEW POOL_DELETE};
class Rva006ED2A0 {public:Rva006ED2A0();char storage[0x78];POOL_NEW POOL_DELETE};
class Rva006F7D80 {public:Rva006F7D80();char storage[0x18];POOL_NEW};
class Rva006F7DA0 {public:Rva006F7DA0();char storage[0x1c];POOL_NEW};
class Rva006EBFF0 {public:void rva006EBE60(AptValue*);};
struct TextInst {const void*vtable;int value;int frame;AptCharacter*character;char unknown10[8];EAStringC text,variable;char unknown20[0x6c-0x20];int flags;};
class Rva006E34D0 {public:AptCIH**newInsts;int count;char unknown08[0xa4-8];int capacity;};
extern Rva006E34D0*g_bfmeAptPtrAtE176D0;
class AptDisplayList {public:BfmeQuery1279*state;void bfmeProcess1279(void*);void instantiateCharacter(int,AptCharacter*,EAStringC*,AptCIH*,int,int,AptCIH**,int*);};
void AptDisplayList::instantiateCharacter(int depth,AptCharacter*character,EAStringC*name,AptCIH*parent,int replace,int value,AptCIH**out,int*created)
{
 CHECK(parent,"pParent",0x254);
 CHECK(state,"pState",0x255);
 bool isNew;
 AptCIH*current=0;
 AptCIH*previous,*existing;
 state->bfmeQuery1279(depth,(int)name,(void**)&previous,(void**)&existing);
 AptCharacter*definition=character;
 if(existing) {
  if(replace) {
   if(existing){bfmeUnlinkNestedBE((BfmeNestedBE*)existing);bfmeProcess1279(existing);existing=0;}
   isNew=true;
  } else if(((BfmeAptValue006DCD20*)existing)->isUndefined()) {
   if(name && name->IsEqualTo(&existing->name)) {existing->setIsDefined(true);current=existing;}
   isNew=true;
  } else {current=existing;isNew=false;goto finish;}
 }
 {
  isNew=true;
  AptCharacterInst*inst=0;
  int type=13;
  if(definition->type==5) {
   inst=(AptCharacterInst*)new Rva006F7140Derived;
   inst->word18=-1;
   _ReadWriteBarrier();
   inst->word1c|=0x03000000;
  } else if(definition->type==4) {
   inst=(AptCharacterInst*)new Rva006F8D70;
   inst->word18=0;type=14;
  } else if(definition->type==2) {
   inst=(AptCharacterInst*)new Rva006ED2A0;
   inst->character=definition;
   inst->word24=definition->value20;
   inst->word60=definition->value24;
   inst->word3c=definition->value1c;
   inst->word64=definition->value18;
   type=15;
  } else if(definition->type==10) {inst=(AptCharacterInst*)new Rva006F7D80;type=16;}
  else if(definition->type==1) {inst=(AptCharacterInst*)new Rva006F7D80;type=12;}
  else if(definition->type==8) {inst=(AptCharacterInst*)new Rva006F7DA0;type=17;}
  else {CHECK(false,"NOT_REACHED",0x2b9);}
  if(((Rva006CFCD0*)parent)->isSpriteInstBase()) {
   if(!((Rva006CFCD0*)parent)->isSpriteInstBase()) {
    g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);
    if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
   }
   inst->frame=*(int*)((char*)parent->inst+0x18);
  } else inst->frame=-1;
  if(!current) {
   typedef AptCIH*(BfmeQuery1279::*Create)(int,int,void*);
   Create create=reinterpret_cast<Create>(&BfmeQuery1279::rva006F6ED0);
   current=(state->*create)(depth,type,inst);
  } else {
   if(depth!=current->depth) {
    bfmeUnlinkNestedBE((BfmeNestedBE*)current);
    state->rva006F6FB0(depth,current);
    current->Release();
   }
   current->inst=inst;
  }
  if(((Rva006CFCD0*)parent)->isSpriteInstBase())current->created=inst->frame;
  else current->created=-1;
  if(name) {
   current->name=*name;
   if(!name->IsEmpty())((AptCharacterInst*)parent->rva006E1170())->hash->Set(name,current);
  }
  if(type==13 || type==14) {
   CHECK(g_bfmeAptPtrAtE176D0->count<g_bfmeAptPtrAtE176D0->capacity,"gpPool->nNewInsts < gpPool->GetMaxNewMovieClips()",0x2f3);
   g_bfmeAptPtrAtE176D0->newInsts[g_bfmeAptPtrAtE176D0->count]=current;
   ++g_bfmeAptPtrAtE176D0->count;
   current->AddRef();
  } else if(type==15) {
   TextInst*text=(TextInst*)((BfmeAptValue006DCD20*)current)->rva006E0F40();
   if(text->character->defaultText){EAStringC str(text->character->defaultText);text->text=str;}
   else {EAStringC str("");text->text=str;}
   if(text->character->variable){EAStringC str(text->character->variable);text->variable=str;}
   else {EAStringC str("");text->variable=str;}
   ((Rva006EBFF0*)text)->rva006EBE60(parent);
   text->flags=6;
  }
 }
finish:
 CHECK(current,"pCurCIH",0x30b);
 parent->AddRef();
 if(current->parent)current->parent->Release();
 current->parent=parent;
 current->inst->character=definition;
 current->inst->value=value;
 if(definition->type==4)current->rva006E1F00(1);
 *out=current;
 *created=isNew;
}

// Existing297B provider included solely for witnessed output-nonescape.
inline __declspec(noinline) void BfmeQuery1279::bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem)
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
