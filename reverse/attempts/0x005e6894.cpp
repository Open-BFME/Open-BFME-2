// ?releaseAndEmptyHook@Rva005E6894@@QAEXXZ
// partial score=0.5789473684 date=2026-10-04
// cl: /O2 /Ob2 /GX- /GS
// BFME1 source lead5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv1768.cpp, sibling profile.
// The served19B destructor label/full28B donor layout are unproven for5E6894.
// Native passes receiver+C to helper5E509F/8; that helper reads its+10 pointer
// and tail-calls5E4E1B. Hence this view must extend at least through receiver+1C,
// exceeding the donor's16B member. Native then tail-calls the shared emptyRET
// atB3FD0 with the original receiver. No original class, destructor/lifetime,
// base relation, complete layout or allocator identity is asserted.
// Address-named member calls preserve observed zero-argument thiscall ABIs.
struct Rva005E509FCallView {
    void rva005E509F();
    char m_unmodelled00[0x10];
    void *m_pointer10;
};
class Rva005E6894 {
public:
    void releaseAndEmptyHook();
    void rva000B3FD0CallView();
private:
    char m_unmodelled00[0xC];
    Rva005E509FCallView m_member0C;
};
void Rva005E6894::releaseAndEmptyHook() {
    m_member0C.rva005E509F();
    rva000B3FD0CallView();
}
