// ??1Rva005B7FA4@@UAE@XZ
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva005B7FA4@@UAE@XZ @0x005B7FA4 86B
// MI dtor with second base Rva005DD1EA at +0x60 then base Rva005248D0 at +0 plus singleton clear.
// Evidence: retail sets [esi] 0x00873964 and [esi+0x60] 0x00873950 then cmp g_00E06478 with esi then calls 0x005DD1EA then sets [esi] 0x0086DB78 then calls 0x005248D0; caller 0x005B8035 is ??_G deleting dtor; bases rowed.
class Rva005248D0
{
public:
    virtual ~Rva005248D0();
private:
    char m_pad[0x60 - 4];
};
class Rva005DD1EA
{
public:
    virtual ~Rva005DD1EA();
private:
    char m_pad[0x24 - 4];
};
class Rva005B7FA4 : public Rva005248D0, public Rva005DD1EA
{
public:
    virtual ~Rva005B7FA4();
};
extern Rva005B7FA4 *g_00E06478;
// ??1Rva005B7FA4@@UAE@XZ present-unmatched
Rva005B7FA4::~Rva005B7FA4()
{
    if (g_00E06478 == this)
        g_00E06478 = 0;
}
