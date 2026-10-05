// cl: /O1 /EHs-c-
// ??0Rva003AD355Module@@QAE@PAXPAVRva003ADBADTemplate@@@Z @0x003AD355 49B
// Chain ctor calling just-landed base ??0Rva003ACD0F 0x003ACD0F then overwriting
// vtable plus three immediates. Evidence: call target rowed; stores match retail
// order vtable g_00C1C12C g_00C1C7E8 g_00C1CBD4; caller at 0x003ADBC3.
extern const void *const g_00C1D09C[];
extern const void *const g_00C1C12C[];
extern const void *const g_00C1C7E8[];
extern const void *const g_00C1CBD4[];
class Rva003ACD0F
{
public:
	Rva003ACD0F(void *a, void *b);
};
class Rva003ADBADTemplate;
class __declspec(novtable) Rva003AD355Module : public Rva003ACD0F
{
public:
	Rva003AD355Module(void *a, Rva003ADBADTemplate *b);
};
Rva003AD355Module::Rva003AD355Module(void *a, Rva003ADBADTemplate *b)
	: Rva003ACD0F(a, (void *)b)
{
	*(void **)this = (void *)g_00C1D09C;
	*(void **)((char *)this + 0x14) = (void *)g_00C1C12C;
	*(void **)((char *)this + 0x18) = (void *)g_00C1C7E8;
	*(void **)((char *)this + 0x1C) = (void *)g_00C1CBD4;
}
