// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva00345F21@@UAE@XZ, retail 0x00345F21, 79 bytes.
// Derived dtor restoring vtable 0x00813638, deleting the +0x68 pointer via
// slot-0 scalarDeletingDestructor(0) plus operator delete (vf0(0)+free shape
// with null->0 path, precedent DX8MeshRendererClass_Invalidate_Thunk) then
// nulling it (state 0), then calling the rowed base ??1Rva0033FF2B at
// 0x0033FF2B (landed). Caller is 0x0034A186.

void __cdecl operator delete(void *ptr);

class Rva00345F21Member
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

class Rva00345F21 : public Rva0033FF2B
{
public:
    virtual ~Rva00345F21();

private:
    char m_pad44[0x68 - 0x44];
    Rva00345F21Member *m_ptr68;
};

Rva00345F21::~Rva00345F21()
{
    ::operator delete(m_ptr68 != 0 ? m_ptr68->scalarDeletingDestructor(0) : 0);
    m_ptr68 = 0;
}
