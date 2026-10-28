// cl: /DNDEBUG /MD
// ??0Rva000A4916@@QAE@PAX@Z @0x000A4916 24B: Gadget window ctor via Host base plus vtable 0x00BC9204
// Evidence: base ??0Rva0078D310Host@@QAE@PAX@Z row 0x00104F8F with void arg plus vptr 0x00BC9204 g_00BC9204 callers 0x0008F77C 0x000A4970
// The retail table at RVA 0x007C9204: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A6007Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A6097Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A6007Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@Rva000A495EWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A52A2Get@@YAHXZ")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC9204[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A6007Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A492E
	(const void *)&__identifier("?system@Rva000A6097Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A4946
	(const void *)&__identifier("?draw@Rva000A6007Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A6007
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@Rva000A495EWindow@@UAEHXZ"), // slot 5 0x000A495E
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A52A2Get@@YAHXZ"), // slot 7 0x000A52A2
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 8 0x0050B5C6
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

class Rva000A4916 : public Rva0078D310Host
{
public:
	Rva000A4916(void *context);
};

Rva000A4916::Rva000A4916(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC9204;
}
