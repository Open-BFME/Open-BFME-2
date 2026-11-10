// cl: /DNDEBUG /MD /EHsc
// ??0Rva0055BCD2@@QAE@ABV0@@Z @0x003ADDCD 31B copy via rowed base 0x003ADDEC with vptrs g_00C1D164 and s_slot3E4first. Evidence: same vptrs as unsigned-int ctor row 0x0055BCD2; callees rowed; callers 0x003ADC7F 0x003ADD3C; same 31B shape as 0x003ADFDB.
class Rva005EA430
{
public:
	Rva005EA430(const Rva005EA430 &other);
};
// The retail table at RVA 0x0081D164: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AE13C@@UAEPAXI@Z")();
int __cdecl _purecall(void);
}
extern const void *const g_00C1D164[6] = {
	(const void *)&__identifier("??_GRva003AE13C@@UAEPAXI@Z"), // slot 0 0x003AE16E
	(const void *)&__identifier("_purecall"), // slot 1 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 3 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 4 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 5 0x0003B810
};
extern "C" char s_slot3E4first;
class Rva0055BCD2
{
public:
	__declspec(noinline) Rva0055BCD2(const Rva0055BCD2 &other);
private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
};
Rva0055BCD2::Rva0055BCD2(const Rva0055BCD2 &that)
{
	const void *src = &that;
	((Rva005EA430 *)this)->Rva005EA430::Rva005EA430(*(const Rva005EA430 *)src);
	*(const void **)this = g_00C1D164;
	*(void **)((char *)this + 8) = (void *)&s_slot3E4first;
}
// _s_slot3E4first: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
