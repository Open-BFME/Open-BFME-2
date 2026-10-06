// cl: /MD
// ??0Rva003ACD0F@@QAE@PAX0@Z @0x003ACD0F 49B
// Chain ctor calling just-landed base ??0Rva003AC0DA 0x003AC0DA then overwriting
// vtable plus three immediates. Evidence: call target rowed; stores match retail
// order vtable s_slot g_00C1C7E8 g_00C1CBD4; caller at 0x003AD360.
extern const void *const g_00C1CBE4[];
extern "C" void *s_slot3E4first;
extern const void *const g_00C1C7E8[];
extern const void *const g_00C1CBD4[];
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
Rva003ACD0F::Rva003ACD0F(void *a, void *b)
	: Rva003AC0DA(a, b)
{
	*(void **)this = (void *)g_00C1CBE4;
	*(void **)((char *)this + 0x14) = (void *)&s_slot3E4first;
	*(void **)((char *)this + 0x18) = (void *)g_00C1C7E8;
	*(void **)((char *)this + 0x1C) = (void *)g_00C1CBD4;
}
