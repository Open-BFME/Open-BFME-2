// cl: /O1 /arch:SSE /G7 /EHsc /DNDEBUG /MD
// Native52751..5276C and5276C..5277C call the matched MSVC71 vector
// ctor/dtor iterators with count5 and stride16. Constructor callback VA
// 451CA2 is a 24B float3-zero/byte-zero constructor ending at451CBA;
// destructor callback is the shared empty RET at4B3FD0. Target callbacks,
// stride, count and measured fields establish this opaque array view.
// Original element/array owner names remain unknown; no Miles type claim.
class Rva00051CA2 {
public:
    __declspec(noinline) Rva00051CA2();
    ~Rva00051CA2();
private:
    float x, y, z;
    bool active;
};
class Rva0005276C {
public:
    Rva0005276C();
    ~Rva0005276C();
private:
    Rva00051CA2 slots[5];
};
Rva00051CA2::Rva00051CA2() : x(0.0f), y(0.0f), z(0.0f), active(false) {}
Rva0005276C::Rva0005276C() {}
Rva0005276C::~Rva0005276C() {}
