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
class AptFrameStack;
class EAStringC;
class AptValue;
struct AptInitParmsT;
struct _AptScriptFunctionState;
struct AptConstantPool { int nItems; AptValue **apItems; };
enum AptVirtualFunctionTable_Indices { AptVFT_ScriptFunctionByteCodeBlock = 45 };

struct AptNativeHash
{
    int mnTotalSize;
    void *mpData; // Hash-item storage; its element layout is not needed here.
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
};

class AptValue
{
public:
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
    virtual void setHasClass(int);
    virtual int getHasClass() const;
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
protected:
    virtual ~AptObject();
    // Native constructor clears the low byte and bits8..9 at+1C. The donor
    // calls these mnImplementedObjects, mbHasClass and mbIsInMainInst.
    unsigned int m_objectFlags;
};

class AptScriptFunctionBase : public AptObject
{
public:
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

struct AptAction_DefineFunction2
{
    const char *szName;
    int nParams;
    short nRegisterCount;
    short nFlags;
    const void *aszParams; // Parameter-record pointer; no record access here.
    int nCodeSize;
    AptConstantPool constantPool;
};
class AptScriptFunction2 : public AptScriptFunctionBase
{
public:
    virtual void CleanupAfterExecution(_AptScriptFunctionState *);
    virtual AptConstantPool GetConstantPool();
protected:
    const AptAction_DefineFunction2 *mpFunction;
};
typedef char AptScriptFunctionBaseSize[sizeof(AptScriptFunctionBase) == 0x30 ? 1 : -1];
typedef char AptScriptFunctionByteCodeBlockSize[sizeof(AptScriptFunctionByteCodeBlock) == 0x44 ? 1 : -1];
typedef char AptScriptFunction2Size[sizeof(AptScriptFunction2) == 0x34 ? 1 : -1];
