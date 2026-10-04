// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// partial score=0.98 date=2026-10-04
// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// cl: /O2 /DNDEBUG /MD
// Retail body 0x006C2FB0, 100 bytes. Log/chat line formatter: it copies the
// second stack argument into a 0x300-byte stack buffer, appends a newline after
// it, then hands the REMAINDER of the buffer plus the first stack argument and
// the remaining room to a thiscall sink on `this`.
//
// Improvement over the banked 0.97 attempt: the copy loop walks a dedicated
// `arg2` alias of the second argument instead of a cached `src` local, which
// reproduces retail's register plan (the argument is loaded once into EDX, the
// strlen walk cursor lives in EAX and yields the length, and the copy loop
// advances EDX). That drops the residual from 22 differing bytes to 10 at the
// exact 100-byte retail size. Remaining residue is two allocator decisions:
// the loop-entry `lea esi,[eax+1]` base comes from EDX here and from EAX in
// retail (MSVC folds the base into the surviving argument once the copy loop
// holds it), and the two sink pushes at the tail are emitted in the opposite
// order. Both are register-allocation ties, not semantics.
class Rva006C2D20Sink
{
public:
	void rva006C2D20(const char *dst, const char *src, unsigned int room);
	void rva006C2FB0(const char *text, const char *extra);
};

void Rva006C2D20Sink::rva006C2FB0(const char *text, const char *extra)
{
	char buffer[0x300];
	const char *p = extra;
	const char *base = p + 1;
	char c;
	do
	{
		c = *p;
		++p;
	} while (c);
	int len = (int)(p - base);
	const char *arg2 = extra;
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
		rva006C2D20(buffer + len + 1, text, 0x2fe - len);
	}
}