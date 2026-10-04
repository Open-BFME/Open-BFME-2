// cl: /O1 /MD /EHs-c-
// BFME1 donor: game/GameEngine/Source/Common/Q2HeapCopyClones.cpp,
// revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, Rva005EA2B0::clone.
// Target vtable at .rdata RVA 0x0081C904 contains this entry at +8.
// Native entry 0x003ADC32 allocates 0x5C bytes through the matched scalar
// operator new at 0x0002FDA0, then invokes matched copy ctor 0x003ADC4F
// with the receiver as its sole argument. The complete body is 29 bytes.
// This view names neither an original class nor individual storage fields.
// Its allocation extent comes from target bytes, not the old private
// Rva003ADC4F declaration's inconsistent sizeof.

#pragma comment(linker, "/alternatename:??0Rva003ADC32View@@QAE@ABV0@@Z=??0Rva003ADC4F@@QAE@ABV0@@Z")

class Rva003ADC32View
{
public:
    Rva003ADC32View(const Rva003ADC32View &other);
    Rva003ADC32View *clone() const;
private:
    char opaque00[0x5C];
};

Rva003ADC32View *Rva003ADC32View::clone() const
{
    return new Rva003ADC32View(*this);
}
