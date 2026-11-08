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
Rva003ADC4F::Rva003ADC4F(const Rva003ADC4F &other)
	: Rva003ADC75(other)
{
	*(const void **)this = __identifier("??_7Rva003AC8D7Object@@6BRva003AC8D7Slot0@@@");
	*(const void **)((char *)this + 8) = __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$00@1@@");
	*(const char **)((char *)this + 12) = "HZz";
}

// The retail call in this body reads 0x003ADC75, an address the ledger already
// carries as ??0BfmeDerivedZL@@QAE@PAV0@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??0Rva003ADC75@@QAE@ABV0@@Z=??0BfmeDerivedZL@@QAE@PAV0@@Z")
