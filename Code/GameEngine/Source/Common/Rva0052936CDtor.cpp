// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Holder38 cleanup is independently rowed at 0x00528CE6.
// The complete Palantir owner is in PalantirCommandInterface.cpp.
class Rva00528B98
{
public:
    void rva00528B98();
private:
    void *m_owner;
    bool m_flag04;
    char m_pad[3];
};
struct Holder38
{
    Rva00528B98 m_inner;
    ~Holder38();
};

Holder38::~Holder38() { m_inner.rva00528B98(); }
