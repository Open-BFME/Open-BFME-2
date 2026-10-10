// ?rva007092F0@AptActionInterpreter@@AAEXPAVAptCIH@@PAVAptValue@@11H1@Z
// partial score=0.8956090242917316 date=2026-10-10
// cl: /O2 /MD /EHsc
class AptCIH; class EAStringC; class AptNativeHash; class AptArray; class AptPrototype; class AptLookup; class AptRegister; class AptString; class AptInteger;
enum AptVirtualFunctionTable_Indices { AptVFT_ScriptFunctionByteCodeBlock=45 };
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptValue {
    unsigned int m_valueFlags;
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    AptValue *findChild(const EAStringC *,AptValue *);
    AptCIH *c_cih(bool=false);
    AptArray *c_array() const;
    bool getIsDefined() const; bool isBoolean() const; bool isNone() const; bool isScriptFunction() const; bool isNativeFunction() const;
    bool isArray() const;
    AptVirtualFunctionTable_Indices getVtblIndex() const;
    bool isPrototype() const;
    AptPrototype *c_prototype() const;
    bool isLookup() const;
    bool isRegister() const;
    AptLookup *c_lookup() const;
    AptRegister *c_register() const;
    bool isExtern() const;
    AptCIH *c_cih(bool=false) const;
    unsigned int getRefCount() const;
    bool isCIH(bool=false) const;
    bool isObject() const;
    AptString *c_string() const;
    AptInteger *c_integer() const;
    bool isUndefined() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isString() const;
    void SetString(const char *);
    float toFloat() const;
    bool toBool() const;
    int toInteger() const;
    void toString(EAStringC &) const;
};
class EAStringC { void *mpData; public: EAStringC &TrimRight(const char *); EAStringC &Rva006D4F00Append(const EAStringC &); EAStringC &Rva006D50A0Append(const char *); EAStringC(unsigned int,unsigned int); EAStringC rva006D5ED0(int) const; EAStringC rva006d5f30(int,int) const; void rva006D3470(); int Find(char,int=0); EAStringC &Append(const char *const,unsigned int); bool IsEmpty() const; bool IsEqualTo(const EAStringC *) const; bool rva006D3560(const EAStringC *) const; const char *rva00620090() const; int rva006d6070(const char *,int=0); EAStringC(); unsigned int rva006D3750() const; EAStringC(const char *); EAStringC(const EAStringC &); int GetAt(int) const; int rva006D54B0(int,int); ~EAStringC(); EAStringC &operator=(const EAStringC &); };
class AptString : public AptValue { public: static AptString *Create(); EAStringC str; __forceinline EAStringC *GetInternalString() { return &str; } };
class AptMovie { public: int labelToFrame(const EAStringC *) const; void runFrameActions(AptCIH *,int); };
struct AptCharacter { unsigned char prefix[8]; AptMovie movie; };
class AptDisplayList { public: void removeClonedObject(AptCIH *); };
struct AptSpriteInstBase { unsigned char prefix[0xC]; AptCharacter *character; unsigned char middle[8]; int mnFrame; int mnObjectClipActions:24; unsigned int mbJustLoaded:1; unsigned int mbIsPlaying:1; unsigned int mnIsCustomControl:2; void *clipActions; AptDisplayList displayList; };
class AptCIH : public AptValue {
public:
    unsigned char prefix[0x1C-8];
    float matrixTX,matrixTY;
    unsigned char matrixToParent[0x48-0x24];
    AptCIH *mpDisplayListParent;
    void *mpCharacterInst;
    void *rva006E1020() const;
    bool IsLevelInst() const;
    bool IsSpriteInst(bool=false) const;
    bool IsAnimationInst(bool=false) const;
    AptSpriteInstBase *GetSpriteInstBase() const;
    bool IsSpriteInstBase() const;
    bool IsCharacterInst() const;
    __forceinline AptSpriteInstBase *GetCharacterInst() const {
        if (!IsCharacterInst()) {
            g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xA5);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return (AptSpriteInstBase *)mpCharacterInst;
    }
    void jumpToFrame(int);
    __forceinline AptSpriteInstBase *SpriteBaseInline() const {
        if (!IsSpriteInstBase()) {
            g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return (AptSpriteInstBase *)mpCharacterInst;
    }
    __forceinline void SetIsPlaying(bool play) {
        GetSpriteInstBase()->mbIsPlaying=play ? 1 : 0;
    }
};
class BfmeAptValue006DCD20 {public:int rva006E0350() const;};
BfmeAptValue006DCD20 *rva007064f0(int,int,EAStringC *);
class AptActionInterpreter { void rva007092F0(AptCIH*,AptValue*,AptValue*,AptValue*,int,AptValue*); };
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
__declspec(noinline) void rva007065e0(int a,int b,BfmeAptValue006DCD20 *value,BfmeAptValue006DCD20 **out) {
 AptValue *v=(AptValue *)value;
 if(v->isCIH(false) || v->ContainsNativeHashVirtual()) {*out=value;return;}
 if(v->isString()) {*out=rva007064f0(a,b,v->c_string()->GetInternalString());return;}
 g_bfmeAptAssertAtE17734("NOT_REACHED","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x7a6);
 if(g_bfmeAptBreakOnAssertAtDDC01C) {__asm int 3}
}

class Rva006E3C80 { public: int rva006E3C80(); };
class AptAnimationPoolData { public: void _tickNewInsts(); };
class BfmeSubmitter1283 { public: void bfmeSubmit1283(int,int,int,int,int,int,int,float*,int,int,int,int); };
class BfmeQuery1279 { public: void bfmeQuery1279(int,int,void**,void**); };
struct Rva007092F0Character { char prefix[0x2c]; int flag2c; };
void AptActionInterpreter::rva007092F0(AptCIH *context,AptValue *with,AptValue *source,AptValue *target,int depth,AptValue *init)
{
    AptValue *value=0;
    rva007065e0((int)context,(int)with,(BfmeAptValue006DCD20*)source,(BfmeAptValue006DCD20**)&value);
    EAStringC name;
    target->toString(name);
    if(value) {
        AptCIH *child=value->c_cih(false);
        if(child->mpDisplayListParent) {
            float morphFloat=static_cast<unsigned char>(((BfmeAptValue006DCD20*)child)->rva006E0350()) ? *(float*)((char*)child->rva006E1020()+0x18) : 0.0f; int morph=*(int*)&morphFloat;
            int actions=child->IsSpriteInstBase() ? (int)child->GetSpriteInstBase()->clipActions : 0;
            AptSpriteInstBase *definition=child->SpriteBaseInline();
            AptCIH *parent=child->mpDisplayListParent;
            AptSpriteInstBase *parentDefinition=parent->SpriteBaseInline();
            ((BfmeSubmitter1283*)&parentDefinition->displayList)->bfmeSubmit1283(0,depth,(int)definition->character,(int)&name,(int)parent,1,-1,(float*)child->matrixToParent,(int)((char*)child+0xc),actions,morph,(int)init);
            if(((Rva007092F0Character*)child->SpriteBaseInline())->flag2c==1) {
                AptCIH *prev=0,*clone=0;
                ((BfmeQuery1279*)&child->mpDisplayListParent->GetSpriteInstBase()->displayList)->bfmeQuery1279(depth,(int)&name,(void**)&prev,(void**)&clone);
                if(clone->isCIH(false)) ((Rva007092F0Character*)((Rva006E3C80*)clone)->rva006E3C80())->flag2c=1;
            }
            ((AptAnimationPoolData*)g_bfmeAptPtrAtE176D0)->_tickNewInsts();
        }
    }
}
