// cl: /MD
// ??0Rva004E3D2A@@QAE@XZ @ 0x004E3D18 (18B). Derived ctor: calls base
// ??0Rva004E3CD0@@QAE@XZ row 0x004E3C8F then stores vtable 0x00862070.
// Chain lane: base just landed. No callers. Neighbours 0x004E3CD0 dtor
// and 0x004E3D2A dtor in Rva004E3CD0Derived.cpp share /O1 /MD.
class Rva004E3CD0
{
public:
    Rva004E3CD0();
    virtual ~Rva004E3CD0();
};

class Rva004E3D2A : public Rva004E3CD0
{
public:
    Rva004E3D2A();
    virtual ~Rva004E3D2A();
};

Rva004E3D2A::Rva004E3D2A()
{
}
