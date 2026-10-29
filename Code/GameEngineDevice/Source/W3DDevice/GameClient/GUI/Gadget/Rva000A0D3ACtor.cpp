// cl: /DNDEBUG /MD
// ??0Rva000A0D3A@@QAE@PAX@Z @0x000A0D3A 24B: Gadget window ctor via Rva000A0CE7 base plus vtable 0x00BC8D30
// Evidence: base ??0Rva000A0CE7@@QAE@PAX@Z row 0x000A0CE7 with void arg plus vptr 0x00BC8D30 g_00BC8D30 caller 0x0008FB56
// The retail table at RVA 0x007C8D30: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@GameWindow@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A12E6Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@GameWindow@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A0D58Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8D30[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@GameWindow@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A0CFF
	(const void *)&__identifier("?system@Rva000A12E6Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A0D22
	(const void *)&__identifier("?draw@GameWindow@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A12F8
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A0D58Get@@YAHXZ"), // slot 7 0x000A0D58
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A0CE7
{
public:
	Rva000A0CE7(void *context);
};

class Rva000A0D3A : public Rva000A0CE7
{
public:
	Rva000A0D3A(void *context);
};

Rva000A0D3A::Rva000A0D3A(void *context)
	: Rva000A0CE7(context)
{
	*(const void **)this = g_00BC8D30;
}
