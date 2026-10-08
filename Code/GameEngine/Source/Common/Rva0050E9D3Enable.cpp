// cl: /GX-
// ?Rva0050E9D3Enable@@YAXXZ @0x0050E9D3 43B.
// One-shot enabler: if global 0x00A046B4 is null or its byte at +0x278 is
// set, return; else set it and the byte at +0x54 of global 0x00A01E48, then
// tail-jmp to rowed enable 0x00222479 on global 0x009FE4CC. Callers at
// 0x00376D56 0x0043CC61 0x0050EBBD 0x0050EC17 0x0051B46C. /O1 for the tail
// jmp; /GX- matches the frameless ColdGlobal neighbours.
class InGameUI;
extern InGameUI *TheInGameUI;
struct GlobalA046B4 { char pad[0x278]; unsigned char flag; };
extern GlobalA046B4 *g_Va00A046B4;
struct GlobalA01E48 { char pad[0x54]; unsigned char flag; };
extern GlobalA01E48 *g_Va00A01E48;
class Rva00222479ByteOneSetter { public: void enable(); };
extern Rva00222479ByteOneSetter *g_Va009FE4CC;
void Rva0050E9D3Enable(void)
{
	GlobalA046B4 *p = g_Va00A046B4;
	if (!p)
		return;
	if (p->flag)
		return;
	p->flag = 1;
	g_Va00A01E48->flag = 1;
	g_Va009FE4CC->enable();
}

// ?Rva004E400DEnable@@YAXXZ @0x004E400D 43B.
// One-shot enabler, twin of 0x0050E9D3 above on global 0x00A04450: if it is
// null or its byte at +0x278 is set, return; else set it and the byte at
// +0x54 of global 0x00A01E48, then tail-jmp to rowed enable 0x00222479 on
// global 0x009FE4CC. Callers at 0x00376D51 0x003CEC9F 0x0043CC5C 0x004E40BF
// 0x004E4342 0x00512DFC 0x0051B467 plus jmp 0x003BD41F. Unlock lane.
struct GlobalA04450 { char pad[0x278]; unsigned char flag; };
extern GlobalA04450 *g_Va00A04450;
void Rva004E400DEnable(void)
{
	GlobalA04450 *p = g_Va00A04450;
	if (!p)
		return;
	if (p->flag)
		return;
	p->flag = 1;
	g_Va00A01E48->flag = 1;
	g_Va009FE4CC->enable();
}

// ?Rva004E40A6Enable@@YGXH@Z @0x004E40A6 33B.
// Guarded enabler, chain lane on 0x004E400D above: call it unless global
// 0x009FE78C has 6 at +0x110 and global 0x009FEDF0 has 0 at +0x16. The int
// parameter is dead (ret 4, never read); __stdcall for the callee cleanup.
// One caller at 0x004E44EF.
struct Global9FE78C { char m_pad[0x110]; int m_val; };
extern Global9FE78C *g_Va009FE78C;
struct Global9FEDF0 { char m_pad[0x16]; unsigned char m_flag; };

void __stdcall Rva004E40A6Enable(int unused)
{
	if (g_Va009FE78C->m_val != 6 || (*(Global9FEDF0 **)&TheInGameUI)->m_flag != 0)
		Rva004E400DEnable();
}

// ?Rva004E4179Get@@YAPAXXZ @0x004E4179 50B.
// One-shot guarded singleton getter: unless guard byte at 0x00A04464 is
// set, set it, point 0x00A0445C at 0x008621F0 (encoded 0x00C621F0) and set
// byte at 0x00A04460, registering cleanup RVA 0x007B8F26 (encoded
// 0x00BB8F26) via rowed _atexit, then return address of 0x00A0445C.
// Callers at 0x004E41BF 0x004E4317 0x004E4321 0x004E432C plus jmp thunk
// 0x004E4312; caller 0x004E432A uses +4 as flag byte.
extern "C" int __cdecl atexit(void (__cdecl *routine)(void));
extern void *g_Va00A0445C;
extern const void *const g_00C621F0[];
void __cdecl rva007B8F26();
// g_Va00A0445C: matched references place it at VA 0xe0445c (zero-filled .bss).
void * g_Va00A0445C;
extern unsigned char g_Va00A04460;
// g_Va00A04460: matched references place it at VA 0xe04460 (zero-filled .bss).
unsigned char g_Va00A04460;
extern int g_Va00A04464;
// g_Va00A04464: matched references place it at VA 0xe04464 (zero-filled .bss).
int g_Va00A04464;
void *Rva004E4179Get(void)
{
	if ((g_Va00A04464 & 1) == 0)
	{
		g_Va00A04464 |= 1;
		g_Va00A0445C = (void *)g_00C621F0;
		g_Va00A04460 = 1;
		atexit(rva007B8F26);
	}
	return &g_Va00A0445C;
}

// Target identity: GameState::init passes this entry's result for the
// ObjectivesMenu snapshot. The five-byte body is an unadjusted tail jump to
// the rowed getter at 0x004E4179; preserve its existing address-derived name.
void *Rva004E4312GetRoute(void)
{
	return Rva004E4179Get();
}

// Target body at 0x004E4317 calls the rowed guarded getter and sets byte +4
// of its returned global block. Keep the entry name address-derived.
void rva004E4317(void)
{
	((unsigned char *)Rva004E4179Get())[4] = 1;
}

// ?Rva004E432ASet@@YAXE@Z @0x004E432A 34B.
// Flag setter on the 0x004E4179 singleton block: if the byte arg equals the
// flag byte at +4 of the block, return; if arg is 0, call rowed enable
// 0x004E400D, then store arg. Caller 0x003BD412 forwards one dword.
void Rva004E432ASet(unsigned char val)
{
	unsigned char *flag = (unsigned char *)Rva004E4179Get() + 4;
	if (val == *flag)
		return;
	if (val == 0)
		Rva004E400DEnable();
	*flag = val;
}

// ?Rva00444040Enable@@YAXXZ @0x00444040 21B.
// Guarded enabler: if int at 0x00A03354 is 0 return else tail-jmp to rowed
// enable 0x00222479 on global 0x009FE4CC. Callers at 0x00444342 0x0044529B
// 0x0044674E. Unlock lane.
extern int g_Va00A03354;
// g_Va00A03354: VA 0xe03354 (zero-filled .bss).
int g_Va00A03354;
void Rva00444040Enable(void)
{
	if (g_Va00A03354 == 0)
		return;
	g_Va009FE4CC->enable();
}

// ?Rva0052340DEnable@@YAXXZ @0x0052340D 43B.
// One-shot enabler, twin of 0x0050E9D3 above on global 0x00A04934: if it is
// null or its byte at +0x278 is set, return; else set it and the byte at
// +0x54 of global 0x00A01E48, then tail-jmp to rowed enable 0x00222479 on
// global 0x009FE4CC. Callers at 0x00523481 0x005235C9 0x005CD60B 0x005CD67A
// 0x005CD6C4 0x005CD6EF plus jmp 0x0052359B. Unlock lane.
struct GlobalA04934 { char pad[0x278]; unsigned char flag; };
extern GlobalA04934 *g_Va00A04934;
// g_Va00A04934: matched references place it at VA 0xe04934 (zero-filled .bss).
GlobalA04934 * g_Va00A04934;
void Rva0052340DEnable(void)
{
	GlobalA04934 *p = g_Va00A04934;
	if (!p)
		return;
	if (p->flag)
		return;
	p->flag = 1;
	g_Va00A01E48->flag = 1;
	g_Va009FE4CC->enable();
}

// ?Rva0043C96FEnable@@YAXXZ @0x0043C96F 43B.
// One-shot enabler, twin of 0x0050E9D3 above on global 0x00A03314: if it is
// null or its byte at +0x278 is set, return; else set it and the byte at
// +0x54 of global 0x00A01E48, then tail-jmp to rowed enable 0x00222479 on
// global 0x009FE4CC. Callers at 0x0031C787 0x0043C9F1 0x0043CCF2 0x0051B45D
// plus jmps 0x0031AD8F 0x0031ADA9. Unlock lane.
struct GlobalA03314 { char pad[0x278]; unsigned char flag; };
extern GlobalA03314 *g_Va00A03314;
void Rva0043C96FEnable(void)
{
	GlobalA03314 *p = g_Va00A03314;
	if (!p)
		return;
	if (p->flag)
		return;
	p->flag = 1;
	g_Va00A01E48->flag = 1;
	g_Va009FE4CC->enable();
}

// ?Rva0043C9B3Get@@YAPAXXZ @0x0043C9B3 50B.
// One-shot guarded singleton getter, twin of 0x004E4179 above: unless guard
// byte at 0x00A03320 is set, set it, point 0x00A03318 at 0x0083D690
// (encoded 0x00C621F0-style 0x00C3D690) and set byte at 0x00A0331C, registering cleanup RVA
// 0x007B83E1 (encoded 0x00BB83E1) via rowed _atexit, then return address of
// 0x00A03318. Caller 0x0043CCD1 uses +4 as flag byte. Unlock lane.
extern void *g_Va00A03318;
// g_Va00A03318: matched references place it at VA 0xe03318 (zero-filled .bss).
void * g_Va00A03318;
extern unsigned char g_Va00A0331C;
// g_Va00A0331C: matched references place it at VA 0xe0331c (zero-filled .bss).
unsigned char g_Va00A0331C;
extern int g_Va00A03320;
// g_Va00A03320: matched references place it at VA 0xe03320 (zero-filled .bss).
int g_Va00A03320;
extern const void *const g_00C3D690[];
void __cdecl rva007B83E1();
void *Rva0043C9B3Get(void)
{
	if ((g_Va00A03320 & 1) == 0)
	{
		g_Va00A03320 |= 1;
		g_Va00A03318 = (void *)g_00C3D690;
		g_Va00A0331C = 1;
		atexit(rva007B83E1);
	}
	return &g_Va00A03318;
}

// ?Rva0043CCC2Get@@YAPAXXZ @0x0043CCC2 5B: forwards to the singleton getter
// above (a tail jump). Address name; nearest neighbour of the users below.
void *Rva0043CCC2Get(void)
{
	return Rva0043C9B3Get();
}

// ?Rva0043CCC7Set@@YAXXZ @0x0043CCC7 10B: sets the singleton's +4 flag byte
// (the byte Rva0043CCDASet below compares). Address name.
void Rva0043CCC7Set(void)
{
	*((unsigned char *)Rva0043C9B3Get() + 4) = 1;
}

// ?Rva0043CCDASet@@YAXE@Z @0x0043CCDA 34B.
// Flag setter on the 0x0043C9B3 singleton block, twin of 0x004E432A above:
// if the byte arg equals the flag byte at +4 of the block, return; if arg
// is 0, call rowed enable 0x0043C96F, then store arg. Caller 0x003BD405
// forwards one dword. Chain lane on 0x0043C9B3.
void Rva0043CCDASet(unsigned char val)
{
	unsigned char *flag = (unsigned char *)Rva0043C9B3Get() + 4;
	if (val == *flag)
		return;
	if (val == 0)
		Rva0043C96FEnable();
	*flag = val;
}

// ?Rva0043CCD1Get@@YAEXZ @0x0043CCD1 9B.
// Flag-byte getter on the 0x0043C9B3 singleton block: returns the byte at
// +4. Callers at 0x002D4CE9 0x002D4D5A. Chain lane on 0x0043C9B3.
unsigned char Rva0043CCD1Get(void)
{
	return *((unsigned char *)Rva0043C9B3Get() + 4);
}

// ?Rva0043C933Get@@YAHXZ @0x0043C933 54B.
// Tri-state gate: 2 when the multiplayer predicate behind global 0x009FE78C
// (rowed bfmeCall939D 0x0023C6FD) answers nonzero, else walks global
// 0x009FEEE8 (+0x10, +0x34) to a flag byte at +0x1BC: 1 when set, 0 when any
// link is null or clear. Caller at 0x0043CD78. Unlock lane.
class BfmeGlob939D
{
public:
	char bfmeCall939D();
};
struct Rva0043C933Sub
{
	char m_pad[0x1BC];
	unsigned char m_flag;
};
struct Rva0043C933Mid
{
	char m_pad[0x34];
	Rva0043C933Sub *m_sub;
};
struct Rva0043C933Outer
{
	char m_pad[0x10];
	Rva0043C933Mid *m_mid;
};
extern Rva0043C933Outer *g_Va009FEEE8;
int Rva0043C933Get(void)
{
	if (((BfmeGlob939D *)g_Va009FE78C)->bfmeCall939D())
		return 2;
	Rva0043C933Mid *mid = g_Va009FEEE8->m_mid;
	if (mid != 0)
	{
		Rva0043C933Sub *sub = mid->m_sub;
		if (sub != 0)
		{
			if (sub->m_flag != 0)
				return 1;
		}
	}
	return 0;
}

// ?Rva0043C99AGet@@YAHXZ @0x0043C99A 25B.
// Null-or-flag test on global 0x00A03314: 1 when set with the byte at
// +0x2A1 set, else 0. Sits between rowed 0x0043C96F and 0x0043C9B3.
// Callers at 0x0029B58A 0x002A1A22 0x002D4CE0 0x0031AD97 0x0031D247
// 0x003EC58E plus jmp 0x003E54A3. Unlock lane.
struct GlobalA03314Flag2A1
{
	char m_pad[0x2A1];
	unsigned char m_flag;
};
int Rva0043C99AGet(void)
{
	GlobalA03314 *p = g_Va00A03314;
	if (p != 0)
	{
		if (((GlobalA03314Flag2A1 *)p)->m_flag != 0)
			return 1;
	}
	return 0;
}

// ?g_Va009FE4CC@@3PAVRva00222479ByteOneSetter@@A: the global at this VA is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVRva00222479ByteOneSetter@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
#pragma comment(linker, "/alternatename:?WindowManagerSubsystem@@3PAVClientSubsystem@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVRva00223A94@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
#pragma comment(linker, "/alternatename:?TheGuiScale@@3PAVGuiScale@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVDummy24@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVRva00224705@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
// ?g_Va009FEEE8@@3PAURva0043C933Outer@@A: the global at this VA is ?ThePlayerList@@3PAVPlayerList@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va009FEEE8@@3PAURva0043C933Outer@@A=?ThePlayerList@@3PAVPlayerList@@A")
#pragma comment(linker, "/alternatename:?TheShroudKeyBase@@3PAUShroudKeyBase@@A=?ThePlayerList@@3PAVPlayerList@@A")
// ?g_Va00A03314@@3PAUGlobalA03314@@A: matched references place it at VA 0xe03314; also referenced as ?g_Va00E03314@@3HA.
GlobalA03314 * g_Va00A03314 = 0;
#pragma comment(linker, "/alternatename:?g_Va00E03314@@3HA=?g_Va00A03314@@3PAUGlobalA03314@@A")
// ?g_Va00A04450@@3PAUGlobalA04450@@A: matched references place it at VA 0xe04450; also referenced as ?g_Va00E04450@@3HA.
GlobalA04450 * g_Va00A04450 = 0;
#pragma comment(linker, "/alternatename:?g_Va00E04450@@3HA=?g_Va00A04450@@3PAUGlobalA04450@@A")
// ?g_Va00A046B4@@3PAUGlobalA046B4@@A: matched references place it at VA 0xe046b4; also referenced as ?g_Va00E046B4@@3HA.
GlobalA046B4 * g_Va00A046B4 = 0;
#pragma comment(linker, "/alternatename:?g_Va00E046B4@@3HA=?g_Va00A046B4@@3PAUGlobalA046B4@@A")
// ?g_Va009FE4CC@@3PAVRva00222479ByteOneSetter@@A: the global at VA 0xdfe4cc is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVRva00222479ByteOneSetter@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
// ?g_Va009FEEE8@@3PAURva0043C933Outer@@A: the global at VA 0xdfeee8 is ?ThePlayerList@@3PAVPlayerList@@A.
#pragma comment(linker, "/alternatename:?g_Va009FEEE8@@3PAURva0043C933Outer@@A=?ThePlayerList@@3PAVPlayerList@@A")
// ?g_Va009FE78C@@3PAUGlobal9FE78C@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE78C@@3PAUGlobal9FE78C@@A=?TheGameLogic@@3PAVGameLogic@@A")
