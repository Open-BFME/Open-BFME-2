// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva00410AABFree@@YGXPAX@Z at 0x00410AAB (28B).
// Free helper: destroys Rva00410688 at +4 via rowed dtor then frees via
// rowed operator delete 0x30830. Evidence: 3 callers in 0x410D05/0x410D96,
// unblocks 2.

#include "ascii_string.h"


struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};

class Rva00410688
{
public:
	~Rva00410688();
private:
	AsciiString m_00;
	TargetRef00217D4C *m_04;
};

struct Holder00410AAB
{
	char m_pad00[4];
	Rva00410688 m_04;
};

void __cdecl operator delete(void *p);
extern "C" void __cdecl free(void *p);

void __stdcall Rva00410AABFree(void *p);

void __stdcall Rva00410AABFree(void *p)
{
	((Holder00410AAB *)p)->m_04.~Rva00410688();
	if (p != 0)
		free(p);
}
