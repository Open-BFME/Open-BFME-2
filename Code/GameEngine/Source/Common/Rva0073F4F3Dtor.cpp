// cl: /MD /EHsc
// ??1Rva0073F4F3@@QAE@XZ @0x0073F4F3 105B.
// Dtor with EH states destroying +0x28/+0x20 Rva0040EDB then +0x1c cleanup
// then +0x14/+0x0c Rva0040EDB then +0x08 cleanup. Evidence: chain lane packet
// calls 0x0073F368 twice plus rowed 0x00040EDB four times; callers unclaimed.
class Rva0040EDB {
public:
    virtual ~Rva0040EDB();
    void *m_handle;
};
struct Rva0073F061 {
    void *m_head;
    void rva0073F061();
    void rva0073F368();
    ~Rva0073F061() { rva0073F368(); }
};
class Rva0073F4F3 {
public:
    ~Rva0073F4F3();
    char m_pad00[8];
    Rva0073F061 m_08;
    Rva0040EDB m_0c;
    Rva0040EDB m_14;
    Rva0073F061 m_1c;
    Rva0040EDB m_20;
    Rva0040EDB m_28;
};
Rva0073F4F3::~Rva0073F4F3()
{
}
