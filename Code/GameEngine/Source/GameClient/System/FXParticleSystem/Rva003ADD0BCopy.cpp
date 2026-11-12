// cl: /EHs-c-
// ??0Rva003ADD0B@@QAE@ABV0@@Z @0x003ADD0B 38B copy ctor via rowed base 0x003ADD31 with three derived stores. Evidence: callee rowed; caller 0x003ADD00; chain from just-landed 0x003ADD31.
class Rva005EA590
{
public:
	Rva005EA590(const Rva005EA590 &other);
private:
	char m_pad[176];
};
typedef Rva005EA590 Rva003ADD31;
// The retail table at RVA 0x0081C954: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ADFB2@@UAEPAXI@Z")();
void __identifier("?rva0055BA3D@Rva0055B9BDView@@QAEXXZ")();
void __identifier("?make@U4Maker005EA530@@QAEPAVU4Made005EA530@@XZ")();
void __identifier("?rva0055BB5C@Rva0055BB5C@@UAEXPAVXfer@@@Z")();
void __identifier("?rva0055BBAE@Rva003ADFB2@@QAE_NH@Z")();
void __identifier("?get@Rva003AC99ALeaGetter@@QBEPAXXZ")();
}
extern const void *const g_00C1C954[6] = {
	(const void *)&__identifier("??_GRva003ADFB2@@UAEPAXI@Z"), // slot 0 0x003AE270
	(const void *)&__identifier("?rva0055BA3D@Rva0055B9BDView@@QAEXXZ"), // slot 1 0x0055BA3D
	(const void *)&__identifier("?make@U4Maker005EA530@@QAEPAVU4Made005EA530@@XZ"), // slot 2 0x003ADCEB
	(const void *)&__identifier("?rva0055BB5C@Rva0055BB5C@@UAEXPAVXfer@@@Z"), // slot 3 0x0055BB5C
	(const void *)&__identifier("?rva0055BBAE@Rva003ADFB2@@QAE_NH@Z"), // slot 4 0x0055BBAE
	(const void *)&__identifier("?get@Rva003AC99ALeaGetter@@QBEPAXXZ"), // slot 5 0x003AC99A
};
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$0A@@1@@")[];
class Rva003ADD0B : public Rva003ADD31
{
public:
	Rva003ADD0B(const Rva003ADD0B &other);
};
// Retail table 0x00C1C940 (4 slots), the +0x0C secondary vftable this constructor
// stores. Its first word, the -0x0C deleting adjustor 0x003A5A48, reads as the
// bytes of "HZz", so the string literal stood in for it. Own the complete
// initialized table (Rva004DF324Dtor.cpp s_10 precedent): each slot names a
// matched row at retail's slot target, taken by address and never called
// through these erased signatures.
extern "C" {
void __identifier("??_ERva003ADFB2@@WM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003AC9A1Get@@YAHXZ")();
void __identifier("?rva0055BB5C@Rva0055BB5C@@WM@AEXPAVXfer@@@Z")();
}
static const void *const s_vtable0C[4] = {
	(const void *)&__identifier("??_ERva003ADFB2@@WM@AEPAXI@Z"), //  0 0x003A5A48
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003AC9A1Get@@YAHXZ"), //  2 0x003AC9A1
	(const void *)&__identifier("?rva0055BB5C@Rva0055BB5C@@WM@AEXPAVXfer@@@Z")  //  3 0x003AC9A7
};
Rva003ADD0B::Rva003ADD0B(const Rva003ADD0B &other)
	: Rva003ADD31(other)
{
	*(const void **)this = g_00C1C954;
	*(const void **)((char *)this + 8) = __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$0A@@1@@");
	*(const void **)((char *)this + 12) = s_vtable0C;
}
