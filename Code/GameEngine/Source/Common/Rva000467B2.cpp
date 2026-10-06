// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva000467B2@Rva000467B2@@QAEXPAVAsciiString@@H@Z @0x000467B2 117B
// Bitflag-to-string builder: clears out then loops 0..0x24E via Rva000454F3::rva000454F3 ModelConditionNames with ", " and g_00BBE498 wrap.
// Evidence: callees releaseBuffer concat rva000454F3 rowed; callers 0x4BA85 0x4BCF1 unclaimed; bound 0x24F and ", " literal from packet.
#include "ascii_string.h"

class Rva000454F3
{
public:
	void *rva000454F3(unsigned int idx);
private:
	unsigned int m_bits[8];
};


class Rva000467B2
{
public:
	void rva000467B2(AsciiString *out, int maxPerLine);
private:
	unsigned int m_bits[8];
};

void Rva000467B2::rva000467B2(AsciiString *out, int maxPerLine)
{
	if (!out)
		return;
	((StringBase<char> *)out)->clear();
	int count = 0;
	bool first = true;
	for (int i = 0; i < 0x24F; ++i)
	{
		const char *name = (const char *)((Rva000454F3 *)this)->rva000454F3((unsigned int)i);
		if (!name)
			continue;
		if (!first)
			((StringBase<char> *)out)->concat(", ");
		if (count >= maxPerLine)
		{
			count = 0;
			((StringBase<char> *)out)->concat("\012");
		}
		first = false;
		((StringBase<char> *)out)->concat(name);
		++count;
	}
}
