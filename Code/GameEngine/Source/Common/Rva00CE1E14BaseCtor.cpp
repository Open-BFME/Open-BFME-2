// cl: /EHs-c- /Ob2
// Base of the independently matched Rva00CE12FCMutex. Retail ctor65D170
// installs vtable VA CE1E14 and returns this; dtor65D180 restores that table.
// Kept separate so the derived constructor retains its retail external call.
class Rva00CE1E14Base {
public:
    Rva00CE1E14Base();
    virtual ~Rva00CE1E14Base();
    virtual void sleep(unsigned long) = 0;
    virtual unsigned long ticks() = 0;
    virtual void wait() = 0;
    virtual void release() = 0;
};
Rva00CE1E14Base::Rva00CE1E14Base() {}

// ??1Rva00CE1E14Base@@UAE@XZ @0x0065D180 7B: the empty dtor, restoring the vtable (the
// deleting dtor still expands it inline).
Rva00CE1E14Base::~Rva00CE1E14Base()
{
}
