// cl: /O2 /MD /EHsc
// Factory706A40 calls identify Sound/StringObject/Error constructor branches.
// Original Redwood6 PDB gives AptObject bases and sizes44/36/40, including
// members at20/24/28. Original Godfather MAP corroborates all three signatures.
// Later donor sources e97b38e0a6efef64 AptSound.cpp, b22da05c4b0dbf6d
// AptStringObject.h and13686598df83d138 AptError.h supply semantic guidance.
// Each native constructor independently proves its type tag, base/hash setup,
// own vtable, field stores and full extent. The canonical bitfields restore
// the native in-memory AND that opaque whole-dword views failed to reproduce.
#include "AptScriptFunction.h"
#include <math.h>
// ?AptValueGC::AptValueGC present-unmatched
inline AptValueGC::AptValueGC(AptVirtualFunctionTable_Indices type) : AptValue(type) {}
// ?AptValueWithHash::AptValueWithHash present-unmatched
inline AptValueWithHash::AptValueWithHash(AptVirtualFunctionTable_Indices type,int n) : AptValueGC(type),mNativeHash(n) {}
// ?AptObject::AptObject present-unmatched
inline AptObject::AptObject(AptVirtualFunctionTable_Indices type,int n) : AptValueWithHash(type,n)
{
    mnImplementedObjects=0;
    mbHasClass=0;
    mbIsInMainInst=0;
}

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
struct SoundCharacter { char pad[4]; void *parent; };
struct SoundSprite { char pad[12]; SoundCharacter *character; };
class AptCIH { public: char pad[0xc];float a,b,c,d,tx,ty;float alphaMultiplier,redMultiplier,greenMultiplier,blueMultiplier;float alphaOffset,redOffset,greenOffset,blueOffset;float *properties;char pad2[4];SoundSprite *sprite;char pad3[0x5c-0x50];union {unsigned int flags;struct {unsigned int flagsLow:16;unsigned int asChanged:1;unsigned int flagsHigh:15;};};void factoryEnsureProperties();bool rva006CFCD0() const;void factorySetProperty(int,float,bool);float factoryGetProperty(int) const; };
// Target scalar destructors6F3960/6FE430/6E9B50 use this pool and class size.
class Rva006D2A60 { public: void *allocBlock(int);void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptSound : public AptObject {
public: static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 AptSound(AptCIH *);virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;
void *pParentAnim;void *zID;const char *szName;
protected: virtual ~AptSound();
};
AptSound::AptSound(AptCIH *p) : AptObject((AptVirtualFunctionTable_Indices)21) {
 zID=0;
 if(!p->rva006CFCD0()) {g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
 pParentAnim=p->sprite->character->parent;szName=0;
}

class AptStringObject : public AptObject {
public: static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 AptStringObject(AptString *);virtual ~AptStringObject();virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;AptString *mpStringObject;
};
AptStringObject::AptStringObject(AptString *p) : AptObject((AptVirtualFunctionTable_Indices)42) {((AptValue *)p)->AddRef();mpStringObject=p;}
class EAStringC {void *data;public:EAStringC(const char *);EAStringC(const EAStringC &);~EAStringC();EAStringC();const char *rva00620090() const;unsigned int rva006D3750() const;int rva006D36C0(const EAStringC *) const;bool rva006D3490(const char *) const;bool rva006D3510(const char *) const;};
class AptError : public AptObject {
public: static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 AptError(EAStringC);virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;virtual bool objectMemberSet(AptValue *const,const EAStringC *const,AptValue *const);EAStringC msMessage,msName;
protected: virtual ~AptError();
};
AptError::AptError(EAStringC msg) : AptObject((AptVirtualFunctionTable_Indices)41),msMessage(msg),msName("Error") {}

#pragma comment(linker, "/alternatename:??0AptValue@@IAE@W4AptVirtualFunctionTable_Indices@@@Z=??0BfmeAptValue006DCD20@@QAE@H@Z")
typedef char SoundSize[sizeof(AptSound)==44?1:-1];
typedef char StringObjectSize[sizeof(AptStringObject)==36?1:-1];
typedef char ErrorSize[sizeof(AptError)==40?1:-1];

// Native vtable slots and scalar destructor calls bind canonical consumers to
// existing exact providers. Opaque provider names retain their prior provenance.
#pragma comment(linker, "/alternatename:??1AptSound@@MAE@XZ=??1Rva006F3990@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1AptStringObject@@UAE@XZ=??1Rva006FE460@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1AptError@@MAE@XZ=??1S4Dtor00587B30@@UAE@XZ")
#pragma comment(linker, "/alternatename:?objectMemberLookup@AptStringObject@@UBEPAVAptValue@@QAV2@QBVEAStringC@@@Z=?rva006FE400@Rva006FE400@@QAEHPAXPAURva008A4570Owner@@@Z")
#pragma comment(linker, "/alternatename:?objectMemberSet@AptError@@UAE_NQAVAptValue@@QBVEAStringC@@0@Z=?rva006E9580@Rva006E9580@@QAE_NHPAVEAStringC@@PAVBfmeAptValue006DCD20@@@Z")

// Original PDB ScriptColour is36B with pSprite+20; MAP supplies const-pointer
// parameter. Donor f1e86798adbb054c supplies semantics. Native6F24E0..6F25C5
// asserts non-null and only clears pSprite when isCIH fails (later code differs).
class BfmeAptValue006DCD20 {public: BfmeAptValue006DCD20 *rva006DCF60(bool);int rva006E02B0() const;void setGCRootCount(unsigned int);void factorySetString(const char *);int isSound() const;BfmeAptValue006DCD20 *rva006DCFE0();void rva006DD6C0(EAStringC *);BfmeAptValue006DCD20 *rva006DD0A0();int toInteger() const;int isObject() const;BfmeAptValue006DCD20 *rva006DD0E0();};
class AptScriptColour : public AptObject {
public:
 AptScriptColour(AptValue *const);
 static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;
 virtual void RegisterReferences() const;
 virtual void DestroyGCPointers();
 AptCIH *pSprite;
protected: virtual ~AptScriptColour();
};
AptScriptColour::AptScriptColour(AptValue *const pMovie) : AptObject((AptVirtualFunctionTable_Indices)26) {
 if(!pMovie){g_bfmeAptAssertAtE17734("pMovie != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptColour.cpp",0x30);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
 if(pMovie->isCIH()) {
  AptCIH *cih=(AptCIH *)((BfmeAptValue006DCD20 *)pMovie)->rva006DCF60(false);
  if(cih->rva006CFCD0() || (unsigned char)((BfmeAptValue006DCD20 *)cih)->rva006E02B0()) {
   pSprite=cih;((AptValue *)cih)->AddRef();
  }
 } else pSprite=0;
}

typedef char ScriptColourSize[sizeof(AptScriptColour)==36?1:-1];

// Native vtable scalar6F2C70 calls complete destructor6F25D0.
#pragma comment(linker, "/alternatename:??1AptScriptColour@@MAE@XZ=??1Rva006F25D0@@UAE@XZ")

// Native ScriptColour vtable slots13/11 are these existing GC providers.
#pragma comment(linker, "/alternatename:?RegisterReferences@AptScriptColour@@UBEXXZ=?rva006F2C20@Rva006F2C20@@UAEXXZ")
#pragma comment(linker, "/alternatename:?DestroyGCPointers@AptScriptColour@@UAEXXZ=?rva006F2C50@Rva006F2C50@@UAEXXZ")

// Lookup source leads: Sound e97b38e0a6efef64 and Colour f1e86798adbb054c.
// Error uses original PDB fields and the verified setter sibling6E9580; no
// readable Error lookup body was available. Native vtable slot7, property
// comparisons, warning strings and callback construction establish its flow.
typedef AptValue *(__cdecl *AptNativeCallback)(AptValue *,int);
class AptNativeFunction : public AptObject {
 void *callback;
public: AptNativeFunction(AptNativeCallback);
 static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
};
struct R4Word {const char *name;int value;};
const R4Word *Rva008B5610(const char *,unsigned int);
AptValue *callback006F3580(AptValue *,int);
AptValue *callback006F3670(AptValue *,int);
AptValue *callback006F36B0(AptValue *,int);
class BfmeS1083;
extern BfmeS1083 *g_bfmeS1083_0,*g_bfmeS1083_1,*g_bfmeS1083_2;
#define g_soundMethod1 ((AptNativeFunction *&)g_bfmeS1083_0)
#define g_soundMethod2 ((AptNativeFunction *&)g_bfmeS1083_2)
#define g_soundMethod3 ((AptNativeFunction *&)g_bfmeS1083_1)
#define DISPATCH(slot,callback) if(!slot){slot=new AptNativeFunction(callback);((BfmeAptValue006DCD20 *)slot)->setGCRootCount(1);slot->AddRef();}return slot;
AptValue *AptSound::objectMemberLookup(AptValue *const context,const EAStringC *const name) const {
 const R4Word *prop=context?Rva008B5610(name->rva00620090(),name->rva006D3750()):0;
 if(prop){switch(prop->value){case 1:{DISPATCH(g_soundMethod1,callback006F3580);}break;case 2:{DISPATCH(g_soundMethod2,callback006F3670);}break;case 3:{DISPATCH(g_soundMethod3,callback006F36B0);}break;}}
 return 0;
}

EAStringC *Rva0070B4F0GetString(int);
AptValue *callback006F2640(AptValue *,int);AptValue *callback006F2700(AptValue *,int);AptValue *callback006F2760(AptValue *,int);AptValue *callback006F29C0(AptValue *,int);
class BfmeS1082;
extern BfmeS1082 *g_bfmeS1082_4,*g_bfmeS1082_5,*g_bfmeS1082_6,*g_bfmeS1082_7;
#define g_colourSetRGB ((AptNativeFunction *&)g_bfmeS1082_4)
#define g_colourGetRGB ((AptNativeFunction *&)g_bfmeS1082_5)
#define g_colourGetTransform ((AptNativeFunction *&)g_bfmeS1082_6)
#define g_colourSetTransform ((AptNativeFunction *&)g_bfmeS1082_7)
AptValue *AptScriptColour::objectMemberLookup(AptValue *const context,const EAStringC *const name) const {
 if(name->rva006D36C0(Rva0070B4F0GetString(0x88))==0){DISPATCH(g_colourSetRGB,callback006F2640);}
 else if(name->rva006D36C0(Rva0070B4F0GetString(0x45))==0){DISPATCH(g_colourGetRGB,callback006F2700);}
 else if(name->rva006D36C0(Rva0070B4F0GetString(0x49))==0){DISPATCH(g_colourGetTransform,callback006F2760);}
 else if(name->rva006D36C0(Rva0070B4F0GetString(0x8b))==0){DISPATCH(g_colourSetTransform,callback006F29C0);}
 return 0;
}

AptValue *factoryCreateString();
AptValue *callback006E9730(AptValue *,int);
class Rva006E97A0Object;
extern Rva006E97A0Object *g_pRva006E97A0Object;
#define g_errorToString ((AptNativeFunction *&)g_pRva006E97A0Object)
void Rva006CC110Log(int,const char *,...);
extern const char g_00CEC838[],g_00BBFDDC[],g_00CEC710[];
AptValue *AptError::objectMemberLookup(AptValue *const context,const EAStringC *const name) const {
 if(name->rva006D3490("message")){AptValue *v=factoryCreateString();((BfmeAptValue006DCD20 *)v)->factorySetString(msMessage.rva00620090());return v;}
 if(name->rva006D3490("name")){AptValue *v=factoryCreateString();((BfmeAptValue006DCD20 *)v)->factorySetString(msName.rva00620090());return v;}
 if(name->rva006D3490("toString")){DISPATCH(g_errorToString,callback006E9730);}
 if(name->rva006D3510("message") || name->rva006D3510("name") || name->rva006D3510("toString")) {
 Rva006CC110Log(3,g_00CEC838,name->rva00620090());g_bfmeAptAssertAtE17734(g_00BBFDDC,g_00CEC710,0x4fa);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 return 0;
}

// Existing provider identities retained; native call operands establish ABI.
#pragma comment(linker, "/alternatename:??0AptNativeFunction@@QAE@P6APAVAptValue@@PAV1@H@Z@Z=??0Rva006D6500@@QAE@H@Z")
#pragma comment(linker, "/alternatename:?factoryCreateString@@YAPAVAptValue@@XZ=?Create@AptString@@SAPAV1@Z")
#pragma comment(linker, "/alternatename:?factorySetString@BfmeAptValue006DCD20@@QAEXPBD@Z=?SetString@AptValue@@QAEXPBD@Z")
#pragma comment(linker, "/alternatename:?callback006F3670@@YAPAVAptValue@@PAV1@H@Z=?Rva006F3670@@YAPAVBfmeAptValue006DCD20@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?callback006E9730@@YAPAVAptValue@@PAV1@H@Z=?rva006e9730@@YAPAVAptValue@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?rva006D36C0@EAStringC@@QBEHPBV1@@Z=?compare008B4260@Rva008B4260StringRef@@QBEHABU1@@Z")
typedef char FactoryNativeFunctionSize[sizeof(AptNativeFunction)==36?1:-1];

// Sound donor e97b38e0a6efef64 attachSound/stop semantics; native body proves
// animation+8, exports count+28/table+2C, character array+10 and sound tag6.
extern AptValue *gpUndefinedValue;
AptValue *callback006F36B0(AptValue *context,int) {
 if((unsigned char)((BfmeAptValue006DCD20 *)context)->isSound()) {
  g_bfmeAptAssertAtE17734("NOT_REACHED","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptSound.cpp",0x6d);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 return gpUndefinedValue;
}
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct SoundExport {const char *name;int id;};
struct SoundCharacterValue {int type;int opaque;void *id;};
struct SoundAnimation {char opaque[0x10];SoundCharacterValue **characters;char opaque2[0x28-0x14];int exportCount;SoundExport *exports;};
AptValue *callback006F3580(AptValue *context,int) {
 if((unsigned char)((BfmeAptValue006DCD20 *)context)->isSound()) {
  BfmeAptValue006DCD20 *name=((AptBasePtrStack *)&g_aptDateInterpreter)->At(0);
  EAStringC text;
  AptSound *sound=(AptSound *)((BfmeAptValue006DCD20 *)context)->rva006DCFE0();
  const SoundAnimation *animation=(const SoundAnimation *)((char *)sound->pParentAnim+8);
  name->rva006DD6C0(&text);
  for(int i=0;i<animation->exportCount;++i) {
   if(text.rva006D3510(animation->exports[i].name)) {
    if(animation->characters[animation->exports[i].id]->type==6) {
     sound->zID=animation->characters[animation->exports[i].id]->id;
     sound->szName=animation->exports[i].name;
    }
    break;
   }
  }
 }
 return gpUndefinedValue;
}

// Colour donor setRGB/getRGB semantics with original procedural-property ABI:
// native indices8/9/10, multiplier fields28/2C/30 and AS-change flag16 at5C.
// Original getRGB omits later clamping and truncates each float to int.
class AptInteger {public:static AptValue *Create(int);};
AptValue *callback006F2700(AptValue *context,int) {
 AptCIH *sprite=((AptScriptColour *)((BfmeAptValue006DCD20 *)context)->rva006DD0A0())->pSprite;
 if(sprite) {
  int rgb=((int)sprite->factoryGetProperty(8))<<16;
  rgb|=((int)sprite->factoryGetProperty(9))<<8;
  rgb|=(int)sprite->factoryGetProperty(10);
  return AptInteger::Create(rgb);
 }
 return gpUndefinedValue;
}
AptValue *callback006F2640(AptValue *context,int) {
 BfmeAptValue006DCD20 *param=((AptBasePtrStack *)&g_aptDateInterpreter)->At(0);
 AptCIH *sprite=((AptScriptColour *)((BfmeAptValue006DCD20 *)context)->rva006DD0A0())->pSprite;
 if(sprite) {
  int rgb=param->toInteger();
  sprite->factorySetProperty(8,(float)((rgb>>16)&255),false);
  sprite->factorySetProperty(9,(float)((rgb>>8)&255),false);
  sprite->factorySetProperty(10,(float)(rgb&255),false);
  sprite->redMultiplier=0; sprite->greenMultiplier=0; sprite->blueMultiplier=0;
  sprite->flags|=0x10000;
 }
 return gpUndefinedValue;
}

#pragma comment(linker, "/alternatename:?factoryGetProperty@AptCIH@@QBEMH@Z=?rva006E0920@Rva006E0920@@QBEMH@Z")

// Donor f1e86798adbb054c getTransform semantics; native6F2760..6F29BF
// uses eight CIH floats at24..40, integer scaling100/255, and hash properties.
// Placement allocation keeps the native32B pool allocation local to this use.
enum FactoryObjectAllocation { factoryObjectAllocation };
// ?operator new absent-from-retail
inline void *operator new(unsigned int n,FactoryObjectAllocation){return g_pChainBlockAllocatorF4->allocBlock(n);}
// ?operator delete absent-from-retail
inline void operator delete(void *p,FactoryObjectAllocation){g_pChainBlockAllocatorF4->freeBlock(p,32);}
class Rva8D0D80String;class Rva8D0D80Value;
class Rva8D0D80Table {public:void add(Rva8D0D80String *,Rva8D0D80Value *);};
#define COLOUR_ASSERT(expr,line) if(!(expr)){g_bfmeAptAssertAtE17734(#expr,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptColour.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
AptValue *callback006F2760(AptValue *context,int count) {
 if(count>0)return gpUndefinedValue;
 AptScriptColour *pTemp=(AptScriptColour *)((BfmeAptValue006DCD20 *)context)->rva006DD0A0();
 COLOUR_ASSERT(pTemp,0xca);
 AptCIH *pSpr=pTemp->pSprite;
 COLOUR_ASSERT(pSpr,0xcc);
 if(((AptValue *)pSpr)->getIsDefined()) {
 AptObject *obj=new(factoryObjectAllocation) AptObject((AptVirtualFunctionTable_Indices)27);
 {AptValue *v=AptInteger::Create((int)(pSpr->redMultiplier*100.f));EAStringC *name=Rva0070B4F0GetString(122);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->greenMultiplier*100.f));EAStringC *name=Rva0070B4F0GetString(58);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->blueMultiplier*100.f));EAStringC *name=Rva0070B4F0GetString(37);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->alphaMultiplier*100.f));EAStringC *name=Rva0070B4F0GetString(29);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->redOffset*255.f));EAStringC *name=Rva0070B4F0GetString(124);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->greenOffset*255.f));EAStringC *name=Rva0070B4F0GetString(59);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->blueOffset*255.f));EAStringC *name=Rva0070B4F0GetString(38);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 {AptValue *v=AptInteger::Create((int)(pSpr->alphaOffset*255.f));EAStringC *name=Rva0070B4F0GetString(30);((Rva8D0D80Table *)((char *)obj+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)v);}
 return obj; }return gpUndefinedValue;
}

// Native setter6F29C0..6F2C14 uses inverse scale factors and per-property
// integer conversion. Later donor supplies the transform property semantics.
AptValue *callback006F29C0(AptValue *context,int count) {
 if(count<=0)return gpUndefinedValue;
 AptValue *pParam=(AptValue *)((AptBasePtrStack *)&g_aptDateInterpreter)->At(0);
 COLOUR_ASSERT(!pParam->isUndefined(),0xf6);
 AptScriptColour *pTemp=(AptScriptColour *)((BfmeAptValue006DCD20 *)context)->rva006DD0A0();
 COLOUR_ASSERT(pTemp,0xf8);
 AptCIH *pSpr=pTemp->pSprite;
 COLOUR_ASSERT(pSpr,0xfa);
 if(((AptValue *)pSpr)->isUndefined())return gpUndefinedValue;
 if(pParam->getIsDefined() && (unsigned char)((BfmeAptValue006DCD20 *)pParam)->isObject()) {
 BfmeAptValue006DCD20 *obj=((BfmeAptValue006DCD20 *)pParam)->rva006DD0E0();
 {EAStringC *name=Rva0070B4F0GetString(122);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->redMultiplier=((BfmeAptValue006DCD20 *)v)->toInteger()*.01f;}
 {EAStringC *name=Rva0070B4F0GetString(124);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->redOffset=((BfmeAptValue006DCD20 *)v)->toInteger()*(1.0f/255.0f);}
 {EAStringC *name=Rva0070B4F0GetString(58);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->greenMultiplier=((BfmeAptValue006DCD20 *)v)->toInteger()*.01f;}
 {EAStringC *name=Rva0070B4F0GetString(59);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->greenOffset=((BfmeAptValue006DCD20 *)v)->toInteger()*(1.0f/255.0f);}
 {EAStringC *name=Rva0070B4F0GetString(37);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->blueMultiplier=((BfmeAptValue006DCD20 *)v)->toInteger()*.01f;}
 {EAStringC *name=Rva0070B4F0GetString(38);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->blueOffset=((BfmeAptValue006DCD20 *)v)->toInteger()*(1.0f/255.0f);}
 {EAStringC *name=Rva0070B4F0GetString(29);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->alphaMultiplier=((BfmeAptValue006DCD20 *)v)->toInteger()*.01f;}
 {EAStringC *name=Rva0070B4F0GetString(30);AptValue *v=((AptNativeHash *)((char *)obj+8))->Lookup(name);if(v)pSpr->alphaOffset=((BfmeAptValue006DCD20 *)v)->toInteger()*(1.0f/255.0f);}
 }return gpUndefinedValue;
}

// Target call operands and original MAP bind canonical hash lookup to existing provider.
#pragma comment(linker, "/alternatename:?Lookup@AptNativeHash@@QBEPAVAptValue@@QBVEAStringC@@@Z=?lookup@Rva0070B380@@QAEPAXABVEAStringC@@@Z")

// Setter semantics follow the later AptCIH source; native indices and layout
// are independently established above. Preserve the older shared AS flag
// update before dispatch, including cases that perform no matrix/colour write.
// Full 392B extent includes the 11-entry jump table, verified case by case.
__declspec(noinline) void AptCIH::factorySetProperty(int property,float value,bool asFlag) {
 factoryEnsureProperties();
 properties[property]=value;
 asChanged=(asFlag!=false);
 switch(property) {
 case 2:case 3:case 6: {
 float rotation=properties[6];
 float xs=properties[2]/100.f;
 float ys=properties[3]/100.f;
 if(rotation!=0.f) {
 rotation*=0.017453292f;
 float cs=cosf(rotation),sn=sinf(rotation);
 a=xs*cs;b=xs*sn;c=-(ys*sn);d=ys*cs;
 }else{a=xs;b=0.f;c=0.f;d=ys;}
 }break;
 case 0:tx=value;break;
 case 1:ty=value;break;
 case 7:if(value<0.f)alphaMultiplier=0.f;else alphaMultiplier=value/100.f;break;
 case 8:redOffset=value/255.f;break;
 case 9:greenOffset=value/255.f;break;
 case 10:blueOffset=value/255.f;break;
 }
}
