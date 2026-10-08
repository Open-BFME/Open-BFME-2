// cl: /GX-
// Cold-slice global dword getters without vtable carriage (twin-free TU).
//
// Same shape as GlobalGetterSingles.cpp (mov eax,[mem] / ret, 6B) but kept in
// a separate TU so this batch does not contend with appends there. Each reads
// one .data dword global; identity unrecoverable, so globals and functions
// are address-derived (g_Va<VA> / Rva<RVA>Get). Opaque names witness only the
// address and the global. The /GX- line matches the sibling TUs (verified
// frameless six-byte shape).
extern int g_Va00DEC3CC;
// ?g_Va00DEC3CC@@3HA: the global at this VA is ?SyncTime@WW3D@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DEC3CC@@3HA=?SyncTime@WW3D@@0IA")

// ?Rva00083B7BGet@@YAHXZ @ 0x00083b7b (6B) over 0x00DEC3CC.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00083B7BGet(void)
{
	return g_Va00DEC3CC;
}

extern int g_Va00DB47EC;
// g_Va00DB47EC: matched references place it at VA 0xdb47ec (retail .data initial value 2).
int g_Va00DB47EC = 2;

// ?Rva00094B87Get@@YAHXZ @ 0x00094b87 (6B) over 0x00DB47EC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00094B87Get(void)
{
	return g_Va00DB47EC;
}

extern int g_Va00DEDA14;

// ?Rva0014D241Get@@YAHXZ @ 0x0014d241 (6B) over 0x00DEDA14.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0014D241Get(void)
{
	return g_Va00DEDA14;
}

extern int g_Va00DFE348;
// g_Va00DFE348: matched references place it at VA 0xdfe348 (zero-filled .bss).
int g_Va00DFE348;

// ?Rva0021913AGet@@YAHXZ @ 0x0021913a (6B) over 0x00DFE348.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0021913AGet(void)
{
	return g_Va00DFE348;
}

extern int g_Va00E032E0;
// g_Va00E032E0: matched references place it at VA 0xe032e0 (zero-filled .bss).
int g_Va00E032E0;

// ?Rva0023C54CGet@@YAHXZ @ 0x0023c54c (6B) over 0x00E032E0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0023C54CGet(void)
{
	return g_Va00E032E0;
}

extern int g_Va00E0333C;
// g_Va00E0333C: matched references place it at VA 0xe0333c (zero-filled .bss).
int g_Va00E0333C;

// ?Rva00248D60Get@@YAHXZ @ 0x00248d60 (6B) over 0x00E0333C.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00248D60Get(void)
{
	return g_Va00E0333C;
}

extern int g_Va00A03354;

// ?Rva00248D66Get@@YAHXZ @ 0x00248d66 (6B) over 0x00E03354.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00248D66Get(void)
{
	return g_Va00A03354;
}

extern int g_Va00DBB708;
// g_Va00DBB708: matched references place it at VA 0xdbb708 (retail .data initial value 1073741824).
int g_Va00DBB708 = 1073741824;

// ?Rva0027C220Get@@YAHXZ @ 0x0027c220 (6B) over 0x00DBB708.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0027C220Get(void)
{
	return g_Va00DBB708;
}

extern int g_Va00E04450;

// ?Rva0029A26FGet@@YAHXZ @ 0x0029a26f (6B) over 0x00E04450.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0029A26FGet(void)
{
	return g_Va00E04450;
}

extern int g_Va00E04478;
// g_Va00E04478: matched references place it at VA 0xe04478 (zero-filled .bss).
int g_Va00E04478;

// ?Rva0031AA00Get@@YAHXZ @ 0x0031aa00 (6B) over 0x00E04478.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0031AA00Get(void)
{
	return g_Va00E04478;
}

extern int g_Va00E032C8;
// g_Va00E032C8: matched references place it at VA 0xe032c8 (zero-filled .bss).
int g_Va00E032C8;

// ?Rva00320607Get@@YAHXZ @ 0x00320607 (6B) over 0x00E032C8.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00320607Get(void)
{
	return g_Va00E032C8;
}

extern int g_Va00DBD0F0;
// g_Va00DBD0F0: matched references place it at VA 0xdbd0f0 (retail .data initial value 1).
int g_Va00DBD0F0 = 1;

// ?Rva00328A65Get@@YAHXZ @ 0x00328a65 (6B) over 0x00DBD0F0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00328A65Get(void)
{
	return g_Va00DBD0F0;
}

extern int g_Va00E04910;

// ?Rva00376D17Get@@YAHXZ @ 0x00376d17 (6B) over 0x00E04910.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00376D17Get(void)
{
	return g_Va00E04910;
}

extern int g_Va00A04908;

// ?Rva00376D1DGet@@YAHXZ @ 0x00376d1d (6B) over 0x00E04908.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00376D1DGet(void)
{
	return g_Va00A04908;
}

extern int g_Va00E05FAC;
// g_Va00E05FAC: matched references place it at VA 0xe05fac (zero-filled .bss).
int g_Va00E05FAC;

// ?Rva00376D23Get@@YAHXZ @ 0x00376d23 (6B) over 0x00E05FAC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00376D23Get(void)
{
	return g_Va00E05FAC;
}

extern int g_Va00E032FC;
// g_Va00E032FC: matched references place it at VA 0xe032fc (zero-filled .bss).
int g_Va00E032FC;

// ?Rva0038071EGet@@YAHXZ @ 0x0038071e (6B) over 0x00E032FC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0038071EGet(void)
{
	return g_Va00E032FC;
}

extern int g_Va00E046B8;

// ?Rva00380724Get@@YAHXZ @ 0x00380724 (6B) over 0x00E046B8.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00380724Get(void)
{
	return g_Va00E046B8;
}

extern int g_Va00E048D0;
// g_Va00E048D0: matched references place it at VA 0xe048d0 (zero-filled .bss).
int g_Va00E048D0;

// ?Rva0040596CGet@@YAHXZ @ 0x0040596c (6B) over 0x00E048D0.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0040596CGet(void)
{
	return g_Va00E048D0;
}
extern int g_Va00E04904;

// ?Rva00415E8AGet@@YAHXZ @ 0x00415e8a (6B) over 0x00E04904.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00415E8AGet(void)
{
	return g_Va00E04904;
}

extern int g_Va00E0330C;
// g_Va00E0330C: matched references place it at VA 0xe0330c (zero-filled .bss).
int g_Va00E0330C;

// ?Rva0043C6E4Get@@YAHXZ @ 0x0043c6e4 (6B) over 0x00E0330C.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0043C6E4Get(void)
{
	return g_Va00E0330C;
}

extern int g_Va00E06398;

// ?Rva0044C5C1Get@@YAHXZ @ 0x0044c5c1 (6B) over 0x00E06398.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0044C5C1Get(void)
{
	return g_Va00E06398;
}

extern int g_Va00DBA4E4;
// g_Va00DBA4E4: matched references place it at VA 0xdba4e4 (retail .data initial value 5).
int g_Va00DBA4E4 = 5;

// ?Rva004B879DGet@@YAHXZ @ 0x004b879d (6B) over 0x00DBA4E4.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004B879DGet(void)
{
	return g_Va00DBA4E4;
}

extern int g_Va00E063EC;
// g_Va00E063EC: matched references place it at VA 0xe063ec (zero-filled .bss).
int g_Va00E063EC;

// ?Rva004FDA11Get@@YAHXZ @ 0x004fda11 (6B) over 0x00E063EC.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004FDA11Get(void)
{
	return g_Va00E063EC;
}

extern int g_Va00DFEFD8;
// g_Va00DFEFD8: matched references place it at VA 0xdfefd8 (zero-filled .bss).
int g_Va00DFEFD8;

// ?Rva0050B426Get@@YAHXZ @ 0x0050b426 (6B) over 0x00DFEFD8.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0050B426Get(void)
{
	return g_Va00DFEFD8;
}

extern int g_Va00E06394;
// g_Va00E06394: matched references place it at VA 0xe06394 (zero-filled .bss).
int g_Va00E06394;

// ?Rva005114B7Get@@YAHXZ @ 0x005114b7 (6B) over 0x00E06394.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005114B7Get(void)
{
	return g_Va00E06394;
}

extern int g_Va00E06544;
// g_Va00E06544: matched references place it at VA 0xe06544 (zero-filled .bss).
int g_Va00E06544;

// ?Rva00516E0AGet@@YAHXZ @ 0x00516e0a (6B) over 0x00E06544.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00516E0AGet(void)
{
	return g_Va00E06544;
}

extern int g_Va00E06548;
// g_Va00E06548: matched references place it at VA 0xe06548 (zero-filled .bss).
int g_Va00E06548;

// ?Rva00516E48Get@@YAHXZ @ 0x00516e48 (6B) over 0x00E06548.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00516E48Get(void)
{
	return g_Va00E06548;
}

extern int g_Va00E0492C;
// g_Va00E0492C: matched references place it at VA 0xe0492c (zero-filled .bss).
int g_Va00E0492C;

// ?Rva0051AEE9Get@@YAHXZ @ 0x0051aee9 (6B) over 0x00E0492C.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0051AEE9Get(void)
{
	return g_Va00E0492C;
}

extern int g_Va00E046BC;
// g_Va00E046BC: matched references place it at VA 0xe046bc (zero-filled .bss).
int g_Va00E046BC;

// ?Rva005AE5E8Get@@YAHXZ @ 0x005ae5e8 (6B) over 0x00E046BC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005AE5E8Get(void)
{
	return g_Va00E046BC;
}

extern int g_Va00E06480;
// g_Va00E06480: matched references place it at VA 0xe06480 (zero-filled .bss).
int g_Va00E06480;

// ?Rva005B901EGet@@YAHXZ @ 0x005b901e (6B) over 0x00E06480.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005B901EGet(void)
{
	return g_Va00E06480;
}

extern int g_Va00E06550;
// g_Va00E06550: matched references place it at VA 0xe06550 (zero-filled .bss).
int g_Va00E06550;

// ?Rva005BA33EGet@@YAHXZ @ 0x005ba33e (6B) over 0x00E06550.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005BA33EGet(void)
{
	return g_Va00E06550;
}

extern int g_Va00E0ABB0;

// ?Rva006891A0Get@@YAHXZ @ 0x006891a0 (6B) over 0x00E0ABB0.
// Follows padding (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006891A0Get(void)
{
	return g_Va00E0ABB0;
}

extern int g_Va00E18078;

// ?Rva006F5100Get@@YAHXZ @ 0x006f5100 (6B) over 0x00E18078.
// Follows padding (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006F5100Get(void)
{
	return g_Va00E18078;
}

extern int g_Va00DF6FD0;
// g_Va00DF6FD0: matched references place it at VA 0xdf6fd0 (zero-filled .bss).
int g_Va00DF6FD0;

// ?Rva00174F30Get@@YAHXZ @ 0x00174f30 (6B) over 0x00DF6FD0.
// Follows padding (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00174F30Get(void)
{
	return g_Va00DF6FD0;
}

extern int g_Va00E062EC;
// g_Va00E062EC: matched references place it at VA 0xe062ec (zero-filled .bss).
int g_Va00E062EC;

// ?Rva00415E90Get@@YAHXZ @ 0x00415e90 (6B) over 0x00E062EC.
// Follows a ret (prev C3); next is a frameless fn start; no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00415E90Get(void)
{
	return g_Va00E062EC;
}

extern int g_Va00E046B4;

// ?Rva0050E9CDGet@@YAHXZ @ 0x0050e9cd (6B) over 0x00E046B4.
// Follows a ret-with-pop (prev C2 0C 00); next is a frameless fn start;
// phase-clean in 512B window; one E8 caller at 0x002D68D6.
// Opaque address-derived name.
int Rva0050E9CDGet(void)
{
	return g_Va00E046B4;
}

// ?g_Va00E0ABB0@@3HA: matched references place it at VA 0xe0abb0; also referenced as ?g_bfmeThingUCHead@@3PAVBfmeNodeUC@@A.
int g_Va00E0ABB0;
#pragma comment(linker, "/alternatename:?g_bfmeThingUCHead@@3PAVBfmeNodeUC@@A=?g_Va00E0ABB0@@3HA")
// ?g_Va00E04910@@3HA: matched references place it at VA 0xe04910; also referenced as ?g_Va00A04910@@3PAUGlobalA04910@@A.
int g_Va00E04910;
#pragma comment(linker, "/alternatename:?g_Va00A04910@@3PAUGlobalA04910@@A=?g_Va00E04910@@3HA")
// ?g_Va00E046B8@@3HA: matched references place it at VA 0xe046b8; also referenced as ?g_Va00E046B8@@3PAURva00511730State@@A.
int g_Va00E046B8;
#pragma comment(linker, "/alternatename:?g_Va00E046B8@@3PAURva00511730State@@A=?g_Va00E046B8@@3HA")
// ?g_Va00E06398@@3HA: matched references place it at VA 0xe06398; also referenced as ?g_Va00A06398@@3PAVRva00583015Obj@@A.
int g_Va00E06398;
#pragma comment(linker, "/alternatename:?g_Va00A06398@@3PAVRva00583015Obj@@A=?g_Va00E06398@@3HA")
// ?g_Va00E04450@@3HA: the global at VA 0xe04450 is ?g_Va00A04450@@3PAUGlobalA04450@@A.
#pragma comment(linker, "/alternatename:?g_Va00E04450@@3HA=?g_Va00A04450@@3PAUGlobalA04450@@A")
// ?g_Va00E04904@@3HA: the global at VA 0xe04904 is ?g_Va00A04904@@3PAURva00517048@@A.
#pragma comment(linker, "/alternatename:?g_Va00E04904@@3HA=?g_Va00A04904@@3PAURva00517048@@A")
// ?g_Va00E046B4@@3HA: the global at VA 0xe046b4 is ?g_Va00A046B4@@3PAUGlobalA046B4@@A.
#pragma comment(linker, "/alternatename:?g_Va00E046B4@@3HA=?g_Va00A046B4@@3PAUGlobalA046B4@@A")
// ?g_Va00E18078@@3HA: the global at VA 0xe18078 is ?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A.
#pragma comment(linker, "/alternatename:?g_Va00E18078@@3HA=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")

// Clean BF1 9cbfb551fe Common/Rva000CBC30Get.cpp semantic donor, normal O1/SSE/G7.
// Native 00380517..00380523 has its own complete RET boundary and establishes
// receiver0 float pointer, indexed FLD, RET4. Original owner and full array bound remain
// unresolved; this separate address-owned view models only observed accesses.
class Rva00380517Array {
public: float getValue(int index);
private: float *values;
};
float Rva00380517Array::getValue(int index) { return values[index]; }
