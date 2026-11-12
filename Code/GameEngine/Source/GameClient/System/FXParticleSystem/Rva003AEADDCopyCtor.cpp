// cl: /GX-

// Rva003AEADD (45B) outer copy via rowed base Rva003AEB0A (91B).
// Same 45B base-plus-4-vtables shape as Rva003AEA15; base is already rowed
// so no pin is needed. All vtable dwords are DIR32.

class Rva003AEB0A
{
public:
	Rva003AEB0A(const Rva003AEB0A &other);
};

// Rva003AEADD_v0: retail table 0x00C1CDF0 (7 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?clone@Rva003AEADD@@QBEPAV1@XZ")();
void __identifier("?DoXfer@Rva003ABCB5@@UAEXAAVXfer@@@Z")();
void __identifier("?rva003ABCE6@Rva003ABCE6Forwarder@@QAEXH@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?rva003ABD04@Rva003ABD04@@QAE?AURva00SlotFloat2@@XZ")();
extern const void *const Rva003AEADD_v0[7] = {
	(const void *)&__identifier("??_GRva003ACB6F@@UAEPAXI@Z"), //  0 0x003AD3F7
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?clone@Rva003AEADD@@QBEPAV1@XZ"), //  2 0x003AEAA3
	(const void *)&__identifier("?DoXfer@Rva003ABCB5@@UAEXAAVXfer@@@Z"), //  3 0x0055B951
	(const void *)&__identifier("?rva003ABCE6@Rva003ABCE6Forwarder@@QAEXH@Z"), //  4 0x003ABCE6
	(const void *)&__identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ"), //  5 0x004F5FA3
	(const void *)&__identifier("?rva003ABD04@Rva003ABD04@@QAE?AURva00SlotFloat2@@XZ")  //  6 0x003ABD04
};
}
// Rva003AEADD_v14: retail table 0x00C1C538 (1 slot). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("?CreateModule@Rva003AC93ETemplate@@UAEPAVRva003AC93EModule@@I@Z")();
extern const void *const Rva003AEADD_v14[1] = {
	(const void *)&__identifier("?CreateModule@Rva003AC93ETemplate@@UAEPAVRva003AC93EModule@@I@Z")  //  0 0x003AC93E
};
}
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$0A@@1@@");
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003ABCB5@@6BSnapshot@@@");

class Rva003AEADD
{
public:
	__declspec(noinline) Rva003AEADD(const Rva003AEADD &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13 owned by base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
	char m_pad20[128]; // +0x20..0x9F owned by base copy
};

// ??0Rva003AEADD@@QAE@ABV0@@Z
Rva003AEADD::Rva003AEADD(const Rva003AEADD &that)
{
	const void *src = &that;
	((Rva003AEB0A *)this)->Rva003AEB0A::Rva003AEB0A(*(const Rva003AEB0A *)src);
	*(void **)this = (void *)Rva003AEADD_v0;
	*(void **)((char *)this + 0x14) = (void *)Rva003AEADD_v14;
	*(void **)((char *)this + 0x18) = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$0A@@1@@");
	*(void **)((char *)this + 0x1C) = &__identifier("??_7Rva003ABCB5@@6BSnapshot@@@");
}
