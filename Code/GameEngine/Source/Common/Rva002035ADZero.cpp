// Whole BFME1 game/GameEngine/Source/Common/S1ZeroingConstructors.cpp
// revision5cc75ddda6455c338a5068307e587a793f96d6b3,
// blob b187205c78b391e963d12db299c952caf0cfa20f; no headers.
// cl: /Ob1
// ?rva002035AD@Rva002035ADZeroView@@QAEPAV1@XZ @0x002035AD 13B
// Evidence: abuts prev 0x002035A9/4 (ends at start) and next 0x002035BA (starts at +13); reads ecx first (thiscall mov eax,ecx); ret-terminated; no callees.
// Donor labels do not establish identity so honest RvaZeroView names are used; second method left unmatched per stash caution.
// These two raw methods are fully exact, but their proposed packed native
// entries have no independently witnessed direct or absolute entry refs.
// The original donor constructor labels do not establish native identity.
// Do not row them until their full-function boundaries are independently proved.
// No original class, full extent, field semantics or lifetime is asserted.
// Boundary for 0x002035AD is proved via abut plus thiscall plus ret; 0x002B599F remains unrowed.
class Rva002035ADZeroView
{
public:
 Rva002035ADZeroView *rva002035AD();
private:
 unsigned int a;
 unsigned char b, c;
};
Rva002035ADZeroView *Rva002035ADZeroView::rva002035AD()
{
 a=0; b=0; c=0;
 return this;
}
class Rva002B599FZeroView
{
public:
 Rva002B599FZeroView *rva002B599F();
private:
 unsigned char head[12];
 unsigned int a,b;
};
Rva002B599FZeroView *Rva002B599FZeroView::rva002B599F()
{
 a=0; b=0;
 return this;
}
