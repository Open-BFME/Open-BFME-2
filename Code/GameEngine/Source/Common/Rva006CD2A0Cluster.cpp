// cl: /GX-
// ?Rva006CD2A0@@YAXPAD@Z @ 0x006CD2A0 (27B) and ?Rva006CD330@@YAXXZ @
// 0x006CD330 (29B). Both stand alone with ret/pad on either side and read the
// Apt object pointer at VA 0x00E176D0 that Rva006CC950Mouse.cpp already
// establishes (same global, same class view).
//
// 0x006CD2A0: `node = apt->+0x6C; if (node) 0x006CD230(node, &buffer)`. The
// single caller 0x00224F98 passes `lea eax,[ebp-0x230]` and then reads the
// first byte of that same buffer, so the argument is the output buffer and the
// callee's second parameter is its address. 0x006CD230 is an unnamed recursive
// path builder (banked attempt re_attempts.log: ?Rva006CD230Append@... 112B
// blocked); only its call is reproduced here.
//
// 0x006CD330: `apt->0x006E47C0(); if (g_at_E180E4) g_at_E180E4->0x0070B220(0)`.
// 0x006E47C0 is an unnamed member of the same Apt class (see 0x006E3530 /
// 0x006E3580 family); 0x0070B220 is the rowed AptNativeHash::rva0070B220.
//
// Both bodies are assigned address-derived names; 0x006CD230 and 0x006E47C0
// are declared but not defined here (defined at their own addresses by other
// work), so this TU is a call site only.

class Rva006E34D0
{
public:
	void rva006E3580(int x, int y);
	void rva006E3530(int a, int b, int c);
	void rva006E47C0();
};

extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
// g_bfmeAptPtrAtE176D0: matched references place it at VA 0xe176d0 (zero-filled .bss).

// Struct key, as the owner of g_bfmeAptHashAtE180E4 declares it.
struct AptNativeHash
{
public:
	void rva0070B220(void *ptr);
};

extern AptNativeHash *g_bfmeAptHashAtE180E4;
// g_bfmeAptHashAtE180E4: matched references place it at VA 0xe180e4 (zero-filled .bss).

// Address-derived: unnamed recursive path builder at 0x006CD230.
struct Rva006CD230Node;
void __cdecl Rva006CD230Path(const Rva006CD230Node *node, char **cursor);

void Rva006CD2A0(char *buffer)
{
	void *node = *(void **)((char *)g_bfmeAptPtrAtE176D0 + 0x6c);
	if (node)
		Rva006CD230Path((const Rva006CD230Node *)node, &buffer);
}

void Rva006CD330()
{
	g_bfmeAptPtrAtE176D0->rva006E47C0();
	if (g_bfmeAptHashAtE180E4)
		g_bfmeAptHashAtE180E4->rva0070B220(0);
}

// 0x006CD2C0 (98B), Ghidra-unlisted: copies a display name into the caller's
// buffer through the rowed AptValue::rva006DE870: the pool's +0x6C value when
// set, else its +0x68 value when that is a CIH whose +8 name string is not
// empty (rowed EAStringC::IsEmpty); otherwise the buffer is emptied. The
// pool is re-read from the global before the second copy, as native.
// Address-derived name.
class AptCIH;
class AptValue
{
public:
	bool isCIH(bool undefinedOK) const;
	AptCIH *c_cih(bool undefinedOK);
	void rva006DE870(char *buffer) const;
};
class EAStringC
{
public:
	bool IsEmpty() const;
};
struct Rva006CD2C0Pool
{
	char pad[0x68];
	AptValue *m_68;
	AptValue *m_6C;
};

void copyDisplayName(char *buffer)
{
	Rva006CD2C0Pool *pool = (Rva006CD2C0Pool *)g_bfmeAptPtrAtE176D0;
	if (pool->m_6C)
	{
		pool->m_6C->rva006DE870(buffer);
		return;
	}
	if (((Rva006CD2C0Pool *)g_bfmeAptPtrAtE176D0)->m_68 && ((Rva006CD2C0Pool *)g_bfmeAptPtrAtE176D0)->m_68->isCIH(false)
		&& !((EAStringC *)((char *)((Rva006CD2C0Pool *)g_bfmeAptPtrAtE176D0)->m_68->c_cih(false) + 8))->IsEmpty())
	{
		((Rva006CD2C0Pool *)g_bfmeAptPtrAtE176D0)->m_68->rva006DE870(buffer);
		return;
	}
	*buffer = 0;
}
