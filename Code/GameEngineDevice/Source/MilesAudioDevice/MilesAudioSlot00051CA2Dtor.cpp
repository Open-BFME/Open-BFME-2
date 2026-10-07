// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// Native52751 and5276C vector iterators both use the shared one-byte RET
// atB3FD0 as the destructor of the16B element whose ctor is51CA2.
// This separate provider retains the caller-visible destructor declaration
// and supplies its linker name. The opaque class view agrees with the
// paired24B constructor; original element identity remains unknown.
class Rva00051CA2 {
public:
    __declspec(noinline) Rva00051CA2();
    ~Rva00051CA2();
private:
    float x, y, z;
    bool active;
};
Rva00051CA2::~Rva00051CA2() {}
