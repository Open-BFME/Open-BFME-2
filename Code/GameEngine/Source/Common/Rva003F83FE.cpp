// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// ?rva003F83FE@Rva003F83FE@@QAEPAXH@Z @0x003F83FE 31B.
// Index AsciiString array at +0xC and forward via rowed Rva002104B6.
// Evidence: rowed rva002104B6 0x002104B6; global g_009FEF10 +0xb0;
// callers at 0x003F8421 0x003F88FB 0x003F8957 0x003F8A35 0x003F8AD6 0x003F8B34
// 0x003F8CA6; same +0xC array as neighbours Rva003F83D9 Rva003F8443.
#include "ascii_string.h"

class Rva002104B6
{
public:
	void *rva002104B6(void *p);
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva002104B6 *m_b0;
};

extern Rva002BA8F1Logic *g_009FEF10;

class Rva003F83FE
{
public:
	void *rva003F83FE(int i);
private:
	char m_pad00[0x0C];
	AsciiString *m_arr0C;
};

void *Rva003F83FE::rva003F83FE(int i)
{
	AsciiString *arr = m_arr0C;
	int j = i;
	Rva002104B6 *h = g_009FEF10->m_b0;
	return h->rva002104B6(arr + j);
}
