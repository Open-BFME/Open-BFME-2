// cl: /EHsc /MD
// ??0Rva000E6350@@QAE@XZ, retail 0x000E6350, 55 bytes.
// Ctor registering "Vegetation" via rowed Rva00153565Register; vtable at +0.
// Evidence: disassembly stores 0x007CEA04 then calls Register("Vegetation", this);
// empty base arms EH state 0. Precedent Rva0018BEC7Ctor.cpp.
void __cdecl Rva00153565Register(const char *name, void *obj);

class Rva000E6350_EmptyBase {
public:
    Rva000E6350_EmptyBase() {}
    ~Rva000E6350_EmptyBase();
};

class Rva000E6350 : public Rva000E6350_EmptyBase {
public:
    virtual ~Rva000E6350();
    Rva000E6350();
};

Rva000E6350::Rva000E6350()
{
    Rva00153565Register("Vegetation", this);
}
