// cl: /O1 /MD /EHs-c-
// BFME1 donor: game/GameEngine/Source/Common/Q2HeapCopyClones.cpp,
// revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, Rva005EAF10::clone.
// Target vtable at .rdata RVA 0x0081CA04 contains this entry at +8.
// Native entry 0x003AE092 allocates 0x20 bytes through the matched scalar
// operator new at 0x0002FDA0, then invokes matched copy ctor 0x003AE0AF
// with the receiver as its sole argument. The complete body is 29 bytes.
// This view names neither an original class nor individual storage fields.
// Its allocation extent comes from target bytes, not the old private
// Rva003AE0AF declaration's inconsistent sizeof.

#pragma comment(linker, "/alternatename:??0Rva003AE092View@@QAE@ABV0@@Z=??0Rva003AE0AF@@QAE@ABV0@@Z")

class Rva003AE092View
{
public:
    Rva003AE092View(const Rva003AE092View &other);
    Rva003AE092View *clone() const;
private:
    char opaque00[0x20];
};

Rva003AE092View *Rva003AE092View::clone() const
{
    return new Rva003AE092View(*this);
}
