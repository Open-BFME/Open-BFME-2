// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z
// partial score=0.85 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O2 /EHsc /DNDEBUG /MD
//
// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z @0x0040AAF8 (~173B).
// Record-key lookup over 0x68-byte entries between +0x18/+0x1C: a pinned
// always-0 fragment call first (its found/end comparison returns early),
// then a NameKeyGenerator warming scan that rebuilds temporaries per entry
// and returns 0. Head range loads stay in registers for the fragment call
// while the loop re-reads the members; the shim AsciiString (friend of
// StringBase) copy-constructs each temporary through the rowed copy ctor
// 0x000365F0 and releases through the rowed releaseBuffer 0x00036410;
// keyToName is the rowed 0x00148C95. Unsigned index/offset/count match the
// jb/test-jbe shapes. Resolves U in 7 units.
#include "ascii_string.h"
#include <new>

enum NameKeyType
{
	DUMMY_NAME_KEY = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

int Rva00080A8C(int a, int b, int c);

class Rva0040BAD0
{
public:
	int rva0040AAF8(int key);
private:
	char m_pad[0x18];
	volatile int m_begin;
	volatile int m_end;
};

int Rva0040BAD0::rva0040AAF8(int key)
{
	int found = Rva00080A8C(m_begin, m_end, (int)&key);
	if (found != m_end)
		return found;
	AsciiString first(TheNameKeyGenerator->keyToName((NameKeyType)key));
	if ((unsigned int)((m_end - m_begin) / 0x68) > 0)
	{
		unsigned int i = 0;
		unsigned int off = 0;
		do
		{
			{
				// Reuse key's dead arg slot for the per-iteration
				// temporary so the frame matches retail exactly.
				AsciiString *t = new ((void *)&key) AsciiString(
					TheNameKeyGenerator->keyToName((NameKeyType)*(int *)(m_begin + off)));
				t->~AsciiString();
			}
			++i;
			off += 0x68;
		} while (i < (unsigned int)((m_end - m_begin) / 0x68));
	}
	return 0;
}
