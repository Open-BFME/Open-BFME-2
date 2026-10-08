// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB
// ?rva00395E19@Rva00395E19@@QAEXPAVAsciiString@@H@Z RVA 0x00395E19 size 58 unlock Dynamic format via +8 +74 +4 +64.
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva00395E19Q
{
	char m_pad[8];
	char m_name[1];
};
struct Rva00395E19Mid
{
	char m_pad[100];
	Rva00395E19Q *m_q;
};
struct Rva00395E19P
{
	void *m_f0;
	Rva00395E19Mid *m_mid;
	char m_pad2[108];
	int m_id;
};
class Rva00395E19
{
public:
	void rva00395E19(AsciiString *out, int idx);
	char m_pad[8];
	Rva00395E19P *m_p;
};
void Rva00395E19::rva00395E19(AsciiString *out, int idx)
{
	Rva00395E19P *p = m_p;
	if (!p)
		return;
	int id = p->m_id;
	Rva00395E19Mid *mid = p->m_mid;
	char *addr = (char *)mid + 100;
	_ReadWriteBarrier();
	Rva00395E19Q *q = *(Rva00395E19Q **)addr;
	const char *s = q ? (const char *)q + 8 : "";
	out->format("Dynamic_%s_of_id_%d_at_index_%d", s, id, idx);
}
