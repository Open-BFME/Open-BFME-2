// cl: /O1 /MD /EHsc
// Native 0004EFE9..0004F037, RET0. The rowed deleting destructor at
// 0004F7D8 establishes the address-derived owner. Target bytes set its vptr,
// invoke virtual slot 3 on the +20 object, release that reference, and call
// the base destructor at 004E84A4. The original class identity is unknown.
class Rva00539926Base
{
public:
    virtual ~Rva00539926Base();
};

class RadarEventRef
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    void release();
};

struct Rva0004EFE9Reference
{
    RadarEventRef *value;
    ~Rva0004EFE9Reference()
    {
        if (value)
            value->release();
    }
};

class Rva004EFE9 : public Rva00539926Base
{
public:
    virtual ~Rva004EFE9();
private:
    char m_unmodelled04[0x1c];
    Rva0004EFE9Reference m_reference; // +20
};

Rva004EFE9::~Rva004EFE9()
{
    void (RadarEventRef::*callback)() = &RadarEventRef::slot3;
    (m_reference.value->*callback)();
}
