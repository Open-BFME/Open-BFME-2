// cl: /MD
// ?rva006E0AC0@Rva006E0AC0@@QAEHXZ retail 0x006E0AC0 96B
// Evidence: virtual slot 0xC returns hash with flags at +0x10 like AptCIH neighbours; loop over 8-byte table 0xDDC2E8-0xDDC370 via GetString and AptValue findChild; caller 0x006E2EE0
#include "AptNativeHash.h"
class EAStringC;
EAStringC *Rva0070B4F0GetString(int v);
#include "Rva006E0AC0Entry.h"
// The clip-event table at 0x009DC2E8 (136 B, .data): seventeen
// {event mask, string-pool index} pairs, values read from the image. This
// loop, AptInput.cpp and AptCIHQueueClipEvents.cpp walk it.
Rva006E0AC0Entry g_00DDC2E8[17] = {
	{ 0x2, 0x68 }, { 0x400, 0x70 }, { 0x800, 0x71 }, { 0x1000, 0x72 },
	{ 0x10, 0x6C }, { 0x20, 0x6E }, { 0x8, 0x6D }, { 0x80, 0x6A },
	{ 0x40, 0x69 }, { 0x1, 0x6B }, { 0x4, 0x75 }, { 0x100, 0x65 },
	{ 0x2000, 0x74 }, { 0x4000, 0x73 }, { 0x8000, 0x67 }, { 0x10000, 0x66 },
	{ 0x80000, 0x6F },
};
struct BfmeW1229
{
	const char *m_bfme00;
	int m_bfme04;
};
extern BfmeW1229 g_bfmeWords1229[];
#include "AptValue.h"
class Rva006E0AC0
{
	virtual void u0();
	virtual void u1();
	virtual void u2();
	virtual AptNativeHash *GetNativeHashVirtual();
public:
	int rva006E0AC0();
};

int Rva006E0AC0::rva006E0AC0()
{
	int done = 0;
	AptNativeHash *hash = GetNativeHashVirtual();
	Rva006E0AC0Entry *p = g_00DDC2E8;
	do
	{
		if ((hash->nEventHandlers & p->m_mask) == 0 && (p->m_mask & 0xbfdff) != 0)
		{
			if (((AptValue *)this)->findChild(Rva0070B4F0GetString(p->m_str), 0) != 0)
			{
				hash->nEventHandlers |= p->m_mask;
				if ((p->m_mask & 0xbfcf8) != 0)
					done = 1;
			}
		}
		++p;
	} while ((int)p < (int)g_bfmeWords1229);
	return done;
}
