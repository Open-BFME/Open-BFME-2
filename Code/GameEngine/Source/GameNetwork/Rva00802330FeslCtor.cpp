// cl: /GX-
// Provisional FESL view: retail initializes +8 before constructing the 12-byte
// member at +0x18. This partial constructor view retains that ordering and
// explicitly tears down the existing base view after clearing the member.
// The complete inheritance layout and original class names remain unproven.
struct V2ZeroInt
{
    __forceinline V2ZeroInt() : m_value(0) {}
    int m_value;
};

class Rva00800630Owner
{
public:
    Rva00800630Owner();
    void *m_block;
    int m_field4;
    int m_field8;
};

class Rva008003C0Owner
{
public:
    void clear();
    void *m_block;
    int m_field4;
    int m_field8;
};

class Rva00802380Base
{
public:
    virtual ~Rva00802380Base() {}
    int m_field4;
    int m_field8;
};

class Rva00802380Owner
{
public:
    __declspec(noinline) Rva00802380Owner();
    virtual ~Rva00802380Owner()
    {
        m_field4 = 0;
        m_field24 = 0;
        m_field28 = 0;
        reinterpret_cast<Rva008003C0Owner *>(&m_owner)->clear();
        reinterpret_cast<Rva00802380Base *>(this)->Rva00802380Base::~Rva00802380Base();
    }

    int m_field4;
    V2ZeroInt m_field8;
    char m_pad00C[0x0C];
    Rva00800630Owner m_owner;
    int m_field24;
    int m_field28;
};

Rva00802380Owner::Rva00802380Owner()
{
    m_field4 = 0;
    m_field24 = 0;
    m_field28 = 0;
}
