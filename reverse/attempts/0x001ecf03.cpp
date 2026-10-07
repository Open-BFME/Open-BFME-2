// ?rva001ECF03@Rva0023D607Holder@@QAEXHH@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 001ECF03..001ECF66, 99B, RET8. The rowed +10 holder
// forwarder 001ECEF6 establishes this receiver view; its global is registered
// as TheLinearCampaignManager. Original method/entry type names are unknown.
// Target entry vector +14/+18 has 36-byte records. Allocation is 196 bytes.
// Existing constructor 001EBAEA retains its opaque two-word argument ABI;
// its vector-base and clear80 calls initialize storage without allocation.
class Rva000AD6F4
{
public:
    void clear();
};
class Rva00575674Sub
{
public:
    void rva00575674(void *value);
};
class Rva001EBAEA
{
public:
    Rva001EBAEA(int entry, int argument) throw();
    void rva001ECDB3();
private:
    char unknown00[0xC4];
};
struct Rva001ECF03Entry { int words[9]; };
class Rva0023D607Holder
{
public:
    void rva001ECF03(int index, int argument);
private:
    char unknown00[0x10];
    Rva001EBAEA *current;
    Rva001ECF03Entry *first, *last, *limit;
};
void Rva0023D607Holder::rva001ECF03(int index, int argument)
{
    reinterpret_cast<Rva000AD6F4 *>(&current)->clear();
    if (index >= 0 && static_cast<unsigned int>(index) < static_cast<unsigned int>(last - first))
    {
        Rva001EBAEA *state = new Rva001EBAEA(reinterpret_cast<int>(first + index), argument);
        reinterpret_cast<Rva00575674Sub *>(&current)->rva00575674(state);
        current->rva001ECDB3();
    }
}
