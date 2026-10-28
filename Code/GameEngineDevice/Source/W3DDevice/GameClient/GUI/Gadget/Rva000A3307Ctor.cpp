// cl: /DNDEBUG /MD
// ??0Rva000A3307@@QAE@PAX@Z @0x000A3307 24B: Gadget window ctor via Host base plus vtable 0x00BC90FC
// Evidence: base ??0Rva0078D310Host@@QAE@PAX@Z row 0x00104F8F with void arg plus vptr 0x00BC90FC g_00BC90FC callers 0x0008F8D8 0x000A3356 prev 0x000A3143 next 0x000A331F same flags
// The retail table at RVA 0x007C90FC: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A3DA8Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A3367Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC90FC[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A331F
	(const void *)&__identifier("?system@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A3337
	(const void *)&__identifier("?draw@Rva000A3DA8Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A3DA8
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A3367Get@@YAHXZ"), // slot 7 0x000A3367
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

class Rva000A3307 : public Rva0078D310Host
{
public:
	Rva000A3307(void *context);
};

Rva000A3307::Rva000A3307(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC90FC;
}

// The retail table at RVA 0x007C9128: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A3DBAWindow@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A336DGet@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC9128[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A331F
	(const void *)&__identifier("?system@Rva000A3DA8Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A3337
	(const void *)&__identifier("?draw@Rva000A3DBAWindow@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A3DBA
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A336DGet@@YAHXZ"), // slot 7 0x000A336D
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A334F : public Rva000A3307
{
public:
	Rva000A334F(void *context);
};

Rva000A334F::Rva000A334F(void *context)
	: Rva000A3307(context)
{
	*(const void **)this = g_00BC9128;
}
