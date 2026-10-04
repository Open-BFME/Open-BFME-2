// cl: /O1 /MD
// ??0Rva003ACC7C@@QAE@PAX0@Z @0x003ACC7C 49B
// Chain ctor calling just-landed base ??0Rva003ABFE1 0x003ABFE1 then overwriting
// vtable plus three immediates. Evidence: call target rowed; stores match retail
// order vtable s_slot g_00C1D788 g_00C1CB54; caller at 0x003AD2BE.
extern const void *const g_00C1CB64[];
extern "C" void *s_slot3E4first;
extern const void *const g_00C1D788[];
extern const void *const g_00C1CB54[];
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
	*(void **)((char *)this + 0x14) = (void *)&s_slot3E4first;
	*(void **)((char *)this + 0x18) = (void *)g_00C1D788;
	*(void **)((char *)this + 0x1C) = (void *)g_00C1CB54;
}
