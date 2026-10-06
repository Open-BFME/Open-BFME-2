// cl: /O1 /MD
// ?rva005CB9D1@Rva005CB9D1@@QAE_NH@Z @0x005CB9D1 34B: null-checked *(arg+0x10) then Rva005CB91E encoder result !=6. Evidence: caller 0x005CBAE6 jmp plus rowed callee 0x005CB91E.
class Rva005CB91E
{
public:
    int rva005CB91E(int key);
};
class Rva005CB9D1
{
public:
    bool rva005CB9D1(int a0);
};
bool Rva005CB9D1::rva005CB9D1(int a0)
{
    int v = *(int *)(a0 + 0x10);
    if (!v)
        return false;
    return ((Rva005CB91E *)this)->rva005CB91E(v) != 6;
}
