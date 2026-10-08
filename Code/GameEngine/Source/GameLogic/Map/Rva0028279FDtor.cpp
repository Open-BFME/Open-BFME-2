// cl: /MD /EHs
// Native 0x0028279F..0x002827F3: clear, notify slot-zero listeners with
// this, destroy the record vector at +0x14, then release the listener buffer.
// Caller 0x002833E7 owns this object's lifetime. The separate clear helper
// at 0x002827F3 has pointer vectors at +4/+0x10, unlike this object's layout;
// its address-derived class name is therefore not this destructor's identity.
extern "C" void __cdecl free(void *block);

struct TargetRef00217D4C;
struct Rva0027EA49
{
    ~Rva0027EA49();
    int m_00;
    TargetRef00217D4C *m_04;
};

namespace _STL
{
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
    ~vector();
    T *m_start;
    T *m_finish;
    T *m_end_of_storage;
};
}

class Rva00281A15Listener
{
public:
    virtual void notify(void *);
};

class Rva00281A15List
{
public:
    void forEach(void (Rva00281A15Listener::*notify)(void *), void *arg);
    ~Rva00281A15List()
    {
        if (m_begin)
            free(m_begin);
    }
    Rva00281A15Listener **m_begin;
    Rva00281A15Listener **m_end;
    Rva00281A15Listener **m_capacity;
    unsigned int m_index;
};

class Rva0028279F : public Rva00281A15List
{
public:
    ~Rva0028279F();
    void rva00282135();
private:
    unsigned int m_word10;
    _STL::vector<Rva0027EA49, _STL::allocator<Rva0027EA49> > m_records14;
};

Rva0028279F::~Rva0028279F()
{
    rva00282135();
    forEach(&Rva00281A15Listener::notify, this);
}
