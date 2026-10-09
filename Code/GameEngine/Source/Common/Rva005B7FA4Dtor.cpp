// cl: /DNDEBUG /MD /EHs
// ??1Rva005B7FA4@@UAE@XZ @0x005B7FA4 86B
// MI dtor with first base Rva0056DC6B at +0 size 0x60 inline emitting 0x0086DB78 then base Rva005248D0 plus second base AptStats at +0x60 plus singleton clear.
// Evidence: retail sets [esi] 0x00873964 and [esi+0x60] 0x00873950 then cmp g_00E06478 with esi then calls 0x005DD1EA then sets [esi] 0x0086DB78 then calls 0x005248D0; middle Rva0056DC6B precedent Rva005B922F and Rva0056DC6B row; caller 0x005B8035 deleting dtor; bases rowed.
class Rva005248D0
{
public:
    virtual ~Rva005248D0();
private:
    char m_pad[0x60 - 4];
};
class Rva0056DC6B : public Rva005248D0
{
public:
    virtual ~Rva0056DC6B();
};
inline Rva0056DC6B::~Rva0056DC6B()
{
}
class AptStats
{
public:
    virtual ~AptStats();
private:
    // Consuming ABI view: native AptStats is44B and its virtual dtor is rowed.
    char m_pad[0x2C - 4];
};
class Rva005B7FA4 : public Rva0056DC6B, public AptStats
{
public:
    virtual ~Rva005B7FA4();
};
extern Rva005B7FA4 *g_00E06478;
Rva005B7FA4::~Rva005B7FA4()
{
    if (g_00E06478 == this)
        g_00E06478 = 0;
}
