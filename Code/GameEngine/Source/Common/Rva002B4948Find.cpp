// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?rva002B4948@LivingWorldLogic@@QAEPAXPAX00@Z @0x002B4948 96B: search vector at +0x1B8 for empty-string owner.
// Evidence: callers 0x002B6721 0x002B6A1F 0x002BA8CB; rowed isEmpty 0x00001E2F;
// pin 0x00318C32 Rva00318C79Owner::rva00318C32; prev Rva002B48E1Find idiom.
// Target call sites 0x003EFDB3 and 0x005E56FC load TheLivingWorldLogic into
// ECX before this RET12 query. Its body uses only the three stack arguments;
// the previous free-function declaration forced a redundant volatile load
// into its callers. The original method name and argument classes are unknown.
#include "ascii_string.h"

class Rva00318C32Ret;
class Rva00318C79Owner
{
public:
	char m_pad[0x18];
	AsciiString m_str18;
	Rva00318C32Ret *rva00318C32();
};

struct Rva002B4948Container
{
	char m_pad[0x1B8];
	Rva00318C79Owner **m_begin1B8;
	Rva00318C79Owner **m_end1BC;
};

class LivingWorldLogic
{
public:
    void *rva002B4948(void *a1, void *a2, void *a3);
};

void *LivingWorldLogic::rva002B4948(void *a1, void *a2, void *a3)
{
	Rva002B4948Container *c = (Rva002B4948Container *)a1;
	Rva00318C32Ret *key = (Rva00318C32Ret *)a2;
	Rva00318C79Owner *exclude = (Rva00318C79Owner *)a3;
	Rva00318C79Owner **b;
	Rva00318C79Owner **e;
	for (unsigned int i = 0; (b = c->m_begin1B8, e = c->m_end1BC, i < (unsigned)(e - b)); ++i) {
		Rva00318C79Owner *cur = b[i];
		if (cur == exclude)
			continue;
		if (((const StringBase<char> *)&cur->m_str18)->isEmpty()) {
			if (cur->rva00318C32() == key)
				return cur;
		}
	}
	return 0;
}
