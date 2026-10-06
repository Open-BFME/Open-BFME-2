// cl: /DNDEBUG /MD
//
// ?Rva003FC43ACompare@@YAHPAVRva003FC43A@@0H@Z @0x003FC43A (136B):
// Case-insensitive chunked compare of two virtual streams: total sizes via
// slot0, 16-byte chunks via slot1 into two stack buffers, _memicmp per
// chunk, first nonzero diff wins, else lenA-lenB. Caller 0x003FCD04 passes
// two stack objects (different vtables, same 2-virtual interface) plus a
// third dword retail never reads (forwarded zero from 0x003FCE11).
// Evidence: caller 0x003FCD04; IAT _memicmp; neighbours use /O1 /DNDEBUG /MD
// plus /arch:SSE for the chunk-min cmovl (RAMFileRead precedent: no /G flag
// emits cmov).

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);

class Rva003FC43A
{
public:
	virtual int v00();
	virtual void v01(void *buffer, int offset, int length);
};

int Rva003FC43ACompare(Rva003FC43A *a, Rva003FC43A *b, int /*unused*/)
{
	int lenA = a->v00();
	int lenB = b->v00();
	int offset = 0;
	int remaining = lenA;
	if (lenA >= lenB)
		remaining = lenB;
	while (remaining > 0)
	{
		int chunk = 16;
		if (remaining < chunk)
			chunk = remaining;
		unsigned char bufA[16];
		unsigned char bufB[16];
		a->v01(bufA, offset, chunk);
		b->v01(bufB, offset, chunk);
		int diff = _memicmp(bufA, bufB, chunk);
		if (diff != 0)
			return diff;
		offset += chunk;
		remaining -= chunk;
	}
	return lenA - lenB;
}
