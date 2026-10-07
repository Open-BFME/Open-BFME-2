// cl: /GX- /O1 /arch:SSE /G7
// ?rva0031AD94@ControlBar@@QAEXXZ @0x0031AD94 26B
// Banked attempt reverse/attempts/0x0031ad94.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?rva0031AD94@ControlBar@@QAEXXZ, retail 0x0031AD94 (26 bytes).
// Target evidence: the body conditionally calls the matched
// ControlBar::showPurchaseScience row at 0x0031AD5A and the matched free
// enabler at 0x0043C96F. Adjacent target methods at 0x0031AD8F and 0x0031AE01
// support ControlBar as the class; the method name remains address-derived.
int Rva0043C99AGet();
void Rva0043C96FEnable();

class ControlBar
{
public:
    void rva0031AD94();
    void showPurchaseScience();
};

void ControlBar::rva0031AD94()
{
    unsigned char enabled = (unsigned char)Rva0043C99AGet();
    if (!enabled) {
        showPurchaseScience();
        return;
    }
    Rva0043C96FEnable();
}
