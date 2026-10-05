#pragma once
// APT 0.19.03 Redwood6 original PDB supplies the inheritance, member names,
// signatures and virtual order. PC ctor709870 independently establishes the
// base fields at20/24/28/2C; ctor70A2C0 establishes the derived fields30..40.
// PC vtableCEEAE8 has the same25-slot order (audit virtual-slot-validation.json).
// Later APT3.02.02 source confirms the constructor semantics, but its enum and
// added virtual methods do NOT describe this PC ABI. Keep the native tag45.
// Original donor PDB SHA256 ab2b0b616a430aebf85f5cb81d0a0ab73f83bc044d8befa2eb46755543c90d03.
// Audit: docs/audits/2026-10-05-openbfme2 under the analysis-materials repository.
class AptNativeFunction;
class AptDate;
class AptCIH;
class AptString;
class AptArray;
class AptFrameStack;
class EAStringC;
class AptValue;
struct AptInitParmsT;
struct _AptScriptFunctionState;
struct AptConstantPool { int nItems; AptValue **apItems; };
enum AptVirtualFunctionTable_Indices { AptVFT_ScriptFunctionByteCodeBlock = 45 };

struct AptNativeHash
{
    AptNativeHash(int);
    ~AptNativeHash();
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
    AptNativeFunction *c_nativefunction() const;
    AptDate *c_date() const;
    AptCIH *c_cih(bool = false) const;
    bool isArray() const;
    int toInteger() const;
    void toString(EAStringC &) const;
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
    AptValue(AptVirtualFunctionTable_Indices);
    virtual ~AptValue();
    unsigned int mnValueData;
};
class AptValueGC : public AptValue
{
public:
    virtual bool IsGarbageCollected() const;
protected:
    AptValueGC(AptVirtualFunctionTable_Indices);
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
