// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?Rva005F02E0Get@@YAPBVImage@@PAX@Z @0x005F02E0 56B
// Evidence: unlock lane, prev Rva005F0220Get 0x005F0220 next rva005F05E6
// 0x005F05E6 in Common, 3 callers, callees rva002D06CA ThingTemplate
// ButtonImage flows plus tail rva0033BA46, global g_009FF000, literal none.
// Identity: free function returning Image* with void* arg, honest address name.
#include "ascii_string.h"

class Image
{
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

class ThingTemplate
{
public:
	const Image *getButtonImage();
	const Image *rva0033BA46();
};

struct Rva005F02E0Mid
{
	char m_pad[0xc];
	AsciiString m_name;
};

struct Rva005F02E0In
{
	char m_pad[0x28];
	Rva005F02E0Mid *m_mid;
};

const Image *Rva005F02E0Get(void *in)
{
	Rva005F02E0Mid *mid = ((Rva005F02E0In *)in)->m_mid;
	void *found;
	if (!mid || !(found = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&mid->m_name)))
		return 0;
	ThingTemplate *tmpl = (ThingTemplate *)found;
	const Image *img = tmpl->getButtonImage();
	if (img)
		return img;
	return tmpl->rva0033BA46();
}
