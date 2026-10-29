// cl: /MD
// ??0Rva003ACD0F@@QAE@PAX0@Z @0x003ACD0F 49B
// Chain ctor calling just-landed base ??0Rva003AC0DA 0x003AC0DA then overwriting
// vtable plus three immediates. Evidence: call target rowed; stores match retail
// order vtable s_slot g_00C1C7E8 g_00C1CBD4; caller at 0x003AD360.
// The retail table at RVA 0x0081CBE4: 8 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD2AE@@UAEPAXI@Z")();
void __identifier("?rva0055D616@Rva003AF7FE@@UAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@Rva003AF7FE@@MAEXPAVXfer@@@Z")();
void __identifier("?rva0055D6D7@Rva003AF7FE@@QAEXUCoord3D@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ")();
void __identifier("?getPosition@CylinderEmissionVolumeModule@FXParticleSystem@@UAE?AUCoord3D@2@MMMM@Z")();
}
extern const void *const g_cylinderEmissionVolumeModuleVTable[8] = {
	(const void *)&__identifier("??_GRva003AD2AE@@UAEPAXI@Z"), // slot 0 0x003AD42F
	(const void *)&__identifier("?rva0055D616@Rva003AF7FE@@UAEXXZ"), // slot 1 0x0055D616
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("?xfer@Rva003AF7FE@@MAEXPAVXfer@@@Z"), // slot 3 0x0055D638
	(const void *)&__identifier("?rva0055D6D7@Rva003AF7FE@@QAEXUCoord3D@@@Z"), // slot 4 0x0055D6D7
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ"), // slot 6 0x003ABEFD
	(const void *)&__identifier("?getPosition@CylinderEmissionVolumeModule@FXParticleSystem@@UAE?AUCoord3D@2@MMMM@Z"), // slot 7 0x0055D741
};
extern "C" void *s_slot3E4first;
extern "C" const void *const __identifier("??_7Rva003AF7D1@@6BIntermediate3AFC6FC@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF7D1@@6BLineEmissionVolumeInfo@FXParticleSystem@@@")[];
class Rva003AC0DA
{
public:
	Rva003AC0DA(void *a, void *b);
};
class __declspec(novtable) Rva003ACD0F : public Rva003AC0DA
{
public:
	Rva003ACD0F(void *a, void *b);
};
Rva003ACD0F::Rva003ACD0F(void *a, void *moduleTemplate)
	: Rva003AC0DA(a, moduleTemplate)
{
	*(void **)this = (void *)g_cylinderEmissionVolumeModuleVTable;
	*(void **)((char *)this + 0x14) = (void *)&s_slot3E4first;
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003AF7D1@@6BIntermediate3AFC6FC@@@");
	*(void **)((char *)this + 0x1C) = (void *)__identifier("??_7Rva003AF7D1@@6BLineEmissionVolumeInfo@FXParticleSystem@@@");
}
