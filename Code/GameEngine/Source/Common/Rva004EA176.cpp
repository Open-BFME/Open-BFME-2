// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
#include "ascii_string.h"

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004EA176
{
public:
	AsciiString rva004EA176();
	char m_pad00[0x14];
	void *m_14;
};

AsciiString Rva004EA176::rva004EA176()
{
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_14);
	void *p160 = *(void **)((char *)rec + 0x160);
	AsciiString *src = (AsciiString *)((char *)p160 + 0x24);
	return *src;
}
