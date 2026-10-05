// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// ??0Rva005D7F5D@@QAE@XZ @0x005D7F5D 73B unlock lane ctor via base plus memset.
// Evidence: calls rowed base Rva005EE30C 0x005EE2E6 then memset via rowed ji_006291AE then rowed rva005D7E98 0x005D7E98; vtable 0x00875ED0 DIR32; same shape as WaypointStarts neighbours.
void *ji_006291ae(void *dst, int val, unsigned int size);

class Rva0058AD7A
{
public:
    Rva0058AD7A(int x);
    virtual ~Rva0058AD7A();
private:
    int m_04;
    int m_08;
    int m_0C;
    float m_10;
    float m_14;
    unsigned char m_18;
    unsigned char m_19;
    unsigned char m_1A;
};

class Rva005EE30C : public Rva0058AD7A
{
public:
    Rva005EE30C();
    virtual ~Rva005EE30C();
private:
    float m_1C;
    float m_20;
    float m_24;
};

class Rva005D7E98
{
public:
    void rva005D7E98();
};

class Rva005D7F5D : public Rva005EE30C
{
public:
    Rva005D7F5D();
private:
    int m_28;
    unsigned int m_starts[8];
};

Rva005D7F5D::Rva005D7F5D()
    : Rva005EE30C()
{
    m_28 = 0;
    ji_006291ae(m_starts, 0, 0x20);
    ((Rva005D7E98 *)this)->rva005D7E98();
}
