// cl: /Ireference/shims/bfme2_ascii /EHs /MD
// ??0Rva00496ADE@@QAE@XZ, retail 0x00496ADE 78B. Ctor: AsciiString +0/+54 via
// shared defaults (m_text 0), Rva0042526Member +8, int +4 cleared in body, then
// +54 set to g_Rva0107301CEmptyString and +0 clear (releaseBuffer) via clear().
// Evidence: callees EH_prolog 0x00629188 Rva0042526Member 0x00042526 set
// 0x000055F5 releaseBuffer 0x00036410, string g_Rva0107301CEmptyString,
// caller 0x00497174, stash 0x00496ade 0.93 (order + dummy fixed, shared header).
#include "ascii_string.h"


class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class Rva00496ADE
{
public:
	Rva00496ADE();
private:
	AsciiString m_str00;
	int m_04;
	Rva0042526Member m_mem08;
	AsciiString m_str54;
};

Rva00496ADE::Rva00496ADE()
	: m_mem08()
{
	m_04 = 0;
	m_str54.set("");
	m_str00.clear();
}
