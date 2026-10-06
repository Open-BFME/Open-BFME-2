// cl: /EHsc /MD
// ??1Rva0018BEC7@@UAE@XZ, retail 0x0018BE87, 64 bytes.
// Ctor registers "WW3D" (rowed 0x0018BEC7), dtor erases "WW3D"; vtable at +0
// plus member vptr at +4, both reset to the base vtable in the dtor. Evidence:
// dtor stores the derived vtable then Erase then both to the base vtable;
// callers 0x0017414B/0x0018BF0C. A trailing _ReadWriteBarrier (no code) holds
// the EH epilogue scheduling retail uses.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void __cdecl Rva001532E1Erase(const char *name);

class Rva0018BEC7_Base {
public:
    virtual ~Rva0018BEC7_Base() {}
};

class Rva0018BEC7_Member : public Rva0018BEC7_Base {
public:
    ~Rva0018BEC7_Member() {}
};

class Rva0018BEC7 : public Rva0018BEC7_Base {
public:
    virtual ~Rva0018BEC7();
    Rva0018BEC7();
    Rva0018BEC7_Member m_member;
};

Rva0018BEC7::~Rva0018BEC7()
{
    Rva001532E1Erase("WW3D");
    _ReadWriteBarrier();
}
