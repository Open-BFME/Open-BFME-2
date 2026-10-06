// Target evidence: Ghidra bounds 0x00513988-0x005139AF (40B); the preceding
// byte is RET and the next Ghidra function starts at 0x005139B0. Retail calls
// 0x005B1A6C with this+0x27C, then invokes virtual slot 1 on five pointers at
// this+0x418. The containing class identity and member meanings are unknown.
class Rva005B1A6C {
public:
    void rva005B1A6C();
};

class Rva00513988Part {
public:
    virtual void slot0();
    virtual void slot1();
};

class Rva00513988 {
public:
    void rva00513988();
};

void Rva00513988::rva00513988()
{
    ((Rva005B1A6C *)((char *)this + 0x27C))->rva005B1A6C();

    Rva00513988Part **part = (Rva00513988Part **)((char *)this + 0x418);
    for (int count = 5; count > 0; --count) {
        (*part)->slot1();
        ++part;
    }
}
