// cl: /O1 /MD
// Native entry RVA0x00050FC4 is a complete five-byte JMP to0x002D9A43.
// The rowed single-record Destroy at0x00053E2B tail-calls this entry;
// the next independent entry starts at0x00050FC9. Both take only ECX.
// The existing128-byte prefix destructor owns the native teardown.
// BfmeStringTailRecord144 remains a compatibility name; this opaque
// forwarding view neither allocates the record nor claims its member layout.
class BfmeStringTailRecord144
{
public:
    ~BfmeStringTailRecord144();
private:
    void releasePrefix();
};

#pragma comment(linker, "/alternatename:?releasePrefix@BfmeStringTailRecord144@@AAEXXZ=??1BfmeStringTailRecord144@@UAE@XZ")

BfmeStringTailRecord144::~BfmeStringTailRecord144()
{
    releasePrefix();
}
