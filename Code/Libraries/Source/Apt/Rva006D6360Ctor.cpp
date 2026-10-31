// cl: /DNDEBUG /MD /EHsc
// ??0Rva006D6360@@QAE@HH@Z @0x006D6360 86B. Base Apt object ctor taking (type hashSize).
// Evidence: stores vtable 0x008EA228; calls rowed ??0BfmeAptValue006DCD20@@QAE@H@Z (0x006DCCC0)
// and rowed ??0AptNativeHash@@QAE@H@Z (0x0070A740); member AptNativeHash at +8 (size 0x14 total 0x1C);
// 7 callers forward to it (0x006D6410 0x006DA4D0 0x006F1310 0x006FBB10 0x00709870 0x00709A10 0x00711380);
// EH handler 0x007A8838 with state 0 after base; derived 0x006D6410 stores 0x008EA264 then calls this.
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
// Retail vtable 0x008EA228 starts with the rowed AptValue::AddRef (0x006DCAC0) and Release.
class BfmeAptValue006DCD20 : public AptValue
{
    unsigned int m_flags;
    void setTypeAt006DBBC0(int type);
public:
    BfmeAptValue006DCD20(int type);
    virtual ~BfmeAptValue006DCD20();
};
class AptNativeHash
{
    struct Entry { void *key; AptValue *value; };
    int mnTotalSize;
    Entry *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
public:
    AptNativeHash(int size);
    ~AptNativeHash();
};
class Rva006D6360 : public BfmeAptValue006DCD20
{
    AptNativeHash m_hash;
public:
    Rva006D6360(int type, int size);
    virtual ~Rva006D6360();
};
class Rva006D2A60 { public: void freeBlock(void *, int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6470Owner : public Rva006D6360
{
    unsigned int m_bits;
public:
    Rva006D6470Owner(int type, int hashSize);
    virtual ~Rva006D6470Owner();
public:
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocatorF4->freeBlock(p, size); }
};
class Rva006D6500 : public Rva006D6360
{
    unsigned int m_bits;
    int m_arg;
public:
    Rva006D6500(int a0);
    // Compiler-generated destruction (members, then the rowed base dtor), the
    // body retail's vtable slot 0 reaches.
    virtual ~Rva006D6500() {}
};
inline Rva006D6360::Rva006D6360(int type, int size) : BfmeAptValue006DCD20(type), m_hash(size)
{
}
inline Rva006D6470Owner::Rva006D6470Owner(int type, int hashSize) : Rva006D6360(type, hashSize)
{
    *(unsigned char *)&m_bits = 0;
    m_bits &= 0xFFFFFCFF;
}
Rva006D6500::Rva006D6500(int a0) : Rva006D6360(9, 8)
{
    *(unsigned char *)&m_bits = 0;
    m_bits &= 0xFFFFFCFF;
    m_arg = a0;
}

// Rva006ECFC0Siblings, Rva006EC730GetBounds, Rva006FC1D0Ctor and others define
// these two constructors in-class, emitting select-any copies of the same
// bodies; defining them inline here too keeps one body under each name. The
// anchor keeps this unit's copies emitted.
// ?bfmeAnchorRva006D6470Owner absent-from-retail
void bfmeAnchorRva006D6470Owner(Rva006D6470Owner *p)
{
    p->Rva006D6470Owner::Rva006D6470Owner(0, 0);
}
