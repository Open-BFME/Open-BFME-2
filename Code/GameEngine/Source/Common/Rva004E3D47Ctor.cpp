// cl: /MD
// ??0Rva004E3D47@@QAE@XZ @ 0x004E3D35 (18B). Derived ctor: calls base
// ??0Rva004E3CD0@@QAE@XZ row 0x004E3C8F then stores vtable 0x0086208C.
// Chain lane: base just landed. No callers. Neighbours 0x004E3D2A/0x004E3D47
// dtors in Rva004E3CD0Derived.cpp share /O1 /MD.
class Rva004E3CD0
{
public:
    Rva004E3CD0();
    virtual ~Rva004E3CD0();
};

class Rva004E3D47 : public Rva004E3CD0
{
public:
    Rva004E3D47();
    virtual ~Rva004E3D47();
};

Rva004E3D47::Rva004E3D47()
{
}
