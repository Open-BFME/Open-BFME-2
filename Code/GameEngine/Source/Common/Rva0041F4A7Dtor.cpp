// cl: /O1 /DNDEBUG /MD /EHsc
// Native 0041F4A7..0041F4E0, 57 bytes: clear POD hash nodes, then free
// the bucket allocation. This replaces the old gen-alias at its own address.
// Target accesses establish bucket pointers at +4/+8/+C and count at +10.
// Original key/value identities remain unknown. Armor's template supplies
// the already-rowed shared clear body, not this table's original identity.
// Keep this allocator-owning body separate from headers importing CRT free:
// retail uses the game allocator at 00030830 and a throwing declaration.

extern "C" void __cdecl free(void *block) throw(...);

class Rva001DBCDCTarget
{
public:
    void rva001DBCDC();
};

struct Rva0041F4A7Buckets
{
    ~Rva0041F4A7Buckets();
    void **begin;
    void **end;
    void **storageEnd;
};

class Rva0041F4A7
{
public:
    ~Rva0041F4A7();
private:
    void *unused00;
    Rva0041F4A7Buckets buckets;
    unsigned int count;
};

// ?Rva0041F4A7Buckets::~Rva0041F4A7Buckets present-unmatched
inline Rva0041F4A7Buckets::~Rva0041F4A7Buckets()
{
    if (begin != 0)
        free(begin);
}

Rva0041F4A7::~Rva0041F4A7()
{
    reinterpret_cast<Rva001DBCDCTarget *>(this)->rva001DBCDC();
}
