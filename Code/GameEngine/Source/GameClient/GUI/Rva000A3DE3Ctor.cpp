// cl: /MD
// ??0Rva000A3DE3@@QAE@PAX@Z @0x000A3DE3 24B ctor forwards void arg to rowed base 0x00104F8F stores vtable 0x007C9154 returns this evidence callers 0x0008F7F0 0x000A3E32 neighbours WinInstanceDataTextLength and W3DGadgetWindowDrawSlots unblocks 0x0008F7C9 0x000A3E2B
class Rva0078D310Host
{
public:
	Rva0078D310Host(void *ctx);
};

// The retail table at RVA 0x007C9154: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A4328Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A4328Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A4328Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A3E43Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC9154[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A4328Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A3DFB
	(const void *)&__identifier("?system@Rva000A4328Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A3E13
	(const void *)&__identifier("?draw@Rva000A4328Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A4328
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A3E43Get@@YAHXZ"), // slot 7 0x000A3E43
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A3DE3 : public Rva0078D310Host
{
public:
	Rva000A3DE3(void *ctx);
};

Rva000A3DE3::Rva000A3DE3(void *ctx)
	: Rva0078D310Host(ctx)
{
	*(const void **)this = g_00BC9154;
}
