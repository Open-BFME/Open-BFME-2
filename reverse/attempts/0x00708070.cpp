// ?_FunctionAptActionCallMethod@AptActionInterpreter@@CAXQAU1@QAULocalContextT@1@@Z
// partial score=0.9963 date=2026-10-06
// cl: /O2 /MD /EHsc /GR-
// BANK TRIAL: canonical declaration expansion must be reconciled into shared
// header before landing. Original708070..7087E1 is1905B. Later source guide
// 0cbfd5f746c89504 with native pre-2007 superclass and string behavior retained.
#pragma once
// APT 0.19.03 Redwood6 original PDB supplies the inheritance, member names,
// signatures and virtual order. PC ctor709870 independently establishes the
// base fields at20/24/28/2C; ctor70A2C0 establishes the derived fields30..40.
// PC vtableCEEAE8 has the same25-slot order (audit virtual-slot-validation.json).
// Later APT3.02.02 source confirms the constructor semantics, but its enum and
// added virtual methods do NOT describe this PC ABI. Keep the native tag45.
// Original donor PDB SHA256 ab2b0b616a430aebf85f5cb81d0a0ab73f83bc044d8befa2eb46755543c90d03.
// Audit: docs/audits/2026-10-05-openbfme2 under the analysis-materials repository.
class AptCIH;
class AptString;
class AptArray;
class AptPrototype;
class AptObject;
class AptScriptFunctionBase;
class AptFrameStack;
class EAStringC;
class AptValue;
struct AptInitParmsT;
struct _AptScriptFunctionState;
struct AptConstantPool { int nItems; AptValue **apItems; };
enum AptVirtualFunctionTable_Indices { AptVFT_ScriptFunctionByteCodeBlock = 45 };

struct AptNativeHash
{
    AptValue *Lookup(const EAStringC *const) const;
    __forceinline AptValue *Get__Proto__() const { return mp__proto__; }
    void SetPrototype(AptValue *);
    void Set__Proto__(AptValue *);
    int mnTotalSize;
    void *mpData; // Hash-item storage; its element layout is not needed here.
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
};

class AptValue
{
public:
    bool isPrototype() const; AptPrototype *c_prototype() const;
    bool isObject() const; AptObject *c_object() const;
    AptCIH *c_cih(bool=false) const;
    bool isScriptFunction() const; AptScriptFunctionBase *c_scriptfunction() const;
    bool isArray() const; bool isInteger() const; bool isFloat() const;
    unsigned int getRefCount() const; int isMCInParentChain();
    int toInteger() const; void toString(EAStringC &) const;
    AptArray *c_array() const;
    AptString *c_string() const;
    bool isUndefined() const;
    AptValue *findChild(const EAStringC *, AptValue *);
    bool getIsDefined() const;
    bool isCIH(bool = false) const;
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const, const EAStringC *const, AptValue *const);
    virtual void DeleteThis();
    virtual void PreDestroy();
    virtual void DestroyGCPointers();
    virtual bool IsGarbageCollected() const = 0;
    virtual void RegisterReferences() const = 0;
protected:
    virtual ~AptValue();
    unsigned int mnValueData;
};
class AptValueGC : public AptValue
{
public:
    virtual bool IsGarbageCollected() const;
protected:
    virtual ~AptValueGC();
};
class AptValueWithHash : public AptValueGC
{
public:
    AptValueWithHash(AptVirtualFunctionTable_Indices, int);
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
protected:
    virtual ~AptValueWithHash();
    AptNativeHash mNativeHash;
};
class AptFrameStack : public AptValueWithHash
{
protected:
    AptFrameStack *mpParentScope;
};
struct _AptScriptFunctionState
{
    AptFrameStack *mpFrameStack;
    AptValue **mpRegBlockPreviousFrameBase;
};
class AptObject : public AptValueWithHash
{
public:
    __forceinline void setInMainInst(int v) { mbIsInMainInst=v; }
    bool DoesImplementObject(AptValue *) const;
    AptObject(AptVirtualFunctionTable_Indices, int = 8);
    virtual void setHasClass(int);
    virtual int getHasClass() const;
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
protected:
    virtual ~AptObject();
    // Original donor names and widths; native constructor independently clears
    // the low byte and bits8..9 at+1C.
    unsigned int mnImplementedObjects : 8;
    unsigned int mbHasClass : 1;
    unsigned int mbIsInMainInst : 1;
};

class AptScriptFunctionBase : public AptObject
{
    friend struct AptActionInterpreter;
public:
    void rva006FBED0();
    virtual AptScriptFunctionBase *Duplicate(AptCIH *) = 0;
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
    virtual void PreDestroy();
    virtual const char *GetName() const = 0;
    virtual unsigned int GetNumArguments() = 0;
    virtual const unsigned char *GetByteCodeBase() = 0;
    virtual unsigned int GetByteCodeSize() = 0;
    virtual AptConstantPool GetConstantPool() = 0;
    virtual void SetupBeforeExecution(_AptScriptFunctionState *, AptValue *);
    virtual void SetArgument(AptValue *, int) = 0;
    virtual void CleanupAfterExecution(_AptScriptFunctionState *);
    static AptValue **spRegBlockBase, **spRegBlockCurrentFrameBase;
    static int snRegBlockCurrentFrameCount, snRegisterBlockSize;
    static void InitializeStaticData(const AptInitParmsT &);
    static void ShutdownStaticData();
    static void *PushStaticData();
protected:
    AptScriptFunctionBase(AptVirtualFunctionTable_Indices, AptScriptFunctionBase *, AptCIH *, bool);
    static AptFrameStack *spFrameStack;
    virtual void CreatingNestedFunction();
    virtual ~AptScriptFunctionBase();
    AptCIH *mpCIH;
    AptCIH *mpParentAnim;
    AptFrameStack *mpCreatorScope;
    unsigned short mnFrameStackReserve;
};

class AptScriptFunctionByteCodeBlock : public AptScriptFunctionBase
{
public:
    AptScriptFunctionByteCodeBlock(const unsigned char *, int, AptConstantPool,
                                 const char *, AptCIH *, AptScriptFunctionBase *);
    virtual const char *GetName() const;
    virtual unsigned int GetNumArguments();
    virtual const unsigned char *GetByteCodeBase();
    virtual unsigned int GetByteCodeSize();
    virtual AptConstantPool GetConstantPool();
    virtual void SetArgument(AptValue *, int);
    virtual AptScriptFunctionBase *Duplicate(AptCIH *);
protected:
    virtual ~AptScriptFunctionByteCodeBlock();
    const unsigned char *mpByteCodeBase;
    const int mnByteCodeSize;
    const char *mpName;
    AptConstantPool mConstantPool;
};

// Original Redwood6 PDB gives24-byte DefineFunction record and52-byte
// function objects; PC704B50/704C60 access the same offsets and allocate0x34.
struct AptAction_DefineFunction {
    const char *szName;
    int nParams;
    const char **aszParams;
    int nCodeSize;
    mutable AptConstantPool constantPool;
};
class AptScriptFunction1 : public AptScriptFunctionBase {
public:
    AptScriptFunction1(AptScriptFunctionBase *,const AptAction_DefineFunction *,AptCIH *);
    static void *operator new(unsigned int);
    static void operator delete(void *);
    virtual const char *GetName() const;
    virtual unsigned int GetNumArguments();
    virtual const unsigned char *GetByteCodeBase();
    virtual unsigned int GetByteCodeSize();
    virtual AptConstantPool GetConstantPool();
    virtual void SetArgument(AptValue *,int);
    virtual AptScriptFunctionBase *Duplicate(AptCIH *);
protected:
    virtual ~AptScriptFunction1();
    const AptAction_DefineFunction *mpFunction;
};

struct AptAction_DefineFunction2
{
    const char *szName;
    int nParams;
    short nRegisterCount;
    short nFlags;
    int getDF2Flag(unsigned short f) const { return nFlags & f; }
    const void *aszParams; // Parameter-record pointer; no record access here.
    int nCodeSize;
    mutable AptConstantPool constantPool;
};
class AptScriptFunction2 : public AptScriptFunctionBase
{
public:
    AptScriptFunction2(AptScriptFunctionBase *,const AptAction_DefineFunction2 *,AptCIH *);
    static void *operator new(unsigned int);
    static void operator delete(void *);
    virtual const char *GetName() const;
    virtual unsigned int GetNumArguments();
    virtual const unsigned char *GetByteCodeBase();
    virtual unsigned int GetByteCodeSize();
    virtual void SetArgument(AptValue *,int);
    virtual AptScriptFunctionBase *Duplicate(AptCIH *);
    virtual void SetupBeforeExecution(_AptScriptFunctionState *, AptValue *);
    virtual void CleanupAfterExecution(_AptScriptFunctionState *);
    virtual AptConstantPool GetConstantPool();
protected:
    const AptAction_DefineFunction2 *mpFunction;
};
typedef char AptScriptFunctionBaseSize[sizeof(AptScriptFunctionBase) == 0x30 ? 1 : -1];
typedef char AptScriptFunctionByteCodeBlockSize[sizeof(AptScriptFunctionByteCodeBlock) == 0x44 ? 1 : -1];
typedef char AptScriptFunction2Size[sizeof(AptScriptFunction2) == 0x34 ? 1 : -1];

typedef char AptScriptFunction1Size[sizeof(AptScriptFunction1) == 0x34 ? 1 : -1];

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern AptValue *gpUndefinedValue, *gpGlobalMovieclipPrototype;
class EAStringC { void *data; public: EAStringC(); EAStringC(const char *); ~EAStringC(); EAStringC &operator=(const EAStringC &); bool EqualNoCase(const char *) const; const char *rva00620090() const; };
class AptPrototype : public AptValueWithHash { public: AptValue *superConstructor; };
class AptCIH : public AptValue { unsigned char opaque[0x48-8]; public: AptValue *displayParent; };
class AptArray : public AptValueWithHash { unsigned char opaque[0x28-0x1c]; public: int count; AptValue *GetAt(int); };
class Rva006DB160 { public: void *allocBlock(int); };
class Rva006DB270 { public: void freeBlock(void *,int); };
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006FBDB0 : public EAStringC { public: Rva006FBDB0(EAStringC,int,int); ~Rva006FBDB0(){context=0;} int context,action; static void *operator new(unsigned int n){return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n);} static void operator delete(void *v){g_pChainBlockAllocator->freeBlock(v,12);} };
class AptBasePtrStack
{
public:
    void PopAndPush(int,AptValue *);
    void Push(AptValue *);
    void PushNoInc(AptValue *);
    void rva006FE920();
    inline AptValue *At(int nPos) const
    {
        if (!(count-nPos>0)) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x10A);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return items[count-nPos-1];
    }
    inline void PopNoDec()
    {
        if (count<=0) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0xBF);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        } else --count;
    }
    AptValue *Top();
    void Pop(int);
    inline void Pop()
    {
        if (count<=0) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x98);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        } else {
            items[count-1]->Release();
            --count;
        }
    }
    int count,capacity;
    AptValue **items;
};

struct AptValuePtrStack {
 int count,capacity; AptValue **items;
 void push(AptValue *); AptValue *top(); AptValue *at(int);
 inline void pushInline(AptValue *v) {
  if(count>=capacity) { g_bfmeAptAssertAtE17734("m_nElements < m_nSize","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x76); if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3} }
  items[count++]=v; v->AddRef();
 }
 inline AptValue *topInline() {
  if(count<=0) {g_bfmeAptAssertAtE17734("m_nElements > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x89); if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3} }
  return items[count-1];
 }
 inline void pop() {
  if(count<=0) {g_bfmeAptAssertAtE17734("size() > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x7d); if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3} }
  items[count-1]->Release(); --count;
 }
};
struct AptCallDebugStack {int count,capacity; Rva006FBDB0 **items;
 inline void Push(Rva006FBDB0 *v){if(count>=capacity){g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptDebugStack.h",0x6a);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}} items[count++]=v;}
 inline void Pop(){--count;delete items[count];items[count]=0;}
};
struct AptActionInterpreter {
 struct LocalContextT { const unsigned char *pInstruction; AptCIH *pCurrentContext; AptValue *pCurWith; const unsigned char *pRemoveWithAt; AptValue *pSuper; bool bEncounteredReturn; void *pParentCharacter; };
 AptBasePtrStack stack; AptValuePtrStack withStack; char between[12]; AptValuePtrStack thisStack; AptScriptFunctionBase *mpCurrentFunction; AptCallDebugStack debugCallStack;
 AptValue *getVariable(AptValue *,AptValue *,const EAStringC *,int=1,int=1,int=0);
 void callFunction(AptValue *,AptValue *,int);
private: static void _FunctionAptActionCallMethod(AptActionInterpreter *const,LocalContextT *const);
};
void AptActionInterpreter::_FunctionAptActionCallMethod(AptActionInterpreter *const p,LocalContextT *const c)
{
 AptValue *function=p->stack.At(0);
 AptValue *object=p->stack.At(1);
 AptValue *params=p->stack.At(2);
 int nParams=params->toInteger();
 EAStringC name;
 bool pushed=false;
 AptValue *fn=0;
 if(function==gpUndefinedValue) {
  name="super";
  if(object->isPrototype()) fn=object->c_prototype()->superConstructor;
  else fn=object;
 } else function->toString(name);
 if(!object->isUndefined()) {
  AptValue *savedObject=object,*savedParams=params;
  p->thisStack.pushInline((AptValue *)c->pCurrentContext);
  function=0;
  p->stack.Pop();p->stack.PopNoDec();p->stack.PopNoDec();
  if(fn==0 || fn==gpUndefinedValue) fn=p->getVariable(object,0,&name);
  if(!fn || fn->isUndefined()) {
   if(name.EqualNoCase("apply") || name.EqualNoCase("call")) {
    fn=object;
    if(params->isInteger() || params->isFloat()) {
     if(nParams>0) { AptValue *thisObj=p->stack.At(0); object=(!thisObj || thisObj->isUndefined())?gpUndefinedValue:thisObj; p->stack.Pop(); --nParams; }
     else object=gpUndefinedValue;
    } else {
     object=params; AptValue *actualParams=p->stack.At(0); nParams=actualParams->toInteger();
     if(nParams>1) {AptValue *thisObj=p->stack.At(1);if(thisObj && !thisObj->isUndefined())object=thisObj; p->stack.Pop();--nParams;}
     p->stack.Pop();
    }
    if(name.EqualNoCase("apply")) {
     AptValue *v=p->stack.At(0);
     if(v->isArray()) {p->stack.Pop(); AptArray *a=v->c_array(); int length=a->count; nParams=nParams-1+length;for(int i=length-1;i>=0;--i)p->stack.Push(a->GetAt(i));}
    }
   }
  }
  if(object->getHasClass()) {
   bool good=true; AptValue *value=object;
   if(p->withStack.count==0) {if(value==c->pSuper){EAStringC thisName("this");value=p->getVariable((AptValue *)c->pCurrentContext,0,&thisName);}}
   else {
    AptValue *top=p->withStack.top();
    if(value->isCIH() && value->c_cih()->displayParent==top) {}
    else if(value!=top) {
     AptNativeHash *hash=top->GetNativeHashVirtual();
     while(hash){AptValue *proto=hash->mp__proto__;if(proto && proto==value){good=false;break;}hash=proto?proto->GetNativeHashVirtual():0;}
    }
   }
   if(good){pushed=true;if(value->isObject())value->c_object()->setInMainInst(1);p->withStack.push(value);}
  }
  bool stayAlive=false;
  if(object->getRefCount()==1){object->AddRef();stayAlive=true;}
  p->debugCallStack.Push(new Rva006FBDB0(name.rva00620090(),(int)object,0x8000000));
  if(object->isMCInParentChain()) {
   if(object==gpGlobalMovieclipPrototype)object=p->thisStack.at(1);
   if(object==c->pSuper) {
    if(fn->isScriptFunction()){AptScriptFunctionBase *sf=fn->c_scriptfunction();AptCIH *old=sf->mpCIH;sf->mpCIH=c->pCurrentContext;p->callFunction(object,fn,nParams);sf->mpCIH=old;}
    else p->callFunction(object,fn,nParams);
   } else p->callFunction(object,fn,nParams);
  } else p->callFunction(object,fn,nParams);
  if(pushed==true){AptValue *top=p->withStack.topInline();if(top->isObject())top->c_object()->setInMainInst(0);p->withStack.pop();}
  if(stayAlive)object->Release();
  p->debugCallStack.Pop();
  if(p->stack.At(0)!=gpUndefinedValue && object->isArray() && (name.EqualNoCase("pop") || name.EqualNoCase("shift")))p->stack.Top()->Release();
  p->thisStack.pop();savedObject->Release();savedParams->Release();
 } else {p->stack.Pop(nParams+3);p->stack.PushNoInc(gpUndefinedValue);}
}
