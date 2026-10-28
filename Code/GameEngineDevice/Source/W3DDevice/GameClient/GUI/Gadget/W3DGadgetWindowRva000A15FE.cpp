// cl: /DNDEBUG /MD
// ??0Rva000A15FE@@QAE@PAX@Z @0x000A15FE 24B. Ctor forwards void* to base
// Rva0078D310Host 0x00104F8F then stores vtable 0x007C8DB4 (same as
// Rva000A1616Window input/system vtable in W3DGadgetWindowDrawSlots).
// Evidence: gap between 0x000A15EC/0x000A1616 rows sharing these flags;
// callees rowed base ctor and vtable extern g_00BC8DB4; callers 0x0008FC04
// 0x000A164D.
class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

// The retail table at RVA 0x007C8DB4: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A1CFBWindow@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A165EGet@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8DB4[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A1616
	(const void *)&__identifier("?system@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A162E
	(const void *)&__identifier("?draw@Rva000A1CFBWindow@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A1CFB
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A165EGet@@YAHXZ"), // slot 7 0x000A165E
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A15FE : public Rva0078D310Host
{
public:
	Rva000A15FE(void *context);
};

Rva000A15FE::Rva000A15FE(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8DB4;
}

// The retail table at RVA 0x007C8DE0: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A1D0DWindow@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A1664Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8DE0[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A1616
	(const void *)&__identifier("?system@Rva000A1616Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A162E
	(const void *)&__identifier("?draw@Rva000A1D0DWindow@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A1D0D
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A1664Get@@YAHXZ"), // slot 7 0x000A1664
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A1646 : public Rva000A15FE
{
public:
	Rva000A1646(void *context);
};

Rva000A1646::Rva000A1646(void *context)
	: Rva000A15FE(context)
{
	*(const void **)this = g_00BC8DE0;
}

// The retail table at RVA 0x007C8D5C: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A1CFBWindow@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A135EGet@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8D5C[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A1316
	(const void *)&__identifier("?system@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A132E
	(const void *)&__identifier("?draw@Rva000A1CFBWindow@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A1CFB
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A135EGet@@YAHXZ"), // slot 7 0x000A135E
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A12FE : public Rva0078D310Host
{
public:
	Rva000A12FE(void *context);
};

Rva000A12FE::Rva000A12FE(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8D5C;
}

// The retail table at RVA 0x007C8D88: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A15ECWindow@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A1364Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8D88[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A1316
	(const void *)&__identifier("?system@Rva000A1CFBWindow@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A132E
	(const void *)&__identifier("?draw@Rva000A15ECWindow@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A15EC
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A1364Get@@YAHXZ"), // slot 7 0x000A1364
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A1346 : public Rva000A12FE
{
public:
	Rva000A1346(void *context);
};

Rva000A1346::Rva000A1346(void *context)
	: Rva000A12FE(context)
{
	*(const void **)this = g_00BC8D88;
}

// The retail table at RVA 0x007C91AC: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A4783Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A43BCGet@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC91AC[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A4374
	(const void *)&__identifier("?system@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A438C
	(const void *)&__identifier("?draw@Rva000A4783Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A4783
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A43BCGet@@YAHXZ"), // slot 7 0x000A43BC
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A435C : public Rva0078D310Host
{
public:
	Rva000A435C(void *context);
};

Rva000A435C::Rva000A435C(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC91AC;
}

// The retail table at RVA 0x007C91D8: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A4795Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A43C2Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC91D8[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A4374
	(const void *)&__identifier("?system@Rva000A4783Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A438C
	(const void *)&__identifier("?draw@Rva000A4795Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A4795
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A43C2Get@@YAHXZ"), // slot 7 0x000A43C2
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A43A4 : public Rva000A435C
{
public:
	Rva000A43A4(void *context);
};

Rva000A43A4::Rva000A43A4(void *context)
	: Rva000A435C(context)
{
	*(const void **)this = g_00BC91D8;
}

// The retail table at RVA 0x007C8CAC: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A0C42Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A08F1Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8CAC[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A08A9
	(const void *)&__identifier("?system@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A08C1
	(const void *)&__identifier("?draw@Rva000A0C42Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A0C42
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A08F1Get@@YAHXZ"), // slot 7 0x000A08F1
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A0891 : public Rva0078D310Host
{
public:
	Rva000A0891(void *context);
};

Rva000A0891::Rva000A0891(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8CAC;
}

// The retail table at RVA 0x007C8CD8: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0008FF3E@@UAEPAXI@Z")();
void __identifier("?input@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?system@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z")();
void __identifier("?draw@Rva000A0C54Window@@UAEHPAVWinInstanceData@@@Z")();
void __identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z")();
void __identifier("?rva0009FD78@GameWindow@@UAEHXZ")();
void __identifier("?vslot6@GameWindow@@UBE_NXZ")();
void __identifier("?Rva000A08F7Get@@YAHXZ")();
void __identifier("?vslot8@GameWindow@@UBE_NXZ")();
void __identifier("?vslot9@GameWindow@@UBE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00BC8CD8[11] = {
	(const void *)&__identifier("??_GRva0008FF3E@@UAEPAXI@Z"), // slot 0 0x0008FFC4
	(const void *)&__identifier("?input@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 1 0x000A08A9
	(const void *)&__identifier("?system@Rva000A0C42Window@@UAE?AW4WindowMsgHandledType@@III@Z"), // slot 2 0x000A08C1
	(const void *)&__identifier("?draw@Rva000A0C54Window@@UAEHPAVWinInstanceData@@@Z"), // slot 3 0x000A0C54
	(const void *)&__identifier("?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z"), // slot 4 0x0008FF56
	(const void *)&__identifier("?rva0009FD78@GameWindow@@UAEHXZ"), // slot 5 0x0009FD78
	(const void *)&__identifier("?vslot6@GameWindow@@UBE_NXZ"), // slot 6 0x00313913
	(const void *)&__identifier("?Rva000A08F7Get@@YAHXZ"), // slot 7 0x000A08F7
	(const void *)&__identifier("?vslot8@GameWindow@@UBE_NXZ"), // slot 8 0x0031393A
	(const void *)&__identifier("?vslot9@GameWindow@@UBE_NXZ"), // slot 9 0x0008FF78
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
};

class Rva000A08D9 : public Rva000A0891
{
public:
	Rva000A08D9(void *context);
};

Rva000A08D9::Rva000A08D9(void *context)
	: Rva000A0891(context)
{
	*(const void **)this = g_00BC8CD8;
}
