// cl: /DNDEBUG /MD /EHsc
// ??1Rva006D6D20@@UAE@XZ @0x006D6D20 82B. Dtor of Apt string-value class (vtable 0x008EA358).
// Evidence: stores vtable 0x008EA358; destroys EAStringC at +8 via rowed ??1EAStringC@@QAE@XZ (0x006D3010)
// then base via rowed ??1Rva006DE350@@UAE@XZ (0x006DE350); ctor twin 0x006D6CC0 same vtable same EH handler
// 0x007A8838 constructs base type 1 plus clear plus +0xC=0; deleting dtor 0x006D7320 frees 0x10; size 0x10.
class EAStringC
{
public:
    ~EAStringC();
};
struct Rva006DE350
{
    virtual ~Rva006DE350();
};
struct Rva006D6D20 : public Rva006DE350
{
    char m_pad[4];
    EAStringC m_str;
    int m_0C;
    virtual ~Rva006D6D20();
};
Rva006D6D20::~Rva006D6D20()
{
}
