// cl: /O1 /arch:SSE /G7 /MD
// Native array begins at +0x5C0; 1200 * 0xE8 places count at +0x44540.
// Only the verified key +0x58, guard +0xC8 and unsigned state +0xD4 are exposed.
struct TreeLookupRecord
{
    unsigned char pad00[0x58];
    unsigned key;
    unsigned char pad5C[0x6C];
    unsigned guard;
    unsigned char padCC[8];
    unsigned state;
    unsigned char padD8[0x10];
};
class W3DTreeBuffer
{
public:
    bool rva000ECF2A(unsigned key, int mode);
    void rva000ECA4D(int index, int mode);
    unsigned char pad00[0x5C0];
    TreeLookupRecord records[1200];
    int count;
};
// ?rva000ECF2A@W3DTreeBuffer@@QAE_NIH@Z retail 0x000ECF2A..0x000ECF79.
// Identity: destructor 0x000EDA94 installs vtable 0x007CEEA4, whose +8
// entry 0x000EDB39 returns W3DTreeBuffer. Its +0x44558 type array follows
// the count/flags used here and in indexed callee 0x000ECA4D.
// Native call at 0x000ECF70 passes unchanged ECX, index then mode;
// callee reads those parameters at EBP+8/+C and ends at 0x000ECDF2 ret 8.
// Method names and unused record fields remain unknown. Layout is inferred
// from native offsets, independently of the similar shrub lookup.
bool W3DTreeBuffer::rva000ECF2A(unsigned key, int mode)
{
    if (!key)
        return false;
    for (int index = 0; index < count; ++index)
    {
        if (records[index].key == key && records[index].state <= 0 && records[index].guard == 0)
        {
            rva000ECA4D(index, mode);
            return true;
        }
    }
    return false;
}
