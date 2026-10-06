// cl: /DNDEBUG /MD /EHsc
// ??0Rva006ED2A0@@QAE@XZ, retail 0x006ED1E0, 177 bytes.
// Default ctor for Rva006ED2A0 (vtable 0x008ECB9C, same as dtor 0x006ED2A0):
// base sets +0x14/+0x04/+0x0c/+0x10, clears +0x18/+0x1c, inits +0x28/+0x2c/
// +0x30/+0x34/+0x38/+0x20/+0x40/+0x44/+0x48/+0x70/+0x68 and +0x74 bit ops via
// g_00E1771C. Evidence: same vtable and offsets as dtor TU; callees rowed
// clear 0x006D2F90; caller 0x006F87A0; neighbours share /O2 Apt pool flags.
class EAStringC
{
public:
    EAStringC();
    ~EAStringC();
    EAStringC &clear();
private:
    void *m_pData;
};
inline EAStringC::EAStringC()
{
    clear();
}
class Rva0070A840
{
public:
    ~Rva0070A840();
};
extern unsigned char g_00E1771C;
class Rva006ED2A0Base
{
public:
    Rva006ED2A0Base();
    virtual ~Rva006ED2A0Base();
protected:
    int m_04;
    char m_pad08[4];
    void *m_0C;
    Rva0070A840 *m_10;
    unsigned char m_14;
    char m_pad15[3];
};
inline Rva006ED2A0Base::Rva006ED2A0Base()
{
    m_14 = 0;
    m_04 = -1;
    m_0C = 0;
    m_10 = 0;
}
class Rva006ED2A0 : public Rva006ED2A0Base
{
public:
    Rva006ED2A0();
    virtual ~Rva006ED2A0();
private:
    EAStringC m_18;
    EAStringC m_1C;
    void *m_20;
    int m_24;
    int m_28;
    int m_2C;
    int m_30;
    int m_34;
    int m_38;
    char m_pad3C[4];
    int m_40;
    int m_44;
    int m_48;
    char m_pad4C[20];
    int m_60;
    int m_64;
    EAStringC *m_68;
    char m_pad6C[4];
    int m_70;
    int m_74;
};
Rva006ED2A0::Rva006ED2A0()
    : Rva006ED2A0Base(), m_18(), m_1C()
{
    m_28 = 1;
    m_2C = 1;
    int v74 = m_74;
    v74 &= ~7;
    m_74 = v74;
    m_20 = 0;
    m_40 = 0;
    m_44 = 0;
    m_48 = 0;
    m_70 = 0;
    m_30 = -1;
    m_34 = (int)0xFF000000;
    m_38 = 3;
    unsigned int b = g_00E1771C;
    b <<= 3;
    unsigned int mixed = b ^ (unsigned int)v74;
    mixed &= 8;
    mixed ^= (unsigned int)v74;
    m_74 = (int)mixed;
    m_68 = 0;
}
