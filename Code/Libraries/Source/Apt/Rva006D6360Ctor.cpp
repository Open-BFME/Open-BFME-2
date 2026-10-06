// cl: /DNDEBUG /MD /EHsc
// ??0Rva006D6360@@QAE@HH@Z @0x006D6360 86B. Base Apt object ctor taking (type hashSize).
// Evidence: stores vtable 0x008EA228; calls rowed ??0BfmeAptValue006DCD20@@QAE@H@Z (0x006DCCC0)
// and rowed ??0AptNativeHash@@QAE@H@Z (0x0070A740); member AptNativeHash at +8 (size 0x14 total 0x1C);
// 7 callers forward to it (0x006D6410 0x006DA4D0 0x006F1310 0x006FBB10 0x00709870 0x00709A10 0x00711380);
// EH handler 0x007A8838 with state 0 after base; derived 0x006D6410 stores 0x008EA264 then calls this.
class BfmeAptValue006DCD20
{
    virtual void vtableSlot0();
    unsigned int m_flags;
    void setTypeAt006DBBC0(int type);
public:
    BfmeAptValue006DCD20(int type);
    virtual ~BfmeAptValue006DCD20();
};
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
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
class Rva006D6470Owner : public Rva006D6360
{
    unsigned int m_bits;
public:
    Rva006D6470Owner(int a0, int a1);
    virtual ~Rva006D6470Owner();
};
class Rva006D6500 : public Rva006D6360
{
    unsigned int m_bits;
    int m_arg;
public:
    Rva006D6500(int a0);
    virtual ~Rva006D6500();
};
Rva006D6360::Rva006D6360(int type, int size) : BfmeAptValue006DCD20(type), m_hash(size)
{
}
Rva006D6470Owner::Rva006D6470Owner(int a0, int a1) : Rva006D6360(a0, a1)
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
