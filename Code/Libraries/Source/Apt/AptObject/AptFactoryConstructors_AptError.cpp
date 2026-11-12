// cl: /O2 /MD /EHsc
// Split from AptFactoryConstructors.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Keep MSVC math.h float overloads local; matched operations already inline.
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")
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
#include "../Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptSound : public AptObject {
public: static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 AptSound(AptCIH *);virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;
void *pParentAnim;void *zID;const char *szName;
protected: virtual ~AptSound();
};

class AptStringObject : public AptObject {
public: static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
 AptStringObject(AptString *);virtual ~AptStringObject();virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;AptString *mpStringObject;
};
#include "../EAStringC.h"
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
#pragma comment(linker, "/alternatename:??1AptError@@MAE@XZ=??1S4Dtor00587B30@@UAE@XZ")
#pragma comment(linker, "/alternatename:?objectMemberSet@AptError@@UAE_NQAVAptValue@@QBVEAStringC@@0@Z=?rva006E9580@Rva006E9580@@QAE_NHPAVEAStringC@@PAVBfmeAptValue006DCD20@@@Z")

// Original PDB ScriptColour is36B with pSprite+20; MAP supplies const-pointer
// parameter. Donor f1e86798adbb054c supplies semantics. Native6F24E0..6F25C5
// asserts non-null and only clears pSprite when isCIH fails (later code differs).
#include "../BfmeAptValue006DCD20.h"
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


typedef char ScriptColourSize[sizeof(AptScriptColour)==36?1:-1];

// Native vtable scalar6F2C70 calls complete destructor6F25D0.

// Native ScriptColour vtable slots13/11 are these existing GC providers.

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
#include "../../../../GameEngine/Include/Common/R4Word.h"
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


EAStringC *Rva0070B4F0GetString(int);
AptValue *callback006F2640(AptValue *,int);AptValue *callback006F2700(AptValue *,int);AptValue *callback006F2760(AptValue *,int);AptValue *callback006F29C0(AptValue *,int);
class BfmeS1082;
extern BfmeS1082 *g_bfmeS1082_4,*g_bfmeS1082_5,*g_bfmeS1082_6,*g_bfmeS1082_7;
#define g_colourSetRGB ((AptNativeFunction *&)g_bfmeS1082_4)
#define g_colourGetRGB ((AptNativeFunction *&)g_bfmeS1082_5)
#define g_colourGetTransform ((AptNativeFunction *&)g_bfmeS1082_6)
#define g_colourSetTransform ((AptNativeFunction *&)g_bfmeS1082_7)


AptValue *factoryCreateString();
AptValue *callback006E9730(AptValue *,int);
class Rva006E97A0Object;
extern Rva006E97A0Object *g_pRva006E97A0Object;
#define g_errorToString ((AptNativeFunction *&)g_pRva006E97A0Object)
void Rva006CC110Log(int,const char *,...);
extern const char g_00CEC838[],g_00BBFDDC[],g_00CEC710[];
AptValue *AptError::objectMemberLookup(AptValue *const context,const EAStringC *const name) const {
 if(name->rva006D3490("message")){AptValue *aptValue=factoryCreateString();((BfmeAptValue006DCD20 *)aptValue)->factorySetString(msMessage.rva00620090());return aptValue;}
 if(name->rva006D3490("name")){AptValue *aptValue=factoryCreateString();((BfmeAptValue006DCD20 *)aptValue)->factorySetString(msName.rva00620090());return aptValue;}
 if(name->rva006D3490("toString")){DISPATCH(g_errorToString,callback006E9730);}
 if(name->rva006D3510("message") || name->rva006D3510("name") || name->rva006D3510("toString")) {
 Rva006CC110Log(3,"AptError: Incorrect case for '%s'.\n",name->rva00620090());g_bfmeAptAssertAtE17734(g_00BBFDDC,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",0x4fa);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 return 0;
}

// Existing provider identities retained; native call operands establish ABI.
#pragma comment(linker, "/alternatename:??0AptNativeFunction@@QAE@P6APAVAptValue@@PAV1@H@Z@Z=??0Rva006D6500@@QAE@H@Z")
#pragma comment(linker, "/alternatename:?factoryCreateString@@YAPAVAptValue@@XZ=?Create@AptString@@SAPAV1@XZ")
#pragma comment(linker, "/alternatename:?factorySetString@BfmeAptValue006DCD20@@QAEXPBD@Z=?SetString@AptValue@@QAEXPBD@Z")
#pragma comment(linker, "/alternatename:?callback006E9730@@YAPAVAptValue@@PAV1@H@Z=?rva006e9730@@YAPAVAptValue@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?rva006D36C0@EAStringC@@QBEHPBV1@@Z=?compare008B4260@Rva008B4260StringRef@@QBEHABU1@@Z")
typedef char FactoryNativeFunctionSize[sizeof(AptNativeFunction)==36?1:-1];

// Sound donor e97b38e0a6efef64 attachSound/stop semantics; native body proves
// animation+8, exports count+28/table+2C, character array+10 and sound tag6.
extern AptValue *gpUndefinedValue;
AptValue *callback006F36B0(AptValue *context,int);

struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
AptValue *callback006F3580(AptValue *context,int);


// Colour donor setRGB/getRGB semantics with original procedural-property ABI:
// native indices8/9/10, multiplier fields28/2C/30 and AS-change flag16 at5C.
// Original getRGB omits later clamping and truncates each float to int.
AptValue *callback006F2700(AptValue *context,int);

AptValue *callback006F2640(AptValue *context,int);



// Donor f1e86798adbb054c getTransform semantics; native6F2760..6F29BF
// uses eight CIH floats at24..40, integer scaling100/255, and hash properties.
// Placement allocation keeps the native32B pool allocation local to this use.
// The tag carries the pooled block size the unwind funclet frees (0x20).
enum FactoryObjectAllocation { factoryObjectAllocation = sizeof(AptObject) };
// ?operator new absent-from-retail
inline void *operator new(unsigned int n,FactoryObjectAllocation){return g_pChainBlockAllocatorF4->allocBlock(n);}
// Native6F12F0 pool-delete fold; the tag is a TU-local structural model.
inline void operator delete(void *p,FactoryObjectAllocation size){g_pChainBlockAllocatorF4->freeBlock(p,size);}
class Rva8D0D80String;class Rva8D0D80Value;
#define COLOUR_ASSERT(expr,line) if(!(expr)){g_bfmeAptAssertAtE17734(#expr,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptColour.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
AptValue *callback006F2760(AptValue *context,int count);

AptValue *callback006F29C0(AptValue *context,int count);


// Target call operands and original MAP bind canonical hash lookup to existing provider.


