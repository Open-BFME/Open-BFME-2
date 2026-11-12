// cl: /EHs-c-
// ??0Rva003ADC4F@@QAE@ABV0@@Z @0x003ADC4F 38B copy ctor via rowed base 0x003ADC75 with three derived stores. Evidence: callee rowed; caller 0x003ADC44; chain from just-landed 0x003ADC75.
class Rva003ADC75
{
public:
	Rva003ADC75(const Rva003ADC75 &other);
private:
	char m_pad[176];
};
extern "C" const void *const __identifier("??_7Rva003AC8D7Object@@6BRva003AC8D7Slot0@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$00@1@@")[];
class Rva003ADC4F : public Rva003ADC75
{
public:
	Rva003ADC4F(const Rva003ADC4F &other);
};
// Retail table 0x00C1C8F0 (4 slots), the +0x0C secondary vftable this constructor
// stores. Its first word, the -0x0C deleting adjustor 0x003A5A48, reads as the
// bytes of "HZz", so the string literal stood in for it. Own the complete
// initialized table (Rva004DF324Dtor.cpp s_10 precedent): each slot names a
// matched row at retail's slot target, taken by address and never called
// through these erased signatures.
extern "C" {
void __identifier("??_ERva003ADFB2@@WM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003AC930Get@@YAHXZ")();
void __identifier("?xfer@Rva0055B3D9@@WM@AEXPAVXfer@@@Z")();
}
static const void *const s_vtable0C[4] = {
	(const void *)&__identifier("??_ERva003ADFB2@@WM@AEPAXI@Z"), //  0 0x003A5A48
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003AC930Get@@YAHXZ"), //  2 0x003AC930
	(const void *)&__identifier("?xfer@Rva0055B3D9@@WM@AEXPAVXfer@@@Z")  //  3 0x003AC936
};
Rva003ADC4F::Rva003ADC4F(const Rva003ADC4F &other)
	: Rva003ADC75(other)
{
	*(const void **)this = __identifier("??_7Rva003AC8D7Object@@6BRva003AC8D7Slot0@@@");
	*(const void **)((char *)this + 8) = __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$00@1@@");
	*(const void **)((char *)this + 12) = s_vtable0C;
}

// The retail call in this body reads 0x003ADC75, an address the ledger already
// carries as ??0BfmeDerivedZL@@QAE@PAV0@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??0Rva003ADC75@@QAE@ABV0@@Z=??0BfmeDerivedZL@@QAE@PAV0@@Z")
