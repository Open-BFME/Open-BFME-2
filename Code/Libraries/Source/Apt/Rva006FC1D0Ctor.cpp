// cl: /DNDEBUG /MD /EHsc
// ??0Rva006FC1D0@@QAE@XZ @0x006FC1D0 102B. Apt-derived zero-arg ctor sibling of Rva006D6500.
// Evidence: calls rowed ??0BfmeAptValue006DCD20@@QAE@H@Z (0x006DCCC0) with 0x23 and rowed
// ??0AptNativeHash@@QAE@H@Z (0x0070A740) with 8 for member at +8; stores base vtable 0x008EA228
// via inlined Rva006D6360 base then own vtable 0x008EC7A8; clears bits at +0x1C with 0xFFFFFCFF
// mask and zeroes +0x20; single caller at 0x00707155 in 0x00706A40; donor TU
// Code/Libraries/Source/Apt/Rva006D6360Ctor.cpp for layout and flags.
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
    Rva006D6360(int type, int size) : BfmeAptValue006DCD20(type), m_hash(size)
    {
    }
    virtual ~Rva006D6360();
};
class Rva006FC1D0 : public Rva006D6360
{
    unsigned int m_bits;
    int m_20;
public:
    Rva006FC1D0();
};
Rva006FC1D0::Rva006FC1D0() : Rva006D6360(0x23, 8)
{
    *(unsigned char *)&m_bits = 0;
    m_bits &= 0xFFFFFCFF;
    m_20 = 0;
}
class EAStringC
{
public:
    struct StringDataC;
    StringDataC *m_pData;
public:
    EAStringC(const char *text);
    ~EAStringC();
};
struct Rva006FC240BitsHack
{
    unsigned int v;
    Rva006FC240BitsHack()
    {
        *(unsigned char *)&v = 0;
        v &= 0xFFFFFCFF;
    }
};
class Rva006FC240 : public Rva006D6360, public Rva006FC240BitsHack
{
    EAStringC m_s20;
    EAStringC m_s24;
public:
    Rva006FC240();
};
Rva006FC240::Rva006FC240() : Rva006D6360(0x29, 8), Rva006FC240BitsHack(), m_s20("Error"), m_s24("Error")
{
}
