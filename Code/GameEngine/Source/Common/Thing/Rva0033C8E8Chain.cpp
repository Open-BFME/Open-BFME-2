// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0033C8E8@Rva0033C8E8@@QAE_NABVAsciiString@@AAV2@@Z @0x0033C8E8 113B:
// chain over four 12B vectors at +0x2e4/+0x2f0/+0x2fc/+0x308 via the rowed
// 0x33C807 tag find-erase; ORs the four bool results. Caller passes the same
// two AsciiString params through; ret 8 matches.

#include "ascii_string.h"


class Rva0033C807
{
public:
	bool rva0033C807(const AsciiString &tag, AsciiString &out);

private:
	void *m_p0;
	void *m_p1;
	void *m_p2;
};

class Rva0033C8E8
{
public:
	bool rva0033C8E8(const AsciiString &tag, AsciiString &out);

private:
	char m_pad[0x2E4];
	Rva0033C807 m_v0;
	Rva0033C807 m_v1;
	Rva0033C807 m_v2;
	Rva0033C807 m_v3;
};

bool Rva0033C8E8::rva0033C8E8(const AsciiString &tag, AsciiString &out)
{
	bool found = false;
	if (m_v0.rva0033C807(tag, out))
		found = true;
	if (m_v1.rva0033C807(tag, out))
		found = true;
	if (m_v2.rva0033C807(tag, out))
		found = true;
	if (m_v3.rva0033C807(tag, out))
		found = true;
	return found;
}
