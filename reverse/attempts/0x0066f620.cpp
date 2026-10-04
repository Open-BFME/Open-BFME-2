// ?forward3@Rva0066F5F0ForwardView@@QAEXXZ
// partial score=1.0 date=2026-10-05
// cl: /O2 /Ob1
// BANKED DRAFT: byte-exact, but void/no-argument slot signatures are donor
// assumptions, not established target facts. Do not land without native ABI
// proof and reconciliation with the existing browser-owner views.
// Primary guide: whole BFME1 T2MemberVirtualForwarders.cpp at
// 5cc75ddda6455c338a5068307e587a793f96d6b3, without header dependencies.
// The four independent INT3-bounded native entries at 66F5F0/11,66F600/12,
// 66F610/12,66F620/12 form secondary table CE3F08, installed at owner+4 by
// rowed ctor66F860/104 and dtor66F8D0/96. Each reads this+C, vptr at that
// raw object+4, adjusts ECX+4, then jumps via its own slot0/4/8/C.
// Native facts do not prove stack arguments or return types of those slots.
// No vtable, instance, ctor/dtor, or complete inheritance layout is emitted.
struct Rva0066F5F0Slots {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
};
struct Rva0066F5F0ForwardView {
    unsigned char m_unobserved00[12];
    void *m_rawObject0C;
    void forward0(); void forward1(); void forward2(); void forward3();
};
void Rva0066F5F0ForwardView::forward0() { reinterpret_cast<Rva0066F5F0Slots *>(static_cast<char *>(m_rawObject0C)+4)->slot0(); }
void Rva0066F5F0ForwardView::forward1() { reinterpret_cast<Rva0066F5F0Slots *>(static_cast<char *>(m_rawObject0C)+4)->slot1(); }
void Rva0066F5F0ForwardView::forward2() { reinterpret_cast<Rva0066F5F0Slots *>(static_cast<char *>(m_rawObject0C)+4)->slot2(); }
void Rva0066F5F0ForwardView::forward3() { reinterpret_cast<Rva0066F5F0Slots *>(static_cast<char *>(m_rawObject0C)+4)->slot3(); }
