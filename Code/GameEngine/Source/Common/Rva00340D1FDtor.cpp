// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva00340D1F@@UAE@XZ, retail 0x00340D1F, 75 bytes.
// Derived dtor restoring vtable 0x008121E8, deleting the +0x5c pointer via
// slot-0 scalarDeletingDestructor(0) plus operator delete inside an explicit
// if (vf0(0)+free with je-to-or skip, no xor path) then nulling it
// (state 0, pop-before-or), then calling the rowed base ??1Rva0033FF2B at
// 0x0033FF2B. Caller is 0x00345BB6. Sibling of landed 0x00340BDC-shape.

void __cdecl operator delete(void *ptr);

class Rva00340D1FMember
{
public:
    virtual void *scalarDeletingDestructor(unsigned int flags);
};

class Rva0049B47C
{
public:
    virtual ~Rva0049B47C();

private:
    char m_pad04[8];
};

class Rva0033FF2B : public Rva0049B47C
{
public:
    virtual ~Rva0033FF2B();

private:
    char m_pad0C[0x40 - 0x0C];
    unsigned int m_handle40;
};

class Rva00340D1F : public Rva0033FF2B
{
public:
    virtual ~Rva00340D1F();

private:
    char m_pad44[0x5C - 0x44];
    Rva00340D1FMember *m_ptr5C;
};

Rva00340D1F::~Rva00340D1F()
{
    if (m_ptr5C != 0) {
        ::operator delete(m_ptr5C->scalarDeletingDestructor(0));
        m_ptr5C = 0;
    }
}
