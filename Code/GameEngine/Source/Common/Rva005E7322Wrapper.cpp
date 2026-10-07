// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// Range-34 dump lane: 59B free function at 0x005E7322 (ret, frameless).
// Forwards its int through the pinned 0x005E72B4 helper; on non-null runs
// the pinned 0x0040CB2C mid accessor, treats ret+4 as an AsciiString with
// the rowed isEmpty, and on non-empty looks it up through global ((Rva002D06CA *)TheThingFactory)
// slot rva002D06CA (same recipe as Rva004B0333Get.cpp). All identities
// unproven (address-derived).
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

// Bind to the existing data-ledger owner; keep the retail access view local.
class Rva002D06CA;
extern Rva002D06CA *TheThingFactory;

struct Rva005E7322MidRet
{
	char m_pad[4];
	AsciiString m_str;
};

class Rva005E7322R
{
public:
	Rva005E7322MidRet *mid(int flag);
};

void *rva005E72B4(int v);

void *rva005E7322(int v)
{
	void *r = rva005E72B4(v);
	if (r == 0)
		return 0;
	Rva005E7322R *rr = (Rva005E7322R *)r;
	AsciiString *s = &rr->mid(0)->m_str;
	if (s->isEmpty())
		return 0;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA(s);
}
