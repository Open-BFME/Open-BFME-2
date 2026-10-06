// cl: /MD /EHsc
// BFME2 Keyboard::resetKeys, RVA 0x00232BDD (16 bytes).
// Identity: WndProc's focus-change calls in WinMain.cpp.
// BFME2 differs from the Generals memset implementation: it gathers pending
// input, then synthesizes key releases. Both direct targets have independent
// Ghidra boundaries (0x00232B7B/76 and 0x00232AE8/147 bytes).
// Historical helper names are unknown; retain address-qualified identities.
class Keyboard
{
public:
    void resetKeys();
private:
    void rva00232B7B();
    void rva00232AE8();
};

void Keyboard::resetKeys()
{
    rva00232B7B();
    rva00232AE8();
}
