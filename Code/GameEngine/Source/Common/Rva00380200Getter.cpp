// cl: /Ireference/shims/bfme2_ascii /GX-
// ?rva00380200@Rva00380200@@QAEPAVAsciiString@@XZ @ 0x00380200 (13B): getter returning +4 or AsciiString::TheEmptyString. Callers 0x00380230 0x00380265 push result. Twin of EmptyString fallback pattern.
// ?rva0038020D@Rva00380200@@QAEXXZ @ 0x0038020D (110B): caches at +0x20 the
// value the store (0x00DFE0EC, pinned get 0x002000D7) config for level
// m_14 + 1 reports for this name (0x7FFFFFFF when absent), and at +0x24 the
// one for level m_14 (0 when absent), through the config method 0x00200157
// (pinned from these call sites: thiscall ret 4 taking the name by reference,
// returning a dword field). Retail keeps the config in edx across the
// rva00380200 call, which cl only does when that getter was compiled earlier
// in the same TU; the TU is /O1 so the getter is called rather than inlined.
#include "ascii_string.h"

// Matched DIR32 references place this static object at VA 0x00DE0878. Its
// four retail bytes are zero, the null StringBase buffer of an empty string.
const AsciiString AsciiString::TheEmptyString;

struct Rva002000D7Config
{
	int rva00200157(const AsciiString &name);
};
class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int);
};
extern Rva002000D7Store *Va00DFE0ECStore;

class Rva00380200
{
	int m_00;
	AsciiString *m_ptr;
	char m_pad08[0x14 - 0x08];
	int m_14;
	char m_pad18[0x20 - 0x18];
	int m_20;
	int m_24;
public:
	AsciiString *rva00380200();
	void rva0038020D();
};

AsciiString *Rva00380200::rva00380200()
{
	if (m_ptr)
		return m_ptr;
	return const_cast<AsciiString *>(&AsciiString::TheEmptyString);
}

void Rva00380200::rva0038020D()
{
	Rva002000D7Config *config = Va00DFE0ECStore ? Va00DFE0ECStore->get(m_14 + 1) : 0;
	m_20 = config ? config->rva00200157(*rva00380200()) : 0x7fffffff;
	config = Va00DFE0ECStore ? Va00DFE0ECStore->get(m_14) : 0;
	m_24 = config ? config->rva00200157(*rva00380200()) : 0;
}
