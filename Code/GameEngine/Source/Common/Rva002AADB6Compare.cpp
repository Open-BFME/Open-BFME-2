// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?Rva002AADB6Compare@@YAHPAVRva002AADB6Reader@@0H@Z @0x002AADB6 (135B).
// Target facts: cdecl with three arguments (both callers, 0x002ABC62 and
// 0x0032AF42, pop 12 bytes). Each caller builds two stack reader adaptors
// (vtables 0x00BFDC60/0x00BFDC6C) and passes them with a third argument this
// body never reads. Slot 0 returns a length; slot 1 reads (buffer, offset,
// size) into a 16-byte stack buffer. The loop compares at most 16 bytes per
// step with memcmp, returns the first nonzero difference, and otherwise
// returns lenA - lenB. Retail picks the chunk size with cmovl, which MSVC 7.1
// emits only under /arch:SSE. Original class and function names are unknown.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);

class Rva002AADB6Reader
{
public:
	virtual int GetLength();
	virtual void Read(void *buf, int offset, int size);
};

int Rva002AADB6Compare(Rva002AADB6Reader *a, Rva002AADB6Reader *b, int unused)
{
	(void)unused;
	int lenA = a->GetLength();
	int lenB = b->GetLength();
	int offset = 0;
	int remaining = lenA < lenB ? lenA : lenB;
	char buf1[16];
	char buf2[16];
	while (remaining > 0) {
		int chunk = remaining < 16 ? remaining : 16;
		a->Read(buf1, offset, chunk);
		b->Read(buf2, offset, chunk);
		int cmp = memcmp(buf1, buf2, (unsigned int)chunk);
		if (cmp != 0)
			return cmp;
		offset += chunk;
		remaining -= chunk;
	}
	return lenA - lenB;
}
