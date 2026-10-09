// cl: /O2 /G6 /arch:SSE /MD /EHsc
// _constructBuiltInObjects, retail 0x006DE8E0..0x006DF468 (2952 bytes), ret.
// WB twin 0x0176D380 in Code\Libraries\Source\Apt\AptValue.cpp names the
// function in its AddRef debug arguments ("_constructBuiltInObjects", line
// 0x2C9). Retail evidence: eleven native constructor functions (0x24-byte
// pool objects, ctor 0x006D6500 with callback 0x006F5100) are set on the
// global object under string ids 0x64 0x21 0x99 0x2C 0x31 0xA3 0x5E 0xAF 0x5A
// 0x32 0x9D; each is then looked up again and given a new 0x20-byte
// AptPrototype (ctor 0x006DE1A0) through the inlined AptNativeHash
// SetPrototype/Set__Proto__ pair (+0xC/+0x8), with the GC root count bits
// 18..24 of +4 set to one. The first prototype is gpObjectPrototype (also
// copied to 0x00E180B0) and the seventh is kept at 0x00E1807C. A last native
// function (callback 0x006DDCE0) is kept at 0x00E18064 and AddRef'd. The
// release vector at 0x00E17710 is drained before and after.
class EAStringC;
class AptValue;

struct AptNativeHash;

class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    unsigned int mnLowBits : 18;
    unsigned int mnGCRootCount : 7;
    unsigned int mnType : 7;
};

struct AptNativeHash
{
    int mnTotalSize;
    void *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    // Same bodies as the out-of-line copies at 0x006DB380/0x006DB350;
    // inlined here as in retail.
    void SetPrototype(AptValue *const value)
    {
        if (value) value->AddRef();
        if (mpPrototype) mpPrototype->Release();
        mpPrototype = value;
    }
    void Set__Proto__(AptValue *const value)
    {
        if (value) value->AddRef();
        if (mp__proto__) mp__proto__->Release();
        mp__proto__ = value;
    }
};

class Rva006D2A60
{
public:
    void *allocBlock(int);
    void freeBlock(void *, int);
};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;

typedef AptValue *(__cdecl *AptNativeCallback)(AptValue *, int);

class AptNativeFunction : public AptValue
{
public:
    AptNativeFunction(AptNativeCallback);
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p, n); }
private:
    char mBody[0x24 - 8];
};

class AptPrototype : public AptValue
{
public:
    AptPrototype();
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p, n); }
private:
    char mBody[0x20 - 8];
};

class AptValueVector
{
public:
    void ReleaseValues();
};
extern AptValueVector *g_releaseVectorAtE17710;

class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Result
{
public:
    void rva006FBB90(Rva8D0D80String *name, Rva8D0D80Value *value); // object Set
};
class BfmeN1034;
class Rva0070A5C0
{
public:
    BfmeN1034 *rva0070A5C0(int name); // object Lookup
};
EAStringC *Rva0070B4F0GetString(int id);

extern AptValue *gpGlobalGlobalObject;
extern AptPrototype *gpObjectPrototype;
extern AptValue *g_00E180B0;
extern AptPrototype *g_00E1807C;
extern int g_00E18064;

int Rva006F5100Get();
AptValue *Rva006DDCE0(AptValue *, int);

#define BUILTIN_FUNCTION(id)                                                   \
    ((Rva8D0D80Result *)gpGlobalGlobalObject)                                  \
        ->rva006FBB90((Rva8D0D80String *)Rva0070B4F0GetString(id),            \
                      (Rva8D0D80Value *)new AptNativeFunction(                 \
                          (AptNativeCallback)Rva006F5100Get))

#define LOOKUP(id)                                                             \
    ((AptValue *)((Rva0070A5C0 *)gpGlobalGlobalObject)                         \
         ->rva0070A5C0((int)Rva0070B4F0GetString(id)))

#define BUILTIN_PROTOTYPE(id)                                                  \
    {                                                                          \
        AptValue *pFunc = LOOKUP(id);                                          \
        AptPrototype *pProto = new AptPrototype();                             \
        pFunc->GetNativeHashVirtual()->SetPrototype(pProto);                   \
        pFunc->GetNativeHashVirtual()->Set__Proto__(gpObjectPrototype);        \
        pFunc->mnGCRootCount = 1;                                              \
        pProto->mnGCRootCount = 1;                                             \
    }

void _constructBuiltInObjects()
{
    g_releaseVectorAtE17710->ReleaseValues();

    BUILTIN_FUNCTION(0x64);
    BUILTIN_FUNCTION(0x21);
    BUILTIN_FUNCTION(0x99);
    BUILTIN_FUNCTION(0x2C);
    BUILTIN_FUNCTION(0x31);
    BUILTIN_FUNCTION(0xA3);
    BUILTIN_FUNCTION(0x5E);
    BUILTIN_FUNCTION(0xAF);
    BUILTIN_FUNCTION(0x5A);
    BUILTIN_FUNCTION(0x32);
    BUILTIN_FUNCTION(0x9D);

    {
        AptValue *pFunc = LOOKUP(0x64);
        gpObjectPrototype = new AptPrototype();
        pFunc->GetNativeHashVirtual()->SetPrototype(gpObjectPrototype);
        g_00E180B0 = gpObjectPrototype;
        pFunc->mnGCRootCount = 1;
        gpObjectPrototype->mnGCRootCount = 1;
    }
    BUILTIN_PROTOTYPE(0x21)
    BUILTIN_PROTOTYPE(0x99)
    BUILTIN_PROTOTYPE(0x2C)
    BUILTIN_PROTOTYPE(0x31)
    BUILTIN_PROTOTYPE(0xA3)
    {
        AptValue *pFunc = LOOKUP(0x5E);
        AptPrototype *pProto = new AptPrototype();
        g_00E1807C = pProto;
        pFunc->mnGCRootCount = 1;
        pProto->mnGCRootCount = 1;
        pFunc->GetNativeHashVirtual()->SetPrototype(pProto);
        pFunc->GetNativeHashVirtual()->Set__Proto__(gpObjectPrototype);
    }
    BUILTIN_PROTOTYPE(0xAF)
    BUILTIN_PROTOTYPE(0x5A)
    BUILTIN_PROTOTYPE(0x32)
    BUILTIN_PROTOTYPE(0x9D)

    g_00E18064 = (int)new AptNativeFunction(Rva006DDCE0);
    ((AptValue *)g_00E18064)->mnGCRootCount = 1;
    ((AptValue *)g_00E18064)->AddRef();

    g_releaseVectorAtE17710->ReleaseValues();
}
