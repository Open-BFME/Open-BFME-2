// cl: /O2 /DNDEBUG /MD /EHsc
// ??1Rva006ED2A0@@UAE@XZ, retail 0x006ED2A0, 228 bytes.
// Derived dtor with vtable 0x008ECB9C over base vtable 0x008EC9CC (sibling
// Rva006F8460 pattern): frees +0x68 EAStringC (0x20), +0x20 via g_00E17774
// unless null/sentinel 0x009DC2E0, +0x0c (0x40 if +0x74 bit0), members
// +0x1c/+0x18, base member +0x10 via 0x0070A840 plus 0x14 free. Evidence:
// chain lane via freeBlock 0x006DB270; caller 0x006EFB90; sibling base
// Rva006F8460Dtor shares base vtable/member pattern; same /O1 Apt pool family.
class EAStringC
{
public:
    ~EAStringC();
private:
    void *m_pData;
};
class Rva0070A840
{
public:
    ~Rva0070A840();
};
class Rva006DB270
{
public:
    void freeBlock(void *p, int size);
};
extern Rva006DB270 *g_pChainBlockAllocator;
extern char g_00DDC2E0;
// g_00DDC2E0: matched references place it at VA 0xddc2e0 (retail .data initial value -1).
char g_00DDC2E0 = -1;
extern void (__cdecl *g_00E17774)(void *p, int v);
class Rva006ED2A0Base
{
public:
    virtual ~Rva006ED2A0Base();
protected:
    char m_pad04[8];
    void *m_0C;
    Rva0070A840 *m_10;
};
// ??1Rva006ED2A0Base@@UAE@XZ present-unmatched
inline Rva006ED2A0Base::~Rva006ED2A0Base()
{
    Rva0070A840 *block = m_10;
    if (block) {
        block->Rva0070A840::~Rva0070A840();
        g_pChainBlockAllocator->freeBlock(block, 0x14);
    }
}
class Rva006ED2A0 : public Rva006ED2A0Base
{
public:
    virtual ~Rva006ED2A0();
    static void operator delete(void *p, unsigned int size)
    {
        g_pChainBlockAllocator->freeBlock(p, size);
    }
private:
    char _pad14[4];
    EAStringC m_18;
    EAStringC m_1C;
    void *m_20;
    int m_24;
    char _pad28[56];
    int m_60;
    int m_64;
    EAStringC *m_68;
    char _pad6C[8];
    unsigned char m_74;
    char _pad75[3];
};
Rva006ED2A0::~Rva006ED2A0()
{
    EAStringC *eAStringC = m_68;
    m_24 = 0;
    m_64 = 0;
    m_60 = 0;
    if (eAStringC) {
        eAStringC->~EAStringC();
        g_pChainBlockAllocator->freeBlock(eAStringC, 0x20);
        m_68 = 0;
    }
    void *p20 = m_20;
    if (p20 && p20 != (void *)&g_00DDC2E0) {
        g_00E17774(p20, 2);
        m_20 = 0;
    }
    if (m_74 & 1) {
        void *p0c = m_0C;
        if (p0c)
            g_pChainBlockAllocator->freeBlock(p0c, 0x40);
    }
}
// ?deleteRva006ED2A0@@YAXPAVRva006ED2A0@@@Z present-unmatched
void deleteRva006ED2A0(Rva006ED2A0 *p) { delete p; }
