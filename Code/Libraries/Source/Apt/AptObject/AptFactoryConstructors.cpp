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
class AptCIH { public: char pad[0x4c];SoundSprite *sprite;bool rva006CFCD0() const; };
// Target scalar destructors6F3960/6FE430/6E9B50 use this pool and class size.
class Rva006D2A60 { public: void freeBlock(void *,int); };
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
class EAStringC {void *data;public:EAStringC(const char *);EAStringC(const EAStringC &);~EAStringC();};
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
class BfmeAptValue006DCD20 {public: BfmeAptValue006DCD20 *rva006DCF60(bool);int rva006E02B0() const;};
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
