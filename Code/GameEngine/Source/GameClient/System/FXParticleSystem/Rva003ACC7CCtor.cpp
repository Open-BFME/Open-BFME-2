// cl: /MD
// ??0Rva003ACC7C@@QAE@PAX0@Z @0x003ACC7C 49B
// Chain ctor calling just-landed base ??0Rva003ABFE1 0x003ABFE1 then overwriting
// vtable plus three immediates. Evidence: call target rowed; stores match retail
// order vtable s_slot g_00C1D788 g_00C1CB54; caller at 0x003AD2BE.
// The retail table at RVA 0x0081CB64: 8 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD2AE@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva0055CD38@Rva0055CD38@@UAEXPAVXfer@@@Z")();
void __identifier("?rva0055CD70@Rva0055CD70@@QAEXMMM@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ")();
void __identifier("?getPosition@FXPSEmitterLineVolumeModule@@QAE?AUCoord3D0055CDEC@@IIII@Z")();
}
extern const void *const g_00C1CB64[8] = {
	(const void *)&__identifier("??_GRva003AD2AE@@UAEPAXI@Z"), // slot 0 0x003AD42F
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("?rva0055CD38@Rva0055CD38@@UAEXPAVXfer@@@Z"), // slot 3 0x0055CD38
	(const void *)&__identifier("?rva0055CD70@Rva0055CD70@@QAEXMMM@Z"), // slot 4 0x0055CD70
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 5 0x0050B5C6
	(const void *)&__identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ"), // slot 6 0x003ABEFD
	(const void *)&__identifier("?getPosition@FXPSEmitterLineVolumeModule@@QAE?AUCoord3D0055CDEC@@IIII@Z"), // slot 7 0x0055CDEC
};
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF57F@@6BLineEmissionVolumeInfo@FXParticleSystem@@@")[];
class Rva003ABFE1
{
public:
	Rva003ABFE1(void *a, void *b);
};
class __declspec(novtable) Rva003ACC7C : public Rva003ABFE1
{
public:
	Rva003ACC7C(void *a, void *b);
};
Rva003ACC7C::Rva003ACC7C(void *a, void *b)
	: Rva003ABFE1(a, b)
{
	*(void **)this = (void *)g_00C1CB64;
	*(void **)((char *)this + 0x14) = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@");
	*(void **)((char *)this + 0x1C) = (void *)__identifier("??_7Rva003AF57F@@6BLineEmissionVolumeInfo@FXParticleSystem@@@");
}
