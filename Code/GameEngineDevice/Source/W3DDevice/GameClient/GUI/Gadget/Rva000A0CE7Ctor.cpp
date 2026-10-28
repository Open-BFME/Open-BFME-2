// cl: /DNDEBUG /MD
// ??0Rva000A0CE7@@QAE@PAX@Z @0x000A0CE7 24B: Gadget window ctor via Host base plus vtable 0x00BC8D04
// Evidence: base Rva0078D310Host ctor row 0x00104F8F with void arg plus vptr 0x00BC8D04 g_00BC8D04 slot 3 Rva000A0D5EDraw callers 0x0008FB1C 0x000A0D41
// The retail table at RVA 0x007C8D04: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?bfmeGoEHCa@BfmeThingEHCa@@QAEHPAX00@Z")();
void __identifier("?system@Rva000A12E6Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A12E6Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A0D52Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8D04[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?bfmeGoEHCa@BfmeThingEHCa@@QAEHPAX00@Z"), // slot 1 0x000A0CFF
	(const void *)&__identifier("?system@Rva000A12E6Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A0D22
	(const void *)&__identifier("?draw@Rva000A12E6Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A12E6
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A0D52Get@@YAHXZ"), // slot 7 0x000A0D52
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

class Rva000A0CE7 : public Rva0078D310Host
{
public:
	Rva000A0CE7(void *context);
};

Rva000A0CE7::Rva000A0CE7(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8D04;
}
