// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// partial score=0.995 date=2026-10-05
// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// cl: /O2 /DNDEBUG /MD
//
// Log/chat line formatter, 0x006C2FB0, 100 bytes. Copies the second stack
// argument into a 0x300-byte stack buffer, appends a newline after it, then
// hands the REMAINDER of the buffer plus the first stack argument and the
// remaining room to a thiscall sink on `this`.
//
// The banked body reproduced retail's whole tail byte for byte but loaded the
// second argument into EAX and gave EDX the copy-loop cursor, so the prologue
// read `mov eax,[esp+8]` / `push esi` / `mov edx,eax`. Retail instead loads it
// into EDX, copies EDX into EAX for the strlen walk cursor, and gives EDX the
// copy-loop cursor:
//
//   mov edx,[esp+0x8] / sub esp,0x300 / push ebx / mov eax,edx / push esi
//   lea esi,[eax+0x1] / mov bl,[eax] / inc eax / test bl,bl / jne
//
// THIS body is the v9 spelling that fixes the register ROLES: the walk is
// driven by a separate `walk` cursor alias rather than the parameter itself, so
// MSVC keeps the parameter in EDX (matching retail's `mov edx,[esp+8]`) and the
// walk cursor in EAX. It now matches retail byte for byte through the whole
// prologue up to +0xA and the ENTIRE remainder of the function from +0x15 on.
// The only residue is the order of two adjacent instructions -- retail emits
// `mov eax,edx` then `push esi`, this body emits `push esi` then `mov eax,edx`,
// and the following `lea esi,[edx+1]` reads the parameter rather than the EAX
// copy. MSVC 7.1 always sinks the callee-save push to immediately after the
// preceding `push ebx`, which the bank and 21 measured spellings all confirm is
// not steerable from source.
class Rva006C2D20Sink
{
public:
	void rva006C2D20(const char *text, const char *tail, unsigned int room);
	void rva006C2FB0(const char *text, const char *extra);
};

void Rva006C2D20Sink::rva006C2FB0(const char *text, const char *extra)
{
	char buffer[0x300];
	const char *copy = extra;
	const char *walk = extra;
	const char *base = walk + 1;
	char c;
	do
	{
		c = *walk;
		++walk;
	} while (c);
	int len = (int)(walk - base);
	const char *arg2 = copy;
	if ((unsigned int)(len + 1) < 0x2ff)
	{
		char *dst = buffer;
		char cc;
		do
		{
			cc = *arg2;
			*dst = cc;
			++dst;
			++arg2;
		} while (cc);
		buffer[len] = '\n';
		rva006C2D20(text, buffer + len + 1, 0x2fe - len);
	}
}
