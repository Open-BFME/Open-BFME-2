// cl: /O1 /GX-
// Retail thunk at 0x0031AD8F (5B) calls the matched free enabler at
// 0x0043C96F. RET at 0x0031AD8E and the next start at 0x0031AD94
// corroborate the thunk inventory extent; its JMP targets that provider.
// Target caller 0x00376D49 loads TheControlBar at VA 0x00E01CFC for
// this call and the following rowed hideSpecialPowerShortcut member.
// That global's identity is established by ControlBarFields.cpp's matched
// DIR32 uses. The receiver is unused; no object layout is claimed here.
// BFME1 revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 and the ZH
// GameLogicDispatch.cpp closeWindows body are relationship leads. Their
// hidePurchaseScience name is not independently proved for this address,
// so this member keeps an address-derived name.
void __cdecl Rva0043C96FEnable();
class ControlBar
{
public:
    void rva0031AD8F();
};
void ControlBar::rva0031AD8F()
{
    Rva0043C96FEnable();
}
