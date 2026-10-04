// ?Rva002AADB6Compare@@YAHPAVRva002AADB6Reader@@0H@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /G7 /DNDEBUG /MD
// ?Rva002AADB6Compare@@YAHPAVRva002AADB6Reader@@0H@Z RVA 0x002AADB6 size 135
// Evidence: unlock lane; callers 0x002ABC22 0x0032AF02 forward (wrapper vtables 0x7FDC60 0x7FDC6C 0x80D938); virtual slot0 len slot1 read buf-offset-size with 16B stack buffers and memcmp; min-remaining loop returning memcmp diff else lenA-lenB.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);

class Rva002AADB6Reader
{
public:
	virtual int GetLength();
	virtual void Read(void *buf, int offset, int size);
};

// ?Rva002AADB6Compare@@YAHPAVRva002AADB6Reader@@0H@Z present-unmatched
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
