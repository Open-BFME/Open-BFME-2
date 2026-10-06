// cl: /DNDEBUG /MD /EHsc
// ??0Rva006D6D20@@QAE@XZ @0x006D6CC0 83B. Default ctor of Apt string-value class (vtable 0x008EA358).
// Evidence: calls rowed ??0BfmeAptValue006DCD20@@QAE@H@Z (0x006DCCC0) with type 1 then stores vtable
// 0x008EA358 then rowed ?clear@EAStringC@@QAEAAV1@XZ (0x006D2F90) on member at +8 then +0xC=0;
// dtor twin 0x006D6D20 same vtable same EH handler 0x007A8838 destroys +8 plus base; size 0x10.
class EAStringC
{
public:
    EAStringC() { clear(); }
    EAStringC(const char *text);
    EAStringC &clear();
    ~EAStringC();
};
class BfmeAptValue006DCD20
{
    unsigned int m_flags;
    void setTypeAt006DBBC0(int type);
public:
    BfmeAptValue006DCD20(int type);
    virtual ~BfmeAptValue006DCD20();
};
struct Rva006D6D20 : public BfmeAptValue006DCD20
{
    EAStringC m_str;
    int m_0C;
    Rva006D6D20();
    Rva006D6D20(const char *s);
    virtual ~Rva006D6D20();
};
Rva006D6D20::Rva006D6D20() : BfmeAptValue006DCD20(1), m_0C(0)
{
}
Rva006D6D20::Rva006D6D20(const char *s) : BfmeAptValue006DCD20(1), m_str(s), m_0C(0)
{
}
