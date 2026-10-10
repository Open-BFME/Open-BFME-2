// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// cl: /DNDEBUG /MD
//
// Log/chat line formatter, 0x006C2FB0, 100 bytes. Copies the second stack
// argument into a 0x300-byte stack buffer, appends a newline after it, then
// hands the REMAINDER of the buffer plus the first stack argument and the
// remaining room to a thiscall sink on `this`.
//
// Retail's prologue plan, which this body now reproduces byte for byte:
//
//   mov edx,[esp+0x8] / sub esp,0x300 / push ebx / mov eax,edx / push esi
//   lea esi,[eax+0x1] / mov bl,[eax] / inc eax / test bl,bl / jne
//
// The one instruction every earlier spelling got wrong was `lea esi,[eax+1]`.
// Retail derives the strlen base from the WALK CURSOR's register copy, not from
// the parameter, and both are numerically equal -- which is why 21 prior
// spellings that read `base = walk + 1` from an alias the allocator folded back
// onto the parameter all compiled `lea esi,[edx+1]` instead, moving the callee-
// save push and putting the body 4 bytes out.
//
// A TAUTOLOGICAL PHI fixes it. Writing the cursor initialisation as
// `(extra != 0) ? extra : extra` gives the cursor a distinct SSA value from the
// parameter, so the allocator must copy it into the walk register (the
// `mov eax,edx`) and `base = walk + 1` reads that copy -- yielding retail's
// `lea esi,[eax+0x1]` with the `mov eax,edx` landing between the two pushes,
// exactly as retail orders them. The expression has no runtime effect; it only
// withholds the copy-elision that collapsed the cursor onto the parameter.
class Rva006C2D20Sink
{
public:
	int rva006C2D20(const char *text, const char *tail, unsigned int room);	// returns 0 (xor eax eax at the end of 0x006C2D20)
	void rva006C2FB0(const char *text, const char *extra);
};

// m8: force the walk cursor into its own register with a tautological phi so the
// `+1` for base cannot fold back onto the parameter (retail lea esi,[eax+1]).
void Rva006C2D20Sink::rva006C2FB0(const char *text, const char *extra)
{
	char buffer[0x300];
	const char *walk = (extra != 0) ? extra : extra;
	const char *base = walk + 1;
	char c;
	do
	{
		c = *walk;
		++walk;
	} while (c);
	int len = (int)(walk - base);
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
		rva006C2D20(text, buffer + len + 1, 0x2fe - len);
	}
}