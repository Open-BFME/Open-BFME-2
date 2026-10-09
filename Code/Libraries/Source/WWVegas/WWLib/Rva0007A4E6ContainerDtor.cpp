// cl: /O1 /EHs /MD
// Native 0007A4E6..0007A54B, nonvirtual container-owner destructor.
// Target facts: the direct first call is the existing 7A41E pruning worker;
// then reverse member teardown frees vector buffers at1C and10, destroys the
// string list at0C (799D0) and the tree at0 (79E55). Constructor7A498 confirms
// these member offsets independently. Original owner identity remains unknown.
// STLport4.5.3 vector/list/tree teardown is the semantic reference; existing
// native provider names retained. No names inferred from byte identity alone.
extern "C" void __cdecl free(void *);
class Rva00079A0C {
    unsigned opaque[2];
public:
    ~Rva00079A0C();
};
class Rva000799D0 {
    void *sentinel;
public:
    void rva000799D0();
    ~Rva000799D0() { rva000799D0(); }
};
struct Rva0007A4E6VectorStorage {
    void *begin, *end, *capacity;
    ~Rva0007A4E6VectorStorage() { if (begin) free(begin); }
};
class Rva007A41E {
public:
    void rva007A41E();
};
class Rva007A4E6 {
    Rva00079A0C tree;
    unsigned opaque08;
    Rva000799D0 list;
    Rva0007A4E6VectorStorage first, second;
public:
    ~Rva007A4E6();
};
Rva007A4E6::~Rva007A4E6() {
    reinterpret_cast<Rva007A41E *>(this)->rva007A41E();
}
