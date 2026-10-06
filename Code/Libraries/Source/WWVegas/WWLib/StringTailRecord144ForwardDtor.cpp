// cl: /MD
// Native entry RVA0x00050FC4 is a complete five-byte JMP to0x002D9A43.
// The rowed single-record Destroy at0x00053E2B tail-calls this entry;
// the next independent entry starts at0x00050FC9. Both take only ECX.
// The existing128-byte prefix destructor owns the native teardown.
// BfmeStringTailRecord144 remains a compatibility name; this opaque
// forwarding view neither allocates the record nor claims its member layout.
// BFME1 donor repair0c5e8ba5c0 names the canonical endpoint through a
// typed member pointer; retain this entry and name its cleanup directly.
class BfmeStringTailRecord144 {
public:
    ~BfmeStringTailRecord144();
};
extern "C" void __identifier("??1BfmeStringTailRecord144@@UAE@XZ")();
BfmeStringTailRecord144::~BfmeStringTailRecord144()
{
    typedef void (BfmeStringTailRecord144::*Cleanup)();
    union { void (*entry)(); Cleanup call; } endpoint =
        { __identifier("??1BfmeStringTailRecord144@@UAE@XZ") };
    (this->*endpoint.call)();
}
