// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// partial score=0.99 date=2026-10-05
// ?rva006C2FB0@Rva006C2D20Sink@@QAEXPBD0@Z
// cl: /O2 /DNDEBUG /MD
//
// Retail body 0x006C2FB0, 100 bytes. Log/chat line formatter: it copies the
// second stack argument into a 0x300-byte stack buffer, appends a newline after
// it, then hands the REMAINDER of the buffer plus the first stack argument and
// the remaining room to a thiscall sink on `this`.
//
// Two decisions carry this body to retail's bytes:
//
//  - The sink's arguments are declared (text, tail, room), not (dst, src, room).
//    Retail's tail is `lea eax,[esp+eax+0xd]` / `push eax` / `push edx`, and the
//    pushed register is the reloaded FIRST stack argument, so the buffer pointer
//    is the sink's SECOND parameter and `text` is its FIRST. The bank had this
//    reversed, which is what emitted the `push edx / push eax` pair.
//
//  - The length is `sub eax,esi` against a base taken BEFORE the walk from the
//    walk's own pointer, so the base register is the walk cursor and the
//    comparison is `cmp esi,0x2ff` on the recomputed len+1.
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
	const char *base = copy + 1;
	char c;
	do
	{
		c = *extra;
		++extra;
	} while (c);
	int len = (int)(extra - base);
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
