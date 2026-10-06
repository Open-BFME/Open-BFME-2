// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva004E9F6E@Rva004E9F6E@@QAEXXZ @0x004E9F6E 68B.
// Empty-name gate: probe the +0x08 key through rowed 0x002A8B59 on the
// 0x00DFEEF8 world; when the returned record's +0x28 name compares equal to
// AsciiString::TheEmptyString, set the +0x04 flag. When the global
// 0x00E04484/0x00E04488 bounds agree, clear the 0x00E044A0 counter and
// tail-call the pinned 0x004E9C13 on this.
#include "ascii_string.h"

struct Rva002A8B59Data
{
	char m_pad[0x28];
	AsciiString m_28;
};

class Rva002A8F24
{
public:
	Rva002A8B59Data *rva002A8B59(void *key);
};

extern Rva002A8F24 *g_00DFEEF8;

struct RvaVector
{
	void **m_begin;
	void **m_end;
	void **m_cap;
};

extern RvaVector g_00E04484;
extern int g_00E044A0;

class Rva004E9C13
{
public:
	void rva004E9C13();
};

class Rva004E9F6E
{
public:
	void rva004E9F6E();
private:
	char m_pad[4];
	unsigned char m_4;
	char m_pad05[3];
	void *m_8;
};

void Rva004E9F6E::rva004E9F6E()
{
	Rva002A8B59Data *rec = ((Rva002A8F24 *)g_00DFEEF8)->rva002A8B59(m_8);
	if (rec->m_28.compare(AsciiString::TheEmptyString) == 0)
		m_4 = 1;
	if (g_00E04484.m_begin == g_00E04484.m_end) {
		g_00E044A0 = 0;
		((Rva004E9C13 *)this)->rva004E9C13();
	}
}
